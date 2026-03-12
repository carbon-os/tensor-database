# Types

---

## int32
```tql
let count: int32 = 1048576
let delta: int32 = -500
```

A signed 32-bit integer. The default choice for counts, iterations, and standard numeric identifiers. Replaces the legacy `TINYINT`, `SMALLINT`, and standard `INT` types found in older databases. By collapsing the smaller integer types into a single `int32` standard, Tensor Database eliminates silent overflow errors and aligns perfectly with native C++ `int32_t` boundaries in the storage engine.

---

## int64
```tql
let bytes_read: int64 = 9223372036854775807
let offset:     int64 = -1024
```

A signed 64-bit integer. Used when values will exceed the ~2.1 billion limit of `int32`. The correct choice for tracking exact byte sizes of files mounted via the OS-native path system, high-throughput system telemetry, or massive analytical aggregations. Maps directly to `int64_t` in the `.sst` blocks.

---

## float32
```tql
let temperature: float32 = 38.5
let velocity:    float32 = -9.81
```

A 32-bit IEEE 754 floating-point number. Provides roughly 7 decimal digits of precision. This is the workhorse type for the vector and AI modules, prioritizing memory bandwidth and SIMD throughput over absolute decimal precision. Unless you are performing financial math, `float32` provides the best performance-to-footprint ratio.

---

## float64
```tql
let latitude: float64 = 43.653225
let exact_hz: float64 = 144.0000012
```

A 64-bit IEEE 754 floating-point number. Provides roughly 15 decimal digits of precision. Doubles the memory footprint of `float32`. Use this for geographic coordinates, scientific telemetry, or when accumulated rounding errors would corrupt the dataset.

---

## decimal(p,s)
```tql
let balance: decimal(12,4) = 15000.5000
let price:   decimal(8,2)  = 99.99
```

A 128-bit fixed-point number for exact mathematics. The parameters define the precision `p` (total digits) and scale `s` (digits to the right of the decimal). Unlike floating-point types, `decimal` guarantees no precision loss during arithmetic. The strict choice for financial ledgers, billing systems, and any domain where a dropped fraction of a cent is a critical bug.

---

## bool
```tql
let is_active: bool = true
let clustered: bool = false
```

A true boolean. Tensor Database rejects the legacy database hack of using `TINYINT(1)` to represent truth states. `bool` strictly accepts `true` or `false` and maps directly to a single byte in the `.sst` storage blocks. The compiler enforces that conditional pipelines (like `where` clauses) receive a real boolean — there is no implicit integer coercion.

---

## text
```tql
let os_name: text = "Tensor-OS"
let status:  text = "running"
```

A dynamically sized, UTF-8 encoded string. Replaces `CHAR`, `VARCHAR`, and `TEXT`. Tensor Database drops artificial character limits at the schema level; developers shouldn't have to guess if a string will be 255 or 256 characters long. Stored efficiently in the LSM tree with native support for the Inverted Index (`.rbm`) module for lightning-fast BM25 keyword searches.

---

## uuid
```tql
let machine_id: uuid = gen_uuid()
let trace_id:   uuid = "123e4567-e89b-12d3-a456-426614174000"
```

A 128-bit (16-byte) universally unique identifier stored as raw binary, not as a 36-character string. This eliminates the string-conversion overhead and storage bloat found in legacy systems. `uuid` is the recommended primary key type for distributed multi-tenant environments and container tracking.

---

## timestamp
```tql
let created_at: timestamp = now()
let booted_at:  timestamp = "2026-02-20T07:00:00Z"
```

An absolute point in time, stored as microseconds (µs) since the Unix epoch. **Always UTC.** Tensor Database explicitly refuses to store local timezones in the database engine, eliminating the entire class of timezone-shift bugs. Formatting and timezone offsets are strictly a client-side responsibility.

---

## json<T?>
```tql
let raw_data:  json                = '{"agent": "local", "uptime": 3600}'
let typed_cfg: json<map[text]bool> = '{"debug": true, "trace": false}'
```

A schema-flexible data type stored internally as binary msgpack for zero-parsing-overhead reads. Can be used loosely as raw `json`, or strictly constrained using a type parameter (`json<T>`) to enforce schema validation at the database boundary before the data is ever written to the `.wal`.

---

## array<T>
```tql
let ports: array<int32> = [80, 443, 8080]
let flags: array<text>  = ["--daemon", "--verbose"]
```

A typed, homogeneous list of elements. Provides a clean way to store multiple related scalar values without needing to architect a separate junction table. Arrays are stored contiguously in the `.sst` blocks.

---

## vector(n)
```tql
let memory: vector(1536) = embed("System booted successfully", 'llama-3-8b')
let latent: vector(256)  = [0.12, -0.45, 0.88, ...]
```

A fixed-size array of `float32` values, purpose-built for AI and RAG pipelines. The integer `n` defines the exact dimensionality of the vector. Vectors bypass the standard LSM tree entirely and are written as raw binary blobs to the `.vec` file, memory-mapped for zero-copy reads by the `.hnsw` semantic index module.

---

## T? — Opt-In Nullable
```tql
let alias:  text? = null
let parent: uuid? = "550e8400-e29b-41d4-a716-446655440000"
```

Tensor Database types are strictly **non-nullable by default**. A variable or column typed as `text` must contain a string. If a value might be missing, it must be explicitly marked nullable by appending `?` to the type. This eliminates `NULL` pointer exceptions at the compiler level and forces developers to handle missing data explicitly in their `.tql` pipelines.