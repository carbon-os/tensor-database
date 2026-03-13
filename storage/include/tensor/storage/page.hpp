#pragma once

#include <cstdint>
#include <string_view>
#include <vector>
#include <optional>

namespace tensor::storage {

// ── SST Page Builder ──────────────────────────────────────────────────────
// Internal helper to buffer rows in memory until a target page size is reached.
// Handles the serialization of the page layout before Snappy compression.

class PageBuilder {
public:
    explicit PageBuilder(size_t target_page_size = 4096);

    // Prevent copy/move
    PageBuilder(const PageBuilder&) = delete;
    PageBuilder& operator=(const PageBuilder&) = delete;

    // Appends a row_id and its corresponding msgpack payload to the page.
    // Returns true if successful, or false if the page has reached its target size
    // (indicating the caller should compress/flush this page and start a new one).
    bool append(uint32_t row_id, std::string_view msgpack_row);

    // Applies Snappy compression to the current page buffer.
    // Returns the compressed binary payload ready to be written to the .sst file.
    [[nodiscard]] std::vector<uint8_t> compress() const;

    // Resets the internal buffer to start building a new page.
    void clear();

    [[nodiscard]] size_t size() const noexcept;
    [[nodiscard]] bool   is_empty() const noexcept;

private:
    size_t               target_size_;
    uint32_t             record_count_ = 0;
    std::vector<uint8_t> buffer_;
};

// ── SST Page Reader ───────────────────────────────────────────────────────
// Internal helper to decompress and read a single Snappy-compressed block 
// fetched from an .sst file.

class PageReader {
public:
    // Initializes the reader by immediately decompressing the Snappy payload.
    // Throws or sets an error state if the Snappy decompression fails.
    explicit PageReader(std::string_view compressed_data);

    // Prevent copy/move
    PageReader(const PageReader&) = delete;
    PageReader& operator=(const PageReader&) = delete;

    // Binary searches or linearly scans the uncompressed page for a specific row_id.
    // Returns the msgpack payload if found, or std::nullopt.
    [[nodiscard]] std::optional<std::vector<uint8_t>> get(uint32_t row_id) const;

    // Exposes the uncompressed page data for full sequential scans.
    // The SST scan() method uses this to evaluate predicates against every row.
    [[nodiscard]] const std::vector<uint8_t>& uncompressed_data() const noexcept;

private:
    std::vector<uint8_t> uncompressed_data_;
};

}