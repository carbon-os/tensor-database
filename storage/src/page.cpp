#include <tensor/storage/page.hpp>
#include <snappy.h>
#include <stdexcept>
#include <cstring>

namespace tensor::storage {

// ── Page Layout Format ────────────────────────────────────────────────────
// Inside the uncompressed page, records are stored sequentially:
// [uint32_t row_id] [uint32_t payload_size] [binary msgpack payload]
// Because row_ids are inserted sequentially by the engine, they are 
// naturally sorted in ascending order within the page.

// ── PageBuilder ───────────────────────────────────────────────────────────

PageBuilder::PageBuilder(size_t target_page_size) 
    : target_size_(target_page_size) {
    // Pre-allocate buffer to avoid reallocations during tight append loops
    buffer_.reserve(target_size_ + 1024); // +1KB overflow buffer
}

bool PageBuilder::append(uint32_t row_id, std::string_view msgpack_row) {
    uint32_t payload_size = static_cast<uint32_t>(msgpack_row.size());
    size_t required_space = sizeof(uint32_t) + sizeof(uint32_t) + payload_size;

    // If adding this record exceeds the target size AND the page isn't empty,
    // reject it so the caller knows to compress and flush the current page.
    if (!buffer_.empty() && (buffer_.size() + required_space > target_size_)) {
        return false; 
    }

    size_t offset = buffer_.size();
    buffer_.resize(offset + required_space);

    // 1. Write row_id
    std::memcpy(buffer_.data() + offset, &row_id, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    // 2. Write payload size
    std::memcpy(buffer_.data() + offset, &payload_size, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    // 3. Write msgpack payload
    std::memcpy(buffer_.data() + offset, msgpack_row.data(), payload_size);

    record_count_++;
    return true;
}

std::vector<uint8_t> PageBuilder::compress() const {
    std::string compressed_str;
    // Snappy is optimized for CPU efficiency over maximum compression ratio
    size_t compressed_length = snappy::Compress(
        reinterpret_cast<const char*>(buffer_.data()), 
        buffer_.size(), 
        &compressed_str
    );

    if (compressed_length == 0 && !buffer_.empty()) {
        throw std::runtime_error("Snappy compression failed on SST page.");
    }

    // Convert the std::string back into a raw byte vector
    std::vector<uint8_t> compressed_data(compressed_str.begin(), compressed_str.end());
    return compressed_data;
}

void PageBuilder::clear() {
    buffer_.clear();
    record_count_ = 0;
}

size_t PageBuilder::size() const noexcept {
    return buffer_.size();
}

bool PageBuilder::is_empty() const noexcept {
    return buffer_.empty();
}

// ── PageReader ────────────────────────────────────────────────────────────

PageReader::PageReader(std::string_view compressed_data) {
    std::string uncompressed_str;
    
    // Decompress the Snappy block back into raw page bytes
    bool success = snappy::Uncompress(
        compressed_data.data(), 
        compressed_data.size(), 
        &uncompressed_str
    );

    if (!success) {
        throw std::runtime_error("Snappy decompression failed on SST page read.");
    }

    uncompressed_data_ = std::vector<uint8_t>(uncompressed_str.begin(), uncompressed_str.end());
}

std::optional<std::vector<uint8_t>> PageReader::get(uint32_t target_row_id) const {
    size_t offset = 0;
    size_t total_size = uncompressed_data_.size();

    // Linear scan through the 4KB page. 
    // Given the small target page size, linear scanning is highly cache-friendly 
    // and often faster than binary search due to lack of branching overhead.
    while (offset < total_size) {
        uint32_t current_row_id;
        uint32_t payload_size;

        std::memcpy(&current_row_id, uncompressed_data_.data() + offset, sizeof(uint32_t));
        offset += sizeof(uint32_t);

        std::memcpy(&payload_size, uncompressed_data_.data() + offset, sizeof(uint32_t));
        offset += sizeof(uint32_t);

        if (current_row_id == target_row_id) {
            // Found the requested row! Extract and return the msgpack payload.
            std::vector<uint8_t> payload(payload_size);
            std::memcpy(payload.data(), uncompressed_data_.data() + offset, payload_size);
            return payload;
        }

        if (current_row_id > target_row_id) {
            // Because rows are appended sequentially, if we overshoot the target,
            // it does not exist in this page.
            break;
        }

        // Skip to the next record
        offset += payload_size;
    }

    return std::nullopt;
}

const std::vector<uint8_t>& PageReader::uncompressed_data() const noexcept {
    return uncompressed_data_;
}

} // namespace tensor::storage