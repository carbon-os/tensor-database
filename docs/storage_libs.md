# Storage Libraries (`storage_libs.md`)

---

## Philosophy

Tensor Database's storage layer is purpose-built. Each file module (`.wal`, `.sst`, `.vec`,
`.hnsw`, `.rbm`) has a specific layout that serves the query planner directly — no general-purpose
database library maps cleanly onto that design without fighting the abstraction.

The rule for third-party dependencies is: **one library, one job, no transitive bloat.**
Everything listed here is either header-only or a near-single-file amalgamation. The WAL
append logic, PAX column layout, LSM memtable, mmap access pattern, and BM25 scoring layer
are all written from scratch — those are where the actual storage design lives.

---

## Per-Module Libraries

### `.wal` — No Library

The write-ahead log is sequential appends and `fsync`. The record format is a fixed header,
length-prefixed binary payload, and a CRC32 checksum. No library is needed or appropriate here.
Adding one is where bloat starts.

See **crc32c** below for the checksum primitive.

---

### `.sst` — Snappy

The SST file uses a PAX (Partition Attributes Across) layout — rows at the page level, columns
within the page. This layout is custom and no existing LSM library (RocksDB, LevelDB) maps onto
it without taking over the storage model entirely.

What is needed is block-level compression on individual SST pages.

**[Snappy](https://github.com/google/snappy)**
Google's compression library. No dependencies, extremely fast encode/decode, designed specifically
for page-level block compression rather than stream compression. Does not aim for maximum ratio —
it aims for CPU efficiency, which is the right tradeoff for a hot storage path.
```cpp
#include <snappy.h>

// Compress a PAX page before flushing to disk
std::string compressed;
snappy::Compress(page_data.data(), page_data.size(), &compressed);

// Decompress on read
std::string decompressed;
snappy::Uncompress(compressed.data(), compressed.size(), &decompressed);
```

The in-memory memtable that buffers writes before the SST flush is a skiplist. This is short
enough (~200 lines) to write directly, but a clean header-only reference exists at
[herumi/skip_list](https://github.com/herumi/skip_list) if a starting point is useful.

---

### `.rbm` — CRoaring

The `.rbm` inverted index maps every token to the set of row IDs containing it. Queries like
`where message contains "kernel" and message contains "panic"` resolve to a bitwise AND across
two compressed bitmaps — no text scanning occurs.

**[CRoaring](https://github.com/RoaringBitmap/CRoaring)**
The canonical C/C++ Roaring Bitmap implementation, written by the authors of the data structure
(Daniel Lemire, Owen Kaser, et al.). A single-file amalgamation (`roaring.h` + `roaring.c`) is
available — drop it in and it is ready. Nothing else to evaluate here.
```cpp
#include <roaring/roaring.hh>

roaring::Roaring kernel_rows = index.get("kernel");
roaring::Roaring panic_rows  = index.get("panic");

// Hardware-level bitwise AND — result is the matching row ID set
roaring::Roaring result = kernel_rows & panic_rows;

for (uint32_t row_id : result) {
    // fetch row from .sst by row_id
}
```

---

### `.vec` — POSIX `mmap` Directly

Vectors are raw `float32` binary blobs. Zero-copy read access is `mmap` — no library wraps
this more usefully than the syscall itself.
```cpp
#include <sys/mman.h>
#include <fcntl.h>

int fd = open("store/products.vec", O_RDONLY);

// Map the entire .vec file into the process address space
float* vectors = static_cast<float*>(
    mmap(nullptr, file_size, PROT_READ, MAP_SHARED, fd, 0)
);

// Hint to the kernel: HNSW traversal is random access
madvise(vectors, file_size, MADV_RANDOM);

// Hint to the kernel: sequential scan path (e.g. brute-force fallback)
madvise(vectors, file_size, MADV_SEQUENTIAL);
```

`madvise` hints cost nothing and materially affect kernel prefetch behavior. Use `MADV_RANDOM`
for HNSW graph traversal (scattered jumps) and `MADV_SEQUENTIAL` for any linear scan fallback.

---

### `.hnsw` — hnswlib or usearch

The HNSW graph index enables approximate nearest-neighbor search across the vectors mapped
from `.vec`. Scanning millions of high-dimensional vectors linearly is not viable — the graph
allows the query planner to navigate from the query embedding to the closest matches in
microseconds.

**[hnswlib](https://github.com/nmslib/hnswlib)** — Primary recommendation.
Header-only C++, written by the HNSW paper authors (Yu. A. Malkov and D. A. Yashunin).
Zero dependencies. Covers the standard case cleanly.
```cpp
#include <hnswlib/hnswlib.h>

// L2 space — standard for text and code embeddings
hnswlib::L2Space space(768);
hnswlib::HierarchicalNSW<float> index(&space, max_elements, M, ef_construction);

// Index a vector on write
index.addPoint(vector_ptr, row_id);

// Query at search time — returns k nearest row IDs
auto results = index.searchKnn(query_vector_ptr, k);
```

**[usearch](https://github.com/unum-cloud/usearch)** — Consider if int8 quantization matters.
Newer library, same algorithm, adds support for scalar quantization (int8, fp16) which halves or
quarters the memory footprint of the index at a small accuracy cost. Worth evaluating if the
`.hnsw` index size becomes a concern at scale. Otherwise hnswlib is simpler to integrate.

**Avoid FAISS.** It is GPU-oriented, assumes batch workloads, and is orders of magnitude larger
than either option above. It is the wrong tool for an embedded query engine.

---

## Supporting Libraries

### CRC32 Checksums — crc32c

Used in the `.wal` record format to detect corruption on replay. Uses SSE4.2 hardware
intrinsics when available, falls back to a software implementation otherwise.

**[crc32c](https://github.com/google/crc32c)** — Google's implementation.
```cpp
#include <crc32c/crc32c.h>

uint32_t checksum = crc32c::Crc32c(record_data, record_size);
```

---

### JSON Parsing — simdjson

Used at the storage boundary when validating and ingesting `json<T>` typed fields before
they are encoded to msgpack and written to the `.wal`.

**[simdjson](https://github.com/simdjson/simdjson)**
Fastest available JSON parser. Uses SIMD intrinsics to parse entire cache lines in parallel.
Single-header option available. Zero dependencies.
```cpp
#include <simdjson.h>

simdjson::dom::parser parser;
simdjson::dom::element doc = parser.parse(json_input);
```

---

### JSON Internal Encoding — msgpack-cxx

`json<T>` fields are stored internally as binary msgpack, not raw JSON text. This eliminates
re-parsing on every read and reduces storage size. The `json<T>` field is decoded back to
JSON only at the `select` projection stage when the client requests it.

**[msgpack-cxx](https://github.com/msgpack/msgpack-c)**
Header-only C++ implementation of the MessagePack binary format.
```cpp
#include <msgpack.hpp>

// Pack to binary for .wal / .sst write
msgpack::sbuffer buffer;
msgpack::pack(buffer, your_object);

// Unpack on read
msgpack::object_handle handle = msgpack::unpack(buffer.data(), buffer.size());
msgpack::object obj = handle.get();
```

---

### Logging — spdlog

**[spdlog](https://github.com/gabime/spdlog)**
Header-only mode available. Backed by fmtlib. Fast enough for the hot storage path with
async sink configuration. Used for WAL replay events, compaction progress, and daemon lifecycle.
```cpp
#include <spdlog/spdlog.h>

spdlog::info("WAL replay complete — {} records recovered", count);
spdlog::warn("Memtable at {:.0f}% capacity — flush imminent", pct);
```

---

### String Formatting — fmtlib

**[fmtlib](https://github.com/fmtlib/fmt)**
spdlog pulls this in as a dependency anyway. Use it directly for query error message
formatting, diagnostic output, and anywhere `std::string` construction from mixed types
would otherwise require `stringstream`.
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
tensor-db storage layer
│
├── .wal      crc32c
├── .sst      snappy
├── .rbm      CRoaring
├── .vec      mmap (POSIX — no library)
├── .hnsw     hnswlib  (or usearch for quantization)
│
├── json<T>   simdjson  (parse) + msgpack-cxx  (store)
├── logging   spdlog + fmtlib
└── crc32     crc32c
```

Seven libraries. All header-only or single-file amalgamation. No library owns the storage
model — each covers exactly one primitive that would be worse to reimplement than to adopt.