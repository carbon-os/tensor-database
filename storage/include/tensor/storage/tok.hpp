#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include <optional>

namespace tensor::storage {

// ── Pre-Tokenized Array Storage (TOK) ─────────────────────────────────────
// Caches int32 token arrays generated at write time for raw text fields.
// Used by the Reasoning engine to bypass query-time tokenization, turning 
// context window loading into a fast memcpy.

class TOK {
public:
    // Opens a .tok file. The current_model_name is checked against the file's 
    // header. If they mismatch, the file is safely invalidated because the 
    // cached token IDs belong to a different vocabulary.
    TOK(std::string_view path, std::string_view current_model_name);
    ~TOK();

    TOK(const TOK&) = delete;
    TOK& operator=(const TOK&) = delete;

    // Retrieves the pre-tokenized int32 array for a given row_id.
    // Returns nullopt if the row is missing or the file was invalidated.
    std::optional<std::vector<int32_t>> get(uint32_t row_id) const;

    // True if the file was loaded successfully and the model vocabulary matches.
    bool is_valid() const noexcept { return is_valid_; }

private:
    std::string path_;
    int         fd_ = -1;
    bool        is_valid_ = false;

    // Maps a row_id to its token array's location in the file
    struct IndexEntry {
        uint32_t first_row_id;
        uint64_t offset;
        uint32_t token_count;
    };
    std::vector<IndexEntry> index_;
};

// ── TOK Builder ───────────────────────────────────────────────────────────
// Appends pre-calculated int32 token arrays sequentially to disk.
// The engine calls this at write time after running llama.cpp's tokenizer.

class TOKBuilder {
public:
    // Creates a new .tok file, embedding the model_name into the file header
    // to protect against future model/vocabulary swaps.
    TOKBuilder(std::string_view path, std::string_view model_name);
    ~TOKBuilder();

    TOKBuilder(const TOKBuilder&) = delete;
    TOKBuilder& operator=(const TOKBuilder&) = delete;

    // Appends the int32 token array for a specific row_id.
    void append(uint32_t row_id, const std::vector<int32_t>& tokens);

    // Flushes the footer index and closes the file.
    void finish();

private:
    std::string path_;
    int         fd_ = -1;
    uint64_t    current_offset_ = 0;

    struct IndexEntry {
        uint32_t row_id;
        uint64_t offset;
        uint32_t token_count;
    };
    std::vector<IndexEntry> index_;
};

} // namespace tensor::storage