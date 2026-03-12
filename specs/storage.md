# Physical Storage (`storage.md`)

---

## Directory-Based Isolation

Tensor Database operates as a highly orchestrated directory of specialized file types rather than a single monolithic file. Packing vectors, full-text indexes, and relational integers into one file format destroys CPU cache lines and I/O efficiency.

By splitting the storage layer into distinct modules, Tensor Database ensures that a massive matrix multiplication for a semantic query does not thrash the disk I/O needed for a simple integer lookup.

When you create a table like `"store/products"`, Tensor Database provisions a directory at that path containing specialized storage modules — each purpose-built for a different class of data.

---

## 1. The Scalar Module (`.wal` & `.sst`)

Handles traditional relational data: `int32`, `int64`, `float32`, `float64`, `decimal`, `bool`, `uuid`, `timestamp`, and `text`. Built on a Log-Structured Merge (LSM) Tree architecture optimized for extreme write throughput and crash safety.

### `.wal` — Write-Ahead Log

Every `.tql` mutation is appended immediately to the `.wal` on disk before the engine acknowledges the operation to the client. This guarantees strict ACID durability. If the host system loses power mid-write, Tensor Database replays the `.wal` on boot to reconstruct exact state. No acknowledged mutation is ever lost.

### `.sst` — Sorted String Table

Once the in-memory write buffer (memtable) fills up, it is flushed to disk as an immutable `.sst` file. Because `.sst` files are never modified in place, write amplification is minimized.

Data inside the `.sst` is laid out using PAX (Partition Attributes Across) — row-by-row at the page level, but column-by-column within the page. When the query planner executes `where o.status == "completed"`, the C++ engine loads just the `status` column into a SIMD vector register without pulling the entire row into the CPU cache.

### LSM Compaction

Over time, multiple `.sst` files accumulate. Background compaction merges them, physically dropping tombstoned rows from deletes and reclaiming disk space. Compaction runs independently of query execution and never blocks reads or writes.

---

## 2. The Vector Module (`.vec` & `.hnsw`)

Vectors are explicitly decoupled from the relational layer to keep `.sst` files lean and to allow the AI query path to operate without interfering with scalar I/O.

### `.vec` — Raw Binary Blobs

A `vector(1536)` is a large array of `float32` values. Tensor Database writes these directly to a `.vec` file as pure binary. When a query requires a semantic search, the engine uses `mmap()` to map this file directly into the C++ memory space, bypassing the kernel's read buffers entirely for zero-copy access.

### `.hnsw` — Hierarchical Navigable Small World

Scanning millions of high-dimensional vectors linearly is not viable. The `.hnsw` file stores a multi-layered graph of the vectors. When an `embed()` call returns a query embedding, the planner drops it into the top layer of this graph and navigates down to the closest semantic matches in microseconds.

When a mutation writes or updates a `vector(n)` field, the `.hnsw` index is updated incrementally after the `.wal` is committed. The row is immediately queryable via scalar and text filters, with semantic search availability following within milliseconds.

---

## 3. The Text Module (`.rbm`)

Scanning raw strings in the `.sst` for keyword matches is too slow at scale. Tensor Database builds an inverted index purpose-built for C++ bitwise operations.

### `.rbm` — Roaring Bitmaps

When text is written to the database it is tokenized. The `.rbm` file maps every token to the set of row IDs that contain it. These sets are compressed using Roaring Bitmaps rather than storing lists of integers.

When you query `where match(t.message, "kernel") and match(t.message, "panic")`, the engine does not scan any text. It loads the compressed bitmap for `"kernel"`, the bitmap for `"panic"`, and executes a hardware-level bitwise `AND`. The resulting bits map directly to row IDs in the `.sst`.

---

## 4. The Reasoning Module (`.tok`)

Raw text fields used with `prompt()` require tokenization before they can be loaded into a nano model context window. Rather than tokenizing at query time on every inference call, Tensor Database pre-computes and caches this work at write time.

### `.tok` — Pre-Tokenized Int32 Arrays

When a `text` field is written, the engine immediately tokenizes the content and stores the resulting int32 token array to a `.tok` file. At query time, loading a segment into a context window becomes a memcpy rather than a tokenization pass.

`.tok` files are invalidated when the worker model changes, since different models use different vocabularies and the cached arrays would be incorrect for a different tokenizer.

---

## Unified Execution — Reciprocal Rank Fusion

The true power of isolated modules comes together in the query planner. A hybrid query hits all three modules concurrently:
```tql
import "shared/support"

from "store/tickets" as t: support.Ticket
where t.status == "open"                                          // .sst scalar scan
  and match(t.message, "payment")                                // .rbm bitmap lookup
order by t.embedding <-> embed("refund", tensor.SEARCH)          // .vec / .hnsw traversal
limit 20
```

The `embed()` call is dispatched to the configured AI backend while the C++ engine concurrently evaluates the scalar and text predicates. Once the embedding returns, the planner merges all resulting row ID sets using Reciprocal Rank Fusion and streams a single unified result to the client.

See `ai_backend.md` for how `embed()` and `prompt()` dispatch works.