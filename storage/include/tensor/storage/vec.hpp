#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>

namespace tensor::storage {

// ── Vector Storage (VEC) ──────────────────────────────────────────────────
// Read-only, zero-copy memory-mapped storage for raw float32 vectors.
// Used as the underlying data store for HNSW graph traversal or exact KNN scans.

class VEC {
public:
    // Opens and memory-maps an existing .vec file (e.g., "store/products/.vec")
    explicit VEC(std::string_view path);
    ~VEC();

    // Prevent copy/move to safely manage the file descriptor and mmap region
    VEC(const VEC&) = delete;
    VEC& operator=(const VEC&) = delete;
    VEC(VEC&&) = delete;
    VEC& operator=(VEC&&) = delete;

    // Returns a raw pointer to the start of the memory-mapped vector data.
    // The total number of vectors can be derived by dividing file_size() 
    // by (dimension * sizeof(float)).
    [[nodiscard]] const float* data() const noexcept;

    // Returns the total size of the mapped region in bytes.
    [[nodiscard]] size_t file_size() const noexcept;

    // Memory access hints for the OS kernel via madvise().
    // Call advise_random() before traversing the HNSW graph.
    void advise_random() const;
    
    // Call advise_sequential() before falling back to a linear scan.
    void advise_sequential() const;

private:
    std::string path_;
    int         fd_ = -1;
    size_t      file_size_ = 0;
    float* mapped_data_ = nullptr;
};

// ── VEC Builder ───────────────────────────────────────────────────────────
// Appends raw vector data sequentially to a new .vec file.
// Used when compacting memtables to disk before the file becomes immutable.

class VECBuilder {
public:
    explicit VECBuilder(std::string_view path);
    ~VECBuilder();

    VECBuilder(const VECBuilder&) = delete;
    VECBuilder& operator=(const VECBuilder&) = delete;

    // Appends a single float32 vector to the file.
    // 'dim' specifies the number of float elements in the vector.
    void append(const float* vector_data, uint32_t dim);

    // Flushes any buffered data to disk and closes the file descriptor.
    void finish();

private:
    std::string path_;
    int         fd_ = -1;
};

} // namespace tensor::storage