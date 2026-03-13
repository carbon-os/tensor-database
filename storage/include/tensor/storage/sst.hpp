#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace tensor::storage {

// ── Predicate ─────────────────────────────────────────────────────────────
// Minimal predicate pushdown for SST scans.
// Maps loosely to the AST BinaryExpr (e.g., '==', '!=') from the query planner.
class Predicate {
public:
    enum class Op { Eq, Neq, Lt, Gt, Lte, Gte };

    static Predicate Eq(std::string_view value)  { return {Op::Eq, std::string(value)}; }
    static Predicate Neq(std::string_view value) { return {Op::Neq, std::string(value)}; }
    static Predicate Lt(std::string_view value)  { return {Op::Lt, std::string(value)}; }
    static Predicate Gt(std::string_view value)  { return {Op::Gt, std::string(value)}; }
    static Predicate Lte(std::string_view value) { return {Op::Lte, std::string(value)}; }
    static Predicate Gte(std::string_view value) { return {Op::Gte, std::string(value)}; }

    Op op() const noexcept { return op_; }
    const std::string& value() const noexcept { return value_; }

private:
    Predicate(Op o, std::string v) : op_(o), value_(std::move(v)) {}
    Op op_;
    std::string value_;
};

// ── Sorted String Table (SST) ─────────────────────────────────────────────
// Read-only primary storage for row data. 
// Rows are grouped into pages, and each page is block-compressed using Snappy.

class SST {
public:
    // Opens an existing SST file for reading (e.g., "store/products/.sst")
    explicit SST(std::string_view path);
    ~SST();

    SST(const SST&) = delete;
    SST& operator=(const SST&) = delete;
    SST(SST&&) = delete;
    SST& operator=(SST&&) = delete;

    // Fetches a single row by its unique row_id.
    // The row_id is typically resolved via the .rbm (CRoaring) inverted index.
    // Returns the binary msgpack payload, or std::nullopt if the row_id is invalid.
    std::optional<std::vector<uint8_t>> get(uint32_t row_id) const;

    // Scans the SST for rows matching a specific predicate on a given field.
    // Uncompresses pages on the fly using Snappy to evaluate the predicate.
    std::vector<std::vector<uint8_t>> scan(std::string_view field, const Predicate& pred) const;

private:
    std::string path_;
    int         fd_ = -1;

    // Internal helper to read a compressed block from disk and decode it via Snappy
    std::vector<uint8_t> read_and_decompress_page(uint64_t offset, uint32_t compressed_size) const;
};

// ── SST Builder ───────────────────────────────────────────────────────────
// Utility to construct a new .sst file. 
// Accumulates rows into memory pages, compresses full pages using Snappy, 
// and writes them sequentially to disk.

class SSTBuilder {
public:
    explicit SSTBuilder(std::string_view path, size_t page_size = 4096);
    ~SSTBuilder();

    SSTBuilder(const SSTBuilder&) = delete;
    SSTBuilder& operator=(const SSTBuilder&) = delete;

    // Appends a binary msgpack row to the current working page.
    // Returns the assigned row_id for this record.
    uint32_t append(std::string_view msgpack_row);

    // Flushes the final page to disk, writes the block index/footer, and closes the file.
    void finish();

private:
    std::string path_;
    int         fd_ = -1;
    size_t      page_size_;
    uint32_t    next_row_id_ = 0;

    std::vector<uint8_t> current_page_;
    
    // Flushes current_page_ through snappy::Compress and writes to fd_
    void flush_page();
};

} // namespace tensor::storage