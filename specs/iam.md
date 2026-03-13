# Security & Identity (`iam.md`)

---

## Two-Tiered Security

Tensor Database uses the host operating system for local access control and
explicit API keys for remote access. Once a connection is established, all
internal permissions are governed by a path-based IAM engine written
natively in `.tql`.

---

## 1. Local Authentication — Unix File Permissions

Local applications and services connect via a Unix Domain Socket
(`/tmp/tensordb.sock`). Authentication is handled implicitly by host file
system permissions.

When the Tensor Database daemon boots it creates the socket file and assigns
standard POSIX ownership and permissions. If the OS allows a process to write
to that file, Tensor Database accepts the connection. No credentials, no
handshake — the OS already made the trust decision.

To grant a local service access, add its system user to the `tensor` OS group
or grant it read/write access to the socket file directly.

---

## 2. Remote Authentication — API Keys

When accessing Tensor Database across a network boundary via QUIC, file
permissions no longer apply. Remote clients must authenticate using
cryptographically secure API keys passed as bearer tokens during the initial
connection handshake.

API keys are not just passwords — they are bound directly to a `.tql` role.
A leaked key only exposes the specific paths that role is permitted to access.

---

## 3. DDL Reference

All IAM objects — roles, grants, and API keys — are created and managed
using `.tql` DDL statements. These run through the same compiler and
execution engine as queries and mutations. Every statement is validated at
compile time before it touches any state.

---

### `create role`

Declares a named role. A role is the unit of access control — grants are
attached to roles and API keys are bound to roles.

```tql
create role name
```

```tql
create role storefront
create role analytics
create role warehouse
```

Role names are identifiers, not string literals. They must be unique within
the instance. Creating a role that already exists is a compile-time error.

---

### `grant`

Attaches path-level access rules to a role. A grant block contains one or
more `allow` or `deny` rules evaluated strictly top to bottom.

```tql
grant to role {
    allow operations on "path"
    deny  operations on "path"
}
```

**Operations** are one or more of `read`, `write`, or `*` (all operations).
Multiple operations are comma-separated.

**Paths** are string literals and support `*` as a wildcard segment.

```tql
grant to storefront {
    // Read access to the full product catalog
    allow read on "store/products/*"

    // Read and write on orders it owns
    allow read, write on "store/orders/*"

    // Explicit deny — billing data is off limits regardless of other rules
    deny * on "store/billing/*"
}

grant to analytics {
    // Read-only across the entire store namespace
    allow read on "store/*"

    // No mutations anywhere
    deny write on "store/*"
}

grant to warehouse {
    // Full access to inventory and fulfillment
    allow read, write on "store/products/*"
    allow read, write on "store/fulfillment/*"

    // No access to customer order details
    deny * on "store/orders/*"
}
```

**Deny always wins.** A path matched by both an `allow` and a `deny` rule is
always denied, regardless of rule order. Deny rules take absolute precedence
over allow rules.

A role with no grant block has no access to any path.

---

### `create api_key`

Generates a cryptographically secure API key bound to a role. The key
inherits exactly the path restrictions of its bound role — nothing more.

```tql
create api_key for role expires in Nd
```

The expiry duration is required. `N` is a positive integer and `d` is the
unit — currently only `d` (days) is supported.

```tql
// 90-day key for the remote storefront service
create api_key for storefront expires in 90d

// 365-day key for the internal analytics pipeline
create api_key for analytics expires in 365d
```

The generated key is printed once to stdout at creation time and is not
stored in recoverable form. If a key is lost it must be revoked and
regenerated. There is no key retrieval command.

---

### `revoke api_key`

Immediately invalidates an API key. Any connection currently authenticated
with that key is terminated.

```tql
revoke api_key "key_id"
```

The `key_id` is the identifier returned alongside the key at creation time.

---

### `create table`

Provisions a logical path in the virtual file system and binds it permanently
to a type contract. See `packages.md` for full details.

```tql
create table "path" as package.Type
```

```tql
import "shared/commerce"

create table "store/products" as commerce.Product
create table "store/orders"   as commerce.Order
```

---

### `truncate`

Wipes all rows from a path without removing the path or its type binding.
Unlike `delete`, `truncate` does not require a `where` clause — it is an
explicit, intentional full wipe. It cannot be undone outside of a snapshot
restore.

```tql
truncate "path"
```

```tql
truncate "store/orders"
```

`truncate` is the only way to remove all rows from a path. An unfiltered
`delete` without a `where` clause is a compile-time error — `truncate` is
the deliberate alternative for when a full wipe is genuinely intended.

---

## 4. Rule Evaluation

IAM rules inside a `grant` block are evaluated strictly top to bottom. The
first rule whose path pattern matches the requested path determines the
outcome for that operation — with one absolute exception: **deny always wins
over allow regardless of order or position in the block.**

```tql
grant to storefront {
    allow read on "store/*"       // matches store/billing/invoices → allow
    deny  *    on "store/billing/*" // also matches store/billing/invoices → deny wins
}
```

In the example above, a `read` request on `"store/billing/invoices"` is
denied even though the `allow read on "store/*"` rule appears first and
matches. The `deny` rule takes absolute precedence.

---

## 5. Bootstrapping

When installing or booting the database for the first time, the administrator
runs:

```bash
tensor db start --setup
```

This commands the engine to:

1. Create the default `admin` role with `*` access to all paths.
2. Print a one-time randomly generated `SuperAdmin` API key to stdout.
3. Bind the local socket to the current user's workspace.

The administrator uses this key to run initial `.tql` migration scripts,
establishing the application roles, keys, and logical paths before the key
is discarded. The `SuperAdmin` key cannot be regenerated — if lost, the
instance must be reinitialized.