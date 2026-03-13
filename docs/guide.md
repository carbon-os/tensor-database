# Design Guide (`guide.md`)

---

## Philosophy

Tensor Database is built on a small number of hard principles applied
consistently. Every syntax decision, type rule, and storage choice follows
from them. This document states those principles explicitly so that
contributors, integrators, and users understand not just what the rules
are but why they exist.

---

## 1. One Mental Model

A query is a pipeline. A mutation is a pipeline. An aggregation is a pipeline.
They all flow top-to-bottom through the same stages using the same syntax.
There is no separate `SELECT` world and `INSERT` world — data enters at the
top, transforms in the middle, and exits at the bottom.

This means a developer who understands one pipeline understands all of them.
Complexity comes from combining primitives, not from learning new statement
types.

---

## 2. Strict Typing, No Inference

Every `let` binding requires an explicit type annotation. Every field in a
type definition has an explicit type. Every function returns a known type the
compiler validates at the call site.

There is no type inference. This is intentional. Inference saves keystrokes
and loses clarity — in a pipeline language where types flow across stages,
implicit types make it harder to reason about what is happening at any given
point. Explicit annotations are documentation the compiler enforces.
```tql
// correct — intent is clear, compiler validates
let threshold: int32         = 20
let total:     decimal(10,2) = sum(o.total)

// compile-time error — annotation required
let threshold = 20
```

---

## 3. Non-Nullable by Default

Types are non-nullable unless explicitly marked with `?`. A field typed as
`text` must contain a string. A field typed as `text?` may be null and the
developer must handle both cases explicitly in the pipeline.

This eliminates an entire class of runtime errors. Null handling is opt-in,
not opt-out.
```tql
type Product {
    id:          uuid     // required — never null
    name:        text     // required — never null
    description: text?    // optional — explicitly nullable
}
```

---

## 4. Flat Data Structures

`array<T>` is for flat, homogeneous lists of scalar values. Nesting is not
allowed — `array<array<T>>` is a compile-time error. This is a deliberate
constraint, not an oversight.

Nested arrays destroy the storage properties that make Tensor Database fast.
The PAX column layout in `.sst` files and the SIMD operations the engine
relies on both require predictable, fixed-size values per cell. Nesting
introduces pointer indirection, variable row sizes, and unpredictable memory
access patterns — the same problems that make document stores slow for
analytical queries.
```tql
// correct — flat scalar array
let ports: array<int32> = [80, 443, 8080]

// compile-time error — nesting not allowed
let matrix: array<array<int32>> = [[1, 2], [3, 4]]
```

When you genuinely need nested or mixed-structure data, `json<T>` is the
correct type. It is designed for that use case, stored as binary msgpack, and
makes the schema flexibility explicit rather than smuggling it into the array
type.
```tql
// correct approach for nested structures
let config: json<map[text]array<int32>> = '{"ports": [80, 443]}'
```

The rule is simple: if it is a list of scalars, use `array<T>`. If it has
structure, use `json<T>`.

---

## 5. Type-Before-Data

The type contract always precedes the data it governs. In a `from` clause the
type binding comes before the pipeline reads any rows. In an `insert` the type
binding comes before the value block. In a `let` binding the type annotation
comes before the expression.

This means the compiler always knows the full type context before it evaluates
any data. There are no deferred type checks, no runtime schema validation, no
surprises after execution begins.
```tql
// type binding before pipeline
from "store/products" as p: commerce.Product

// type binding before value block
insert into "store/products" as commerce.Product { ... }

// type annotation before expression
let total: decimal(10,2) = sum(o.total)
```

---

## 6. Paths Are the Namespace

There is no database, schema, or catalog layer. Storage is organized as a
hierarchical virtual file system and paths are the namespace. `"store/products"`
is both the address of the storage and its identity in every query, mutation,
and IAM rule.

This means the organizational structure of your data is visible, navigable,
and consistent across every context — queries, access control, backups, and
the CLI all speak the same path language.

---

## 7. The Storage Architecture Is the Product

The three-module storage split — `.sst` for scalars, `.vec` for vectors,
`.rbm` for text — is not an implementation detail. It is the core design
decision that makes hybrid queries possible without performance compromise.

A scalar filter, a keyword search, and a semantic search run concurrently
against their respective modules and merge via Reciprocal Rank Fusion. This
only works because the modules are physically isolated. Collapsing them into
a single storage format to simplify the implementation would destroy the
property that makes the architecture worth building.

Pluggable storage engines are explicitly out of scope. The three-module
architecture is owned and fixed. MySQL's InnoDB/MyISAM split created decades
of confusion — Tensor Database does not repeat that mistake.

---

## 8. The Compiler Is the Safety Layer

Unfiltered deletes are compile-time errors. Missing type annotations are
compile-time errors. Nested arrays are compile-time errors. Mismatched
vector dimensions are compile-time errors. Wrong types in `where` clauses
are compile-time errors.

The goal is to push every class of preventable error to compile time so that
a pipeline that reaches execution is already known to be structurally sound.
Runtime errors should be rare and caused only by genuinely dynamic conditions
— not by mistakes the compiler could have caught.

---

## 9. What Deliberately Does Not Exist

These are not missing features — they are conscious omissions.

**Stored procedures.** The pipeline model is clean because it is declarative
and stateless. Imperative server-side logic inherits the debugging and
maintainability problems of PL/pgSQL. Application logic belongs in the
application.

**ORM or client libraries.** The CLI and JSON output is the interface. The
package type system already solves the schema drift problem that ORMs exist
to solve — without coupling the database to a specific language ecosystem.

**Query cache.** LSM trees already have bloom filters and block caches.
Application-level query caches are more trouble than they are worth.
MySQL removed theirs for good reason.

**Type inference on `let`.** Covered in section 2. Explicit annotations are
the rule with no exceptions.

**Nested arrays.** Covered in section 4. Use `json<T>` for nested structures.

**Pluggable storage engines.** Covered in section 7. The architecture is fixed.