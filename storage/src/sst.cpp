#include <tensor/storage/sst.hpp>
#include <tensor/storage/page.hpp>
#include <msgpack.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdexcept>
#include <cstring>
#include <algorithm>

namespace tensor::storage {

// ── On-Disk Format Constants ──────────────────────────────────────────────
constexpr uint32_t SST_MAGIC = 0x55AADD11; // Magic bytes for file validation

#pragma pack(push, 1)
// An entry in the SST footer index. Points to a specific compressed page.
struct PageIndexEntry {
    uint32_t first_row_id;
    uint64_t offset;
    uint32_t compressed_size;
};

// The final 12 bytes of the .sst file.
struct SSTTrailer {
    uint64_t index_offset;
    uint32_t magic;
};
#pragma pack(pop)

// ── SSTBuilder ────────────────────────────────────────────────────────────

SSTBuilder::SSTBuilder(std::string_view path, size_t page_size) 
    : path_(path), page_size_(page_size) {
    fd_ = ::open(path_.c_str(), O_CREAT | O_WRONLY | O_TRUNC | O_CLOEXEC, 0644);
    if (fd_ < 0) {
        throw std::runtime_error("Failed to open SST file for writing: " + path_);
    }
}

SSTBuilder::~SSTBuilder() {
    if (fd_ >= 0) {
        ::close(fd_);
    }
}

// Staging for the footer index
static std::vector<PageIndexEntry> current_index_;
static PageBuilder current_page_builder_(4096);
static uint64_t current_file_offset_ = 0;
static uint32_t current_page_first_row_id_ = 0;

uint32_t SSTBuilder::append(std::string_view msgpack_row) {
    uint32_t row_id = next_row_id_++;

    if (current_page_builder_.is_empty()) {
        current_page_first_row_id_ = row_id;
    }

    // Attempt to add to the current page buffer
    if (!current_page_builder_.append(row_id, msgpack_row)) {
        // Page is full. Flush it, then start a new one with this record.
        flush_page();
        
        current_page_first_row_id_ = row_id;
        current_page_builder_.append(row_id, msgpack_row);
    }

    return row_id;
}

void SSTBuilder::flush_page() {
    if (current_page_builder_.is_empty()) return;

    // Apply Snappy compression via our internal page module
    std::vector<uint8_t> compressed = current_page_builder_.compress();

    // Write the compressed page to disk
    ssize_t written = ::write(fd_, compressed.data(), compressed.size());
    if (written < 0 || static_cast<size_t>(written) != compressed.size()) {
        throw std::runtime_error("Failed to write compressed page to SST.");
    }

    // Record this page in our in-memory index
    current_index_.push_back({
        current_page_first_row_id_,
        current_file_offset_,
        static_cast<uint32_t>(compressed.size())
    });

    current_file_offset_ += compressed.size();
    current_page_builder_.clear();
}

void SSTBuilder::finish() {
    // 1. Flush the final pending page
    flush_page();

    // 2. Write the accumulated index array to the end of the file
    uint64_t index_offset = current_file_offset_;
    size_t index_bytes = current_index_.size() * sizeof(PageIndexEntry);
    
    if (index_bytes > 0) {
        ::write(fd_, current_index_.data(), index_bytes);
    }

    // 3. Write the standard trailer
    SSTTrailer trailer{index_offset, SST_MAGIC};
    ::write(fd_, &trailer, sizeof(SSTTrailer));

    // 4. Ensure durability
    ::fdatasync(fd_);
    ::close(fd_);
    fd_ = -1;

    // Reset statics for next build
    current_index_.clear();
    current_file_offset_ = 0;
}

// ── SST (Read-Only) ───────────────────────────────────────────────────────

static std::vector<PageIndexEntry> loaded_index_;

SST::SST(std::string_view path) : path_(path) {
    fd_ = ::open(path_.c_str(), O_RDONLY | O_CLOEXEC);
    if (fd_ < 0) {
        throw std::runtime_error("Failed to open SST file for reading: " + path_);
    }

    struct stat stat_buf;
    if (::fstat(fd_, &stat_buf) < 0 || stat_buf.st_size < static_cast<off_t>(sizeof(SSTTrailer))) {
        throw std::runtime_error("SST file is invalid or too small.");
    }

    // Read trailer to locate the index
    SSTTrailer trailer;
    ::pread(fd_, &trailer, sizeof(SSTTrailer), stat_buf.st_size - sizeof(SSTTrailer));

    if (trailer.magic != SST_MAGIC) {
        throw std::runtime_error("SST file magic mismatch (corruption detected).");
    }

    // Load the index array into memory for fast binary searching
    size_t index_bytes = (stat_buf.st_size - sizeof(SSTTrailer)) - trailer.index_offset;
    size_t num_entries = index_bytes / sizeof(PageIndexEntry);
    
    loaded_index_.resize(num_entries);
    ::pread(fd_, loaded_index_.data(), index_bytes, trailer.index_offset);
}

SST::~SST() {
    if (fd_ >= 0) ::close(fd_);
    loaded_index_.clear();
}

std::vector<uint8_t> SST::read_and_decompress_page(uint64_t offset, uint32_t compressed_size) const {
    std::vector<uint8_t> buffer(compressed_size);
    // pread is thread-safe, avoiding seek conflicts across concurrent queries
    ssize_t bytes_read = ::pread(fd_, buffer.data(), compressed_size, offset);
    if (bytes_read < 0 || static_cast<uint32_t>(bytes_read) != compressed_size) {
        throw std::runtime_error("Failed to read compressed page from disk.");
    }
    return buffer;
}

std::optional<std::vector<uint8_t>> SST::get(uint32_t row_id) const {
    if (loaded_index_.empty()) return std::nullopt;

    // Binary search the index to find the page that *might* contain the row_id
    auto it = std::upper_bound(loaded_index_.begin(), loaded_index_.end(), row_id,
        [](uint32_t id, const PageIndexEntry& entry) {
            return id < entry.first_row_id;
        });

    if (it == loaded_index_.begin()) {
        return std::nullopt; // row_id is strictly smaller than the first row in the SST
    }

    --it; // Step back to the actual page containing our range

    std::vector<uint8_t> compressed_data = read_and_decompress_page(it->offset, it->compressed_size);
    
    // Delegate Snappy decompression and linear byte scanning to PageReader
    PageReader reader(std::string_view(reinterpret_cast<const char*>(compressed_data.data()), compressed_data.size()));
    return reader.get(row_id);
}

std::vector<std::vector<uint8_t>> SST::scan(std::string_view field, const Predicate& pred) const {
    std::vector<std::vector<uint8_t>> results;

    // A full scan must evaluate every row in every page
    for (const auto& entry : loaded_index_) {
        std::vector<uint8_t> compressed_data = read_and_decompress_page(entry.offset, entry.compressed_size);
        PageReader reader(std::string_view(reinterpret_cast<const char*>(compressed_data.data()), compressed_data.size()));
        
        const std::vector<uint8_t>& uncompressed = reader.uncompressed_data();
        size_t offset = 0;
        size_t total_size = uncompressed.size();

        // Iterate through all records in the decompressed page
        while (offset < total_size) {
            uint32_t row_id;
            uint32_t payload_size;

            std::memcpy(&row_id, uncompressed.data() + offset, sizeof(uint32_t));
            offset += sizeof(uint32_t);

            std::memcpy(&payload_size, uncompressed.data() + offset, sizeof(uint32_t));
            offset += sizeof(uint32_t);

            // Parse the msgpack payload using C API
            msgpack_zone zone;
            msgpack_object obj;
            msgpack_zone_init(&zone, 2048);

            size_t off = 0;
            msgpack_unpack_return ret = msgpack_unpack(
                reinterpret_cast<const char*>(uncompressed.data() + offset),
                payload_size,
                &off,
                &zone,
                &obj
            );

            if (ret == MSGPACK_UNPACK_SUCCESS) {
                // Minimal projection logic for the scan predicate. 
                // In a full implementation, this integrates with semantic.hpp's type inference.
                if (obj.type == MSGPACK_OBJECT_MAP) {
                    for (uint32_t i = 0; i < obj.via.map.size; ++i) {
                        msgpack_object_kv* pair = &obj.via.map.ptr[i];
                        msgpack_object& key = pair->key;
                        msgpack_object& val = pair->val;

                        if (key.type == MSGPACK_OBJECT_STR && 
                            std::string_view(key.via.str.ptr, key.via.str.size) == field) {
                            
                            // String Equality Predicate Evaluation
                            if (val.type == MSGPACK_OBJECT_STR) {
                                std::string_view val_str(val.via.str.ptr, val.via.str.size);
                                if (pred.op() == Predicate::Op::Eq && val_str == pred.value()) {
                                    std::vector<uint8_t> payload(payload_size);
                                    std::memcpy(payload.data(), uncompressed.data() + offset, payload_size);
                                    results.push_back(std::move(payload));
                                }
                            }
                        }
                    }
                }
            }

            msgpack_zone_destroy(&zone);

            offset += payload_size;
        }
    }

    return results;
}

} // namespace tensor::storage