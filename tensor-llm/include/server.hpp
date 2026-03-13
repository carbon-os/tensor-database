#pragma once

#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <string>

#include <httplib.h>
#include <llama.h>

namespace tensor_llm {

// ── Inference params carried per-request ────────────────────────────────────
struct GenerateRequest {
    std::string prompt;
    int         max_tokens  = 256;
    float       temperature = 0.8f;
    float       top_p       = 0.9f;
    uint32_t    seed        = LLAMA_DEFAULT_SEED;
};

// ── Thin RAII wrapper around a loaded model + context ───────────────────────
class LlamaEngine {
public:
    explicit LlamaEngine(const std::string& model_path, int n_ctx = 4096,
                         int n_gpu_layers = 99);
    ~LlamaEngine();

    LlamaEngine(const LlamaEngine&)            = delete;
    LlamaEngine& operator=(const LlamaEngine&) = delete;

    // token_cb is called with each decoded piece; return false to abort.
    void generate(const GenerateRequest& req,
                  std::function<bool(const std::string& piece)> token_cb);

    const std::string& model_name() const { return model_name_; }

private:
    llama_model*        model_ = nullptr;
    llama_context*      ctx_   = nullptr;
    const llama_vocab*  vocab_ = nullptr;   // owned by model_, do not free
    std::string         model_name_;
    int                 n_ctx_;

    std::mutex inference_mtx_;
};

// ── HTTP server ──────────────────────────────────────────────────────────────
class Server {
public:
    explicit Server(const std::string& model_path);

    void run(int port);
    void stop();

private:
    void register_routes();

    void handle_generate(const httplib::Request& req, httplib::Response& res);
    void handle_health  (const httplib::Request& req, httplib::Response& res);

    std::unique_ptr<LlamaEngine> engine_;
    httplib::Server              http_;
    std::atomic<bool>            running_{false};
};

} // namespace tensor_llm