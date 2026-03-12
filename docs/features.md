# Tensor Reasoning (`reasoning.md`)

---

## The Idea

Store raw text. Query it with natural language. Get back structured fields.

The engine handles tokenization, splitting, parallel inference, and aggregation
internally. From the outside you put text in and structured `.tql` fields come out.

---

## Schema

Add a `text` field. That is the only addition needed. No vector fields, no token
arrays, no embedding configuration.

```tql
package commerce

type Product {
    id:          uuid
    name:        text
    price:       decimal(10,2)
    stock:       int32
    raw_data:    text    // raw descriptions, specs, any unstructured text
}

type ProductResult {
    name:    text
    price:   decimal(10,2)
    reason:  text?
}
```

---

## Loading Data

Insert raw text directly. Nothing special about the write path.

```go
// golang — insert raw product text over the unix socket
payload := map[string]any{
    "query": `
        import "shared/commerce"
        insert into "store/products" as commerce.Product {
            id:       gen_uuid(),
            name:     "Air Max 270",
            price:    99.99,
            stock:    200,
            raw_data: "Nike Air Max 270 running shoe featuring a large Air unit
                       in the heel. Available in sizes 7-13. Colorways include
                       black/white and university red. Retail price $99.99."
        }
    `,
}

conn.Write(json.Marshal(payload))
```

---

## What the Engine Does Internally

When a `generate` stage is reached the engine handles everything:

```
raw_data text field
    │
    ▼
tokenize                        // engine tokenizes the raw text internally
    │
    ▼
split into 32k segments         // each segment fills one nano model context window
    │
    ├── segment 1 → nano model  // "does this contain gift ideas under $50? yes: Air Max $99 no"
    ├── segment 2 → nano model  // "does this contain gift ideas under $50? no relevant info"
    ├── segment 3 → nano model  // "does this contain gift ideas under $50? yes: Ceramic Mug $14.99"
    │   ... up to N models running fully async
    │
    ▼
aggregator model                // smarter model, receives all responses
    │                           // uses your output schema as its output contract
    ▼
structured fields               // normal .tql typed fields you use in the pipeline
```

None of this is visible in the query. The `generate` stage produces a typed object
and the rest of the pipeline treats it like any other row.

---

## Querying

```tql
import "shared/commerce"

from "store/products" as p: commerce.Product
where p.stock > 0
generate "gift ideas under fifty dollars"
    using  p.raw_data
    as     result: commerce.ProductResult

select {
    name:   result.name,
    price:  result.price,
    reason: result.reason
}
order by result.price asc
limit 10
```

`result` is a normal typed object. Every field on `commerce.ProductResult` is
available to `select`, `where`, `order by`, and any downstream pipeline stage.

---

## Composing With the Rest of the Pipeline

Because `result` fields are normal `.tql` fields, the full pipeline works as expected.

```tql
import "shared/commerce"

from "store/products" as p: commerce.Product
where p.stock > 0

generate "gift ideas under fifty dollars"
    using  p.raw_data
    as     result: commerce.ProductResult

// filter on the structured output
where result.price < 50.00

// aggregate over it
group by result.name
select {
    name:       result.name,
    avg_price:  avg(result.price)
}
order by avg_price asc
```

---

## That Is the Whole Surface

```
1. store raw text in any text field
2. generate "your question" using p.your_text_field as result: YourOutputSchema
3. use result fields like any other field in the rest of the pipeline
```

Tokenization, segmentation, nano model fan-out, async parallel inference,
aggregation, and structured output conversion all happen inside the engine.
The query never sees any of it.