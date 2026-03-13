#include <tensor/storage/vec.hpp>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdexcept>

namespace tensor::storage {

// ── VEC Builder ───────────────────────────────────────────────────────────

VECBuilder::VECBuilder(std::string_view path) : path_(path) {
    fd_ = ::open(path_.c_str(), O_CREAT | O_WRONLY | O_TRUNC | O_CLOEXEC, 0644);
    if (fd_ < 0) {
        throw std::runtime_error("Failed to open VEC file for writing: " + path_);
    }
}

VECBuilder::~VECBuilder() {
    if (fd_ >= 0) {
        finish();
    }
}

void VECBuilder::append(const float* vector_data, uint32_t dim) {
    if (fd_ < 0) {
        throw std::runtime_error("Cannot append to a closed VECBuilder.");
    }

    size_t bytes_to_write = dim * sizeof(float);
    ssize_t written = ::write(fd_, vector_data, bytes_to_write);
    
    if (written < 0 || static_cast<size_t>(written) != bytes_to_write) {
        throw std::runtime_error("Failed to write vector data to VEC file.");
    }
}

void VECBuilder::finish() {
    if (fd_ >= 0) {
        ::fdatasync(fd_);
        ::close(fd_);
        fd_ = -1;
    }
}

// ── VEC (Read-Only Memory Mapped) ─────────────────────────────────────────

VEC::VEC(std::string_view path) : path_(path) {
    fd_ = ::open(path_.c_str(), O_RDONLY | O_CLOEXEC);
    if (fd_ < 0) {
        throw std::runtime_error("Failed to open VEC file for reading: " + path_);
    }

    struct stat stat_buf;
    if (::fstat(fd_, &stat_buf) < 0) {
        ::close(fd_);
        throw std::runtime_error("Failed to stat VEC file: " + path_);
    }

    file_size_ = stat_buf.st_size;

    // POSIX mmap fails if length is 0, so we handle empty files gracefully
    if (file_size_ > 0) {
        void* mapped = ::mmap(nullptr, file_size_, PROT_READ, MAP_SHARED, fd_, 0);
        if (mapped == MAP_FAILED) {
            ::close(fd_);
            throw std::runtime_error("Failed to mmap VEC file: " + path_);
        }
        mapped_data_ = static_cast<float*>(mapped);
    }
}

VEC::~VEC() {
    if (mapped_data_ != nullptr && mapped_data_ != MAP_FAILED) {
        ::munmap(mapped_data_, file_size_);
    }
    if (fd_ >= 0) {
        ::close(fd_);
    }
}

const float* VEC::data() const noexcept {
    return mapped_data_;
}

size_t VEC::file_size() const noexcept {
    return file_size_;
}

// ── Memory Paging Hints ───────────────────────────────────────────────────

void VEC::advise_random() const {
    if (mapped_data_ != nullptr && file_size_ > 0) {
        // Optimizes OS page cache behavior for unpredictable HNSW graph hops
        ::madvise(mapped_data_, file_size_, MADV_RANDOM);
    }
}

void VEC::advise_sequential() const {
    if (mapped_data_ != nullptr && file_size_ > 0) {
        // Triggers OS read-ahead for brute-force linear fallback scans
        ::madvise(mapped_data_, file_size_, MADV_SEQUENTIAL);
    }
}

} // namespace tensor::storage