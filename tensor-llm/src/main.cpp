#include "server.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

static void print_usage(const char* argv0) {
    std::cerr << "Usage:\n"
              << "  " << argv0 << " port <PORT>\n\n"
              << "Environment:\n"
              << "  TENSOR_LLM_MODEL   Path to .gguf model file  (required)\n"
              << "  TENSOR_LLM_CTX     Context window size        (default 4096)\n"
              << "  TENSOR_LLM_GPU     GPU layers to offload      (default 99)\n\n"
              << "Example:\n"
              << "  TENSOR_LLM_MODEL=~/models/qwen3-1.7b-instruct-q4_k_m.gguf \\\n"
              << "  " << argv0 << " port 4000\n";
}

int main(int argc, char* argv[]) {
    // ── CLI ──────────────────────────────────────────────────────────────────
    int port = 4000;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "port" || arg == "--port" || arg == "-p")
            && i + 1 < argc) {
            try { port = std::stoi(argv[++i]); }
            catch (...) {
                std::cerr << "Invalid port: " << argv[i] << "\n";
                return 1;
            }
        } else if (arg == "--help" || arg == "-h") {
            print_usage(argv[0]);
            return 0;
        }
    }

    if (port < 1 || port > 65535) {
        std::cerr << "Port out of range: " << port << "\n";
        return 1;
    }

    // ── Model path ───────────────────────────────────────────────────────────
    const char* model_env = std::getenv("TENSOR_LLM_MODEL");
    if (!model_env || model_env[0] == '\0') {
        std::cerr << "Error: TENSOR_LLM_MODEL environment variable is not set.\n\n";
        print_usage(argv[0]);
        return 1;
    }
    std::string model_path = model_env;

    int n_ctx = 4096;
    if (const char* ctx_env = std::getenv("TENSOR_LLM_CTX")) {
        try { n_ctx = std::stoi(ctx_env); } catch (...) {}
    }

    int n_gpu = 99;
    if (const char* gpu_env = std::getenv("TENSOR_LLM_GPU")) {
        try { n_gpu = std::stoi(gpu_env); } catch (...) {}
    }

    // ── Boot ─────────────────────────────────────────────────────────────────
    std::cout << "[tensor-llm] model=" << model_path
              << "  ctx=" << n_ctx
              << "  gpu_layers=" << n_gpu << "\n";

    try {
        // LlamaEngine constructor takes these extra params via Server indirectly,
        // so we build the engine inline here and forward it.
        // If you need custom ctx/gpu: extend Server(model, ctx, gpu) as needed.
        tensor_llm::Server server(model_path);
        server.run(port);
    } catch (const std::exception& e) {
        std::cerr << "[fatal] " << e.what() << "\n";
        return 1;
    }

    return 0;
}