# CLI (`cli.md`)

---

## One Binary, Two Roles

Tensor Database is delivered as a single unified `tensor db` executable, but the runtime architecture strictly separates two concerns — the **daemon** which owns the storage engine, and the **client** which is a stateless interface to it.

---

## The Daemon — Storage Engine

The daemon owns the C++ memory pools, holds the file locks on the `.sst` and `.vec` directories, manages the IPC socket that all local clients connect through, and runs the built-in embedding engine.

```bash
# Boot the engine in the foreground
tensor db start

# Boot as a detached background service
tensor db start --daemon

# Gracefully flush memtables and shut down
tensor db stop
```

When started, the daemon opens the local Unix Domain Socket (`/tmp/tensordb.sock`) and the remote QUIC port, then waits for `.tql` pipelines to process.

---

## The Client — Execution Interface

The client is completely stateless. It does not parse `.tql` syntax or run query planners. Its sole job is to take input, ship it over the IPC socket to the daemon, and stream results back to stdout.

Because the client is lightweight, a shell script or AI agent can invoke `tensor db eval` thousands of times per second without heavy startup costs.

### 1. File Execution

The standard way to run migrations, apply IAM policies, or execute complex pipelines.

```bash
# Stream the execution result to the console
tensor db run pipeline.tql

# Output strictly as JSON for another script to consume
tensor db run query.tql --format json
```

### 2. Inline Evaluation

Designed for quick lookups, telemetry checks, and Unix shell composition.

```bash
# Check low stock products
tensor db eval 'from "store/products" as p: commerce.Product where p.stock < 10 select { id: p.id, name: p.name, stock: p.stock }'

# Pipe results into standard Unix tools
tensor db eval 'from "store/orders" as o: commerce.Order select { id: o.id }' | wc -l
```

### 3. The Interactive REPL

For exploring paths, testing queries, and manually verifying semantic search results.

```bash
tensor db shell
```

The shell features native `.tql` syntax highlighting, tab-completion for logical paths (e.g. hitting `Tab` after `from "store/`), and multi-line pipeline editing.

---

## Output Formatting

Tensor Database supports complex nested types — `json`, `array`, `vector` — so the CLI ships multiple output modes rather than defaulting to ASCII tables that break on long strings or nested data.

**`--format table` (Default)** — Intelligently truncates large vectors (e.g. `[0.12, 0.44, ... 1534 more]`) and formats nested JSON cleanly for human readability.

**`--format json`** — Dumps the pure unformatted JSON structure. This is the required flag when a script, agent, or pipeline is programmatically consuming results.

**`--format csv`** — Flattens output for export to external data tools. Nested types are serialized as strings.

---

## Observability

```bash
tensor db status
```

**Example output:**
```text
Tensor Database Daemon Status
------------------------------
Uptime:        14d 6h 22m
Socket:        /tmp/tensordb.sock
Connections:   4 active (3 local IPC, 1 remote QUIC)

Storage Metrics
---------------
LSM Memtable:  12 MB / 64 MB
Active Paths:  24 logical, 3 physical mounts

Embedding Engine
----------------
Backend:       built-in
Models:        tensor.SEARCH, tensor.CLASSIFY, tensor.CODE
Status:        running (0.8ms latency)
```

For embedding engine details and the `tensor.*` constants, see `ai_backend.md`.

---

## Snapshots & Restore

A `.tdb` (Tensor Database Backup) file is a flat raw archive — a small header manifest describing the included paths and their module files, followed by the raw binary of each file laid out sequentially with byte offsets in the manifest so any path can be seeked to directly without scanning the whole archive. No compression, no encoding, no transformation. What is on disk is what is in the container.

### `tensor db snapshot`

Flushes all in-memory memtables to disk, waits for any in-flight `.wal` writes to settle, then captures the consistent on-disk state of all logical paths into a single `.tdb` file. The daemon stays running and continues serving queries during the snapshot — reads and writes are not blocked.

```bash
# Snapshot everything
tensor db snapshot --out backup.tdb

# Snapshot specific paths only
tensor db snapshot --paths "store/products,store/orders" --out store_backup.tdb

# Snapshot with a timestamp in the filename
tensor db snapshot --out "backups/snapshot_$(date +%Y%m%d_%H%M%S).tdb"
```

### `tensor db restore`

Restores logical paths from a `.tdb` file. A full restore requires the daemon to be stopped first to prevent write conflicts. Restoring specific paths into a running daemon is supported with the `--paths` flag.

```bash
# Full restore — daemon must be stopped
tensor db stop
tensor db restore backup.tdb
tensor db start

# Restore specific paths into a running daemon
tensor db restore backup.tdb --paths "store/products"
```

If a path being restored already exists, the command requires an explicit `--overwrite` flag. Without it the restore fails at validation before touching any files.

```bash
tensor db restore backup.tdb --paths "store/products" --overwrite
```

### `tensor db snapshot inspect`

Reads the manifest header of a `.tdb` file and prints its contents without extracting anything. Useful for verifying what a snapshot contains before committing to a restore.

```bash
tensor db snapshot inspect backup.tdb
```

**Example output:**
```text
Tensor Database Snapshot
------------------------
Created:    2026-02-20T08:30:00Z
Daemon:     Tensor Database v1.4.2
Paths:      3

store/products
  .sst    412 MB
  .vec    1.2 GB
  .hnsw   88 MB
  .rbm    14 MB

store/orders
  .sst    210 MB
  .rbm    8 MB

store/fulfillment
  .sst    95 MB
  .rbm    4 MB

Total:    2.0 GB (uncompressed)
```

---

## First-Time Setup

```bash
tensor db start --setup
```