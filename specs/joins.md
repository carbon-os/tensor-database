# Joins (`joins.md`)

---

## Joins in the Pipeline

A join combines two paths into a single row stream before any filtering or projection occurs. Tensor Database supports joins as a natural extension of the pipeline model — the joined paths are bound at the entry point and the rest of the pipeline operates on the combined row as if it were a single type.
```
from → join → where → group by → let → having → select → order by → limit
```

---

## `join` — The Entry Point

A join is declared immediately after `from`, binding the second path to its own variable and type contract. The `on` clause defines the match condition.
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
join "store/products" as p: commerce.Product on o.product_id == p.id

where o.status == "completed"
select {
    order_id:  o.id,
    customer:  o.customer_id,
    product:   p.name,
    price:     p.price,
    total:     o.total
}
```

Both variables are available to every downstream stage — `where`, `let`, `group by`, `having`, and `select` all have full access to `o` and `p`.

---

## Join Types

### `join` — Inner Join

The default. Only rows where the `on` condition matches in both paths are included in the stream. Rows with no match on either side are dropped.
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
join "store/customers" as c: commerce.Customer on o.customer_id == c.id

where o.status == "completed"
select {
    order_id:  o.id,
    name:      c.name,
    email:     c.email,
    total:     o.total
}
```

### `left join` — Left Outer Join

All rows from the left path are included. If no match exists in the right path, its fields are returned as `null`. The right-side type must be fully nullable when using a left join.
```tql
import "shared/commerce"

from "store/products" as p: commerce.Product
left join "store/reviews" as r: commerce.Review on r.product_id == p.id

select {
    product:      p.name,
    review_score: r.score,       // null if no review exists
    review_body:  r.body         // null if no review exists
}
```

---

## Filtering Across Paths

`where` has full access to both bound variables, so cross-path filtering is just a normal boolean expression.
```tql
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

---

## Aggregating Across Paths

`group by` and aggregate functions work identically on joined streams. Group by any field from either path.
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
join "store/products" as p: commerce.Product on o.product_id == p.id

where o.status == "completed"
group by p.id, p.name

let units_sold    = count(*)
let gross_revenue = sum(o.total)

having gross_revenue > 10000.00

select {
    product:       p.name,
    units_sold,
    gross_revenue,
    average_order: avg(o.total)
}
order by gross_revenue desc
```

---

## `let` Bindings Across Paths

`let` bindings mid-pipeline can reference fields from both paths freely.
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
join "store/products" as p: commerce.Product on o.product_id == p.id

where o.status == "completed"

let margin        = o.total - p.price
let is_profitable = margin > 0.00

where is_profitable == true
select {
    order_id: o.id,
    product:  p.name,
    margin
}
order by margin desc
limit 25
```

---

## Multiple Joins

Additional paths can be joined sequentially. Each adds a new bound variable available to all downstream stages.
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
join "store/products"  as p: commerce.Product  on o.product_id  == p.id
join "store/customers" as c: commerce.Customer on o.customer_id == c.id

where o.status == "completed"
select {
    order_id:  o.id,
    customer:  c.name,
    email:     c.email,
    product:   p.name,
    total:     o.total,
    placed_at: o.placed_at
}
order by o.placed_at desc
limit 50
```

Each additional join narrows the stream further — a row must satisfy all `on` conditions to pass through.