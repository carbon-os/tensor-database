# Query Pipeline (`query.md`)

---

## The Pipeline Model

A Tensor Database query is a strict, top-to-bottom pipeline. Data enters at the top, flows through filtering and transformation steps, and exits shaped at the bottom. There is no way to reference a downstream value upstream — the order is the contract.
```
from → where → let → select → order by → limit
```

---

## `import` & `from` — Entry Point & Row Binding

Every query must import the necessary types and explicitly bind the incoming data stream to a variable. This eliminates magic columns and gives the compiler everything it needs to validate the rest of the pipeline before a single row is read.

The `from` operator strictly targets managed Tensor Database logical paths instantiated via `create table`. It does not parse raw files or accept ad-hoc paths.
```tql
import "shared/commerce"

// 'p' represents the current row in the execution pipeline.
// The compiler guarantees the underlying .sst binary data perfectly
// matches the commerce.Product memory layout.
from "store/products" as p: commerce.Product
```

---

## `where` — The Filter

Filters rows based on a strict `bool` condition. There is no implicit integer coercion — expressions must evaluate exactly to `true` or `false`.
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
where o.status == "pending" and o.total > 500.00
```

The query planner pushes these predicates down to the storage readers, skipping dead rows before they ever reach the CPU cache.

---

## `let` — Pipeline Bindings

`let` is a zero-cost compiler binding that can appear at two points in the pipeline: before `from` for global bindings computed once, and between `where` and `select` for row-level bindings computed per row.
```tql
import "shared/commerce"

// Global binding — executed once before the scan
let low_stock_threshold: int32 = 20

from "store/products" as p: commerce.Product

// Row-level binding — computed per row mid-stream
let needs_reorder = p.stock < low_stock_threshold

where needs_reorder == true
```

`let` never builds a temporary table or a CTE. It is a named expression the compiler inlines at the point of use.

---

## `select` — The Projection

The `select` block shapes the final output. It behaves like an object literal, allowing you to rename fields, compute derived values, and return clean nested structures.
```tql
import "shared/commerce"

from "store/products" as p: commerce.Product
where p.stock > 0

let revenue_potential = p.price * p.stock

select {
    id:   p.id,
    name: p.name,
    inventory: {
        units:     p.stock,
        value:     revenue_potential,
        is_scarce: p.stock < 10
    }
}
```

---

## `order by` & `limit` — Terminal Operations

Sorting and limiting always happen at the very end of the pipeline. The execution engine uses a bounded min-heap internally, so massive datasets are never fully sorted in memory.
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
where o.status == "completed"
select { id: o.id, customer: o.customer_id, total: o.total }
order by total desc
limit 25
```

`order by` and `limit` are terminal — nothing can follow them in the pipeline.

---

## Semantic Search with `embed()`

When a `vector(n)` field is present on the type, the pipeline supports semantic ordering via the `<->` distance operator. The `embed()` call is dispatched to the configured AI backend and the resulting vector is dropped into the `.hnsw` index for nearest-neighbor traversal.
```tql
import "shared/support"

from "store/tickets" as t: support.Ticket
where t.status == "open"
order by t.embedding <-> embed("refund request", 'nomic-embed-v1.5')
limit 10
```

See `ai_backend.md` for backend configuration and `storage.md` for how the `.hnsw` index and `.vec` module handle vector queries.