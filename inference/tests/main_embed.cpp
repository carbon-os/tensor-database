// inference/tests/main_embed.cpp
// Tests for EmbedEngine — run with:
//   ./inference-embed-test <model_path> [constant]
//
// Example:
//   ./inference-embed-test models/nomic-embed-text-v1.5.gguf search
//   ./inference-embed-test models/all-MiniLM-L6-v2.gguf classify
//   ./inference-embed-test models/jina-embeddings-v2-base-code.gguf code

#include <tensor/inference/embed.hpp>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

using namespace tensor::inference;

// ── Helpers ───────────────────────────────────────────────────────────────

static float cosine_similarity(const std::vector<float>& a,
                                const std::vector<float>& b) {
    assert(a.size() == b.size());
    float dot = 0.0f, na = 0.0f, nb = 0.0f;
    for (size_t i = 0; i < a.size(); ++i) {
        dot += a[i] * b[i];
        na  += a[i] * a[i];
        nb  += b[i] * b[i];
    }
    if (na == 0.0f || nb == 0.0f) return 0.0f;
    return dot / (std::sqrt(na) * std::sqrt(nb));
}

static float l2_norm(const std::vector<float>& v) {
    float sum = 0.0f;
    for (float x : v) sum += x * x;
    return std::sqrt(sum);
}

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

// ── Tests ─────────────────────────────────────────────────────────────────

// Construction must not throw for a valid model path.
static void test_construction(const std::string& model_path) {
    print_header("Construction");
    try {
        EmbedEngine engine(model_path);
        pass("loads model without throwing");

        const int32_t dims = engine.dimensions();
        if (dims <= 0)
            fail("dimensions > 0", "got " + std::to_string(dims));
        std::cout << "  dimensions = " << dims << "\n";
        pass("dimensions() returns positive value");
    } catch (const std::exception& e) {
        fail("construction", e.what());
    }
}

// Output vector length must match dimensions().
static void test_output_shape(EmbedEngine& engine, EmbedConstant constant) {
    print_header("Output shape");

    const auto vec = engine.run("hello world", constant);
    const int32_t dims = engine.dimensions();

    if (static_cast<int32_t>(vec.size()) != dims)
        fail("vector length == dimensions()",
             "got " + std::to_string(vec.size()) +
             " expected " + std::to_string(dims));
    pass("vector length matches dimensions()");
}

// Output must be a unit vector (L2 norm ≈ 1.0).
static void test_unit_norm(EmbedEngine& engine, EmbedConstant constant) {
    print_header("Unit normalisation");

    const auto vec = engine.run("the quick brown fox", constant);
    const float norm = l2_norm(vec);

    std::cout << "  L2 norm = " << std::fixed << std::setprecision(6) << norm << "\n";

    if (std::abs(norm - 1.0f) > 1e-4f)
        fail("L2 norm ≈ 1.0", "got " + std::to_string(norm));
    pass("output vector is unit-normalised");
}

// Same input twice must produce identical output (deterministic).
static void test_determinism(EmbedEngine& engine, EmbedConstant constant) {
    print_header("Determinism");

    const std::string text = "repeat this exact string";
    const auto a = engine.run(text, constant);
    const auto b = engine.run(text, constant);

    if (a.size() != b.size())
        fail("determinism size", "vectors have different lengths");

    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i])
            fail("determinism values",
                 "differ at index " + std::to_string(i));
    }
    pass("identical input produces identical output");
}

// Semantically similar sentences should score higher than dissimilar ones.
static void test_semantic_ordering(EmbedEngine& engine, EmbedConstant constant) {
    print_header("Semantic ordering");

    const auto anchor   = engine.run("waterproof running shoes", constant);
    const auto similar  = engine.run("trail shoes for wet weather", constant);
    const auto unrelated = engine.run("chocolate birthday cake recipe", constant);

    const float sim_score  = cosine_similarity(anchor, similar);
    const float diff_score = cosine_similarity(anchor, unrelated);

    std::cout << "  anchor <-> similar   = "
              << std::fixed << std::setprecision(4) << sim_score << "\n";
    std::cout << "  anchor <-> unrelated = "
              << std::fixed << std::setprecision(4) << diff_score << "\n";

    if (sim_score <= diff_score)
        fail("semantic ordering",
             "similar pair did not outscore unrelated pair");
    pass("similar texts score higher than unrelated texts");
}

// Different texts must not collapse to the same vector.
static void test_distinct_outputs(EmbedEngine& engine, EmbedConstant constant) {
    print_header("Distinct outputs");

    const auto a = engine.run("machine learning", constant);
    const auto b = engine.run("medieval history", constant);

    const float sim = cosine_similarity(a, b);
    std::cout << "  cosine similarity = "
              << std::fixed << std::setprecision(4) << sim << "\n";

    if (sim > 0.99f)
        fail("distinct outputs", "unrelated texts collapsed to near-identical vectors");
    pass("different inputs produce meaningfully different vectors");
}

// Empty string should not crash — just return a valid unit vector.
static void test_empty_input(EmbedEngine& engine, EmbedConstant constant) {
    print_header("Empty input");
    try {
        const auto vec = engine.run("", constant);
        if (vec.empty())
            fail("empty input returns non-empty vector", "got empty vector");
        pass("empty string does not crash");
    } catch (const std::exception& e) {
        // Acceptable for some models to throw on empty input — just note it.
        std::cout << "  note: empty input threw: " << e.what() << "\n";
        pass("empty string throws cleanly (acceptable)");
    }
}

// Long input should truncate gracefully rather than crash.
static void test_long_input(EmbedEngine& engine, EmbedConstant constant) {
    print_header("Long input (truncation)");

    // ~2000 words of repeated filler — well above typical 512-token cap.
    std::string long_text;
    long_text.reserve(12000);
    for (int i = 0; i < 300; ++i)
        long_text += "the quick brown fox jumps over the lazy dog ";

    try {
        const auto vec = engine.run(long_text, constant);
        if (static_cast<int32_t>(vec.size()) != engine.dimensions())
            fail("long input output shape", "wrong dimension count");
        const float norm = l2_norm(vec);
        if (std::abs(norm - 1.0f) > 1e-4f)
            fail("long input unit norm", "got " + std::to_string(norm));
        pass("long input truncates and returns valid unit vector");
    } catch (const std::exception& e) {
        fail("long input", e.what());
    }
}

// All three constants must produce valid output from the same engine instance.
static void test_all_constants(EmbedEngine& engine) {
    print_header("All EmbedConstant values");

    const std::string text = "open source software license";
    for (auto c : { EmbedConstant::Search,
                    EmbedConstant::Classify,
                    EmbedConstant::Code }) {
        const auto vec = engine.run(text, c);
        if (static_cast<int32_t>(vec.size()) != engine.dimensions())
            fail("constant output shape", "wrong dimension for constant");
        const float norm = l2_norm(vec);
        if (std::abs(norm - 1.0f) > 1e-4f)
            fail("constant unit norm", "not normalised for constant");
    }
    pass("Search, Classify, Code all return valid unit vectors");
}

// Default constant (no second arg) must behave identically to Search.
static void test_default_constant(EmbedEngine& engine) {
    print_header("Default constant");

    const std::string text = "default constant test";
    const auto with_default  = engine.run(text);
    const auto with_explicit = engine.run(text, EmbedConstant::Search);

    if (with_default.size() != with_explicit.size())
        fail("default constant size", "size mismatch");

    for (size_t i = 0; i < with_default.size(); ++i) {
        if (with_default[i] != with_explicit[i])
            fail("default constant values",
                 "differ at index " + std::to_string(i));
    }
    pass("default constant is identical to explicit Search");
}

// ── Entry point ───────────────────────────────────────────────────────────

static EmbedConstant parse_constant(const char* s) {
    if (!s || std::strcmp(s, "search")   == 0) return EmbedConstant::Search;
    if (       std::strcmp(s, "classify") == 0) return EmbedConstant::Classify;
    if (       std::strcmp(s, "code")     == 0) return EmbedConstant::Code;
    std::cerr << "Unknown constant '" << s
              << "' — expected search / classify / code\n";
    std::exit(1);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0]
                  << " <model_path> [search|classify|code]\n";
        return 1;
    }

    const std::string  model_path = argv[1];
    const EmbedConstant constant  = parse_constant(argc >= 3 ? argv[2] : nullptr);

    std::cout << "=== EmbedEngine tests ===\n";
    std::cout << "model   : " << model_path << "\n";
    std::cout << "constant: " << (argc >= 3 ? argv[2] : "search (default)") << "\n";
    std::cout << "\n";

    // Construction test creates its own engine to validate the load path.
    test_construction(model_path);

    // Remaining tests share one engine instance.
    EmbedEngine engine(model_path);

    test_output_shape     (engine, constant);
    test_unit_norm        (engine, constant);
    test_determinism      (engine, constant);
    test_semantic_ordering(engine, constant);
    test_distinct_outputs (engine, constant);
    test_empty_input      (engine, constant);
    test_long_input       (engine, constant);
    test_all_constants    (engine);
    test_default_constant (engine);

    std::cout << "\n=== All embed tests passed ===\n\n";
    return 0;
}