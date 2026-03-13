#include <tensor/storage/rbm.hpp>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdexcept>
#include <vector>
#include <cstring>

namespace tensor::storage {

// ── On-Disk Format ────────────────────────────────────────────────────────
// The .rbm file is serialized as a sequence of key-value pairs:
// [uint32_t num_entries]
// Followed by `num_entries` blocks of:
// [uint32_t token_length] [char* token_bytes]
// [uint32_t bitmap_size] [char* serialized_bitmap]

// ── RBM Builder ───────────────────────────────────────────────────────────

RBMBuilder::RBMBuilder(std::string_view path) : path_(path) {
    // We don't open the file descriptor until finish() because the index 
    // is built entirely in memory first.
}

void RBMBuilder::add(std::string_view token, uint32_t row_id) {
    // The CRoaring wrapper overloads the add() method to insert integers.
    // It automatically upgrades internal containers (Array -> Bitmap -> Run)
    // as the density of the row_ids increases.
    index_[std::string(token)].add(row_id);
}

void RBMBuilder::finish() {
    int fd = ::open(path_.c_str(), O_CREAT | O_WRONLY | O_TRUNC | O_CLOEXEC, 0644);
    if (fd < 0) {
        throw std::runtime_error("Failed to open RBM file for writing: " + path_);
    }

    uint32_t num_entries = static_cast<uint32_t>(index_.size());
    ::write(fd, &num_entries, sizeof(uint32_t));

    for (auto& [token, bitmap] : index_) {
        // 1. Optimize the bitmap to use Run-Length Encoding (RLE) where beneficial.
        // This makes dense sequences (e.g., row_id 1 to 10000) extremely compact.
        bitmap.runOptimize();

        // 2. Write the token string
        uint32_t token_len = static_cast<uint32_t>(token.size());
        ::write(fd, &token_len, sizeof(uint32_t));
        ::write(fd, token.data(), token_len);

        // 3. Serialize the Roaring Bitmap
        uint32_t bitmap_size = static_cast<uint32_t>(bitmap.getSizeInBytes());
        ::write(fd, &bitmap_size, sizeof(uint32_t));

        // CRoaring requires a pre-allocated char buffer to write its serialized state
        std::vector<char> buffer(bitmap_size);
        bitmap.write(buffer.data());

        ::write(fd, buffer.data(), bitmap_size);
    }

    ::fdatasync(fd);
    ::close(fd);
    
    // Clear the memory after successful flush
    index_.clear();
}

// ── RBM (Read-Only) ───────────────────────────────────────────────────────

RBM::RBM(std::string_view path) : path_(path) {
    int fd = ::open(path_.c_str(), O_RDONLY | O_CLOEXEC);
    if (fd < 0) {
        throw std::runtime_error("Failed to open RBM file for reading: " + path_);
    }

    uint32_t num_entries = 0;
    ssize_t bytes_read = ::read(fd, &num_entries, sizeof(uint32_t));
    if (bytes_read == 0) {
        ::close(fd);
        return; // Empty index
    }

    index_.reserve(num_entries);

    for (uint32_t i = 0; i < num_entries; ++i) {
        // 1. Read the token string
        uint32_t token_len = 0;
        ::read(fd, &token_len, sizeof(uint32_t));

        std::string token(token_len, '\0');
        ::read(fd, token.data(), token_len);

        // 2. Read the serialized bitmap
        uint32_t bitmap_size = 0;
        ::read(fd, &bitmap_size, sizeof(uint32_t));

        std::vector<char> buffer(bitmap_size);
        ::read(fd, buffer.data(), bitmap_size);

        // 3. Deserialize back into a CRoaring object
        // readSafe ensures we don't segfault on corrupted disk data
        roaring::Roaring bitmap = roaring::Roaring::readSafe(buffer.data(), bitmap_size);
        
        index_.emplace(std::move(token), std::move(bitmap));
    }

    ::close(fd);
}

roaring::Roaring RBM::get(std::string_view token) const {
    auto it = index_.find(std::string(token));
    if (it != index_.end()) {
        return it->second; // Returns a copy of the Roaring object
    }
    
    // Return an empty bitmap if the keyword doesn't exist.
    // This allows the query executor to safely do: `rbm.get("kernel") & rbm.get("panic")`
    // If "kernel" is missing, the empty bitmap naturally cascades into an empty intersection.
    return roaring::Roaring();
}

} // namespace tensor::storage