# Tensor Database — Design Review

A coherent design. The philosophy is clear — you've internalized lessons from SQLite's simplicity, Postgres's complexity sprawl, and modern tools like DuckDB and LanceDB.

---

## What's Strong

**Unified binary with client/daemon separation** gives you the deployment story of SQLite with the concurrency story of Postgres. Unix socket for local auth is pragmatic — no "why do I need a password on localhost" frustration.

**Storage module split** (`.sst`, `.vec`, `.rbm`) is genuinely clever. Cramming embeddings into relational rows destroys cache locality. Fanning out a hybrid query to three specialized engines concurrently and merging via Reciprocal Rank Fusion is a real architectural differentiator.

**Type contracts as packages** solve schema drift — the persistent production bug where your DB schema and application types slowly diverge. One `.tql` package file is the source of truth for both.

**Non-nullable by default with `T?`** is the correct modern choice. Matches Kotlin, Swift, Rust. Forces developers to handle absence explicitly rather than discovering nulls at runtime.

**PAX layout inside SSTs** is a smart middle ground between row-store and column-store for a mixed workload of OLTP writes, analytical scans, and vector search.

**Built-in embedding engine** with `tensor.*` constants is the right call. Abstracting the model behind a use-case constant means pipelines don't rot when default models are upgraded.

---

## Things That Feel Missing

**Transactions and concurrency control.** The biggest gap. `.wal` covers crash safety but there's no discussion of multi-statement transactions, isolation levels, or concurrent writers. Even a simple stance — "single-writer, multi-reader with snapshot isolation via LSM versioning" — would anchor the design.

**Schema evolution.** `create table` is covered but what happens when a type changes? Additive-only migrations, zero-downtime column additions, backward compatibility of type packages — this is where production systems live and die.

**Secondary scalar indexes.** `.hnsw` covers vectors, `.rbm` covers text, but what about `where cpu_usage > 90.0` on 50 million rows? Is that always a full SST scan? The LSM architecture supports bloom filters and prefix indexes natively — worth specifying.

**Error handling in pipelines.** What happens when a JSON path hits null mid-stream? When `embed()` fails? Do rows get skipped, does the pipeline abort? The type system is strict at compile time but runtime errors in a streaming pipeline need a story.

---

## Things to Add Without Adding Bloat

**`watch` or streaming mode.** Given the Unix-native architecture, a `tensor db eval --watch` that tails new rows as they arrive is a natural fit for agents and system monitoring workloads.

**Bulk import at the CLI level.** If agents are writing thousands of embeddings per second, a first-class path like `tensor db import data.jsonl --into "store/events" --as commerce.Event` matters for throughput.

---

## Things to Avoid

**Stored procedures.** The pipeline model is clean because it's declarative and stateless. Imperative server-side logic inherits Postgres's PL/pgSQL debugging nightmare.

**ORM or language-specific client libraries.** The CLI and JSON output is the interface. ORMs are where type contracts go to die — and the package system already solves the problem ORMs exist to solve.

**Query cache.** LSM trees already have bloom filters and block caches. Application-level query caches are more trouble than they're worth — MySQL removed theirs for good reason.

**Pluggable storage engines.** The three-module architecture (`.sst`/`.vec`/`.rbm`) working in concert is the product. MySQL's InnoDB/MyISAM split created decades of confusion. Own the architecture.

---

## Overall

This is one of the more coherent database designs at the spec stage. The biggest risk isn't missing features — it's underspecifying the concurrency and transaction model before getting deep into implementation.