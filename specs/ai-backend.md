# AI Backend (`ai_backend.md`)

---

## Built-In Embeddings

Tensor Database ships with a native embedding engine. There is no separate process to configure, no remote endpoint to point at, and no model name to remember. The engine is built directly into the database daemon and exposed over the same Unix Domain Socket (`/tmp/tensordb.sock`) that all other queries use.

When the daemon starts, the embedding engine starts with it. When you call `embed()` in a `.tql` pipeline, the engine handles it inline — no round trips, no configuration, no failure domain to manage.

---

## `embed()` — The Query Interface

`embed()` takes a text string and an optional use-case constant. With no second argument it defaults to `tensor.SEARCH` silently.
```tql
embed("query")                      // silent default → tensor.SEARCH
embed("query", tensor.SEARCH)       // explicit retrieval / RAG
embed("query", tensor.CLASSIFY)     // clustering, categorization, tagging
embed("query", tensor.CODE)         // code similarity, code search
```

The second argument is a namespaced constant, not a string. This means typos and invalid values are caught at compile time before execution begins, consistent with the rest of `.tql`.

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

### Use-Case Constants

| Constant | Intent | Typical Use |
|---|---|---|
| `tensor.SEARCH` | Semantic retrieval | RAG pipelines, product search, ticket lookup |
| `tensor.CLASSIFY` | Grouping and labeling | Clustering, tagging, categorization |
| `tensor.CODE` | Code representation | Code search, diff similarity, symbol lookup |

---

## Default Models

Tensor Database ships with a custom inference engine built into the daemon. It loads and runs open source embedding models directly — no external runtime, no GPU required for standard workloads. When you call `embed()`, the inference engine encodes your input and returns the vector inline.

Each use-case constant maps to a curated default model chosen for accuracy, speed, and permissive licensing. You never need to reference these directly — they are the implementation behind the constant.

| Constant | Default Model | Dimensions | License |
|---|---|---|---|
| `tensor.SEARCH` | `nomic-embed-text-v1.5` | 768 | Apache 2.0 |
| `tensor.CLASSIFY` | `all-MiniLM-L6-v2` | 384 | Apache 2.0 |
| `tensor.CODE` | `jina-embeddings-v2-base-code` | 768 | Apache 2.0 |

These defaults will be updated as better open source models are released. Because the model is abstracted behind the constant, your `.tql` pipelines require no changes when defaults are upgraded — the same `tensor.SEARCH` call simply gets better results.

---

## Unix Socket — Agent & External Access

The embedding engine is also accessible directly over the Unix Domain Socket as a lightweight helper for agents and external processes that need embeddings without running a full `.tql` pipeline.

Any process with access to `/tmp/tensordb.sock` can request an embedding by sending a JSON payload:
```json
{
    "embed": "your input text here",
    "mode": "SEARCH"
}
```

The socket returns a raw float array immediately:
```json
{
    "vector": [0.12, -0.45, 0.88, "..."]
}
```

`mode` accepts `SEARCH`, `CLASSIFY`, or `CODE` and maps directly to the same models backing the `tensor.*` constants in `.tql`. If `mode` is omitted it defaults to `SEARCH`.

This makes the embedding engine a first-class utility for agents operating outside the database — an agent can generate embeddings on the fly to construct semantic queries, rank results, or compare documents without any additional infrastructure.

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
Models:        tensor.SEARCH, tensor.CLASSIFY, tensor.CODE
Latency:       0.8ms avg (last 100 calls)
```