# Project Structure (`project_structure.md`)

---

## Layout

```
tensor-db/
│
├── tql/
│   ├── include/
│   │   └── tensor/
│   │       └── tql/
│   │           ├── ast.hpp
│   │           ├── lexer.hpp
│   │           ├── parser.hpp
│   │           ├── pipeline.hpp
│   │           ├── stage.hpp
│   │           ├── result.hpp
│   │           └── types.hpp
│   └── src/
│       ├── ast.cpp
│       ├── lexer.cpp
│       ├── parser.cpp
│       ├── pipeline.cpp
│       └── stage.cpp
│
├── storage/
│   ├── include/
│   │   └── tensor/
│   │       └── storage/
│   │           ├── wal.hpp
│   │           ├── sst.hpp
│   │           ├── rbm.hpp
│   │           ├── vec.hpp
│   │           ├── hnsw.hpp
│   │           └── tok.hpp
│   └── src/
│       ├── wal.cpp
│       ├── sst.cpp
│       ├── rbm.cpp
│       ├── vec.cpp
│       ├── hnsw.cpp
│       └── tok.cpp
│
├── inference/
│   ├── include/
│   │   └── tensor/
│   │       └── inference/
│   │           ├── embed.hpp
│   │           └── reasoning.hpp
│   └── src/
│       ├── embed.cpp
│       └── reasoning.cpp
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
| `tql/`        | `tensor::tql`             | ANTLR4 wrappers, AST, pipeline and stage model, compile-time types |
| `storage/`    | `tensor::storage`         | WAL, SST, RBM, VEC, HNSW, TOK — all physical storage modules      |
| `inference/`  | `tensor::inference`       | llama.cpp wrappers for `embed()` and `prompt()`                    |
| `net/`        | `tensor::net`             | Unix Domain Socket IPC, msquic remote transport, connection model  |
| `db/`         | `tensor::db`              | Engine init, pipeline execution, IAM, CLI                          |

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

using namespace tensor::tql;

Result<Pipeline> result = Pipeline::compile(source);
if (!result.ok()) return result.error();

Pipeline pipeline = result.value();

pipeline.target()      // "store/products"
pipeline.type()        // commerce.Product
pipeline.mutation()    // Mutation::None

for (const Stage& stage : pipeline.stages()) {
    switch (stage.kind()) {
        case Stage::Kind::Filter:
        case Stage::Kind::TextMatch:
        case Stage::Kind::Embed:
        case Stage::Kind::Prompt:
        case Stage::Kind::Project:
        case Stage::Kind::OrderBy:
        case Stage::Kind::Limit:
    }
}
```

---

### `storage/` — Physical Storage

```cpp
#include <tensor/storage/wal.hpp>
#include <tensor/storage/sst.hpp>
#include <tensor/storage/rbm.hpp>
#include <tensor/storage/vec.hpp>
#include <tensor/storage/hnsw.hpp>

using namespace tensor::storage;

// WAL — write before anything else touches disk
WAL wal("store/products/.wal");
wal.append(record);
wal.flush();

// SST — scalar reads, predicate pushdown
SST sst("store/products/.sst");
sst.scan("status", Predicate::Eq("completed"));
sst.get(row_id);

// RBM — full-text keyword resolution
RBM rbm("store/products/.rbm");
Roaring result = rbm.get("kernel") & rbm.get("panic");

// VEC — zero-copy mmap read
VEC vec("store/products/.vec");
const float* vectors = vec.data();   // raw mmap pointer, ready for HNSW

// HNSW — approximate nearest-neighbor over .vec
HNSW hnsw("store/products/.hnsw", 768);
hnsw.insert(row_id, vector_ptr);
auto matches = hnsw.search(query_vec, k);  // returns row IDs
```

---

### `inference/` — Embed & Reasoning

```cpp
#include <tensor/inference/embed.hpp>
#include <tensor/inference/reasoning.hpp>

using namespace tensor::inference;

// Embed — called when pipeline hits Stage::Kind::Embed
EmbedEngine embed("models/nomic-embed-text-v1.5.gguf");

std::vector<float> vec = embed.run("gift ideas under fifty dollars", Constant::Search);
// vec.size() == 768, ready to drop into HNSW search

// Reasoning — called when pipeline hits Stage::Kind::Prompt
ReasoningEngine reasoning(
    "models/qwen2.5-0.5b-q4_k_m.gguf",       // nano worker
    "models/qwen2.5-3b-instruct-q4_k_m.gguf"  // aggregator
);

ReasoningResult result = reasoning.run(
    "gift ideas under fifty dollars",  // prompt
    raw_text,                          // p.raw_data content
    output_schema                      // commerce.ProductResult — output contract
);

result.field("name");    // tensor::tql::Value — flows back into pipeline as typed field
result.field("price");
result.field("reason");
```

---

### `net/` — Transport

```cpp
#include <tensor/net/socket.hpp>
#include <tensor/net/quic.hpp>

using namespace tensor::net;

// Unix Domain Socket — local clients
UnixSocket sock("/tmp/tensordb.sock");
sock.listen();

sock.on_pipeline([](Connection& conn, std::string_view source) {
    // source is the raw .tql string off the wire
    // hand it to tql::Pipeline::compile(), execute, stream rows back
    conn.stream(row);        // newline-delimited JSON rows
    conn.complete();         // 0x43 CommandComplete envelope
});

// QUIC — remote clients
QuicListener quic(port, tls_config);
quic.listen();

quic.on_pipeline([](Connection& conn, std::string_view source) {
    // identical handler — same wire format, same execution path
    conn.stream(row);
    conn.complete();
});
```

---

## Notes

**`tql/types.hpp`** defines the core type enum (`int32`, `uuid`, `text`, `vector(n)`, etc.)
and `Result<T>` — shared across the compiler internals. These are TQL-level types only,
not storage representations.

**`db/executor.cpp`** is where the compiled `tensor::tql::Pipeline` meets storage and
inference. It walks the pipeline stages and dispatches to the appropriate sub-project.

**`db/engine.cpp`** owns instance-level setup — opening storage paths, booting the inference
engine, binding the socket and QUIC port.

**ANTLR4 generated files** (`TQLLexer.cpp`, `TQLParser.cpp`, `TQLVisitor.cpp`) are generated
into `tql/src/` at build time. They are not checked in — the `.g4` grammar is the source of
truth.

**`cli/`** lives inside `db/` as a leaf. Nothing outside of `db/` depends on it.