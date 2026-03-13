#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace tensor::inference {

// ── Output schema ─────────────────────────────────────────────────────────

struct SchemaField {
    std::string name;
    std::string type;
    bool        nullable = false;
};

struct OutputSchema {
    std::string              type_name;
    std::vector<SchemaField> fields;
};

// ── Result ────────────────────────────────────────────────────────────────

class ReasoningResult {
public:
    bool has(std::string_view name) const noexcept;
    std::optional<std::string> field(std::string_view name) const noexcept;

    const std::unordered_map<std::string, std::string>& all() const noexcept {
        return fields_;
    }

private:
    friend class ReasoningEngine;
    friend ReasoningResult parse_result(const std::string&, const OutputSchema&);

    std::unordered_map<std::string, std::string> fields_;
};

// Declared after ReasoningResult so the return type is fully defined.
ReasoningResult parse_result(const std::string& json, const OutputSchema& schema);

// ── Engine ────────────────────────────────────────────────────────────────

class ReasoningEngine {
public:
    ReasoningEngine(std::string_view worker_model_path,
                    std::string_view aggregator_model_path);
    ~ReasoningEngine();

    ReasoningEngine(const ReasoningEngine&)            = delete;
    ReasoningEngine& operator=(const ReasoningEngine&) = delete;

    size_t max_workers() const noexcept;

    std::vector<int32_t> tokenize(std::string_view text) const;

    ReasoningResult run(std::string_view    query,
                        std::string_view    raw_text,
                        const OutputSchema& schema);

    ReasoningResult run_tokenized(std::string_view            query,
                                  const std::vector<int32_t>& tokens,
                                  const OutputSchema&          schema);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace tensor::inference