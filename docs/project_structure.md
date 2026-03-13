# Project Structure (`project_structure.md`)

---

## Layout

```
tensor-db/
│
├── tql/
│   ├── CMakeLists.txt
│   ├── include/
│   │   └── tensor/
│   │       └── tql/
│   │           ├── pipeline.hpp
│   │           ├── resolver.hpp                (PackageResolver interface)
│   │           ├── stage.hpp
│   │           ├── types.hpp
│   │           ├── TQLLexer.h                  (generated)
│   │           ├── TQLParser.h                 (generated)
│   │           ├── TQLParserVisitor.h          (generated)
│   │           └── TQLParserBaseVisitor.h      (generated)
│   ├── src/
│   │   ├── semantic.hpp                        (internal — declares all pass functions)
│   │   ├── compiler.cpp                        (ANTLR visitor → unverified Pipeline)
│   │   ├── import_resolver.cpp                 (Pass 1 — import resolution)
│   │   ├── scope_checker.cpp                   (Pass 2 — scope resolution + SymbolTable)
│   │   ├── type_checker.cpp                    (Pass 3 — type checking)
│   │   ├── aggregate_checker.cpp               (Pass 4 — aggregate context validation)
│   │   ├── constant_folder.cpp                 (Pass 5 — constant folding)
│   │   ├── TQLLexer.cpp                        (generated)
│   │   ├── TQLParser.cpp                       (generated)
│   │   ├── TQLParserVisitor.cpp                (generated)
│   │   └── TQLParserBaseVisitor.cpp            (generated)
│   └── tests/
│       ├── main.cpp
│       └── scripts/
│           ├── aggregate.tql
│           ├── delete.tql
│           ├── insert.tql
│           ├── query.tql
│           └── update.tql
│
├── storage/
│   ├── CMakeLists.txt
│   ├── include/
│   │   └── tensor/
│   │       └── storage/
│   │           ├── wal.hpp                     # Write-Ahead Log (durability)
│   │           ├── sst.hpp                     # Sorted String Table (row storage)
│   │           ├── page.hpp                    # Page builder/reader (Snappy compression)
│   │           ├── rbm.hpp                     # Roaring Bitmap (inverted index)
│   │           ├── vec.hpp                     # Vector storage (memory-mapped)
│   │           ├── hnsw.hpp                    # HNSW (approximate nearest neighbor)
│   │           ├── tok.hpp                     # Token storage (pre-tokenized arrays)
│   │           └── options.hpp                 # Configuration & tuning parameters
│   ├── src/
│   │   ├── wal.cpp
│   │   ├── sst.cpp
│   │   ├── page.cpp
│   │   ├── rbm.cpp
│   │   ├── vec.cpp
│   │   ├── hnsw.cpp
│   │   └── tok.cpp
│   └── tests/
│       └── main.cpp                            # Integration tests (WAL, SST, RBM, VEC, TOK, HNSW)
│
├── inference/
│   ├── CMakeLists.txt
│   ├── include/
│   │   └── tensor/
│   │       └── inference/
│   │           ├── embed.hpp                   # EmbedEngine — unit-normalised float32 vectors
│   │           └── reasoning.hpp               # ReasoningEngine — grammar-constrained JSON extraction
│   ├── src/
│   │   ├── llama_guard.hpp                     (internal — ensures llama_backend_init() called once)
│   │   ├── embed.cpp
│   │   └── reasoning.cpp
│   └── tests/
│       ├── main_embed.cpp                      # inference-embed-test binary
│       └── main_reasoning.cpp                  # inference-reasoning-test binary
│
├── net/
│   ├── include/
│   │   └── tensor/
│   │       └── net/
│   │           ├── socket.hpp
│   │           ├── quic.hpp
│   │           └── connection.hpp
│   └── src/
│       ├── socket.cpp
│       ├── quic.cpp
│       └── connection.cpp
│
└── db/
    ├── include/
    │   └── tensor/
    │       └── db/
    │           ├── engine.hpp
    │           ├── executor.hpp
    │           ├── iam.hpp
    │           └── cli.hpp
    └── src/
        ├── engine.cpp
        ├── executor.cpp
        ├── iam.cpp
        ├── cli.cpp
        └── main.cpp
```

---

## Namespaces

| Sub-project   | Namespace                 | Owns                                                               |
|---------------|---------------------------|--------------------------------------------------------------------|
| `tql/`        | `tensor::tql`             | ANTLR4 wrappers, pipeline and stage model, five-pass compiler      |
| `storage/`    | `tensor::storage`         | WAL, SST, RBM, VEC, HNSW, TOK — all physical storage modules      |
| `inference/`  | `tensor::inference`       | llama.cpp wrappers for `embed()` and `run()`                       |
| `net/`        | `tensor::net`             | Unix Domain Socket IPC, msquic remote transport, connection model  |
| `db/`         | `tensor::db`              | Engine init, pipeline execution, IAM, CLI                          |

---

## Storage Architecture

The storage layer provides durable, efficient physical storage across six specialized formats:

| Component | Purpose | Data Type | Access Pattern |
|-----------|---------|-----------|-----------------|
| **WAL** | Crash recovery, durability guarantee | Binary records with LSN | Sequential write, recovery replay |
| **SST** | Primary row storage | Snappy-compressed msgpack payloads | Random row lookup, full scan with predicates |
| **Page** | Internal SST abstraction | 4KB uncompressed pages | Read/decompress/scan within page |
| **RBM** | Full-text search index | Roaring bitmaps (token → row IDs) | Bitmap AND/OR for multi-term queries |
| **VEC** | Vector embeddings | Raw float32 arrays (mmap'd) | Dense read for similarity search |
| **TOK** | Pre-tokenized text | int32 token arrays per row | Lookup for context window loading |
| **HNSW** | Approximate nearest neighbor | Graph + vector references | KNN search, hierarchical traversal |

### Dependencies and Data Flow

```
Write Path:
  WAL → SSTBuilder → Page (compress) → Disk
         RBMBuilder → Disk
         VECBuilder → Disk
         TOKBuilder → Disk
         HNSW::insert() → HNSW::save()

Read Path:
  SST::get(row_id) → PageReader (decompress) → msgpack parsing
  SST::scan() → iterate all pages → predicate evaluation
  RBM::get(token) → Roaring bitmap operations
  VEC::data() → direct pointer to mmap'd region
  HNSW::search(query, k) → KNN traversal → row IDs
```

---

## Dependency Flow

```
tql/        →   no dependencies on any other sub-project
storage/    →   no dependencies on any other sub-project
inference/  →   no dependencies on any other sub-project
net/        →   no dependencies on any other sub-project
db/         →   depends on all four — wires them together
```

Nothing flows upward. `db/` is the only integration point.

---

## End Usage

### `tql/` — Compiler

```cpp
#include <tensor/tql/pipeline.hpp>
#include <tensor/tql/resolver.hpp>

using namespace tensor::tql;

// Without a resolver — imports skipped, UserDefined field validation bypassed.
// Variable scope and all structural checks still run.
Result<Pipeline> result = Pipeline::compile(source);

// With a resolver — full five-pass validation including import resolution,
// field existence checks, and type compatibility.
Result<Pipeline> result = Pipeline::compile(source, &my_resolver);

if (!result.ok()) {
    // result.error() carries line, column, and message.
    return result.error();
}

Pipeline pipeline = result.value();

pipeline.target()     // "store/products"
pipeline.from_var()   // "p"
pipeline.type()       // commerce.Product
pipeline.mutation()   // Mutation::None
pipeline.registry()   // PackageRegistry — resolved types from imported packages

for (const Stage& stage : pipeline.stages()) {
    switch (stage.kind()) {
        case Stage::Kind::Filter:   ...
        case Stage::Kind::Join:     ...
        case Stage::Kind::GroupBy:  ...
        case Stage::Kind::Having:   ...
        case Stage::Kind::Let:      ...
        case Stage::Kind::Project:  ...
        case Stage::Kind::OrderBy:  ...
        case Stage::Kind::Limit:    ...
    }
}
```

#### Compiler pass summary

| Pass | File                    | Input              | Validates / produces                                   |
|------|-------------------------|--------------------|--------------------------------------------------------|
| 0    | ANTLR (generated)       | source text        | Parse tree; syntax errors with line/column             |
| 1    | `import_resolver.cpp`   | parse tree         | `PackageRegistry` — loads and registers package types  |
| 2    | `scope_checker.cpp`     | stage list         | `SymbolTable` — variable scope, field existence        |
| 3    | `type_checker.cpp`      | stage list + sym   | Type compatibility, predicate bool, arithmetic types   |
| 4    | `aggregate_checker.cpp` | stage list         | Aggregate context rules, having without group by       |
| 5    | `constant_folder.cpp`   | stage list         | Collapses literal expressions at compile time          |

#### db::Engine implements PackageResolver

```cpp
// db/engine.hpp
class Engine : public tensor::tql::PackageResolver {
public:
    tensor::tql::Result<std::string> resolve(std::string_view import_path) override;
    // Loads .tql package files from the configured package root directory.
};
```

#### What the engine is still responsible for at runtime

- Path existence — does `"store/products"` name a live `create table` path
- IAM permission checks — does the API key's role allow this operation
- Vector dimension matching — `embed()` output dimension vs. the field's declared `vector(n)`
- Role name uniqueness on `create role`

---

### `storage/` — Physical Storage

```cpp
#include <tensor/storage/wal.hpp>
#include <tensor/storage/sst.hpp>
#include <tensor/storage/rbm.hpp>
#include <tensor/storage/vec.hpp>
#include <tensor/storage/hnsw.hpp>
#include <tensor/storage/tok.hpp>

using namespace tensor::storage;

// Write-Ahead Log
WAL wal("store/products/.wal");
wal.append(record);
wal.flush();

// Sorted String Table
SSTBuilder sst_builder("store/products/.sst");
uint32_t row_id = sst_builder.append(msgpack_row);
sst_builder.finish();

SST sst("store/products/.sst");
auto row = sst.get(row_id);
auto results = sst.scan("status", Predicate::Eq("completed"));

// Inverted Index
RBMBuilder rbm_builder("store/products/.rbm");
rbm_builder.add("keyword", row_id);
rbm_builder.finish();

RBM rbm("store/products/.rbm");
Roaring matches = rbm.get("kernel") & rbm.get("panic");

// Vector Storage (memory-mapped)
VECBuilder vec_builder("store/products/.vec");
vec_builder.append(vector_ptr, dim);
vec_builder.finish();

VEC vec("store/products/.vec");
const float* vectors = vec.data();
size_t total_bytes = vec.file_size();

// Token Storage
TOKBuilder tok_builder("store/products/.tok", "gpt2");
tok_builder.append(row_id, token_array);
tok_builder.finish();

TOK tok("store/products/.tok", "gpt2");
auto tokens = tok.get(row_id);

// Approximate Nearest Neighbor
HNSW hnsw("store/products/.hnsw", 768);
hnsw.insert(row_id, vector_ptr);
hnsw.save();

auto matches = hnsw.search(query_vec, k);
for (const auto& match : matches) {
    uint32_t row_id = match.row_id;
    float distance = match.distance;
}
```

---

### `inference/` — Embed & Reasoning

```cpp
#include <tensor/inference/embed.hpp>
#include <tensor/inference/reasoning.hpp>

using namespace tensor::inference;

// ── Embedding ─────────────────────────────────────────────────────────────
// One engine per EmbedConstant. Each maps to a different model and task prefix.
//
//   Search   → nomic-embed-text-v1.5   (768-d, "search_query: " prefix)
//   Classify → all-MiniLM-L6-v2        (384-d, no prefix)
//   Code     → jina-embeddings-v2-base-code (768-d, "search_query: " prefix)
//
// Returns a unit-normalised float32 vector.

EmbedEngine embed("models/nomic-embed-text-v1.5.gguf");
std::vector<float> vec = embed.run("gift ideas under fifty dollars",
                                    EmbedConstant::Search);
int32_t dims = embed.dimensions();  // 768


// ── Reasoning ─────────────────────────────────────────────────────────────
// Two-model pipeline: worker fans out over 28k-token segments in parallel,
// aggregator synthesises results into grammar-constrained JSON.
//
//   Worker      — Qwen3-0.6B Q4_K_M       (~400 MB)  plain prose extraction
//   Aggregator  — Qwen3-1.7B-Instruct Q4_K_M (~1.1 GB) structured JSON output
//
// Worker count is computed at construction time from device memory remaining
// after both models are loaded. Use max_workers() to inspect.

ReasoningEngine reasoning(
    "models/qwen3-0.6b-q4_k_m.gguf",
    "models/qwen3-1.7b-instruct-q4_k_m.gguf"
);

size_t workers = reasoning.max_workers();  // computed from available VRAM/RAM

// Run over raw text — tokenizes internally.
OutputSchema schema{
    "ProductResult",
    {
        { "name",   "text",    false },
        { "price",  "float64", false },
        { "reason", "text",    true  },
    }
};

ReasoningResult result = reasoning.run("gift ideas under fifty dollars",
                                        raw_text, schema);
result.field("name");    // std::optional<std::string>
result.field("price");
result.field("reason");  // nullopt if model produced no value

// Run over pre-tokenized input from a .tok file — skips tokenization.
std::vector<int32_t> tokens = reasoning.tokenize(raw_text);  // call at write time
ReasoningResult result2 = reasoning.run_tokenized("gift ideas", tokens, schema);
```

#### Default models

| Role        | Model                      | Quant   | Size    |
|-------------|----------------------------|---------|---------|
| Worker      | Qwen3-0.6B                 | Q4_K_M  | ~400 MB |
| Aggregator  | Qwen3-1.7B-Instruct        | Q4_K_M  | ~1.1 GB |
| Aggregator+ | Qwen3-4B-Instruct (upgrade)| Q4_K_M  | ~2.6 GB |
| Search      | nomic-embed-text-v1.5      | Q4_K_M  | ~80 MB  |
| Classify    | all-MiniLM-L6-v2           | Q8_0    | ~25 MB  |
| Code        | jina-embeddings-v2-base-code | F16   | ~354 MB |

#### Internal notes

- `llama_guard.hpp` is an internal-only header (not installed). It ensures
  `llama_backend_init()` is called exactly once per process via `std::call_once`,
  regardless of how many engine instances are constructed.
- KV cache is cleared between runs via `llama_memory_clear(llama_get_memory(ctx), false)`.
- The grammar sampler (`llama_sampler_init_grammar`) enforces the `OutputSchema`
  as GBNF at token-selection time — the aggregator output is structurally valid
  JSON without post-generation parsing.
- `ReasoningEngine::tokenize()` is called by `db::executor` at write time to
  populate `.tok` files. `run_tokenized()` loads from those files at query time,
  skipping re-tokenization.

---

### `net/` — Transport

```cpp
#include <tensor/net/socket.hpp>
#include <tensor/net/quic.hpp>

using namespace tensor::net;

UnixSocket sock("/tmp/tensordb.sock");
sock.listen();
sock.on_pipeline([](Connection& conn, std::string_view source) {
    conn.stream(row);
    conn.complete();
});

QuicListener quic(port, tls_config);
quic.listen();
quic.on_pipeline([](Connection& conn, std::string_view source) {
    conn.stream(row);
    conn.complete();
});
```

---

## Notes

**`tql/include/tensor/tql/pipeline.hpp`** is the single public entry point.
`Pipeline::compile(source, resolver?)` runs all five passes and returns either a
fully validated, constant-folded `Pipeline` or an `Error` with line/column/message.

**`tql/include/tensor/tql/resolver.hpp`** declares the `PackageResolver` interface.
`db::Engine` implements it by loading `.tql` package files from the configured
package root. Passing `nullptr` skips import resolution — variable scope and
structural checks still run; UserDefined field validation is bypassed.

**`tql/src/semantic.hpp`** is an internal header. It declares the `SymbolTable`
struct and all five pass functions. It is not installed and is never included by
any public header.

**ANTLR4 generated files** (`TQLLexer`, `TQLParser`, `TQLParserVisitor`,
`TQLParserBaseVisitor` — `.h` and `.cpp`) are generated at build time from
`TQLLexer.g4` and `TQLParser.g4`. They are not checked in.

**`tql/tests/main.cpp`** is the `tql-test` binary. It calls `Pipeline::compile()`
without a resolver — imports are skipped, the five passes still run on scope,
types, aggregates, and constants.

**`storage/tests/main.cpp`** is the `storage_tests` binary. It demonstrates all
six storage modules (WAL, SST, RBM, VEC, TOK, HNSW) with write and read operations,
validating durability and correctness.

**`inference/src/llama_guard.hpp`** is an internal header, never installed.
It wraps `llama_backend_init()` in a `std::call_once` guard so multiple engine
instances in the same process do not double-initialise the llama.cpp backend.

**`inference/tests/main_embed.cpp`** is the `inference-embed-test` binary.
Run with: `./inference-embed-test <model_path> [search|classify|code]`

**`inference/tests/main_reasoning.cpp`** is the `inference-reasoning-test` binary.
Run with: `./inference-reasoning-test <worker_model> <aggregator_model>`

**`db/executor.cpp`** walks the compiled `Pipeline` stages and dispatches to
`storage/` and `inference/`. It receives a fully resolved, type-checked Pipeline
and does not re-derive types or validate scope.

**`db/engine.cpp`** owns instance-level setup and implements `PackageResolver`.
It passes itself to `Pipeline::compile()` so package files are resolved from disk.

**`cli/`** lives inside `db/` as a leaf. Nothing outside `db/` depends on it.