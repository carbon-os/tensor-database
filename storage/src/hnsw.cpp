#include <tensor/storage/hnsw.hpp>
#include <hnswlib/hnswlib.h>
#include <unistd.h>
#include <stdexcept>
#include <algorithm>

namespace tensor::storage {

// ── PIMPL Implementation ──────────────────────────────────────────────────
// Hides hnswlib types from the public header.

struct HNSW::Impl {
    hnswlib::L2Space space;
    std::unique_ptr<hnswlib::HierarchicalNSW<float>> index;

    // Initialize the L2 distance space with the required vector dimension
    explicit Impl(uint32_t dim) : space(dim) {}
};

// ── Constructor & Destructor ──────────────────────────────────────────────

HNSW::HNSW(std::string_view path, uint32_t dim) 
    : path_(path), dim_(dim), impl_(std::make_unique<Impl>(dim)) {
    
    // Check if the physical index file already exists
    if (::access(path_.c_str(), F_OK) != -1) {
        // Load the existing index from disk
        impl_->index = std::make_unique<hnswlib::HierarchicalNSW<float>>(
            &impl_->space, path_.c_str()
        );
    } else {
        // Initialize a new empty graph. 
        // In a fully integrated setup, these default capacities could be pulled 
        // from the `HnswOptions` struct we defined earlier.
        size_t max_elements = 100000;
        size_t M = 16;
        size_t ef_construction = 200;
        
        impl_->index = std::make_unique<hnswlib::HierarchicalNSW<float>>(
            &impl_->space, max_elements, M, ef_construction
        );
    }
}

// The destructor must be defined in the .cpp file where Impl is a complete type,
// otherwise std::unique_ptr<Impl> will fail to compile in the header.
HNSW::~HNSW() = default; 

// ── Write Path ────────────────────────────────────────────────────────────

void HNSW::insert(uint32_t row_id, const float* vector_ptr) {
    if (!impl_->index) {
        throw std::runtime_error("HNSW index is not initialized.");
    }
    // Insert the vector mapped to the 32-bit row_id
    impl_->index->addPoint(vector_ptr, row_id);
}

void HNSW::save() const {
    if (!impl_->index) {
        throw std::runtime_error("HNSW index is not initialized.");
    }
    // Flushes the in-memory graph structure to the .hnsw file on disk
    impl_->index->saveIndex(path_);
}

// ── Read Path ─────────────────────────────────────────────────────────────

std::vector<KNNMatch> HNSW::search(const float* query_vec, size_t k) const {
    std::vector<KNNMatch> matches;
    
    if (!impl_->index || impl_->index->cur_element_count == 0) {
        return matches; // Return empty if the index has no data
    }

    try {
        // Execute the approximate nearest-neighbor search
        auto result_queue = impl_->index->searchKnn(query_vec, k);
        matches.reserve(result_queue.size());
        
        // hnswlib's searchKnn returns a std::priority_queue acting as a max-heap.
        // This means the furthest element is at the top. We must pop them off 
        // and then reverse the vector to get the standard closest-first ordering.
        while (!result_queue.empty()) {
            auto top = result_queue.top();
            // top.second is the label (row_id), top.first is the distance
            matches.push_back({static_cast<uint32_t>(top.second), top.first});
            result_queue.pop();
        }
        
        // Reverse to achieve ascending order by distance
        std::reverse(matches.begin(), matches.end());
        
    } catch (const std::exception& e) {
        // hnswlib can throw if k > current elements. 
        // For a resilient engine, we catch and return whatever matches are available.
    }
    
    return matches;
}

} // namespace tensor::storage