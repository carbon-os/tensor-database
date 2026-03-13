#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

namespace tensor::storage {

// Represents a single durable operation parsed from the log during recovery.
struct WalRecord {
    uint64_t             lsn;         // Log Sequence Number
    uint32_t             checksum;    // crc32c checksum
    std::vector<uint8_t> payload;     // Binary msgpack payload
};

// ── Write-Ahead Log ────────────────────────────────────────────────────────
// Provides durability for incoming mutations. 
// Every mutation is written to the WAL and flushed before the engine
// acknowledges the transaction. Corrupted records are detected via crc32c.

class WAL {
public:
    // Opens or creates a WAL file at the specified path (e.g., "store/products/.wal")
    explicit WAL(std::string_view path);
    ~WAL();

    // Prevent copy/move to safely manage the underlying file descriptor
    WAL(const WAL&) = delete;
    WAL& operator=(const WAL&) = delete;
    WAL(WAL&&) = delete;
    WAL& operator=(WAL&&) = delete;

    // Appends a raw binary msgpack payload to the in-memory log buffer.
    // Returns the assigned Log Sequence Number (LSN).
    uint64_t append(std::string_view record_data);

    // Forces an fsync/fdatasync of the internal buffer to the physical disk.
    void flush();

    // Reads the WAL sequentially from disk. 
    // Computes the crc32c checksum for each record and invokes the callback 
    // only for valid records. Halts and reports if corruption is detected.
    bool recover(const std::function<void(const WalRecord&)>& on_valid_record);

    // Truncates the WAL and resets the file. 
    // Typically invoked after the memtable is successfully compacted into an SST.
    void clear();

private:
    std::string path_;
    int         fd_ = -1;
    uint64_t    next_lsn_ = 0;

    // A staging buffer for batched writes before flush() is explicitly called
    std::vector<uint8_t> buffer_;
};

} // namespace tensor::storage