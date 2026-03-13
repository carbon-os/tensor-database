#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace tensor::storage {

// ── KNN Match ─────────────────────────────────────────────────────────────
// Represents a single result from an approximate nearest-neighbor search.

struct KNNMatch {
    uint32_t row_id;
    float    distance;
};

// ── Hierarchical Navigable Small World (HNSW) Index ───────────────────────
// Approximate nearest-neighbor index for vector search.
// Provides fast vector similarity lookups against L2 space.

class HNSW {
public:
    // Opens an existing .hnsw index or creates a new one if it doesn't exist.
    // 'dim' specifies the vector dimensionality (e.g., 768).
    HNSW(std::string_view path, uint32_t dim);
    ~HNSW();

    // Prevent copy/move to safely manage the underlying C++ index object
    HNSW(const HNSW&) = delete;
    HNSW& operator=(const HNSW&) = delete;
    HNSW(HNSW&&) = delete;
    HNSW& operator=(HNSW&&) = delete;

    // Inserts a new vector into the HNSW graph with its associated row_id.
    void insert(uint32_t row_id, const float* vector_ptr);

    // Searches the index for the 'k' nearest neighbors to the query vector.
    // Returns a list of matches ordered by distance (closest first).
    [[nodiscard]] std::vector<KNNMatch> search(const float* query_vec, size_t k) const;

    // Serializes and flushes the current in-memory graph state to the .hnsw file.
    void save() const;

private:
    std::string path_;
    uint32_t    dim_;
    
    // PIMPL idiom to hide hnswlib implementation details and prevent 
    // <hnswlib/hnswlib.h> from bleeding into the global include paths.
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace tensor::storage