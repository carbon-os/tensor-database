# Tensor Database

A modern embedded database built for applications that need fast relational queries, full-text search, semantic vector search, and native reasoning over raw text — all in one engine, with no external dependencies.

Tensor Database is one of the first databases to treat reasoning as a first-class query primitive, alongside filtering, aggregation, and semantic search.

---

## What It Is

Tensor Database is a purpose-built data engine that treats vectors, text, relational data, and reasoning as first-class citizens. Instead of bolting AI capabilities onto a legacy SQL engine, Tensor Database was designed from the ground up around a single pipeline model that handles all four query types natively and concurrently.

Queries are written in **Tensor Query Language** (`.tql`) — a strict, compile-time validated pipeline language that replaces SQL with a top-to-bottom execution model. No magic columns, no implicit coercions, no runtime surprises.

---

## What Makes It Different

**One query language, three storage engines.** A single `.tql` pipeline can filter on a scalar field, match a keyword, and rank by semantic similarity in the same query. The storage layer splits these into three purpose-built modules — `.sst` for relational data, `.rbm` for full-text, `.vec` and `.hnsw` for vectors — and merges the results using Reciprocal Rank Fusion.

**Reasoning is built in.** Store raw text in any `text` field and query it with natural language using `prompt()`. The engine runs a nano+aggregator inference pipeline internally — tokenizing, splitting, fanning out across parallel worker models, and synthesizing the results into fully typed `.tql` fields that flow into the rest of the pipeline like any other variable.

**Embeddings are built in.** Tensor Database ships with a native embedding engine. Call `embed()` directly in any `.tql` pipeline — no external model server, no configuration, no separate process. The engine loads and runs open source embedding models inline.

**Compile-time correctness.** Types are defined once in `.tql` package files and enforced at every layer — schema, query, and mutation. If a pipeline is wrong, it fails before touching data, not against live rows.

**Unix-native.** Local access uses Unix Domain Socket IPC with OS-level file permission auth. Remote access uses QUIC with API key bearer tokens bound to path-level IAM roles. The same socket that serves queries also exposes the embedding and reasoning engines directly to agents and external processes.

---

## Query Language at a Glance
```tql
import "shared/commerce"

from "store/products" as p: commerce.Product
where p.stock > 0 and p.price < 50.00
order by p.embedding <-> embed("gift ideas under fifty dollars")
limit 10
```
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
join "store/customers" as c: commerce.Customer on o.customer_id == c.id

where o.status == "completed"
group by c.id, c.name

let total_spent = sum(o.total)
let order_count = count(*)

having total_spent > 1000.00

select {
    customer:      c.name,
    email:         c.email,
    total_spent,
    order_count,
    average_order: total_spent / order_count
}
order by total_spent desc
limit 25
```
```tql
import "shared/commerce"

from "store/products" as p: commerce.Product
where p.stock > 0
prompt("gift ideas under fifty dollars", tensor.REASONING) from p.raw_data as result: commerce.ProductResult

select {
    name:   result.name,
    price:  result.price,
    reason: result.reason
}
order by result.price asc
limit 10
```

---

## Embedding Engine

`embed()` is a first-class primitive in `.tql`. It maps to use-case constants that abstract away the underlying model — your pipelines stay stable as default models are upgraded.
```tql
embed("query")                      // silent default → tensor.SEARCH
embed("query", tensor.SEARCH)       // semantic retrieval, RAG
embed("query", tensor.CLASSIFY)     // clustering, tagging, categorization
embed("query", tensor.CODE)         // code search, symbol lookup
```

| Constant | Default Model | Dimensions |
|---|---|---|
| `tensor.SEARCH` | `nomic-embed-text-v1.5` | 768 |
| `tensor.CLASSIFY` | `all-MiniLM-L6-v2` | 384 |
| `tensor.CODE` | `jina-embeddings-v2-base-code` | 768 |

---

## Reasoning Engine

`prompt()` is a first-class pipeline stage in `.tql`. It runs a nano+aggregator inference pipeline over any raw text field and returns a fully typed result bound to your declared output schema.
```tql
prompt("prompt", tensor.REASONING)   // full reading comprehension, multi-fact synthesis
```

The mode constant is validated at compile time. The underlying models are daemon configuration — your pipelines never reference model names directly and require no changes when defaults are upgraded.

---

## Storage Architecture

| Module | Format | Purpose |
|---|---|---|
| `.wal` | Write-ahead log | ACID durability, crash recovery |
| `.sst` | Sorted string table (LSM) | Relational scalar data |
| `.rbm` | Roaring bitmap index | Full-text BM25 keyword search |
| `.vec` | Raw binary float arrays | Vector storage, zero-copy mmap reads |
| `.hnsw` | Navigable small world graph | Approximate nearest-neighbor search |
| `.tok` | Pre-tokenized int32 arrays | Fast segment loading for reasoning |

---

## Getting Started
```bash
# First-time setup
tensor db start --setup

# Run a migration
tensor db run migrations/001_setup.tql

# Interactive shell
tensor db shell

# Check engine status
tensor db status
```

---

## Documentation

| File | Description |
|---|---|
| `specs/query.md` | Query pipeline, filtering, projection, semantic search |
| `specs/mutations.md` | Insert, update, delete, upsert, returning |
| `specs/joins.md` | Inner joins, left joins, multi-path queries |
| `specs/aggregations.md` | Group by, aggregate functions, having |
| `specs/packages.md` | Type definitions, schema, migrations |
| `specs/types.md` | Full type reference |
| `specs/ai_backend.md` | Embedding and reasoning engine, tensor.* constants, socket access |
| `specs/reasoning.md` | prompt() pipeline stage, nano+aggregator architecture, capacity planning |
| `specs/storage.md` | Physical storage modules and execution model |
| `specs/iam.md` | Authentication, API keys, path-based access control |
| `specs/cli.md` | CLI reference, REPL, snapshots, observability |