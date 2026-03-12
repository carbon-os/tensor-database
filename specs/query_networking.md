# Query Networking (`query_networking.md`)

---

## How Queries Execute

Tensor Database uses a standard client/server model. The client sends a `.tql`
pipeline to the daemon over a transport, the daemon executes it entirely
server-side, and the results are streamed back. The client has no query planner,
no storage access, and no awareness of how any pipeline stage is resolved
internally.

This applies uniformly to every operation — scalar filters, joins, aggregations,
`embed()`, `prompt()`. From the client's perspective they are all just parts of a
pipeline that went in and rows that came back.

---

## Transports

### Unix Domain Socket — Local

```
/tmp/tensordb.sock
```

Used for all local access: the CLI, the REPL, and any process running on the
same host. Authentication is handled by OS-level file permissions on the socket
— no credentials required for permitted users.

This is the default transport. Any tool that talks to a local Tensor Database
instance uses it automatically.

### QUIC — Remote

Used for connections from other hosts. QUIC gives low-latency multiplexed
streams over UDP without the head-of-line blocking of TCP, which matters when
streaming large result sets or running many concurrent pipelines.

Remote connections authenticate with API key bearer tokens bound to path-level
IAM roles. See `iam.md` for access control details.

---

## Wire Format

Queries are sent as plain text — the `.tql` pipeline string as-is, framed with
a small binary envelope: a 1-byte message type, a 4-byte length, then the
pipeline as UTF-8 bytes. The daemon parses and plans it server-side.

```
┌──────────┬────────────────┬─────────────────────────────┐
│  type    │  length        │  payload                    │
│  1 byte  │  4 bytes       │  n bytes (UTF-8)            │
└──────────┴────────────────┴─────────────────────────────┘
```

### Message Types

| Byte | Type | Description |
|---|---|---|
| `0x51` | Query | Execute a `.tql` pipeline |
| `0x58` | Terminate | Close the connection |

---

## Sending a Query

A scalar query:

```
51 00 00 00 3A
66 72 6F 6D 20 22 73 74 6F 72 65 2F 70 72 6F 64
75 63 74 73 22 20 61 73 20 70 ...
```

```
type:    0x51          →  Query
length:  0x0000003A    →  58 bytes follow
payload: from "store/products" as p: commerce.Product where p.stock > 0 limit 10
```

The payload is always the raw `.tql` string. A pipeline that calls `embed()` or
`prompt()` is no different on the wire — those are resolved server-side during
execution.

```
type:    0x51          →  Query
length:  0x000000A2    →  162 bytes follow
payload: from "store/products" as p: commerce.Product
         where p.stock > 0 and p.price < 50.00
         order by p.embedding <-> embed("gift ideas under fifty dollars")
         limit 10
```

```
type:    0x51          →  Query
length:  0x000000C4    →  196 bytes follow
payload: from "store/products" as p: commerce.Product
         where p.stock > 0
         prompt("gift ideas under fifty dollars", tensor.REASONING) from p.raw_data as result: commerce.ProductResult
         select { name: result.name, price: result.price, reason: result.reason }
         order by result.price asc
         limit 10
```

---

## Result Rows

Results stream back as newline-delimited JSON. The daemon begins streaming as
soon as the first rows are available — the client does not wait for the full
result set to materialize.

A scalar result row:

```json
{"id":"a1b2c3","name":"Air Max 270","price":99.99,"stock":200}
{"id":"d4e5f6","name":"Pegasus 40","price":44.99,"stock":85}
```

A row with a vector field — vectors are returned as JSON float arrays:

```json
{"id":"a1b2c3","name":"Air Max 270","embedding":[0.1823,0.0492,-0.3781,0.2156, ... 764 more]}
```

A `prompt()` result row — structured fields from the declared output schema:

```json
{"name":"Pegasus 40","price":44.99,"reason":"Running shoe under $50, good fit for gift ideas"}
```

A hybrid query result — scalar, keyword, and semantic fields together:

```json
{"id":"d4e5f6","name":"Pegasus 40","price":44.99,"stock":85,"score":0.94}
```

---

## End of Results

After the final row the daemon sends a completion envelope:

```
┌──────────┬────────────────┐
│  type    │  length        │
│  1 byte  │  4 bytes       │
└──────────┴────────────────┘

type:    0x43    →  CommandComplete
length:  0x00000000
```

The client reads rows until it receives `CommandComplete`, then the stream is
done.

---

## The Daemon Socket

When the daemon starts it opens the Unix Domain Socket and the QUIC port, then
waits for pipelines. Both transports use the same wire format and land in the
same execution engine — there is no difference in behavior or capability between
a query sent locally and one sent remotely.

```bash
tensor db start        // opens /tmp/tensordb.sock and QUIC port
tensor db status       // shows active connections on both transports
```

See `cli.md` for full daemon lifecycle commands.