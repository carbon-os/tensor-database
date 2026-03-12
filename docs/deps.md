# Dependencies (`deps.md`)

---

## Philosophy

One library, one job, no transitive bloat. Every dependency listed here is either header-only,
a near-single-file amalgamation, or a full build that earns its place by owning an entire
subsystem that would be worse to reimplement. The storage design, query planner, wire protocol,
and inference pipeline are all written from scratch — dependencies cover exactly the primitives
that would be worse to reimplement than to adopt.

---

## Query Language

### ANTLR4 — TQL Parser

**[ANTLR4](https://github.com/antlr/antlr4)**
Parser and lexer generator for the Tensor Query Language. The `.tql` grammar is defined once
in an `.g4` file — ANTLR generates the C++ lexer, parser, and visitor scaffolding from it.
The generated visitor pattern maps cleanly onto AST construction, which feeds directly into
the query planner.

ANTLR4's C++ runtime is a full library build rather than header-only, but it earns that
position. Writing and maintaining a hand-rolled recursive descent parser for TQL's full
syntax — pipeline stages, type annotations, `prompt()`, `embed()`, join paths, `group by`,
`having`, `upsert` conflict blocks — would be a significant ongoing burden. The `.g4` file
doubles as the authoritative language specification.

The runtime's threading overhead is a non-issue here since the daemon is long-running.
Parsing happens once per pipeline, then the AST is handed off to the planner and discarded.

```cpp
#include <antlr4-runtime.h>
#include "TQLLexer.h"
#include "TQLParser.h"
#include "TQLVisitor.h"

antlr4::ANTLRInputStream input(pipeline_source);
TQLLexer lexer(&input);
antlr4::CommonTokenStream tokens(&lexer);
TQLParser parser(&tokens);

// Parse the pipeline — fails fast on syntax errors before touching any data
TQLParser::PipelineContext* tree = parser.pipeline();

// Walk the AST to build the query plan
TQLVisitor visitor;
visitor.visit(tree);
```

---

## Inference & Embeddings

### llama.cpp

**[llama.cpp](https://github.com/ggerganov/llama.cpp)**
The inference backend for both the embedding engine and the reasoning engine. Handles model
loading, GGUF quantized weight formats, KV cache management, batched inference, and GPU
offload. The nano worker models and aggregator model for `prompt()` run entirely through
llama.cpp. The `embed()` call dispatches through its embeddings API.

Not header-only — llama.cpp is a full build, but it is self-contained with no external
dependencies beyond a C++17 compiler and optional CUDA/Metal backends. It is the only library
in this stack that owns a full subsystem rather than a single primitive, and it earns that
position.

```cpp
#include "llama.h"

// Load a GGUF model
llama_model_params model_params = llama_model_default_params();
model_params.n_gpu_layers = 99; // offload all layers to GPU
llama_model* model = llama_load_model_from_file(
    "models/qwen2.5-0.5b-q4_k_m.gguf", model_params
);

// Create an inference context
llama_context_params ctx_params = llama_context_default_params();
ctx_params.n_ctx = 32768; // 32k token context window for nano workers
llama_context* ctx = llama_new_context_with_model(model, ctx_params);

// Embeddings path — used by embed()
llama_context_params embed_params = llama_context_default_params();
embed_params.embeddings = true;
llama_context* embed_ctx = llama_new_context_with_model(model, embed_params);
```

The worker model pool for `prompt()` loads one copy of the nano weights and forks shared
contexts from it — llama.cpp's context model maps cleanly onto the nano+aggregator
architecture. See `reasoning.md` for capacity planning details.

---

## Networking

### msquic

**[msquic](https://github.com/microsoft/msquic)**
Microsoft's production QUIC implementation, used for all remote connections to the daemon.
Provides low-latency multiplexed streams over UDP without TCP head-of-line blocking — which
matters when streaming large result sets or running many concurrent pipelines from remote
clients. TLS 1.3 is built in.

msquic is a full shared library build, not header-only, but it ships with a stable C API and
has no transitive dependencies that bleed into the rest of the engine.

```cpp
#include <msquic.h>

// Load the QUIC API table
const QUIC_API_TABLE* MsQuic;
MsQuicOpen2(&MsQuic);

// Configure the listener — binds to the remote QUIC port
HQUIC Registration;
QUIC_REGISTRATION_CONFIG reg_config = { "tensordb", QUIC_EXECUTION_PROFILE_LOW_LATENCY };
MsQuic->RegistrationOpen(&reg_config, &Registration);

// Each incoming stream maps to one .tql pipeline execution
// Results are streamed back over the same stream as newline-delimited JSON
```

Local access continues to use the Unix Domain Socket directly — msquic is only in the path
for connections crossing a network boundary. See `query_networking.md` for the full transport
model.

---

## Storage

### Snappy — `.sst` block compression

**[Snappy](https://github.com/google/snappy)**
Page-level block compression on individual SST pages. No dependencies, extremely fast
encode/decode, designed for CPU efficiency over maximum ratio — the right tradeoff for a hot
storage path.

```cpp
#include <snappy.h>

std::string compressed;
snappy::Compress(page_data.data(), page_data.size(), &compressed);

std::string decompressed;
snappy::Uncompress(compressed.data(), compressed.size(), &decompressed);
```

---

### CRoaring — `.rbm` inverted index

**[CRoaring](https://github.com/RoaringBitmap/CRoaring)**
The canonical C/C++ Roaring Bitmap implementation. Single-file amalgamation (`roaring.h` +
`roaring.c`) — drop it in and it is ready. Used for the full-text inverted index: keyword
queries resolve to a hardware-level bitwise AND across compressed bitmap sets, no text
scanning occurs.

```cpp
#include <roaring/roaring.hh>

roaring::Roaring kernel_rows = index.get("kernel");
roaring::Roaring panic_rows  = index.get("panic");
roaring::Roaring result      = kernel_rows & panic_rows;

for (uint32_t row_id : result) {
    // fetch row from .sst by row_id
}
```

---

### hnswlib — `.hnsw` approximate nearest-neighbor

**[hnswlib](https://github.com/nmslib/hnswlib)**
Header-only C++, written by the HNSW paper authors. Zero dependencies. Covers the standard
ANN search case cleanly.

```cpp
#include <hnswlib/hnswlib.h>

hnswlib::L2Space space(768);
hnswlib::HierarchicalNSW<float> index(&space, max_elements, M, ef_construction);

index.addPoint(vector_ptr, row_id);
auto results = index.searchKnn(query_vector_ptr, k);
```

**usearch** is the alternative if int8 scalar quantization becomes necessary to control
`.hnsw` index memory footprint at scale. Otherwise hnswlib is simpler. **Avoid FAISS** —
GPU-oriented, batch-workload assumptions, orders of magnitude larger than either option.

---

### POSIX `mmap` — `.vec` zero-copy reads

No library. Vectors are raw `float32` binary blobs and zero-copy read access is `mmap`
directly.

```cpp
#include <sys/mman.h>

int fd = open("store/products.vec", O_RDONLY);
float* vectors = static_cast<float*>(
    mmap(nullptr, file_size, PROT_READ, MAP_SHARED, fd, 0)
);

madvise(vectors, file_size, MADV_RANDOM);     // HNSW graph traversal
madvise(vectors, file_size, MADV_SEQUENTIAL); // linear scan fallback
```

---

## Supporting Libraries

### crc32c — WAL checksums

**[crc32c](https://github.com/google/crc32c)**
Used in the `.wal` record format to detect corruption on replay. SSE4.2 hardware intrinsics
when available, software fallback otherwise.

```cpp
#include <crc32c/crc32c.h>
uint32_t checksum = crc32c::Crc32c(record_data, record_size);
```

---

### simdjson — `json<T>` ingestion

**[simdjson](https://github.com/simdjson/simdjson)**
Used at the storage boundary to validate and parse `json<T>` typed fields before encoding to
msgpack and writing to the `.wal`. SIMD-based, single-header option available, zero
dependencies.

```cpp
#include <simdjson.h>
simdjson::dom::parser parser;
simdjson::dom::element doc = parser.parse(json_input);
```

---

### msgpack-cxx — `json<T>` internal encoding

**[msgpack-cxx](https://github.com/msgpack/msgpack-c)**
`json<T>` fields are stored internally as binary msgpack rather than raw JSON text —
eliminates re-parsing on every read and reduces storage size. Decoded back to JSON only at
the `select` projection stage. Header-only.

```cpp
#include <msgpack.hpp>

msgpack::sbuffer buffer;
msgpack::pack(buffer, your_object);

msgpack::object_handle handle = msgpack::unpack(buffer.data(), buffer.size());
```

---

## Dependency Summary

```
tensor-db
│
├── query         antlr4             (TQL lexer, parser, AST visitor)
├── inference     llama.cpp          (embed() + prompt() — nano workers + aggregator)
├── networking    msquic             (remote QUIC transport)
│
├── .wal          crc32c
├── .sst          snappy
├── .rbm          CRoaring
├── .vec          mmap (POSIX — no library)
├── .hnsw         hnswlib            (or usearch for quantization)
│
└── json<T>       simdjson  (parse) + msgpack-cxx  (store)
```