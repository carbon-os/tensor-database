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
    id:       uuid
    name:     text
    price:    decimal(10,2)
    stock:    int32
    raw_data: text    // raw descriptions, specs, any unstructured text
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

## Querying
```tql
import "shared/commerce"

from "store/products" as p: commerce.Product
where p.stock > 0
prompt("gift ideas under fifty dollars", tensor.REASONING) from p.raw_data as result: commerce.ProductResult

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

Because `result` fields are normal `.tql` fields the full pipeline works as expected.
```tql
import "shared/commerce"

from "store/products" as p: commerce.Product
where p.stock > 0

prompt("gift ideas under fifty dollars", tensor.REASONING) from p.raw_data as result: commerce.ProductResult

where result.price < 50.00

group by result.name
select {
    name:      result.name,
    avg_price: avg(result.price)
}
order by avg_price asc
```

---

## What the Engine Does Internally

When a `prompt()` stage is reached the engine handles everything:
```
raw_data text field
    │
    ▼
tokenize                        // engine tokenizes the raw text internally
    │
    ▼
split into 32k segments         // each segment fills one nano model context window
    │
    ├── segment 1 → nano model  // "does this contain gift ideas under $50? yes: Air Max $99"
    ├── segment 2 → nano model  // "does this contain gift ideas under $50? no relevant info"
    ├── segment 3 → nano model  // "does this contain gift ideas under $50? yes: Mug $14.99"
    │   ... up to N models running fully async
    │
    ▼
aggregator model                // smarter model, receives all nano responses
    │                           // uses your output schema as its output contract
    ▼
structured fields               // normal .tql typed fields, continue in pipeline
```

---

## Internal Models

The engine maintains two model roles internally. These are never referenced
in `.tql` directly — they are daemon configuration.

### Worker Model — Nano

Handles reading comprehension over a single 32k segment. Does not need
multi-step reasoning. Its only job is:

> "Does this segment contain relevant information for the prompt, and if so what is it?"
```
Recommended:    Qwen2.5-0.5B   Q4_K_M   ~400MB on disk
                                         loaded once, shared across all instances
                                         32k token context window
                                         holds reading comprehension reliably

Do not go below 0.5B parameters. Below this threshold models begin losing
facts that are explicitly in their context window — missing negation,
dropping numbers, losing track of the question mid-context above ~4k tokens.
That failure mode defeats the architecture entirely.
```

### Aggregator Model — Smarter

Receives all nano model responses and synthesizes them into structured output
matching your declared schema. Needs real reasoning and strong instruction
following — a 0.5B model is too marginal here.
```
Recommended:    Qwen2.5-3B-Instruct   Q4_K_M   ~1.9GB
                                                good reasoning
                                                strong instruction following
                                                uses your .tql type as output contract

Stronger:       Qwen2.5-7B-Instruct   Q4_K_M   ~4.4GB
                Qwen2.5-14B-Instruct  Q4_K_M   ~8.8GB
```

---

## Making Models Smaller When Segments Are Large

When the total raw text across your dataset grows, each segment covers less
data and more nano instances are needed simultaneously. The engine has one
technique to reduce memory pressure without quality loss.

### Quantization

Reduce the bits used to represent each model weight via llama.cpp.
Q4_K_M is the recommended floor for both worker and aggregator.
```
Worker model Qwen2.5-0.5B:

  float16    ~988MB    baseline
  Q8_0       ~494MB    nearly lossless
  Q5_K_M     ~340MB    very good
  Q4_K_M     ~400MB    recommended sweet spot
  Q3_K_M     ~215MB    noticeable degradation on reading comprehension
  Q2_K       ~180MB    significant loss — misses explicit facts
  IQ1_S      ~110MB    not viable

At 0.5B scale quantization saves ~600MB on the weights.
The KV caches are the real bottleneck at this size, not the weights.
Quantization matters more for the aggregator where the weight
size is meaningful (3B-14B range).
```

---

## Capacity on 48GB VRAM

Reference hardware: dual RTX 4090 (48GB) or RTX 6000 Ada (48GB single card).
Dual 4090 is the practical recommendation — instances are fully independent
with no inter-GPU communication so the lack of NVLink is not a bottleneck.
```
KV cache per token — Qwen2.5-0.5B (GQA architecture):

  2  × (K and V)
  2  × (key-value heads — GQA, not full attention heads)
  64 × (head dimension)
  24 × (layers)
  2  × (float16 bytes)
  = 12,288 bytes ≈ 12KB per token
```
```
Recommended configuration:

  48GB total VRAM
  -  1.9GB  Qwen2.5-3B aggregator   Q4_K_M  (resident)
  -  0.4GB  Qwen2.5-0.5B worker     Q4_K_M  (shared across all instances)
  -  2.0GB  runtime overhead
  = 43.7GB  available for worker KV caches

  At 1:1 (no compression):

  KV per instance    Instances (~43.7GB)    Tokens in flight    Raw text covered
  ────────────────────────────────────────────────────────────────────────────────
  384MB              ~113                   3.6M                3.6M tokens
```

Running a 3B aggregator instead of 0.5B costs ~20 worker instances.
The synthesis quality improvement is worth that cost.

---

## Storage Modules
```
.tok    Pre-tokenized int32 arrays
        Engine tokenizes raw_data at write time and caches the result.
        Loading a segment into a context window becomes a memcpy.
        Invalidated when the worker model changes.
```

**Full storage layer:**
```
tensor-db
├── .wal      write-ahead log
├── .sst      scalar PAX columns
├── .rbm      roaring bitmap inverted index
├── .vec      raw float32 vectors
├── .hnsw     ANN graph index
└── .tok      pre-tokenized int32 arrays
```

---

## That Is the Whole Surface
```
1. store raw text in any text field
2. prompt("your question", tensor.REASONING) from p.your_text_field as result: YourOutputSchema
3. use result fields like any other field in the rest of the pipeline
```

Tokenization, segmentation, nano model fan-out, async parallel inference,
quantization, aggregation, and structured output conversion all happen inside
the engine. The pipeline never sees any of it.