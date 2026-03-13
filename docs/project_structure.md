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
| `tql/`        | `tensor::tql`             | ANTLR4 wrappers, pipeline and stage model, five-pass compiler      |
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

using namespace tensor::storage;

WAL wal("store/products/.wal");
wal.append(record);
wal.flush();

SST sst("store/products/.sst");
sst.scan("status", Predicate::Eq("completed"));
sst.get(row_id);

RBM rbm("store/products/.rbm");
Roaring result = rbm.get("kernel") & rbm.get("panic");

VEC vec("store/products/.vec");
const float* vectors = vec.data();

HNSW hnsw("store/products/.hnsw", 768);
hnsw.insert(row_id, vector_ptr);
auto matches = hnsw.search(query_vec, k);
```

---

### `inference/` — Embed & Reasoning

```cpp
#include <tensor/inference/embed.hpp>
#include <tensor/inference/reasoning.hpp>

using namespace tensor::inference;

EmbedEngine embed("models/nomic-embed-text-v1.5.gguf");
std::vector<float> vec = embed.run("gift ideas under fifty dollars", Constant::Search);

ReasoningEngine reasoning(
    "models/qwen2.5-0.5b-q4_k_m.gguf",
    "models/qwen2.5-3b-instruct-q4_k_m.gguf"
);
ReasoningResult result = reasoning.run("gift ideas under fifty dollars",
                                        raw_text, output_schema);
result.field("name");
result.field("price");
result.field("reason");
```

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

**`db/executor.cpp`** walks the compiled `Pipeline` stages and dispatches to
`storage/` and `inference/`. It receives a fully resolved, type-checked Pipeline
and does not re-derive types or validate scope.

**`db/engine.cpp`** owns instance-level setup and implements `PackageResolver`.
It passes itself to `Pipeline::compile()` so package files are resolved from disk.

**`cli/`** lives inside `db/` as a leaf. Nothing outside `db/` depends on it.