# Modern Database Query Languages

SQL's 30-year dominance is being challenged. The `SELECT → FROM → WHERE` inside-out reading order is being replaced by pipeline-oriented, strictly-typed, top-to-bottom execution models across next-generation engines.

The consensus is clear — databases are no longer static data stores. They are execution engines for complex data streams, AI vectors, and system telemetry. Here is the modern landscape that informed `.tql`'s design.

---

## PRQL (Pipelined Relational Query Language)

SQL is hard to read and impossible to compose. PRQL compiles down to SQL but reverses the syntax into a sequential pipeline. Data enters at the top, gets transformed step by step, and exits at the bottom.

**Validates:** Top-to-bottom execution, `let` bindings for constants, mid-pipeline derived columns.
```prql
let memory_threshold = 8192
let target_status = "running"

from system_containers
filter status == target_status
filter allocated_ram >= memory_threshold
derive [
    total_cpu_time = user_cpu + kernel_cpu,
    is_critical = total_cpu_time > 10000
]
filter is_critical == true
select [ id, image_name, total_cpu_time ]
sort [-total_cpu_time]
take 10
```

---

## KQL (Kusto Query Language)

Built by Microsoft for high-throughput telemetry, logs, and time-series data. Powers Azure Data Explorer. Abandons SQL entirely for a Unix-style pipe (`|`) architecture.

**Validates:** `let` to set up the query environment before the first table scan. Highly optimized for machine-generated data.
```kusto
let StartTime = ago(1h);
let TargetAgent = "local-llama-3";

system_telemetry_logs
| where timestamp > StartTime
| where agent_name == TargetAgent
| extend execution_time_ms = datetime_diff('millisecond', end_time, start_time)
| where execution_time_ms > 500
| project trace_id, execution_time_ms, error_code
| order by execution_time_ms desc
| limit 50
```

---

## SurrealQL (SurrealDB)

A multi-model database treating the query language like a scripting language — multi-step transactions, variable assignments, and native AI integration in a single request.

**Validates:** AI embeddings as native database primitives, not Python-side logic bolted on after the fact.
```surrealql
LET $query_text = "Container engine failed to mount virtiofs";
LET $prompt_embedding = vector::embed('llama-3-8b', $query_text);
LET $min_score = 0.85;

SELECT
    id,
    timestamp,
    message,
    vector::similarity::cosine(embedding, $prompt_embedding) AS match_score
FROM system_events
WHERE type = "crash"
    AND vector::similarity::cosine(embedding, $prompt_embedding) > $min_score
ORDER BY match_score DESC
LIMIT 5;
```

---

## EdgeQL (EdgeDB)

A strict, strongly-typed graph-relational database built on PostgreSQL. Fixes SQL's type ambiguity by treating data as connected objects with strict shapes.

**Validates:** Non-nullable by default, `WITH :=` assignments over joins and subqueries, hierarchical data shaping in the final select block.
```edgedb
WITH
    target_port := 8080,
    active_vms := (
        SELECT VirtualMachine
        WHERE .status = 'running'
    )
SELECT active_vms {
    id,
    hostname,
    network_bindings: {
        ip_address,
        port
    } FILTER .port = target_port,
    is_exposed := EXISTS .network_bindings
}
FILTER .is_exposed = true;
```

---

## What This Means for `.tql`

Four patterns are consistent across every modern engine:

**The death of the CTE.** No modern engine uses `WITH alias AS (SELECT ...)` for intermediate state. `let` is the undisputed standard.

**Top-down execution.** Declare the source, filter, compute, project. Legacy SQL forces you to write the end of the story before the beginning.

**AI as a primitive.** Vector embeddings belong in the query language itself — not injected as raw float arrays from application code. `.tql`'s `embed()` with `tensor.*` constants is the natural evolution of what SurrealQL started.

**Strict output shaping.** The final `select` should return nested structures natively, not force clients to reconstruct meaning from flat rows.