#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

namespace tensor::storage {

// ── WAL Options ───────────────────────────────────────────────────────────
struct WalOptions {
    // If true, forces fsync/fdatasync on every append (maximum durability).
    // If false, relies on the OS buffer cache and background flushes, or 
    // explicit flush() calls from the engine at transaction commit boundaries.
    bool   sync_on_append = false;
    
    // Maximum size in bytes before the WAL file is rotated or truncated.
    size_t max_file_size = 64 * 1024 * 1024; // 64 MB
};

// ── SST Options ───────────────────────────────────────────────────────────
struct SstOptions {
    // Target uncompressed size of a page before applying Snappy compression.
    size_t page_size = 4096; // 4 KB
    
    // Allows disabling Snappy compression for purely in-memory/ephemeral workloads.
    bool   use_compression = true;
};

// ── HNSW Options ──────────────────────────────────────────────────────────
// These map directly to the hnswlib::HierarchicalNSW constructor requirements.
struct HnswOptions {
    // The maximum number of elements the index can hold. 
    // hnswlib requires this upfront, though it can be resized dynamically with a penalty.
    size_t   max_elements = 100000;
    
    // The number of bi-directional links created for every new element during insertion.
    size_t   M = 16;
    
    // The size of the dynamic list for the nearest neighbors used during construction.
    // Higher values mean higher index quality but slower build times.
    size_t   ef_construction = 200;
};

// ── RBM Options ───────────────────────────────────────────────────────────
struct RbmOptions {
    // If true, calls roaring_bitmap_run_optimize() before serializing the index to disk.
    // This compresses contiguous sequences of row_ids to save space and speed up AND operations.
    bool   run_optimize = true; 
};

// ── Storage Engine Master Configuration ───────────────────────────────────
// Passed from tensor::db::Engine to the physical storage layer at initialization.
struct StorageOptions {
    // The base directory path where all physical files (.wal, .sst, .rbm, .vec, .hnsw) are stored.
    std::string base_path = "store/";

    WalOptions  wal;
    SstOptions  sst;
    HnswOptions hnsw;
    RbmOptions  rbm;
};

} // namespace tensor::storage