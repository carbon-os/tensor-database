# Query Pipeline (`query.md`)

---

## The Pipeline Model

A Tensor Database query is a strict, top-to-bottom pipeline. Data enters at the top, flows through filtering and transformation steps, and exits shaped at the bottom. There is no way to reference a downstream value upstream — the order is the contract.

The full pipeline superset is:
```
from → join → where → group by → let → having → select → order by → limit
```

Not every stage is required in every query. The stages that are present must always appear in this order. The three common forms are:

**Scalar query** — no join, no aggregation:
```
from → where → let → select → order by → limit
```

**Join query** — multiple paths, no aggregation:
```
from → join → where → let → select → order by → limit
```

**Aggregation query** — with or without a join:
```
from → join → where → group by → let → having → select → order by → limit
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

## `join` — Binding Additional Paths

A `join` immediately follows `from` and binds a second path to its own variable and type contract. Both variables are available to every downstream stage. Multiple joins are declared sequentially — each adds a new bound variable to the pipeline.

See `joins.md` for full join syntax, join types, and examples.
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
join "store/products" as p: commerce.Product on o.product_id == p.id

where o.status == "completed"
select {
    order_id: o.id,
    product:  p.name,
    total:    o.total
}
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

## `group by` — Collapsing the Stream

Collapses the row stream into groups. Once `group by` is present every field in `select` must either appear in the grouping key or be wrapped in an aggregate function. See `aggregations.md` for full aggregation syntax and examples.
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
where o.status == "completed"
group by o.customer_id
select {
    customer:    o.customer_id,
    order_count: count(o.id),
    total_spent: sum(o.total)
}
```

---

## `let` — Pipeline Bindings

`let` bindings require an explicit type annotation at every declaration. The compiler rejects any `let` without a type — inference is not supported. This keeps pipelines unambiguous and consistent with the strict typing enforced everywhere else in `.tql`.

```tql
let name: Type = expression
```

`let` can appear at two points in the pipeline:

**Before `from`** — for global bindings computed once before the scan begins.

**After `where` (or after `group by` in an aggregation pipeline)** — for row-level or group-level bindings computed mid-stream.

```tql
import "shared/commerce"

// Global binding — executed once before the scan
let low_stock_threshold: int32 = 20

from "store/products" as p: commerce.Product

// Row-level binding — computed per row mid-stream
let needs_reorder: bool = p.stock < low_stock_threshold

where needs_reorder == true
```

`let` never builds a temporary table or a CTE. It is a named expression the compiler inlines at the point of use.

---

## `having` — Filtering Groups

`having` filters the grouped stream after aggregation. It is only valid when `group by` is present. `where` filters individual rows before grouping — `having` filters groups after aggregation and has access to aggregate values. See `aggregations.md` for full examples.
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
where o.status == "completed"
group by o.customer_id
having sum(o.total) > 1000.00
select {
    customer:    o.customer_id,
    total_spent: sum(o.total)
}
```

---

## `select` — The Projection

The `select` block shapes the final output. It behaves like an object literal, allowing you to rename fields, compute derived values, and return clean nested structures.
```tql
import "shared/commerce"

from "store/products" as p: commerce.Product
where p.stock > 0

let revenue_potential: decimal(10,2) = p.price * p.stock

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
order by t.embedding <-> embed("refund request", tensor.SEARCH)
limit 10
```

See `ai_backend.md` for backend configuration and `storage.md` for how the `.hnsw` index and `.vec` module handle vector queries.