#include <tensor/inference/embed.hpp>
#include "llama_guard.hpp"

#include <llama.h>

#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

namespace tensor::inference {

// ── Task prefixes ─────────────────────────────────────────────────────────
// nomic-embed-text-v1.5 requires an instruction prefix per task type.
// MiniLM and jina do not use prefixes; the empty string is a no-op.

static const char* prefix_for(EmbedConstant c) noexcept {
    switch (c) {
        case EmbedConstant::Search:   return "search_query: ";
        case EmbedConstant::Classify: return "classification: ";
        case EmbedConstant::Code:     return "search_query: ";
    }
    return "";
}

// ── Impl ──────────────────────────────────────────────────────────────────

struct EmbedEngine::Impl {
    llama_model*        model = nullptr;
    llama_context*      ctx   = nullptr;
    const llama_vocab*  vocab = nullptr;
    int32_t             dims  = 0;

    explicit Impl(std::string_view path) {
        detail::ensure_backend_init();

        llama_model_params mparams = llama_model_default_params();
        mparams.n_gpu_layers = 99;

        model = llama_model_load_from_file(std::string(path).c_str(), mparams);
        if (!model)
            throw std::runtime_error(
                "EmbedEngine: failed to load model: " + std::string(path));

        vocab = llama_model_get_vocab(model);

        llama_context_params cparams = llama_context_default_params();
        cparams.n_ctx        = 512;
        cparams.n_batch      = 512;
        cparams.embeddings   = true;
        cparams.pooling_type = LLAMA_POOLING_TYPE_MEAN;

        ctx = llama_init_from_model(model, cparams);
        if (!ctx)
            throw std::runtime_error("EmbedEngine: failed to create context");

        dims = llama_model_n_embd(model);
    }

    ~Impl() {
        if (ctx)   llama_free(ctx);
        if (model) llama_model_free(model);
    }

    std::vector<float> embed(std::string_view text, EmbedConstant constant) {
        std::string input = prefix_for(constant);
        input.append(text.data(), text.size());

        const int32_t n_ctx_max = static_cast<int32_t>(llama_n_ctx(ctx));
        std::vector<llama_token> toks(static_cast<size_t>(n_ctx_max));

        int32_t n = llama_tokenize(
            vocab,
            input.c_str(), static_cast<int32_t>(input.size()),
            toks.data(), n_ctx_max,
            /*add_special=*/true, /*parse_special=*/false);
        if (n < 0) n = std::min(-n, n_ctx_max);
        toks.resize(static_cast<size_t>(n));

        llama_memory_clear(llama_get_memory(ctx), false);

        llama_batch batch = llama_batch_get_one(toks.data(), n);
        if (llama_decode(ctx, batch) != 0)
            throw std::runtime_error("EmbedEngine: llama_decode failed");

        const float* raw = llama_get_embeddings_seq(ctx, 0);
        if (!raw)
            throw std::runtime_error("EmbedEngine: no embeddings returned");

        std::vector<float> out(raw, raw + dims);

        // L2-normalise to unit vector
        float sq_sum = 0.0f;
        for (float v : out) sq_sum += v * v;
        const float norm = std::sqrt(sq_sum);
        if (norm > 0.0f)
            for (float& v : out) v /= norm;

        return out;
    }
};

// ── Public API ────────────────────────────────────────────────────────────

EmbedEngine::EmbedEngine(std::string_view model_path)
    : impl_(std::make_unique<Impl>(model_path)) {}

EmbedEngine::~EmbedEngine() = default;

std::vector<float> EmbedEngine::run(std::string_view text, EmbedConstant constant) {
    return impl_->embed(text, constant);
}

int32_t EmbedEngine::dimensions() const noexcept { return impl_->dims; }

} // namespace tensor::inference