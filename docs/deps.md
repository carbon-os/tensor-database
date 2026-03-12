# Dependencies (`deps.md`)

---

## Philosophy

One library, one job, no transitive bloat. Every dependency listed here is either header-only or a near-single-file amalgamation. The storage design, query planner, wire protocol, and inference pipeline are all written from scratch — dependencies cover exactly the primitives that would be worse to reimplement than to adopt.

---

## Inference & Embeddings

### llama.cpp

**[llama.cpp](https://github.com/ggerganov/llama.cpp)**
The inference backend for both the embedding engine and the reasoning engine. Handles model loading, GGUF quantized weight formats, KV cache management, batched inference, and GPU offload. The nano worker models and aggregator model for `prompt()` run entirely through llama.cpp. The `embed()` call dispatches through its embeddings API.

Single-header option is not available — llama.cpp is a full build, but it is self-contained with no external dependencies beyond a C++17 compiler and optional CUDA/Metal backends. It is the only library in this stack that owns a full subsystem rather than a single primitive, and it earns that position.

```cpp
#include "llama.h"

// Load a GGUF model
llama_model_params model_params = llama_model_default_params();
model_params.n_gpu_layers = 99; // offload all layers to GPU
llama_model* model = llama_load_model_from_file("models/qwen2.5-0.5b-q4_k_m.gguf", model_params);

// Create an inference context
llama_context_params ctx_params = llama_context_default_params();
ctx_params.n_ctx = 32768; // 32k token context window for nano workers
llama_context* ctx = llama_new_context_with_model(model, ctx_params);

// Embeddings path — used by embed()
llama_context_params embed_params = llama_context_default_params();
embed_params.embeddings = true;
llama_context* embed_ctx = llama_new_context_with_model(model, embed_params);
```

The worker model pool for `prompt()` loads one copy of the nano weights and forks shared contexts from it — llama.cpp's context model maps cleanly onto the nano+aggregator architecture. See `reasoning.md` for capacity planning details.

---

## Networking

### msquic

**[msquic](https://github.com/microsoft/msquic)**
Microsoft's production QUIC implementation, used for all remote connections to the daemon. Provides low-latency multiplexed streams over UDP without TCP head-of-line blocking — which matters when streaming large result sets or running many concurrent pipelines from remote clients.

msquic is a full shared library build, not header-only, but it ships with a stable C API and has no transitive dependencies that bleed into the rest of the engine. TLS 1.3 is built in.

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

Local access continues to use the Unix Domain Socket directly — msquic is only in the path for connections crossing a network boundary. See `query_networking.md` for the full transport model.

---

## Storage

### Snappy — `.sst` block compression

**[Snappy](https://github.com/google/snappy)**
Page-level block compression on individual SST pages. No dependencies, extremely fast encode/decode, designed for CPU efficiency over maximum ratio — the right tradeoff for a hot storage path.

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
The canonical C/C++ Roaring Bitmap implementation. Single-file amalgamation (`roaring.h` + `roaring.c`) — drop it in and it is ready. Used for the full-text inverted index: keyword queries resolve to a hardware-level bitwise AND across compressed bitmap sets, no text scanning occurs.

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
Header-only C++, written by the HNSW paper authors. Zero dependencies. Covers the standard ANN search case cleanly.

```cpp
#include <hnswlib/hnswlib.h>

hnswlib::L2Space space(768);
hnswlib::HierarchicalNSW<float> index(&space, max_elements, M, ef_construction);

index.addPoint(vector_ptr, row_id);
auto results = index.searchKnn(query_vector_ptr, k);
```

**usearch** is the alternative if int8 scalar quantization becomes necessary to control `.hnsw` index memory footprint at scale. Otherwise hnswlib is simpler. **Avoid FAISS** — GPU-oriented, batch-workload assumptions, orders of magnitude larger than either option.

---

### POSIX `mmap` — `.vec` zero-copy reads

No library. Vectors are raw `float32` binary blobs and zero-copy read access is `mmap` directly.

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
Used in the `.wal` record format to detect corruption on replay. SSE4.2 hardware intrinsics when available, software fallback otherwise.

```cpp
#include <crc32c/crc32c.h>
uint32_t checksum = crc32c::Crc32c(record_data, record_size);
```

---

### simdjson — `json<T>` ingestion

**[simdjson](https://github.com/simdjson/simdjson)**
Used at the storage boundary to validate and parse `json<T>` typed fields before encoding to msgpack and writing to the `.wal`. SIMD-based, single-header option available, zero dependencies.

```cpp
#include <simdjson.h>
simdjson::dom::parser parser;
simdjson::dom::element doc = parser.parse(json_input);
```

---

### msgpack-cxx — `json<T>` internal encoding

**[msgpack-cxx](https://github.com/msgpack/msgpack-c)**
`json<T>` fields are stored internally as binary msgpack rather than raw JSON text — eliminates re-parsing on every read and reduces storage size. Decoded back to JSON only at the `select` projection stage. Header-only.

```cpp
#include <msgpack.hpp>

msgpack::sbuffer buffer;
msgpack::pack(buffer, your_object);

msgpack::object_handle handle = msgpack::unpack(buffer.data(), buffer.size());
```

---

### spdlog — logging

**[spdlog](https://github.com/gabime/spdlog)**
Header-only mode available. Backed by fmtlib. Fast enough for the hot storage path with async sink configuration. Used for WAL replay events, compaction progress, inference lifecycle, and daemon startup.

```cpp
#include <spdlog/spdlog.h>
spdlog::info("WAL replay complete — {} records recovered", count);
spdlog::warn("Memtable at {:.0f}% capacity — flush imminent", pct);
```

---

### fmtlib — string formatting

**[fmtlib](https://github.com/fmtlib/fmt)**
spdlog pulls this in as a dependency. Used directly for query error message formatting, diagnostic output, and anywhere `std::string` construction from mixed types would otherwise require `stringstream`.

```cpp
#include <fmt/format.h>
std::string msg = fmt::format(
    "type mismatch on field '{}': expected {}, got {}",
    field_name, expected_type, actual_type
);
```

---

## Dependency Summary

```
tensor-db
│
├── inference     llama.cpp          (embed() + prompt() — nano workers + aggregator)
├── networking    msquic             (remote QUIC transport)
│
├── .wal          crc32c
├── .sst          snappy
├── .rbm          CRoaring
├── .vec          mmap (POSIX — no library)
├── .hnsw         hnswlib            (or usearch for quantization)
│
├── json<T>       simdjson  (parse) + msgpack-cxx  (store)
├── logging       spdlog + fmtlib
└── crc32         crc32c
```