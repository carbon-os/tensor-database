#pragma once

#include <cstdint>
#include <memory>
#include <string_view>
#include <vector>

namespace tensor::inference {

// Maps to tensor.SEARCH / tensor.CLASSIFY / tensor.CODE in .tql.
// The executor holds one EmbedEngine per constant and routes embed() calls
// to the correct instance. The constant also controls the task prefix
// prepended before tokenization (nomic-style instruction-prefixed models).
enum class EmbedConstant : uint8_t {
    Search   = 0,   // nomic-embed-text-v1.5         768-d  Apache 2.0
    Classify = 1,   // all-MiniLM-L6-v2              384-d  Apache 2.0
    Code     = 2,   // jina-embeddings-v2-base-code   768-d  Apache 2.0
};

class EmbedEngine {
public:
    explicit EmbedEngine(std::string_view model_path);
    ~EmbedEngine();

    EmbedEngine(const EmbedEngine&)            = delete;
    EmbedEngine& operator=(const EmbedEngine&) = delete;

    // Returns a unit-normalised float32 vector.
    std::vector<float> run(std::string_view text,
                           EmbedConstant    constant = EmbedConstant::Search);

    // Embedding dimensionality reported by the loaded model.
    int32_t dimensions() const noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace tensor::inference