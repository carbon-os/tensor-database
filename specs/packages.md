# Packages & Schema (`packages.md`)

---

## The Type-Driven Philosophy

Legacy SQL forces a redundant split: you define a table schema in the database, then manually recreate that exact shape as a struct or class in your application code. These two definitions drift apart over time and the compiler never catches it.

Tensor Database eliminates this through **Package-Level Type Contracts**. Types are defined once in standalone `.tql` package files, imported wherever needed, and used to strictly bind data at the storage boundary. The same definition that governs what the C++ engine writes to the `.sst` is the same definition your query pipeline compiles against.

---

## 1. Defining a Package (`package` & `type`)

A package file is the single source of truth for one or more related types. Any `.tql` file — migrations, queries, mutations — can import from it.
```tql
// file: shared/commerce.tql
package commerce

type Product {
    id:           uuid
    name:         text
    price:        decimal(10,2)
    stock:        int32
    description:  text?
}

type Order {
    id:          uuid
    customer_id: uuid
    placed_at:   timestamp
    total:       decimal(10,2)
    status:      text
}
```

Types are strict. Every field has an explicit type. Nullable fields must be marked with `?`. There are no implicit defaults, no `NOT NULL` annotations bolted on after the fact — non-nullable is the baseline and opt-in nullability is the exception.

---

## 2. Instantiating Storage (`create table`)

Defining a type does not create any storage. Storage is instantiated explicitly using `create table`, which mounts a logical path in the OS-native virtual file system and binds it to a type contract using the `as` keyword.
```tql
// file: migrations/001_setup.tql
import "shared/commerce"

create table "store/products" as commerce.Product
create table "store/orders"   as commerce.Order
```

When this migration runs, Tensor Database provisions a directory at each path containing the specialized storage modules — `.wal`, `.sst`, `.vec`, `.hnsw`, `.rbm` — pre-configured to enforce the declared memory layout for every write. See `storage.md` for details on what each module does.

The `as` binding is permanent. Once a path is created with a type contract, the engine rejects any write whose shape does not exactly match. Schema changes require an explicit migration.

---

## 3. Importing Types

Any `.tql` file that references a type must import the package that defines it.

```tql
import "shared/commerce"
```

### Rules

**One import per line.** There is no multi-package import syntax.
```tql
// correct
import "shared/commerce"
import "shared/identity"

// not valid
import "shared/commerce", "shared/identity"
```

**No aliasing.** The `as` keyword is not valid on an import statement. The package name declared inside the package file (`package commerce`) is always the namespace used to reference its types.
```tql
// correct
import "shared/commerce"
// types are referenced as commerce.Product, commerce.Order

// not valid
import "shared/commerce" as shop
```

**Imports must appear at the top of the file**, before any pipeline statements, DDL, or mutation blocks.

**Paths are string literals** resolved relative to the workspace root. The `.tql` extension is omitted.
```tql
import "shared/commerce"       // resolves to shared/commerce.tql
import "shared/types/identity" // resolves to shared/types/identity.tql
```

**Resolution is compile-time only.** If the package file does not exist, or a referenced type is not declared within it, the pipeline fails before execution begins — not at runtime against live data. There is no lazy loading.

---

## 4. Organizing Packages

Because packages are just files on the virtual file system, you organize them the same way you organize any code. A reasonable convention for a growing project:
```
shared/
  types/
    commerce.tql      // package commerce  — products, orders
    identity.tql      // package identity  — users, sessions
    analytics.tql     // package analytics — events, metrics
migrations/
  001_setup.tql
  002_add_analytics.tql
```

There is no registry, no catalog table, no global namespace to manage. The file path is the identity of the package.