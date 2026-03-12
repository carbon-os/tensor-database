# Aggregations (`aggregations.md`)

---

## Aggregations in the Pipeline

Aggregations follow the same top-to-bottom pipeline model as everything else in `.tql`. The `group by` clause sits after `where` and collapses the row stream into groups. `select` then operates on those groups rather than individual rows, using aggregate functions to produce a single output row per group.
```
from → where → group by → let → having → select → order by → limit
```

---

## `group by` — Collapsing the Stream
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

Every field in `select` must either appear in `group by` or be wrapped in an aggregate function. The compiler rejects any bare field reference that is not part of the grouping key.

---

## Aggregate Functions

### `count()`

Counts the number of rows in each group. `count(field)` excludes null values. `count(*)` counts all rows including nulls.
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
group by o.status
select {
    status:      o.status,
    order_count: count(*)
}
order by order_count desc
```

### `sum()`

Returns the total of a numeric field across the group.
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
where o.status == "completed"
group by o.customer_id
select {
    customer:       o.customer_id,
    lifetime_value: sum(o.total)
}
order by lifetime_value desc
limit 10
```

### `avg()`

Returns the mean of a numeric field across the group.
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
group by o.status
select {
    status:        o.status,
    average_order: avg(o.total)
}
```

### `min()` and `max()`

Return the lowest and highest values of a field across the group. Work on any orderable type — numeric, `timestamp`, `text`.
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
where o.status == "completed"
group by o.customer_id
select {
    customer:      o.customer_id,
    first_order:   min(o.placed_at),
    last_order:    max(o.placed_at),
    largest_order: max(o.total)
}
```

---

## `having` — Filtering Groups

`where` filters individual rows before grouping. `having` filters the resulting groups after aggregation. The distinction matters — `having` has access to aggregate values, `where` does not.
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
where o.status == "completed"
group by o.customer_id
having sum(o.total) > 1000.00
select {
    customer:    o.customer_id,
    total_spent: sum(o.total),
    order_count: count(*)
}
order by total_spent desc
```

---

## `let` Bindings With Aggregations

`let` bindings after `group by` have access to aggregate values, letting you compute derived metrics cleanly before the `select` projection.
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
where o.status == "completed"
group by o.customer_id

let total_spent   = sum(o.total)
let order_count   = count(*)
let average_order = total_spent / order_count

having total_spent > 500.00

select {
    customer:      o.customer_id,
    total_spent,
    order_count,
    average_order,
    is_high_value: total_spent > 5000.00
}
order by total_spent desc
limit 25
```

---

## Aggregating Without `group by`

Omitting `group by` collapses the entire result stream into a single row. Useful for global metrics across a full path.
```tql
import "shared/commerce"

from "store/orders" as o: commerce.Order
where o.status == "completed"
select {
    total_orders:   count(*),
    total_revenue:  sum(o.total),
    average_order:  avg(o.total),
    largest_order:  max(o.total),
    smallest_order: min(o.total)
}
```