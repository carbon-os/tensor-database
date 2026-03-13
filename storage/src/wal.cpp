#include <tensor/storage/wal.hpp>
#include <crc32c/crc32c.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdexcept>
#include <cstring>

namespace tensor::storage {

// ── On-Disk Format ────────────────────────────────────────────────────────
// A packed binary header that precedes every msgpack payload in the .wal file.
#pragma pack(push, 1)
struct WalRecordHeader {
    uint64_t lsn;
    uint32_t payload_size;
    uint32_t checksum;
};
#pragma pack(pop)

// ── Constructor / Destructor ──────────────────────────────────────────────

WAL::WAL(std::string_view path) : path_(path) {
    // Open the WAL file for appending. Create it if it doesn't exist.
    // O_CLOEXEC prevents fd leaks to child processes.
    fd_ = ::open(path_.c_str(), O_CREAT | O_WRONLY | O_APPEND | O_CLOEXEC, 0644);
    if (fd_ < 0) {
        throw std::runtime_error("Failed to open WAL file for writing: " + path_);
    }
}

WAL::~WAL() {
    if (fd_ >= 0) {
        flush(); // Ensure any pending buffered writes are pushed before closing
        ::close(fd_);
    }
}

// ── Write Path ────────────────────────────────────────────────────────────

uint64_t WAL::append(std::string_view record_data) {
    uint64_t current_lsn = next_lsn_++;
    uint32_t payload_size = static_cast<uint32_t>(record_data.size());
    
    // Calculate CRC32C over the msgpack payload as specified
    uint32_t checksum = crc32c::Crc32c(record_data.data(), payload_size);

    WalRecordHeader header{current_lsn, payload_size, checksum};

    // Serialize the header and payload into the staging buffer
    size_t current_buffer_size = buffer_.size();
    buffer_.resize(current_buffer_size + sizeof(WalRecordHeader) + payload_size);
    
    std::memcpy(buffer_.data() + current_buffer_size, &header, sizeof(WalRecordHeader));
    std::memcpy(buffer_.data() + current_buffer_size + sizeof(WalRecordHeader), record_data.data(), payload_size);

    return current_lsn;
}

void WAL::flush() {
    if (buffer_.empty()) return;

    // Write the accumulated buffer to the OS
    ssize_t written = ::write(fd_, buffer_.data(), buffer_.size());
    if (written < 0 || static_cast<size_t>(written) != buffer_.size()) {
        throw std::runtime_error("Failed to write buffer to WAL file: " + path_);
    }

    // Force the OS to flush the page cache to the physical disk device
    if (::fdatasync(fd_) < 0) {
        throw std::runtime_error("Failed to fsync WAL file: " + path_);
    }

    buffer_.clear();
}

// ── Lifecycle / Recovery ──────────────────────────────────────────────────

bool WAL::recover(const std::function<void(const WalRecord&)>& on_valid_record) {
    // Open a separate read-only file descriptor for recovery
    int read_fd = ::open(path_.c_str(), O_RDONLY | O_CLOEXEC);
    if (read_fd < 0) {
        // If the file doesn't exist, there is nothing to recover.
        return true; 
    }

    bool recovery_successful = true;
    WalRecordHeader header;
    
    while (true) {
        ssize_t bytes_read = ::read(read_fd, &header, sizeof(WalRecordHeader));
        if (bytes_read == 0) {
            break; // Clean EOF
        }
        if (bytes_read != sizeof(WalRecordHeader)) {
            // Partial header read indicates a torn write at the end of the file
            recovery_successful = false;
            break; 
        }

        std::vector<uint8_t> payload(header.payload_size);
        bytes_read = ::read(read_fd, payload.data(), header.payload_size);
        
        if (bytes_read < 0 || static_cast<uint32_t>(bytes_read) != header.payload_size) {
            // Torn write in the payload section
            recovery_successful = false;
            break;
        }

        // Verify the CRC32C checksum to detect data corruption
        uint32_t calculated_checksum = crc32c::Crc32c(
            reinterpret_cast<const char*>(payload.data()), header.payload_size
        );
        
        if (calculated_checksum != header.checksum) {
            // Corruption detected
            recovery_successful = false;
            break;
        }

        // Record is valid. Dispatch to the engine to rebuild the memtable.
        on_valid_record(WalRecord{header.lsn, header.checksum, std::move(payload)});
        
        // Ensure the next LSN assigned during normal operation continues from the recovered state
        next_lsn_ = header.lsn + 1;
    }

    ::close(read_fd);
    return recovery_successful;
}

void WAL::clear() {
    // Drop all buffered data
    buffer_.clear();
    
    // Truncate the physical file to 0 bytes
    if (::ftruncate(fd_, 0) < 0) {
        throw std::runtime_error("Failed to truncate WAL file: " + path_);
    }
    
    // Reset the file offset back to the beginning
    if (::lseek(fd_, 0, SEEK_SET) < 0) {
        throw std::runtime_error("Failed to seek WAL file to start: " + path_);
    }
}

} // namespace tensor::storage