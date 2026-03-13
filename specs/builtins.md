# Built-In Functions (`builtins.md`)

---

## Overview

Tensor Database ships a set of built-in functions available in any `.tql`
pipeline without an import. They are first-class values — each returns a
typed result that the compiler validates at the point of use.

---

## `gen_uuid()` — Generate a UUID

Returns a new cryptographically random `uuid` each time it is called. The
standard choice for primary key generation on insert.

```tql
gen_uuid() → uuid
```

```tql
import "shared/commerce"

insert into "store/products" as commerce.Product {
    id:    gen_uuid(),
    name:  "Leather Wallet",
    price: 49.99,
    stock: 200
}
```

Each row in a multi-row insert gets its own unique value — `gen_uuid()` is
evaluated independently per row, not once for the batch.

```tql
import "shared/commerce"

insert into "store/products" as commerce.Product
    { id: gen_uuid(), name: "Leather Wallet",  price: 49.99, stock: 200 },
    { id: gen_uuid(), name: "Canvas Backpack", price: 89.99, stock: 85  },
    { id: gen_uuid(), name: "Ceramic Mug",     price: 14.99, stock: 500 }
```

---

## `now()` — Current Timestamp

Returns the current time as a `timestamp` (microseconds since the Unix epoch,
always UTC). Useful for audit fields, expiry calculations, and soft deletes.

```tql
now() → timestamp
```

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

```tql
import "shared/commerce"

update "store/sessions" as s: identity.Session
where s.expires_at < now()
set {
    status: "expired"
}
```

`now()` is evaluated once per pipeline execution, not once per row. Every row
in the same pipeline sees the same timestamp.

---

## `match()` — Keyword Search

Performs a full-text keyword lookup against the `.rbm` inverted index. Does
not scan raw strings — it loads the compressed bitmap for the token and
executes a bitwise operation against other predicates in the `where` clause.

```tql
match(field, "token") → bool
```

```tql
import "shared/support"

from "store/tickets" as t: support.Ticket
where t.status == "open"
  and match(t.message, "payment")
```

Multiple `match()` calls in the same `where` clause are combined using
hardware-level bitwise operations before any rows are loaded from the `.sst`.

```tql
import "shared/support"

from "store/tickets" as t: support.Ticket
where match(t.message, "kernel") and match(t.message, "panic")
```

`match()` only works on `text` fields. Applying it to any other type is a
compile-time error.

---

## `embed()` — Semantic Embedding

Generates a vector embedding from a text string for use in semantic search.
Returns a `vector(n)` sized to the dimensions of the chosen model.

```tql
embed("query", tensor.SEARCH)    → vector(768)
embed("query", tensor.CLASSIFY)  → vector(384)
embed("query", tensor.CODE)      → vector(768)
```

```tql
import "shared/commerce"

from "store/products" as p: commerce.Product
where p.stock > 0
order by p.embedding <-> embed("waterproof outdoor gear", tensor.SEARCH)
limit 10
```

See `ai_backend.md` for constants, default models, and backend configuration.

---

## `prompt()` — Reasoning Over Raw Text

Runs the nano+aggregator inference pipeline over a raw text field and returns
a fully typed result bound via `let`.

```tql
let result: OutputType = prompt(source_field, "query", tensor.REASONING)
```

```tql
import "shared/commerce"

from "store/products" as p: commerce.Product
where p.stock > 0

let result: commerce.ProductResult = prompt(p.raw_data, "gift ideas under fifty dollars", tensor.REASONING)

select {
    name:   result.name,
    price:  result.price,
    reason: result.reason
}
```

See `ai_backend.md` for constants and `reasoning.md` for the full
nano+aggregator architecture.