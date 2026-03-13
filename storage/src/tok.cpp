#include <tensor/storage/tok.hpp>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdexcept>
#include <cstring>
#include <algorithm>

namespace tensor::storage {

constexpr uint32_t TOK_MAGIC = 0x746F6B31; // "tok1"

#pragma pack(push, 1)
struct TOKTrailer {
    uint64_t index_offset;
    uint32_t magic;
};
#pragma pack(pop)

// ── TOK Builder ───────────────────────────────────────────────────────────

TOKBuilder::TOKBuilder(std::string_view path, std::string_view model_name) : path_(path) {
    fd_ = ::open(path_.c_str(), O_CREAT | O_WRONLY | O_TRUNC | O_CLOEXEC, 0644);
    if (fd_ < 0) {
        throw std::runtime_error("Failed to open TOK file for writing: " + path_);
    }

    // Write the magic bytes and the model name length + string as the header.
    // This allows the reader to validate the vocabulary.
    ::write(fd_, &TOK_MAGIC, sizeof(uint32_t));
    
    uint32_t name_len = static_cast<uint32_t>(model_name.size());
    ::write(fd_, &name_len, sizeof(uint32_t));
    ::write(fd_, model_name.data(), name_len);

    current_offset_ = sizeof(uint32_t) + sizeof(uint32_t) + name_len;
}

TOKBuilder::~TOKBuilder() {
    if (fd_ >= 0) finish();
}

void TOKBuilder::append(uint32_t row_id, const std::vector<int32_t>& tokens) {
    if (tokens.empty() || fd_ < 0) return;

    size_t byte_size = tokens.size() * sizeof(int32_t);
    
    // Write the raw token array directly to disk
    ssize_t written = ::write(fd_, tokens.data(), byte_size);
    if (written < 0 || static_cast<size_t>(written) != byte_size) {
        throw std::runtime_error("Failed to write tokens to TOK file.");
    }

    // Record the location in the index
    index_.push_back({
        row_id,
        current_offset_,
        static_cast<uint32_t>(tokens.size())
    });

    current_offset_ += byte_size;
}

void TOKBuilder::finish() {
    if (fd_ < 0) return;

    uint64_t index_offset = current_offset_;
    
    // Write the index blocks
    for (const auto& entry : index_) {
        ::write(fd_, &entry.row_id, sizeof(uint32_t));
        ::write(fd_, &entry.offset, sizeof(uint64_t));
        ::write(fd_, &entry.token_count, sizeof(uint32_t));
    }

    // Write the trailer
    TOKTrailer trailer{index_offset, TOK_MAGIC};
    ::write(fd_, &trailer, sizeof(TOKTrailer));

    ::fdatasync(fd_);
    ::close(fd_);
    fd_ = -1;
}

// ── TOK (Read-Only) ───────────────────────────────────────────────────────

TOK::TOK(std::string_view path, std::string_view current_model_name) : path_(path) {
    fd_ = ::open(path_.c_str(), O_RDONLY | O_CLOEXEC);
    if (fd_ < 0) return; // Silent fail means is_valid_ remains false

    struct stat stat_buf;
    if (::fstat(fd_, &stat_buf) < 0 || stat_buf.st_size < static_cast<off_t>(sizeof(TOKTrailer))) {
        ::close(fd_);
        fd_ = -1;
        return;
    }

    // 1. Validate Trailer
    TOKTrailer trailer;
    ::pread(fd_, &trailer, sizeof(TOKTrailer), stat_buf.st_size - sizeof(TOKTrailer));
    if (trailer.magic != TOK_MAGIC) {
        ::close(fd_);
        fd_ = -1;
        return;
    }

    // 2. Validate Header & Model Vocabulary
    uint32_t magic;
    ::pread(fd_, &magic, sizeof(uint32_t), 0);
    if (magic != TOK_MAGIC) {
        ::close(fd_);
        fd_ = -1;
        return;
    }

    uint32_t name_len;
    ::pread(fd_, &name_len, sizeof(uint32_t), sizeof(uint32_t));
    
    std::string file_model_name(name_len, '\0');
    ::pread(fd_, file_model_name.data(), name_len, sizeof(uint32_t) * 2);

    // If the worker model changed, the tokens are invalid for this context window
    if (file_model_name != current_model_name) {
        ::close(fd_);
        fd_ = -1;
        return; 
    }

    // 3. Load the index for fast binary searching
    size_t index_bytes = (stat_buf.st_size - sizeof(TOKTrailer)) - trailer.index_offset;
    size_t num_entries = index_bytes / (sizeof(uint32_t) + sizeof(uint64_t) + sizeof(uint32_t));
    
    index_.reserve(num_entries);
    uint64_t read_offset = trailer.index_offset;
    
    for (size_t i = 0; i < num_entries; ++i) {
        IndexEntry entry;
        ::pread(fd_, &entry.first_row_id, sizeof(uint32_t), read_offset);
        read_offset += sizeof(uint32_t);
        ::pread(fd_, &entry.offset, sizeof(uint64_t), read_offset);
        read_offset += sizeof(uint64_t);
        ::pread(fd_, &entry.token_count, sizeof(uint32_t), read_offset);
        read_offset += sizeof(uint32_t);
        
        index_.push_back(entry);
    }

    is_valid_ = true;
}

TOK::~TOK() {
    if (fd_ >= 0) ::close(fd_);
}

std::optional<std::vector<int32_t>> TOK::get(uint32_t row_id) const {
    if (!is_valid_ || index_.empty()) return std::nullopt;

    // Binary search to find the exact offset for this row's token array
    auto it = std::lower_bound(index_.begin(), index_.end(), row_id,
        [](const IndexEntry& entry, uint32_t target) {
            return entry.first_row_id < target;
        });

    if (it != index_.end() && it->first_row_id == row_id) {
        std::vector<int32_t> tokens(it->token_count);
        
        // This pread acts as the memcpy directly from the page cache into 
        // the std::vector, ready to be handed to the llama.cpp context window.
        ::pread(fd_, tokens.data(), it->token_count * sizeof(int32_t), it->offset);
        
        return tokens;
    }

    return std::nullopt;
}

} // namespace tensor::storage