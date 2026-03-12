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

| Sub-project   | Namespace                 | Owns                                                              |
|---------------|---------------------------|-------------------------------------------------------------------|
| `tql/`        | `tensor::tql`             | ANTLR4 wrappers, AST, pipeline and stage model, compile-time types |
| `storage/`    | `tensor::storage`         | WAL, SST, RBM, VEC, HNSW, TOK — all physical storage modules     |
| `inference/`  | `tensor::inference`       | llama.cpp wrappers for `embed()` and `prompt()`                   |
| `net/`        | `tensor::net`             | Unix Domain Socket IPC, msquic remote transport, connection model |
| `db/`         | `tensor::db`              | Engine init, pipeline execution, IAM, CLI                         |

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