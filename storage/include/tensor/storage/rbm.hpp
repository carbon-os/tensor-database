#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <roaring/roaring.hh>

namespace tensor::storage {

// ── Roaring Bitmap Index (RBM) ──────────────────────────────────────────
// Read-only inverted index for full-text search.
// Maps a text token (keyword) to a compressed roaring bitmap of row IDs.

class RBM {
public:
    // Opens an existing .rbm index file for reading (e.g., "store/products/.rbm")
    explicit RBM(std::string_view path);
    ~RBM() = default;

    // Prevent copy/move
    RBM(const RBM&) = delete;
    RBM& operator=(const RBM&) = delete;
    RBM(RBM&&) = delete;
    RBM& operator=(RBM&&) = delete;

    // Retrieves the bitmap of row IDs containing the specified token.
    // Returns an empty bitmap if the token does not exist in the index.
    roaring::Roaring get(std::string_view token) const;

private:
    std::string path_;
    
    // Internal dictionary mapping tokens to their respective bitmaps.
    // In the physical implementation (.cpp), this could be heavily optimized 
    // to map directly from a memory-mapped (mmap) file without full deserialization.
    std::unordered_map<std::string, roaring::Roaring> index_;
};

// ── RBM Builder ─────────────────────────────────────────────────────────
// Constructs a new .rbm file.
// Typically used alongside the SSTBuilder when flushing an in-memory 
// table to disk, extracting tokens from text fields and building the index.

class RBMBuilder {
public:
    explicit RBMBuilder(std::string_view path);
    ~RBMBuilder() = default;

    RBMBuilder(const RBMBuilder&) = delete;
    RBMBuilder& operator=(const RBMBuilder&) = delete;

    // Associates a specific row_id with a given text token.
    // The CRoaring C++ wrapper automatically handles compression and container
    // types (array, bitmap, run) as the integers are added.
    void add(std::string_view token, uint32_t row_id);

    // Serializes the token dictionary and all CRoaring bitmaps to the .rbm file.
    void finish();

private:
    std::string path_;
    
    // Accumulates bitmaps in memory before flushing.
    std::unordered_map<std::string, roaring::Roaring> index_;
};

} // namespace tensor::storage