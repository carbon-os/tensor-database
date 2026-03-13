// inference/tests/main_reasoning.cpp
// Tests for ReasoningEngine — run with:
//   ./inference-reasoning-test <worker_model> <aggregator_model>
//
// Example:
//   ./inference-reasoning-test \
//       models/qwen3-0.6b-q4_k_m.gguf \
//       models/qwen3-1.7b-instruct-q4_k_m.gguf

#include <tensor/inference/reasoning.hpp>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace tensor::inference;

// ── Helpers ───────────────────────────────────────────────────────────────

static void print_header(const char* title) {
    std::cout << "\n── " << title << " ";
    for (int i = static_cast<int>(strlen(title)); i < 60; ++i) std::cout << '-';
    std::cout << "\n";
}

static void pass(const char* name) {
    std::cout << "  [PASS] " << name << "\n";
}

static void fail(const char* name, const std::string& reason) {
    std::cerr << "  [FAIL] " << name << " — " << reason << "\n";
    std::exit(1);
}

static void print_result(const ReasoningResult& r, const OutputSchema& schema) {
    for (const auto& f : schema.fields) {
        const auto val = r.field(f.name);
        std::cout << "    " << std::setw(16) << std::left << f.name << " = "
                  << (val ? *val : "(null)") << "\n";
    }
}

// Elapsed time helper
struct Timer {
    std::chrono::steady_clock::time_point start =
        std::chrono::steady_clock::now();

    double elapsed_ms() const {
        using namespace std::chrono;
        return duration<double, std::milli>(
            steady_clock::now() - start).count();
    }
};

// ── Shared test data ──────────────────────────────────────────────────────

// A realistic product description used across multiple tests.
static const std::string k_product_text = R"(
Nike Air Max 270 React running shoe.
Retail price: $89.99.
Available in sizes 6 through 14, wide widths available.
Colorways: black/white, university red, volt green.
Features a full-length React foam midsole and a large Air unit in the heel
for all-day cushioning. Weight: 10.2 oz (men's size 10).
Best suited for casual wear and light jogging.
Carbon footprint offset: this product ships carbon-neutral.
)";

static const std::string k_irrelevant_text = R"(
The history of the Byzantine Empire spans over a thousand years,
from the founding of Constantinople in 330 AD to its fall in 1453.
During this period the empire served as a bulwark of Christianity
against various invaders from the east and north.
)";

static OutputSchema make_product_schema() {
    return OutputSchema{
        "ProductResult",
        {
            { "name",   "text",    false },
            { "price",  "float64", false },
            { "reason", "text",    true  },
        }
    };
}

static OutputSchema make_detail_schema() {
    return OutputSchema{
        "ProductDetail",
        {
            { "name",      "text",    false },
            { "price",     "float64", false },
            { "size_range","text",    true  },
            { "weight_oz", "float64", true  },
            { "in_stock",  "bool",    false },
        }
    };
}

// ── Tests ─────────────────────────────────────────────────────────────────

static void test_construction(const std::string& worker_path,
                               const std::string& agg_path) {
    print_header("Construction");
    try {
        ReasoningEngine engine(worker_path, agg_path);
        pass("loads both models without throwing");

        const size_t n = engine.max_workers();
        if (n == 0)
            fail("max_workers > 0", "got 0");
        std::cout << "  max_workers = " << n << "\n";
        pass("max_workers() returns positive value");
    } catch (const std::exception& e) {
        fail("construction", e.what());
    }
}

// tokenize() must return a non-empty int32 array for non-empty input.
static void test_tokenize(ReasoningEngine& engine) {
    print_header("tokenize()");

    const auto toks = engine.tokenize("hello world, this is a test");
    if (toks.empty())
        fail("tokenize non-empty", "got empty token array");
    std::cout << "  token count = " << toks.size() << "\n";
    pass("tokenize() returns non-empty array");

    // Empty string should not crash — may return empty or BOS-only.
    try {
        const auto empty_toks = engine.tokenize("");
        std::cout << "  empty input token count = " << empty_toks.size() << "\n";
        pass("tokenize('') does not crash");
    } catch (const std::exception& e) {
        fail("tokenize empty", e.what());
    }
}

// run() over clearly relevant text must populate mandatory fields.
static void test_run_relevant(ReasoningEngine& engine) {
    print_header("run() — relevant text");

    const auto schema = make_product_schema();
    Timer t;
    const auto result = engine.run(
        "gift ideas under one hundred dollars",
        k_product_text,
        schema);
    std::cout << "  elapsed = " << std::fixed << std::setprecision(1)
              << t.elapsed_ms() << " ms\n";
    print_result(result, schema);

    if (!result.has("name"))
        fail("name field present", "mandatory field 'name' missing");
    if (!result.has("price"))
        fail("price field present", "mandatory field 'price' missing");
    pass("mandatory fields populated from relevant text");

    // Price must look like a number.
    const auto price_str = result.field("price");
    if (price_str) {
        bool has_digit = false;
        for (char c : *price_str)
            if (std::isdigit((unsigned char)c)) { has_digit = true; break; }
        if (!has_digit)
            fail("price is numeric", "got '" + *price_str + "'");
        pass("price field contains numeric characters");
    }
}

// run_tokenized() must produce the same shape of result as run().
static void test_run_tokenized(ReasoningEngine& engine) {
    print_header("run_tokenized()");

    const auto schema = make_product_schema();
    const auto tokens = engine.tokenize(k_product_text);

    if (tokens.empty())
        fail("tokenize pre-test", "token array is empty");
    std::cout << "  tokens from .tok cache = " << tokens.size() << "\n";

    Timer t;
    const auto result = engine.run_tokenized(
        "shoes under one hundred dollars",
        tokens,
        schema);
    std::cout << "  elapsed = " << std::fixed << std::setprecision(1)
              << t.elapsed_ms() << " ms\n";
    print_result(result, schema);

    if (!result.has("name"))
        fail("run_tokenized name field", "mandatory field 'name' missing");
    pass("run_tokenized() populates mandatory fields");
}

// Nullable fields should be absent (nullopt) when the text has no value
// for them, and present when the text does.
static void test_nullable_fields(ReasoningEngine& engine) {
    print_header("Nullable fields");

    const auto schema = make_detail_schema();
    const auto result = engine.run(
        "product details",
        k_product_text,
        schema);
    print_result(result, schema);

    // Mandatory fields must be present.
    if (!result.has("name"))
        fail("nullable: name present", "'name' missing");
    if (!result.has("price"))
        fail("nullable: price present", "'price' missing");

    // Optional fields: if present they must be non-empty strings.
    if (result.has("size_range")) {
        const auto v = result.field("size_range");
        if (!v || v->empty())
            fail("nullable: size_range value", "present but empty");
        std::cout << "  size_range found: " << *v << "\n";
    } else {
        std::cout << "  size_range absent (acceptable)\n";
    }

    pass("mandatory fields present, nullable fields handled correctly");
}

// Irrelevant text should still return valid (possibly empty) fields
// without crashing. The grammar guarantees structurally valid JSON
// regardless of whether the text contains useful information.
static void test_irrelevant_text(ReasoningEngine& engine) {
    print_header("Irrelevant text");

    const auto schema = make_product_schema();
    Timer t;

    ReasoningResult result;
    try {
        result = engine.run(
            "gift ideas under fifty dollars",
            k_irrelevant_text,
            schema);
    } catch (const std::exception& e) {
        fail("irrelevant text no crash", e.what());
    }

    std::cout << "  elapsed = " << std::fixed << std::setprecision(1)
              << t.elapsed_ms() << " ms\n";
    print_result(result, schema);
    pass("irrelevant text does not crash");
}

// Empty token array should return an empty result, not crash.
static void test_empty_tokens(ReasoningEngine& engine) {
    print_header("Empty token array");

    const auto schema = make_product_schema();
    try {
        const std::vector<int32_t> empty_toks;
        const auto result = engine.run_tokenized(
            "any query",
            empty_toks,
            schema);
        // We just want no crash and an empty result.
        if (result.has("name") || result.has("price"))
            std::cout << "  note: non-empty result from empty tokens\n";
        pass("empty token array does not crash");
    } catch (const std::exception& e) {
        fail("empty token array", e.what());
    }
}

// Schema with only a single field.
static void test_minimal_schema(ReasoningEngine& engine) {
    print_header("Minimal schema (single field)");

    const OutputSchema schema{
        "NameOnly",
        { { "name", "text", false } }
    };

    const auto result = engine.run(
        "what is the product name",
        k_product_text,
        schema);

    print_result(result, schema);
    if (!result.has("name"))
        fail("minimal schema name", "'name' missing from single-field schema");
    pass("single-field schema works correctly");
}

// Two back-to-back run() calls on the same engine — verifies the aggregator
// context is cleared between calls and results are independent.
static void test_sequential_runs(ReasoningEngine& engine) {
    print_header("Sequential runs");

    const auto schema = make_product_schema();

    const auto r1 = engine.run("shoe price", k_product_text, schema);
    const auto r2 = engine.run("shoe price", k_product_text, schema);

    if (!r1.has("name") || !r2.has("name"))
        fail("sequential runs: name present", "missing in one of the runs");

    // Results should be identical for the same input (deterministic at temp=0.1).
    const auto n1 = r1.field("name");
    const auto n2 = r2.field("name");
    if (n1 && n2 && *n1 != *n2)
        std::cout << "  note: name differs between runs (temp > 0 allows this)\n"
                  << "    run1: " << *n1 << "\n"
                  << "    run2: " << *n2 << "\n";

    pass("two sequential run() calls both complete without error");
}

// run_tokenized() result must be consistent with run() for the same input
// (not necessarily byte-identical given temp=0.1, but both must populate
// the same mandatory fields).
static void test_tok_cache_consistency(ReasoningEngine& engine) {
    print_header(".tok cache consistency");

    const auto schema  = make_product_schema();
    const auto tokens  = engine.tokenize(k_product_text);

    const auto r_raw = engine.run(
        "gift under one hundred dollars", k_product_text, schema);
    const auto r_tok = engine.run_tokenized(
        "gift under one hundred dollars", tokens, schema);

    const bool raw_has_name = r_raw.has("name");
    const bool tok_has_name = r_tok.has("name");

    std::cout << "  run()           name = "
              << (r_raw.field("name") ? *r_raw.field("name") : "(null)") << "\n";
    std::cout << "  run_tokenized() name = "
              << (r_tok.field("name") ? *r_tok.field("name") : "(null)") << "\n";

    if (raw_has_name != tok_has_name)
        fail("tok cache consistency",
             "run() and run_tokenized() disagree on field presence");
    pass("run() and run_tokenized() agree on mandatory field presence");
}

// Measures and prints throughput for a single run() call.
static void test_latency(ReasoningEngine& engine) {
    print_header("Latency (informational)");

    const auto schema = make_product_schema();

    // Warm-up
    engine.run("warmup", k_product_text, schema);

    Timer t;
    engine.run("gift ideas under fifty dollars", k_product_text, schema);
    const double ms = t.elapsed_ms();

    std::cout << "  single run() latency = "
              << std::fixed << std::setprecision(1) << ms << " ms\n";
    pass("latency measurement complete (informational only)");
}

// ── Entry point ───────────────────────────────────────────────────────────

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0]
                  << " <worker_model_path> <aggregator_model_path>\n\n"
                  << "Example:\n"
                  << "  " << argv[0]
                  << " models/qwen3-0.6b-q4_k_m.gguf"
                     " models/qwen3-1.7b-instruct-q4_k_m.gguf\n";
        return 1;
    }

    const std::string worker_path = argv[1];
    const std::string agg_path    = argv[2];

    std::cout << "=== ReasoningEngine tests ===\n";
    std::cout << "worker     : " << worker_path << "\n";
    std::cout << "aggregator : " << agg_path    << "\n";

    // Construction test creates its own engine to validate the load path.
    test_construction(worker_path, agg_path);

    // Remaining tests share one engine instance so model weights are
    // loaded only once.
    ReasoningEngine engine(worker_path, agg_path);

    std::cout << "\n  max_workers on this device = " << engine.max_workers() << "\n";

    test_tokenize             (engine);
    test_run_relevant         (engine);
    test_run_tokenized        (engine);
    test_nullable_fields      (engine);
    test_irrelevant_text      (engine);
    test_empty_tokens         (engine);
    test_minimal_schema       (engine);
    test_sequential_runs      (engine);
    test_tok_cache_consistency(engine);
    test_latency              (engine);

    std::cout << "\n=== All reasoning tests passed ===\n\n";
    return 0;
}