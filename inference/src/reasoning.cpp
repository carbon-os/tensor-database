#include <tensor/inference/reasoning.hpp>
#include "llama_guard.hpp"

#include <llama.h>

#include <algorithm>
#include <condition_variable>
#include <future>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// ── Device memory headers ─────────────────────────────────────────────────

#if defined(GGML_USE_CUDA)
#  include <cuda_runtime.h>
#endif

#if defined(__APPLE__)
#  include <mach/mach.h>
#  include <sys/sysctl.h>
#elif defined(__linux__)
#  include <sys/sysinfo.h>
#endif

namespace tensor::inference {

// ── Tuning constants ──────────────────────────────────────────────────────

// Qwen3-0.6B supports 32k; reserve ~4k headroom for the prompt wrapper.
static constexpr int32_t k_worker_ctx     = 32768;
static constexpr int32_t k_aggregator_ctx = 8192;
static constexpr int32_t k_segment_tokens = 28000;

static constexpr int32_t k_worker_max_new     = 512;
static constexpr int32_t k_aggregator_max_new = 512;

static constexpr size_t k_min_workers = 1;
static constexpr size_t k_max_workers = 128;

// ── Device memory query ───────────────────────────────────────────────────
// Called after both models are loaded so their VRAM footprint is already
// reflected in the "used" side of the query.
//
// Priority:
//   1. CUDA  — cudaMemGetInfo() on device 0
//   2. Metal — sysctl hw.memsize minus conservative OS headroom
//   3. CPU   — platform free RAM (Linux sysinfo)
//
// Fallback is 4 GB so the engine always starts on unrecognised platforms.

static uint64_t query_available_bytes() noexcept {
    constexpr uint64_t k_fallback = uint64_t(4) * 1024 * 1024 * 1024;

#if defined(GGML_USE_CUDA)
    size_t free_bytes = 0, total_bytes = 0;
    if (cudaMemGetInfo(&free_bytes, &total_bytes) == cudaSuccess && free_bytes > 0)
        return static_cast<uint64_t>(free_bytes);
#endif

    // Metal / Apple Silicon — unified memory.
    // hw.memsize is total physical RAM; subtract 2 GB for OS + models.
#if defined(__APPLE__)
    uint64_t mem_total = 0;
    size_t   sz        = sizeof(mem_total);
    if (sysctlbyname("hw.memsize", &mem_total, &sz, nullptr, 0) == 0 && mem_total > 0) {
        constexpr uint64_t headroom = uint64_t(2) * 1024 * 1024 * 1024;
        return mem_total > headroom ? mem_total - headroom : k_fallback;
    }
#endif

#if defined(__linux__)
    struct sysinfo si{};
    if (sysinfo(&si) == 0) {
        const uint64_t avail =
            static_cast<uint64_t>(si.freeram + si.bufferram) *
            static_cast<uint64_t>(si.mem_unit);
        if (avail > 0) return avail;
    }
#endif

    return k_fallback;
}

// ── KV cache bytes per context ────────────────────────────────────────────
// Reads actual model metadata so the estimate is correct for any model.
//
//   KV bytes = 2 (K+V)
//            × n_kv_heads   (GQA heads — llama_model_n_head_kv)
//            × head_dim     (n_embd / n_head — query heads give the right dim)
//            × n_layers     (llama_model_n_layer)
//            × n_ctx        (tokens per context window)
//            × 2            (float16 bytes per element)

static uint64_t kv_bytes_per_ctx(llama_model* model, int32_t n_ctx) noexcept {
    const int32_t  n_head    = llama_model_n_head(model);
    const uint64_t n_kv_heads = static_cast<uint64_t>(llama_model_n_head_kv(model));
    const uint64_t n_embd    = static_cast<uint64_t>(llama_model_n_embd(model));
    const uint64_t n_layers  = static_cast<uint64_t>(llama_model_n_layer(model));
    const uint64_t ctx       = static_cast<uint64_t>(n_ctx);

    // head_dim = embedding_dim / query_head_count
    const uint64_t head_dim = (n_head > 0)
        ? n_embd / static_cast<uint64_t>(n_head)
        : 64; // safe fallback

    return 2 * n_kv_heads * head_dim * n_layers * ctx * 2 /* f16 */;
}

// ── Worker count calculation ──────────────────────────────────────────────
// Called once after both models are resident so the device query reflects
// real post-load availability.
//
// Subtracts:
//   - 512 MB runtime overhead (driver, CUDA context, ggml scratch buffers)
//   - aggregator KV cache (about to be allocated immediately after)
// Divides what remains by the KV cost of one worker context.

static size_t compute_max_workers(llama_model* worker_model,
                                  llama_model* agg_model,
                                  int32_t      worker_n_ctx,
                                  int32_t      agg_n_ctx) noexcept {
    constexpr uint64_t k_runtime_overhead = uint64_t(512) * 1024 * 1024;

    const uint64_t available = query_available_bytes();
    const uint64_t worker_kv = kv_bytes_per_ctx(worker_model, worker_n_ctx);
    const uint64_t agg_kv    = kv_bytes_per_ctx(agg_model,    agg_n_ctx);

    if (worker_kv == 0) return k_min_workers;

    const uint64_t reserved = k_runtime_overhead + agg_kv;
    if (available <= reserved) return k_min_workers;

    const uint64_t budget = available - reserved;
    const size_t   n      = static_cast<size_t>(budget / worker_kv);

    return std::max(k_min_workers, std::min(n, k_max_workers));
}

// ── Context pool ──────────────────────────────────────────────────────────
// Worker model weights are loaded once and shared across all contexts via
// llama.cpp's per-model context design. Each context owns its own KV cache.
// acquire() blocks at max_ rather than over-allocating.

class ContextPool {
public:
    ContextPool(llama_model* model, int32_t n_ctx, size_t max)
        : model_(model), n_ctx_(n_ctx), max_(max) {}

    ~ContextPool() {
        std::lock_guard lock(mu_);
        for (auto* c : free_) llama_free(c);
    }

    llama_context* acquire() {
        std::unique_lock lock(mu_);
        cv_.wait(lock, [&] { return !free_.empty() || active_ < max_; });

        if (!free_.empty()) {
            auto* ctx = free_.back();
            free_.pop_back();
            ++active_;
            return ctx;
        }

        // Allocate outside the lock so other threads aren't blocked during
        // the (potentially slow) context creation.
        ++active_;
        lock.unlock();

        llama_context_params cp = llama_context_default_params();
        cp.n_ctx   = n_ctx_;
        cp.n_batch = 512;

        llama_context* ctx = llama_init_from_model(model_, cp);
        if (!ctx)
            throw std::runtime_error("ContextPool: failed to create worker context");
        return ctx;
    }

    void release(llama_context* ctx) {
        llama_memory_clear(llama_get_memory(ctx), false);
        {
            std::lock_guard lock(mu_);
            free_.push_back(ctx);
            --active_;
        }
        cv_.notify_one();
    }

private:
    llama_model*                model_;
    int32_t                     n_ctx_;
    size_t                      max_;
    size_t                      active_ = 0;
    std::vector<llama_context*> free_;
    std::mutex                  mu_;
    std::condition_variable     cv_;
};

// ── llama.cpp helpers ─────────────────────────────────────────────────────
// All vocab-dependent operations now take const llama_vocab* directly.
// Callers obtain this once via llama_model_get_vocab() and reuse it.

static std::vector<llama_token> tokenize_str(const llama_vocab*  vocab,
                                              const std::string&  text,
                                              bool                add_special) {
    const int32_t max = static_cast<int32_t>(text.size()) + 128;
    std::vector<llama_token> out(static_cast<size_t>(max));
    int32_t n = llama_tokenize(vocab, text.c_str(), static_cast<int32_t>(text.size()),
                               out.data(), max, add_special, false);
    if (n < 0) {
        out.resize(static_cast<size_t>(-n));
        n = llama_tokenize(vocab, text.c_str(), static_cast<int32_t>(text.size()),
                           out.data(), -n, add_special, false);
    }
    out.resize(static_cast<size_t>(n));
    return out;
}

static std::string token_to_piece(const llama_vocab* vocab, llama_token tok) {
    char buf[256] = {};
    int n = llama_token_to_piece(vocab, tok, buf, sizeof(buf) - 1, 0, false);
    return n > 0 ? std::string(buf, static_cast<size_t>(n)) : std::string{};
}

static std::string detokenize(const llama_vocab*              vocab,
                               const std::vector<llama_token>& toks) {
    std::string out;
    out.reserve(toks.size() * 4);
    for (llama_token t : toks) out += token_to_piece(vocab, t);
    return out;
}

// Generate with an optional GBNF grammar constraint on the sampler chain.
// grammar_str == nullptr or empty string → no grammar, plain greedy.

static std::string generate(const llama_vocab* vocab,
                             llama_context*     ctx,
                             int32_t            max_new,
                             const char*        grammar_str = nullptr) {
    std::string out;
    out.reserve(static_cast<size_t>(max_new) * 4);

    llama_sampler* chain = llama_sampler_chain_init(
        llama_sampler_chain_default_params());

    if (grammar_str && grammar_str[0] != '\0') {
        // Grammar sampler enforces the JSON schema at token-selection time.
        // Output is structurally guaranteed — no post-generation parsing needed.
        llama_sampler_chain_add(chain,
            llama_sampler_init_grammar(vocab, grammar_str, "root"));
    }

    llama_sampler_chain_add(chain, llama_sampler_init_temp(0.1f));
    llama_sampler_chain_add(chain, llama_sampler_init_greedy());

    for (int32_t i = 0; i < max_new; ++i) {
        llama_token tok = llama_sampler_sample(chain, ctx, -1);

        if (llama_vocab_is_eog(vocab, tok)) break;

        out += token_to_piece(vocab, tok);

        llama_batch batch = llama_batch_get_one(&tok, 1);
        if (llama_decode(ctx, batch) != 0) break;
    }

    llama_sampler_free(chain);
    return out;
}

// ── JSON schema → GBNF ────────────────────────────────────────────────────
// Builds a GBNF grammar from OutputSchema that the llama.cpp sampler
// compiles at runtime. Flat object only — exactly what prompt() produces.
//
// SchemaField::type → JSON value rule:
//   text / uuid / timestamp         → json-string
//   int32 / int64                   → json-integer
//   float32 / float64 / decimal     → json-number
//   bool                            → json-bool
//   (unknown)                       → json-string  (safe fallback)
//
// Nullable fields accept their typed value or "null".

static std::string schema_to_gbnf(const OutputSchema& schema) {
    std::ostringstream ss;

    ss << R"(
root   ::= object
object ::= "{" ws members ws "}"
members ::= member ("," ws member)*
ws ::= [ \t\n\r]*

json-string       ::= "\"" json-string-chars "\""
json-string-chars ::= ([^"\\] | "\\" json-escape)*
json-escape       ::= ["\\\/bfnrt] | "u" [0-9a-fA-F]{4}

json-integer ::= "-"? ([0] | [1-9][0-9]*)
json-number  ::= "-"? ([0] | [1-9][0-9]*) ("." [0-9]+)? ([eE] [+-]? [0-9]+)?
json-bool    ::= "true" | "false"
json-null    ::= "null"

)";

    // Per-field value rules
    for (const auto& f : schema.fields) {
        ss << "field-" << f.name << " ::= ";

        std::string_view base;
        if      (f.type == "text" || f.type == "uuid" || f.type == "timestamp")
            base = "json-string";
        else if (f.type == "int32" || f.type == "int64")
            base = "json-integer";
        else if (f.type == "float32" || f.type == "float64" || f.type == "decimal")
            base = "json-number";
        else if (f.type == "bool")
            base = "json-bool";
        else
            base = "json-string";

        if (f.nullable)
            ss << base << " | json-null";
        else
            ss << base;
        ss << "\n";
    }

    // Member rule: one alternative per field in declaration order.
    ss << "\nmember ::= ";
    for (size_t i = 0; i < schema.fields.size(); ++i) {
        const auto& f = schema.fields[i];
        if (i > 0) ss << "\n         | ";
        ss << "\"\\\"" << f.name << "\\\"\" ws \":\" ws field-" << f.name;
    }
    ss << "\n";

    return ss.str();
}

// ── Result parser ─────────────────────────────────────────────────────────
// The grammar guarantees valid JSON so a full DOM parser is unnecessary.
// This walks the flat JSON object the aggregator always emits and extracts
// string representations of each field value.
//
// Not static — friended by ReasoningResult in reasoning.hpp so it can
// populate fields_ directly.

ReasoningResult parse_result(const std::string&  json,
                              const OutputSchema& schema) {
    ReasoningResult result;

    for (const auto& f : schema.fields) {
        const std::string key = "\"" + f.name + "\"";
        const auto kpos = json.find(key);
        if (kpos == std::string::npos) continue;

        auto vpos = json.find(':', kpos + key.size());
        if (vpos == std::string::npos) continue;
        ++vpos;
        while (vpos < json.size() && std::isspace((unsigned char)json[vpos])) ++vpos;
        if (vpos >= json.size()) continue;

        if (json.compare(vpos, 4, "null") == 0) continue;

        std::string val;
        if (json[vpos] == '"') {
            ++vpos;
            while (vpos < json.size() && json[vpos] != '"') {
                if (json[vpos] == '\\' && vpos + 1 < json.size()) {
                    ++vpos;
                    val += json[vpos];
                } else {
                    val += json[vpos];
                }
                ++vpos;
            }
        } else {
            auto end = vpos;
            while (end < json.size() &&
                   json[end] != ',' && json[end] != '}' &&
                   !std::isspace((unsigned char)json[end]))
                ++end;
            val = json.substr(vpos, end - vpos);
        }

        if (!val.empty())
            result.fields_[f.name] = std::move(val);
    }

    return result;
}

// ── Prompt builders ───────────────────────────────────────────────────────

// Worker — Qwen3-0.6B base completion.
// No JSON, no format requirements. Plain prose extraction only.
// The aggregator handles all structure via grammar constraint.
static std::string build_worker_prompt(const std::string& segment_text,
                                       const std::string& query) {
    std::ostringstream ss;
    ss << "Read the text below and write down any facts relevant to: \""
       << query << "\"\n"
       << "Write whatever you find in plain sentences. "
       << "If there is nothing relevant just say so.\n\n"
       << "Text:\n"
       << segment_text << "\n\n"
       << "Relevant facts:\n";
    return ss.str();
}

// Aggregator — Qwen3-1.7B-Instruct with non-thinking mode (/no_think).
// Schema fields are listed so the model knows what to populate.
// The grammar sampler enforces the output structure — no JSON formatting
// instructions needed in the prompt itself.
static std::string build_aggregator_prompt(
    const std::vector<std::string>& responses,
    const std::string&              query,
    const OutputSchema&             schema)
{
    std::ostringstream fields_ss;
    for (const auto& f : schema.fields) {
        fields_ss << "  " << f.name << " (" << f.type;
        if (f.nullable) fields_ss << ", optional";
        fields_ss << ")\n";
    }

    std::ostringstream sums_ss;
    for (size_t i = 0; i < responses.size(); ++i)
        sums_ss << "[" << (i + 1) << "] " << responses[i] << "\n";

    std::ostringstream ss;
    ss << "<|im_start|>system\n"
       << "You are a data extraction assistant. /no_think\n"
       << "<|im_end|>\n"
       << "<|im_start|>user\n"
       << "Query: \"" << query << "\"\n\n"
       << "Fields to extract (" << schema.type_name << "):\n"
       << fields_ss.str() << "\n"
       << "Research notes from document segments:\n"
       << sums_ss.str()
       << "<|im_end|>\n"
       << "<|im_start|>assistant\n";
    return ss.str();
}

// ── Impl ──────────────────────────────────────────────────────────────────

struct ReasoningEngine::Impl {
    llama_model*        worker_model     = nullptr;
    llama_model*        aggregator_model = nullptr;
    llama_context*      aggregator_ctx   = nullptr;
    const llama_vocab*  worker_vocab     = nullptr;
    const llama_vocab*  aggregator_vocab = nullptr;

    std::unique_ptr<ContextPool> worker_pool;
    std::mutex aggregator_mu;

    // Exposed via max_workers() for `tensor db ai status`.
    size_t max_workers_count = 0;

    Impl(std::string_view worker_path, std::string_view agg_path) {
        detail::ensure_backend_init();

        llama_model_params mp = llama_model_default_params();
        mp.n_gpu_layers = 99;

        // Load worker model — weights resident in VRAM from this point on.
        worker_model = llama_model_load_from_file(std::string(worker_path).c_str(), mp);
        if (!worker_model)
            throw std::runtime_error(
                "ReasoningEngine: failed to load worker model: " + std::string(worker_path));
        worker_vocab = llama_model_get_vocab(worker_model);

        // Load aggregator model — also resident in VRAM.
        aggregator_model = llama_model_load_from_file(std::string(agg_path).c_str(), mp);
        if (!aggregator_model)
            throw std::runtime_error(
                "ReasoningEngine: failed to load aggregator model: " + std::string(agg_path));
        aggregator_vocab = llama_model_get_vocab(aggregator_model);

        // Both models are resident. Query the device now so the weight
        // footprints are already reflected in the "used" side of the query.
        max_workers_count = compute_max_workers(
            worker_model, aggregator_model,
            k_worker_ctx, k_aggregator_ctx);

        worker_pool = std::make_unique<ContextPool>(
            worker_model, k_worker_ctx, max_workers_count);

        // Aggregator context allocated after the pool is sized so its KV
        // cost was already subtracted from the budget in compute_max_workers.
        llama_context_params cp = llama_context_default_params();
        cp.n_ctx   = k_aggregator_ctx;
        cp.n_batch = 512;

        aggregator_ctx = llama_init_from_model(aggregator_model, cp);
        if (!aggregator_ctx)
            throw std::runtime_error("ReasoningEngine: failed to create aggregator context");
    }

    ~Impl() {
        // Pool must be destroyed before the worker model it references.
        worker_pool.reset();
        if (aggregator_ctx)   llama_free(aggregator_ctx);
        if (aggregator_model) llama_model_free(aggregator_model);
        if (worker_model)     llama_model_free(worker_model);
    }

    // ── Write-time tokenization ────────────────────────────────────────────

    std::vector<int32_t> tokenize(std::string_view text) const {
        auto toks = tokenize_str(worker_vocab, std::string(text), false);
        return { toks.begin(), toks.end() };
    }

    // ── Single-segment worker run ──────────────────────────────────────────

    std::string run_segment(const std::vector<llama_token>& seg,
                            const std::string&              query) {
        const std::string seg_text = detokenize(worker_vocab, seg);
        const std::string prompt   = build_worker_prompt(seg_text, query);
        auto prompt_toks = tokenize_str(worker_vocab, prompt, true);

        llama_context* ctx = worker_pool->acquire();

        llama_batch batch = llama_batch_get_one(
            prompt_toks.data(), static_cast<int32_t>(prompt_toks.size()));

        if (llama_decode(ctx, batch) != 0) {
            worker_pool->release(ctx);
            return {};
        }

        // No grammar — worker writes plain sloppy prose.
        std::string response = generate(worker_vocab, ctx, k_worker_max_new);
        worker_pool->release(ctx);
        return response;
    }

    // ── Core pipeline ──────────────────────────────────────────────────────

    ReasoningResult pipeline(const std::string&       query,
                             std::vector<llama_token> tokens,
                             const OutputSchema&       schema) {
        if (tokens.empty()) return {};

        // 1. Segment into k_segment_tokens-sized chunks
        std::vector<std::vector<llama_token>> segs;
        for (size_t off = 0; off < tokens.size(); off += k_segment_tokens) {
            const size_t end = std::min(
                off + static_cast<size_t>(k_segment_tokens), tokens.size());
            segs.emplace_back(tokens.begin() + off, tokens.begin() + end);
        }

        // 2. Fan out — each segment runs fully async on the worker pool
        std::vector<std::future<std::string>> futures;
        futures.reserve(segs.size());
        for (auto& seg : segs) {
            futures.push_back(
                std::async(std::launch::async,
                    [this, &query, s = std::move(seg)]() mutable {
                        return run_segment(s, query);
                    }));
        }

        // 3. Collect worker responses
        std::vector<std::string> responses;
        responses.reserve(futures.size());
        for (auto& f : futures) responses.push_back(f.get());

        // 4. Filter clearly uninformative responses. Keep everything if all
        //    segments returned nothing — let the aggregator produce a null/
        //    empty result rather than crashing on empty input.
        std::vector<std::string> useful;
        useful.reserve(responses.size());
        for (const auto& r : responses) {
            std::string low = r;
            std::transform(low.begin(), low.end(), low.begin(), ::tolower);
            const bool blank = low.size() < 24 && (
                low.find("nothing")     != std::string::npos ||
                low.find("no relevant") != std::string::npos ||
                low.find("none")        != std::string::npos);
            if (!blank) useful.push_back(r);
        }
        if (useful.empty()) useful = std::move(responses);

        // 5. Aggregate — grammar-constrained JSON, serialised across
        //    concurrent run() calls since the aggregator context is not
        //    thread-safe.
        std::lock_guard lock(aggregator_mu);

        const std::string gbnf       = schema_to_gbnf(schema);
        const std::string agg_prompt = build_aggregator_prompt(useful, query, schema);
        auto agg_toks = tokenize_str(aggregator_vocab, agg_prompt, true);

        llama_memory_clear(llama_get_memory(aggregator_ctx), false);

        llama_batch batch = llama_batch_get_one(
            agg_toks.data(), static_cast<int32_t>(agg_toks.size()));
        if (llama_decode(aggregator_ctx, batch) != 0) return {};

        // Grammar sampler guarantees valid JSON — parse_result() just walks
        // the flat object, no DOM parser required.
        const std::string json = generate(
            aggregator_vocab, aggregator_ctx,
            k_aggregator_max_new, gbnf.c_str());

        return parse_result(json, schema);
    }
};

// ── ReasoningResult ───────────────────────────────────────────────────────

bool ReasoningResult::has(std::string_view name) const noexcept {
    return fields_.count(std::string(name)) > 0;
}

std::optional<std::string> ReasoningResult::field(std::string_view name) const noexcept {
    const auto it = fields_.find(std::string(name));
    if (it == fields_.end()) return std::nullopt;
    return it->second;
}

// ── ReasoningEngine ───────────────────────────────────────────────────────

ReasoningEngine::ReasoningEngine(std::string_view worker_model_path,
                                 std::string_view aggregator_model_path)
    : impl_(std::make_unique<Impl>(worker_model_path, aggregator_model_path)) {}

ReasoningEngine::~ReasoningEngine() = default;

size_t ReasoningEngine::max_workers() const noexcept {
    return impl_->max_workers_count;
}

std::vector<int32_t> ReasoningEngine::tokenize(std::string_view text) const {
    return impl_->tokenize(text);
}

ReasoningResult ReasoningEngine::run(std::string_view    query,
                                     std::string_view    raw_text,
                                     const OutputSchema& schema) {
    auto toks = tokenize_str(impl_->worker_vocab, std::string(raw_text), false);
    return impl_->pipeline(std::string(query), std::move(toks), schema);
}

ReasoningResult ReasoningEngine::run_tokenized(std::string_view            query,
                                               const std::vector<int32_t>& tokens,
                                               const OutputSchema&          schema) {
    std::vector<llama_token> toks(tokens.begin(), tokens.end());
    return impl_->pipeline(std::string(query), std::move(toks), schema);
}

} // namespace tensor::inference