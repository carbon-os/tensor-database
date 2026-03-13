# AI Backend (`ai_backend.md`)

---

## Built-In AI Engine

Tensor Database ships with a native AI engine built directly into the daemon.
When you call `embed()` or `prompt()` in a `.tql` pipeline, the engine resolves
them inline during execution — no external model server, no separate process,
no additional configuration.

---

## `embed()` — Semantic Search

`embed()` takes a text string and an optional use-case constant. With no second
argument it defaults to `tensor.SEARCH` silently.
```tql
embed("query")                      // silent default → tensor.SEARCH
embed("query", tensor.SEARCH)       // explicit retrieval / RAG
embed("query", tensor.CLASSIFY)     // clustering, categorization, tagging
embed("query", tensor.CODE)         // code similarity, code search
```

### In a Query Pipeline
```tql
import "shared/commerce"

from "store/products" as p: commerce.Product
where p.stock > 0
order by p.embedding <-> embed("waterproof outdoor gear")
limit 10
```
```tql
import "shared/commerce"

let query_vec: vector(768) = embed("gift ideas under fifty dollars")

from "store/products" as p: commerce.Product
where p.stock > 0 and p.price < 50.00
order by p.embedding <-> query_vec
limit 10
```

---

## `prompt()` — Reasoning Over Raw Text

`prompt()` takes a source field, a natural language prompt, and a mode constant.
It runs the nano+aggregator inference pipeline over the source field and returns
a fully typed result bound via `let` that flows into the rest of the pipeline
like any other variable.
```tql
let result: OutputType = prompt(source_field, "query", tensor.REASONING)
```

The type annotation on the `let` binding is required. The declared type is used
as the output contract for the aggregator model — it must be a type defined in
an imported package.

### In a Query Pipeline
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
order by result.price asc
limit 10
```

The mode constant is validated at compile time. Typos and unsupported modes are
caught before execution begins, consistent with the rest of `.tql`.

---

## Constants

### Embedding Constants — `embed()`

| Constant | Intent | Typical Use |
|---|---|---|
| `tensor.SEARCH` | Semantic retrieval | RAG pipelines, product search, ticket lookup |
| `tensor.CLASSIFY` | Grouping and labeling | Clustering, tagging, categorization |
| `tensor.CODE` | Code representation | Code search, diff similarity, symbol lookup |

### Prompt Constants — `prompt()`

| Constant | Intent | Typical Use |
|---|---|---|
| `tensor.REASONING` | Full nano+aggregator pipeline | Complex questions, multi-fact synthesis |

---

## Default Models

Each constant maps to a curated default model chosen for accuracy, speed, and
permissive licensing. You never need to reference these directly — they are the
implementation behind the constant. Model defaults will be updated as better open
source options are released. Because the model is abstracted behind the constant,
your `.tql` pipelines require no changes when defaults are upgraded.

### Embedding Models

| Constant | Default Model | Dimensions | License |
|---|---|---|---|
| `tensor.SEARCH` | `nomic-embed-text-v1.5` | 768 | Apache 2.0 |
| `tensor.CLASSIFY` | `all-MiniLM-L6-v2` | 384 | Apache 2.0 |
| `tensor.CODE` | `jina-embeddings-v2-base-code` | 768 | Apache 2.0 |

### Prompt Models

| Constant | Worker Model | Aggregator Model |
|---|---|---|
| `tensor.REASONING` | `Qwen2.5-0.5B Q4_K_M` | `Qwen2.5-3B-Instruct Q4_K_M` |

See `reasoning.md` for details on the nano+aggregator architecture, quantization,
and capacity planning.

---

## Verifying the Engine
```bash
tensor db ai status
```

**Example output:**
```text
AI Backend Status
-----------------
Backend:       built-in
Socket:        /tmp/tensordb.sock
Status:        running
Embedding:     tensor.SEARCH, tensor.CLASSIFY, tensor.CODE
Prompt:        tensor.REASONING
Latency:       0.8ms avg embed / 42ms avg prompt (last 100 calls)
```