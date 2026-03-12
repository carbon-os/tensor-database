# AI Backend (`ai_backend.md`)

---

## Built-In AI Engine

Tensor Database ships with a native AI engine. There is no separate process to
configure, no remote endpoint to point at, and no model name to remember. The
engine is built directly into the database daemon and exposed over the same Unix
Domain Socket (`/tmp/tensordb.sock`) that all other queries use.

When the daemon starts, the AI engine starts with it. When you call `embed()` or
`prompt()` in a `.tql` pipeline, the engine handles it inline — no round trips,
no configuration, no failure domain to manage.

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

let query_vec = embed("gift ideas under fifty dollars")

from "store/products" as p: commerce.Product
where p.stock > 0 and p.price < 50.00
order by p.embedding <-> query_vec
limit 10
```

---

## `prompt()` — Reasoning Over Raw Text

`prompt()` takes a natural language prompt and runs the nano+aggregator inference
pipeline over a raw text field, returning a fully typed result that flows into
the rest of the pipeline like any other variable.
```tql
prompt("prompt", tensor.REASONING)   // nano+aggregator pipeline — full reading comprehension
```

### In a Query Pipeline
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

## Unix Socket — Agent & External Access

The AI engine is also accessible directly over the Unix Domain Socket as a
lightweight helper for agents and external processes that need embeddings or
reasoning without running a full `.tql` pipeline.

Any process with access to `/tmp/tensordb.sock` can request an embedding:
```json
{
    "embed": "your input text here",
    "mode": "SEARCH"
}
```

Or a reasoning pass over raw text:
```json
{
    "prompt": "gift ideas under fifty dollars",
    "text":   "Nike Air Max 270 running shoe...",
    "mode":   "REASONING"
}
```

Both return immediately. `embed` returns a raw float array. `prompt` returns
a JSON object matching the shape of your declared output schema.

`mode` accepts `SEARCH`, `CLASSIFY`, `CODE`, and `REASONING`. If `mode` is
omitted it defaults to `SEARCH`.

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