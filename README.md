# Tensor Database

**The declarative, multi-module database for scalar, text, and vector data.**

Tensor Database (`tensor-db`) is a high-performance storage engine built to eliminate the boundary between relational data and semantic search. It operates on a strict, top-to-bottom pipeline architecture (Tensor SQL or `.tsql`) and physically isolates data into purpose-built storage modules — ensuring that massive semantic vector queries never thrash the disk I/O needed for high-throughput scalar lookups.

Designed to run alongside the Tensor Inference Engine, it provides the blazing-fast memory layer required for Zero-Code RAG and autonomous AI agents. And because it ships as a single, compiled binary, the `tensor-db` CLI is absolutely goated.

---

## Core Architecture

Tensor Database discards the monolithic file approach. When you instantiate a logical path, the engine provisions a directory containing specialized storage modules, each optimized for a specific access pattern.

1.  **The Scalar Module (`.wal` & `.sst`)**
    * Handles relational data (`int32`, `uuid`, `timestamp`, `bool`, etc.) using a Log-Structured Merge (LSM) Tree.
    * Every mutation is immediately appended to the Write-Ahead Log (`.wal`) for strict ACID durability.
    * Data is flushed to immutable Sorted String Tables (`.sst`) using a PAX layout, allowing the engine to load specific columns into SIMD registers without caching entire rows.
2.  **The Vector Module (`.vec` & `.hnsw`)**
    * Stores `vector(n)` fields as pure binary blobs (`.vec`) memory-mapped directly into C++ space for zero-copy access.
    * Maintains a Hierarchical Navigable Small World (`.hnsw`) graph for microsecond nearest-neighbor semantic search.
3.  **The Text Module (`.rbm`)**
    * An inverted index mapping tokenized text to compressed Roaring Bitmaps (`.rbm`).
    * Enables lightning-fast keyword filtering via hardware-level bitwise operations, bypassing raw string scans entirely.

When a hybrid query is executed, the planner hits all three modules concurrently and merges the results using Reciprocal Rank Fusion.



---

## Type-Driven Schema (Tensor SQL)

Tensor Database eliminates the drift between application code and database schema using **Package-Level Type Contracts**. Types are defined in standalone `.tsql` files, imported where needed, and strictly bind data at the storage boundary.

### 1. Define the Type
Types are strict and non-nullable by default (append `?` for opt-in nullability).

```tsql
// file: shared/commerce.tsql
package commerce

type Product {
    id:           uuid
    name:         text
    price:        decimal(10,2)
    stock:        int32
    embedding:    vector(1536)
    description:  text?
}

```

### 2. Instantiate Storage

Mount a logical path and bind it to the type contract.

```tsql
// file: migrations/001_setup.tsql
import "shared/commerce"

create table "store/products" as commerce.Product

```

---

## The Query Pipeline

Queries are strict, top-to-bottom pipelines. Data flows through stages; there is no way to reference a downstream value upstream.

```
from → join → where → group by → let → having → select → order by → limit

```

### Basic Query & Joins

The engine supports inner and left joins, binding paths to variables accessible throughout the pipeline.

```tsql
import "shared/commerce"

from "store/orders" as o: commerce.Order
join "store/products" as p: commerce.Product on o.product_id == p.id

where o.status == "completed" and p.price > 50.00
select {
    order_id: o.id,
    product:  p.name,
    price:    p.price,
    total:    o.total
}
order by o.total desc
limit 20

```

### Semantic Search & Embedded AI

Tensor Database features a **built-in inference runtime exclusively for embeddings**. The `embed()` function converts text to a `vector(n)` inline, which the planner uses to traverse the `.hnsw` index.

```tsql
import "shared/commerce"

from "store/products" as p: commerce.Product
where p.stock > 0
// The embed() call is processed natively by the built-in AI engine
order by p.embedding <-> embed("waterproof outdoor gear", 'nomic-embed-v1.5')
limit 10

```

### Aggregations & `let` Bindings

Compute derived metrics efficiently. `let` bindings inline expressions without building temporary tables.

```tsql
import "shared/commerce"

from "store/orders" as o: commerce.Order
where o.status == "completed"
group by o.customer_id

let total_spent  = sum(o.total)
let order_count  = count(*)
let average_order = total_spent / order_count

having total_spent > 500.00

select {
    customer:      o.customer_id,
    total_spent,
    average_order
}
order by total_spent desc

```

---

## Mutations

Mutations are simply pipelines that write instead of read. They flow top-to-bottom and can end with a `returning` block to shape the output.

```tsql
import "shared/commerce"

insert into "store/products" as commerce.Product {
    id:          gen_uuid(),
    name:        "Leather Wallet",
    price:       49.99,
    stock:       200,
    embedding:   embed("Full-grain leather bifold wallet", 'nomic-embed-v1.5'),
    description: null
}
returning {
    id,
    name
}

```

Pipeline inserts (`insert ... from`) allow streaming rows directly between paths without materializing intermediate results in memory. Unfiltered deletes (`delete from ...` without a `where` clause) are rejected at compile time.

---

## CLI & Management

The single `tensor-db` compiled binary serves as both the storage daemon and the stateless execution client. It is built for speed and zero-friction deployment.

### Service Management

```bash
# Boot the engine as a background service
tensor-db start --daemon

# Gracefully flush memtables and shut down
tensor-db stop

```

### Query Execution

The client ships input over an IPC socket to the daemon.

```bash
# Execute a file
tensor-db run query.tsql

# Inline evaluation
tensor-db eval 'from "store/products" as p: commerce.Product select { id: p.id }' | wc -l

# Launch the interactive REPL
tensor-db shell

```

### Output Formatting

Supports `--format table` (default, intelligently truncates vectors), `--format json`, and `--format csv`.

### Snapshots & Backups

Capture consistent on-disk state into a single flat `.dbc` (Database Container) archive without blocking reads or writes.

```bash
# Snapshot specific paths
tensor-db snapshot --paths "store/products,store/orders" --out store_backup.dbc

# Inspect a snapshot manifest
tensor-db snapshot inspect store_backup.dbc

```

---

## Security (IAM)

Security is managed via path-based IAM policies evaluated top-to-bottom. Local connections authenticate via Unix file permissions on the IPC socket, while remote clients require API keys bound to specific roles.

```tsql
create role storefront

grant to storefront {
    allow read on "store/products/*"
    allow read, write on "store/orders/*"
    deny * on "store/billing/*"
}

// Generate an API key bound to the storefront role
create api_key for storefront expires in 90d

```