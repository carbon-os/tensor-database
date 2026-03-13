# Mutations (`mutations.md`)

---

## Mutations Are Pipelines

Legacy SQL treats `INSERT`, `UPDATE`, and `DELETE` as fundamentally different statement types from `SELECT`. Tensor Database rejects this split. A mutation is a pipeline that writes instead of reads. Data flows top-to-bottom through the same stages, and the `returning` block at the end shapes the output exactly like a `select` projection. One mental model. One syntax. One execution engine.

---

## 1. `insert` — Writing New Rows

### Literal Insert

Declare the target path, bind the type contract to a variable, and provide values inline. The variable binding follows the same `as name: Type` pattern used throughout `.tql` and is required when a `returning` block is present. The compiler validates every field against the type before a single byte touches the `.wal`.
```tql
import "shared/commerce"

insert into "store/products" as p: commerce.Product {
    id:          gen_uuid(),
    name:        "Leather Wallet",
    price:       49.99,
    stock:       200,
    description: "Full-grain leather bifold wallet"
}
```

### Multi-Row Insert

Multiple rows are expressed as a comma-separated list of row blocks inside a single outer `{}` container, consistent with the single row literal syntax. The engine batches these into a single `.wal` append and a single memtable write for maximum throughput.
```tql
import "shared/commerce"

insert into "store/products" as p: commerce.Product {
    { id: gen_uuid(), name: "Leather Wallet",  price: 49.99, stock: 200, description: null },
    { id: gen_uuid(), name: "Canvas Backpack", price: 89.99, stock: 85,  description: null },
    { id: gen_uuid(), name: "Ceramic Mug",     price: 14.99, stock: 500, description: null }
}
```

The outer `{}` always follows the type binding. A single row insert and a multi-row insert are the same production — one row block or many, always wrapped in the outer container.

### Pipeline Insert (`insert ... from`)

Instead of providing literal values, you feed the `insert` from another query. The source pipeline streams rows directly into the target path without ever materializing an intermediate result in memory.
```tql
import "shared/commerce"

// Archive all out-of-stock products into a separate path
insert into "store/products/archived" as p: commerce.Product
from "store/products" as src: commerce.Product
where src.stock == 0
select {
    id:          src.id,
    name:        src.name,
    price:       src.price,
    stock:       src.stock,
    description: src.description
}
```

The `insert into` declaration comes first, followed by the source pipeline. The `select` block must produce a shape that exactly matches the target type. If a field is missing or types don't align, the compiler rejects the pipeline before execution begins.

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

For complex transformations, `let` bindings sit between `where` and `set`, giving you a clean place to compute intermediate values before applying them. As with all `let` bindings, an explicit type annotation is required.
```tql
import "shared/commerce"

update "store/products" as p: commerce.Product
where p.stock < 20

let reorder_qty: int32 = 100 - p.stock
let restocked:   int32 = p.stock + reorder_qty

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

### Field Reference Rules

`returning` follows the same `key: variable.field` syntax as `select`. Shorthand bare field names are not valid — every field reference must explicitly name its source variable.

```tql
// correct
returning {
    id:   p.id,
    name: p.name
}

// compile-time error — shorthand bare field names are not allowed
returning {
    id,
    name
}
```

The only bare name permitted in a `returning` block is the compiler-provided
`_mutation` field on `upsert`, which has no bound variable owner.

### Returning After Insert

Get back generated UUIDs and timestamps immediately after creation, without a follow-up query. The variable bound in the `insert into` declaration is available to the `returning` block.
```tql
import "shared/commerce"

insert into "store/products" as p: commerce.Product {
    id:          gen_uuid(),
    name:        "Leather Wallet",
    price:       49.99,
    stock:       200,
    description: null
}
returning {
    id:   p.id,
    name: p.name
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

`conflict on` declares the field that triggers conflict detection. `values` introduces the full row to be written for new rows. `conflict set` declares the fields to update when a conflict is found.

```tql
import "shared/commerce"

upsert into "store/products" as p: commerce.Product
conflict on id
values {
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

### Upsert With Returning

`upsert` supports `returning` like any other mutation. The output includes a compiler-provided `_mutation` field of type `text` that tells you whether each row was inserted or updated. Its value is always either `"inserted"` or `"updated"`. The `_mutation` field is only valid inside a `returning` block — it cannot be referenced in `where`, `having`, `set`, or any other pipeline stage.
```tql
import "shared/commerce"

upsert into "store/products" as p: commerce.Product
conflict on id
values {
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
    id:        p.id,
    name:      p.name,
    _mutation             // compiler-provided, no variable owner
}
```

---

## 6. Pipeline Position Summary

### Query Pipeline
```
from → where → let → select → order by → limit
```

### Insert Pipeline (literal)
```
insert into → values → returning
```

### Insert Pipeline (from source)
```
insert into → from → where → let → select → returning
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