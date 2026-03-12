# Mutations (`mutations.md`)

---

## Mutations Are Pipelines

Legacy SQL treats `INSERT`, `UPDATE`, and `DELETE` as fundamentally different statement types from `SELECT`. Tensor Database rejects this split. A mutation is a pipeline that writes instead of reads. Data flows top-to-bottom through the same stages, and the `returning` block at the end shapes the output exactly like a `select` projection. One mental model. One syntax. One execution engine.

---

## 1. `insert` — Writing New Rows

### Literal Insert

Declare the target path, bind the type contract, and provide values inline. The compiler validates every field against the type before a single byte touches the `.wal`.
```tql
import "shared/commerce"

insert into "store/products" as commerce.Product {
    id:          gen_uuid(),
    name:        "Leather Wallet",
    price:       49.99,
    stock:       200,
    description: "Full-grain leather bifold wallet"
}
```

### Multi-Row Insert

Multiple rows are expressed as a comma-separated list of value blocks. The engine batches these into a single `.wal` append and a single memtable write for maximum throughput.
```tql
import "shared/commerce"

insert into "store/products" as commerce.Product
    { id: gen_uuid(), name: "Leather Wallet",  price: 49.99, stock: 200, description: null },
    { id: gen_uuid(), name: "Canvas Backpack", price: 89.99, stock: 85,  description: null },
    { id: gen_uuid(), name: "Ceramic Mug",     price: 14.99, stock: 500, description: null }
```

### Pipeline Insert (`insert ... from`)

Instead of providing literal values, you feed the `insert` from another query. The source pipeline streams rows directly into the target path without ever materializing an intermediate result in memory.
```tql
import "shared/commerce"

// Archive all out-of-stock products into a separate path
insert into "store/products/archived" as commerce.Product
from "store/products" as p: commerce.Product
where p.stock == 0
select {
    id:          p.id,
    name:        p.name,
    price:       p.price,
    stock:       p.stock,
    description: p.description
}
```

The `select` block must produce a shape that exactly matches the target type. If a field is missing or types don't align, the compiler rejects the pipeline before execution begins.

---

## 2. `update` — Modifying Existing Rows

An `update` is a filtered pipeline that targets specific rows and applies field-level mutations using a `set` block. Only the fields listed in `set` are modified — all other fields remain untouched.

### Basic Update
```tql
import "shared/commerce"

update "store/orders" as o: commerce.Order
where o.status == "pending" and o.placed_at < "2026-01-01T00:00:00Z"
set {
    status: "expired"
}
```

### Computed Updates

Because `set` is an expression block, you can reference the current row values to compute the new ones.
```tql
import "shared/commerce"

update "store/products" as p: commerce.Product
where p.stock > 100
set {
    price: p.price * 0.90
}
```

### `let` Bindings in Updates

For complex transformations, `let` bindings sit between `where` and `set`, giving you a clean place to compute intermediate values before applying them.
```tql
import "shared/commerce"

update "store/products" as p: commerce.Product
where p.stock < 20

let reorder_qty = 100 - p.stock
let restocked   = p.stock + reorder_qty

set {
    stock: restocked
}
```

---

## 3. `delete` — Removing Rows

A `delete` targets a path, binds the type, filters to the target rows, and removes them.
```tql
import "shared/commerce"

delete from "store/orders" as o: commerce.Order
where o.status == "expired"
```

### Safety: Unfiltered Deletes Are Compile-Time Errors

A `delete` without a `where` clause will not compile. Wiping an entire path is a destructive, non-recoverable operation that should never happen by accident. If you genuinely need to truncate a path, use the dedicated `truncate` command.
```tql
// This will NOT compile — no where clause
delete from "store/orders" as o: commerce.Order

// Explicit, intentional full wipe
truncate "store/orders"
```

---

## 4. `returning` — The Output Pipeline

Every mutation can end with a `returning` block. It behaves identically to `select`: it shapes the output of the rows actually affected by the mutation and streams them back to the client in a single round trip.

### Returning After Insert

Get back generated UUIDs and timestamps immediately after creation, without a follow-up query.
```tql
import "shared/commerce"

insert into "store/products" as commerce.Product {
    id:          gen_uuid(),
    name:        "Leather Wallet",
    price:       49.99,
    stock:       200,
    description: null
}
returning {
    id,
    name
}
```

**Output:**
```text
┌──────────────────────────────────────┬────────────────┐
│ id                                   │ name           │
├──────────────────────────────────────┼────────────────┤
│ a3f1e2c0-88d4-4b17-9c22-df01a8b3e5c1│ Leather Wallet │
└──────────────────────────────────────┴────────────────┘
```

### Returning After Update

The `returning` block sees the row after `set` has been applied, so you get the new values back, not the old ones.
```tql
import "shared/commerce"

update "store/products" as p: commerce.Product
where p.stock < 20
set {
    stock: p.stock + 100
}
returning {
    id:        p.id,
    name:      p.name,
    new_stock: p.stock
}
```

### Returning After Delete

Capture a receipt of everything removed. Essential for audit trails and feeding deleted rows into an archive pipeline.
```tql
import "shared/commerce"

delete from "store/orders" as o: commerce.Order
where o.status == "expired"
returning {
    id:         o.id,
    customer:   o.customer_id,
    deleted_at: now()
}
```

### Piping `returning` Into Other Commands

Because the CLI streams `returning` output to stdout like any other query result, it composes natively with Unix shell tools and the `--format json` flag.
```bash
# Insert a product and pipe the generated ID into another script
tensor db run create_product.tql --format json | jq '.id'

# Delete expired orders and log the receipts
tensor db run expire_orders.tql --format json >> /var/log/tensor/expired_orders.jsonl
```

---

## 5. `upsert` — Insert or Update

The classic "write this row, but if it already exists, update it instead" pattern. Tensor Database resolves conflicts using the path's primary key or an explicitly declared conflict target.
```tql
import "shared/commerce"

upsert into "store/products" as commerce.Product
conflict on id
{
    id:          "550e8400-e29b-41d4-a716-446655440000",
    name:        "Leather Wallet",
    price:       54.99,
    stock:       200,
    description: null
}
conflict set {
    price: 54.99,
    stock: 200
}
```

`conflict on` declares the field that triggers conflict detection. `conflict set` declares the fields to update when one is found. For new rows the full value block is inserted as-is.

### Upsert With Returning

`upsert` supports `returning` like any other mutation. The output includes a compiler-provided `_mutation` field that tells you whether each row was inserted or updated.
```tql
import "shared/commerce"

upsert into "store/products" as commerce.Product
conflict on id
{
    id:          "550e8400-e29b-41d4-a716-446655440000",
    name:        "Leather Wallet",
    price:       54.99,
    stock:       200,
    description: null
}
conflict set {
    price: 54.99,
    stock: 200
}
returning {
    id,
    name,
    _mutation   // "inserted" or "updated"
}
```

---

## 6. Pipeline Position Summary

### Query Pipeline
```
from → where → group by → let → having → select → order by → limit
```

### Insert Pipeline (from source)
```
from → where → let → select → insert into → returning
```

### Update Pipeline
```
update → where → let → set → returning
```

### Delete Pipeline
```
delete from → where → returning
```

### Upsert Pipeline
```
upsert into → conflict on → values → conflict set → returning
```

---

## Execution Notes

**Write-Ahead Guarantee** — Every mutation is appended to the `.wal` before the engine acknowledges the operation to the client. If the process crashes between the `.wal` write and the memtable update, the engine replays the log on boot. No acknowledged mutation is ever lost.

**Batch Optimization** — Multi-row `insert` blocks and pipeline inserts are written as a single batched `.wal` entry. A thousand-row insert is one disk operation, not a thousand.

**Vector Mutations** — When a mutation writes or updates a `vector(n)` field, the binary data is appended to the `.vec` file and the `.hnsw` index is updated incrementally. The row is immediately queryable via scalar and text filters, with semantic search availability following within milliseconds.

**Delete Mechanics** — Rows are not physically removed on delete. The engine writes a tombstone marker to the `.wal` and memtable. Physical reclamation happens during background LSM compaction when the `.sst` files containing the tombstones are merged and dead rows are dropped.