#include "server.hpp"

#include <cstring>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace tensor_llm {

// ── Helpers ──────────────────────────────────────────────────────────────────

static std::string json_string(const std::string& s) {
    std::string out;
    out.reserve(s.size() + 2);
    out += '"';
    for (unsigned char c : s) {
        switch (c) {
            case '"':  out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\n': out += "\\n";  break;
            case '\r': out += "\\r";  break;
            case '\t': out += "\\t";  break;
            default:
                if (c < 0x20) {
                    char buf[8];
                    snprintf(buf, sizeof(buf), "\\u%04x", c);
                    out += buf;
                } else {
                    out += static_cast<char>(c);
                }
        }
    }
    out += '"';
    return out;
}

static std::string make_sse_token(const std::string& piece, bool done) {
    std::string payload = "{\"token\":" + json_string(piece) +
                          ",\"done\":"  + (done ? "true" : "false") + "}";
    return "data: " + payload + "\n\n";
}

static bool parse_string_field(const std::string& body,
                               const std::string& key, std::string& out) {
    std::string needle = "\"" + key + "\"";
    auto pos = body.find(needle);
    if (pos == std::string::npos) return false;
    pos += needle.size();
    while (pos < body.size() && (body[pos] == ' ' || body[pos] == ':')) ++pos;
    if (pos >= body.size() || body[pos] != '"') return false;
    ++pos;
    std::string result;
    while (pos < body.size() && body[pos] != '"') {
        if (body[pos] == '\\' && pos + 1 < body.size()) {
            ++pos;
            switch (body[pos]) {
                case '"':  result += '"';  break;
                case '\\': result += '\\'; break;
                case 'n':  result += '\n'; break;
                case 'r':  result += '\r'; break;
                case 't':  result += '\t'; break;
                default:   result += body[pos]; break;
            }
        } else {
            result += body[pos];
        }
        ++pos;
    }
    out = std::move(result);
    return true;
}

static float parse_float_field(const std::string& body,
                               const std::string& key, float fallback) {
    std::string needle = "\"" + key + "\"";
    auto pos = body.find(needle);
    if (pos == std::string::npos) return fallback;
    pos += needle.size();
    while (pos < body.size() && (body[pos] == ' ' || body[pos] == ':')) ++pos;
    if (pos >= body.size()) return fallback;
    try { return std::stof(body.substr(pos)); }
    catch (...) { return fallback; }
}

static int parse_int_field(const std::string& body,
                           const std::string& key, int fallback) {
    std::string needle = "\"" + key + "\"";
    auto pos = body.find(needle);
    if (pos == std::string::npos) return fallback;
    pos += needle.size();
    while (pos < body.size() && (body[pos] == ' ' || body[pos] == ':')) ++pos;
    if (pos >= body.size()) return fallback;
    try { return std::stoi(body.substr(pos)); }
    catch (...) { return fallback; }
}

// ── LlamaEngine ──────────────────────────────────────────────────────────────

LlamaEngine::LlamaEngine(const std::string& model_path,
                         int n_ctx, int n_gpu_layers)
    : n_ctx_(n_ctx) {

    llama_model_params mparams = llama_model_default_params();
    mparams.n_gpu_layers       = n_gpu_layers;

    model_ = llama_model_load_from_file(model_path.c_str(), mparams);
    if (!model_)
        throw std::runtime_error("Failed to load model: " + model_path);

    // vocab is owned by the model — just borrow the pointer
    vocab_ = llama_model_get_vocab(model_);

    llama_context_params cparams = llama_context_default_params();
    cparams.n_ctx            = static_cast<uint32_t>(n_ctx);
    cparams.n_batch          = 512;
    cparams.flash_attn_type  = LLAMA_FLASH_ATTN_TYPE_ENABLED;  // was flash_attn

    // llama_init_from_model replaces the deprecated llama_new_context_with_model
    ctx_ = llama_init_from_model(model_, cparams);
    if (!ctx_) {
        llama_model_free(model_);
        throw std::runtime_error("Failed to create llama context");
    }

    auto slash = model_path.find_last_of("/\\");
    model_name_ = (slash == std::string::npos)
                      ? model_path
                      : model_path.substr(slash + 1);
    auto dot = model_name_.rfind('.');
    if (dot != std::string::npos) model_name_ = model_name_.substr(0, dot);

    std::cout << "[llama] Model loaded: " << model_name_
              << "  ctx=" << n_ctx
              << "  gpu_layers=" << n_gpu_layers << "\n";
}

LlamaEngine::~LlamaEngine() {
    if (ctx_)   llama_free(ctx_);
    if (model_) llama_model_free(model_);
}

void LlamaEngine::generate(const GenerateRequest& req,
                            std::function<bool(const std::string&)> token_cb) {
    std::lock_guard<std::mutex> lock(inference_mtx_);

    // ── Tokenise prompt ──────────────────────────────────────────────────────
    const int n_prompt_max = n_ctx_ - req.max_tokens - 4;
    std::vector<llama_token> prompt_tokens(n_prompt_max);

    // llama_tokenize now takes llama_vocab*, not llama_model*
    int n_prompt = llama_tokenize(
        vocab_,
        req.prompt.c_str(), static_cast<int32_t>(req.prompt.size()),
        prompt_tokens.data(), n_prompt_max,
        /*add_special=*/true,
        /*parse_special=*/true);

    if (n_prompt < 0) {
        prompt_tokens.resize(-n_prompt);
        n_prompt = llama_tokenize(
            vocab_,
            req.prompt.c_str(), static_cast<int32_t>(req.prompt.size()),
            prompt_tokens.data(), -n_prompt,
            true, true);
    }
    prompt_tokens.resize(n_prompt);

    // ── Build sampler chain ──────────────────────────────────────────────────
    llama_sampler* sampler =
        llama_sampler_chain_init(llama_sampler_chain_default_params());

    llama_sampler_chain_add(sampler, llama_sampler_init_top_p(req.top_p, 1));
    llama_sampler_chain_add(sampler, llama_sampler_init_temp(req.temperature));
    llama_sampler_chain_add(sampler, llama_sampler_init_dist(req.seed));

    // ── KV / memory reset ────────────────────────────────────────────────────
    // llama_kv_cache_clear is gone; use the new memory API
    llama_memory_clear(llama_get_memory(ctx_), /*data=*/false);

    // ── Prefill ──────────────────────────────────────────────────────────────
    llama_batch batch = llama_batch_get_one(prompt_tokens.data(), n_prompt);
    if (llama_decode(ctx_, batch) != 0) {
        llama_sampler_free(sampler);
        throw std::runtime_error("llama_decode failed during prompt prefill");
    }

    // ── Generate tokens ──────────────────────────────────────────────────────
    char piece_buf[256];

    for (int i = 0; i < req.max_tokens; ++i) {
        llama_token tok = llama_sampler_sample(sampler, ctx_, -1);

        // llama_vocab_is_eog replaces the deprecated llama_token_is_eog
        if (llama_vocab_is_eog(vocab_, tok))
            break;

        // llama_token_to_piece now takes llama_vocab*, not llama_model*
        int n_piece = llama_token_to_piece(
            vocab_, tok, piece_buf, sizeof(piece_buf), 0, /*special=*/false);

        if (n_piece <= 0)
            break;

        std::string piece(piece_buf, static_cast<size_t>(n_piece));

        if (!token_cb(piece))
            break;

        batch = llama_batch_get_one(&tok, 1);
        if (llama_decode(ctx_, batch) != 0)
            break;
    }

    llama_sampler_free(sampler);
}

// ── Server ───────────────────────────────────────────────────────────────────

Server::Server(const std::string& model_path)
    : engine_(std::make_unique<LlamaEngine>(model_path)) {
    register_routes();
}

void Server::register_routes() {
    http_.Options(".*", [](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin",  "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.status = 204;
    });

    http_.Post("/generate", [this](const httplib::Request& req,
                                    httplib::Response& res) {
        handle_generate(req, res);
    });

    http_.Get("/health", [this](const httplib::Request& req,
                                 httplib::Response& res) {
        handle_health(req, res);
    });
}

void Server::handle_generate(const httplib::Request& req,
                              httplib::Response& res) {
    GenerateRequest gen_req;
    if (!parse_string_field(req.body, "prompt", gen_req.prompt) ||
        gen_req.prompt.empty()) {
        res.status = 400;
        res.set_content("{\"error\":\"missing or empty 'prompt' field\"}",
                        "application/json");
        return;
    }

    gen_req.max_tokens  = parse_int_field  (req.body, "max_tokens",  256);
    gen_req.temperature = parse_float_field(req.body, "temperature", 0.8f);
    gen_req.top_p       = parse_float_field(req.body, "top_p",       0.9f);

    if (gen_req.max_tokens < 1)    gen_req.max_tokens = 1;
    if (gen_req.max_tokens > 4096) gen_req.max_tokens = 4096;
    gen_req.temperature = std::max(0.0f, std::min(gen_req.temperature, 2.0f));
    gen_req.top_p       = std::max(0.0f, std::min(gen_req.top_p,       1.0f));

    std::cout << "[req] prompt_len=" << gen_req.prompt.size()
              << " max_tokens="      << gen_req.max_tokens
              << " temp="            << gen_req.temperature
              << " top_p="           << gen_req.top_p << "\n";

    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Cache-Control",               "no-cache");
    res.set_header("X-Accel-Buffering",           "no");

    res.set_chunked_content_provider(
        "text/event-stream",
        [this, gen_req](size_t /*offset*/, httplib::DataSink& sink) -> bool {
            try {
                engine_->generate(gen_req, [&sink](const std::string& piece) -> bool {
                    std::string msg = make_sse_token(piece, false);
                    return sink.write(msg.data(), msg.size());
                });
            } catch (const std::exception& e) {
                std::string err = std::string("data: {\"error\":") +
                                  json_string(e.what()) + "}\n\n";
                sink.write(err.data(), err.size());
            }

            std::string done_msg = make_sse_token("", true);
            sink.write(done_msg.data(), done_msg.size());
            sink.done();
            return true;
        });
}

void Server::handle_health(const httplib::Request& /*req*/,
                            httplib::Response& res) {
    res.set_header("Access-Control-Allow-Origin", "*");
    std::string body = "{\"status\":\"ok\",\"model\":"
                     + json_string(engine_->model_name()) + "}";
    res.set_content(body, "application/json");
}

void Server::run(int port) {
    running_ = true;
    std::cout << "[server] Listening on http://0.0.0.0:" << port << "\n";
    std::cout << "[server] POST /generate  — SSE token stream\n";
    std::cout << "[server] GET  /health    — status check\n";
    http_.listen("0.0.0.0", port);
}

void Server::stop() {
    running_ = false;
    http_.stop();
}

} // namespace tensor_llm