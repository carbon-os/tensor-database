# Security & Identity (`iam.md`)

---

## Two-Tiered Security

Tensor Database uses the host operating system for local access control and explicit API keys for remote access. Once a connection is established, all internal permissions are governed by a path-based IAM engine written natively in `.tql`.

---

## 1. Local Authentication — Unix File Permissions

Local applications and services connect via a Unix Domain Socket (`/tmp/tensordb.sock`). Authentication is handled implicitly by host file system permissions.

When the Tensor Database daemon boots it creates the socket file and assigns standard POSIX ownership and permissions. If the OS allows a process to write to that file, Tensor Database accepts the connection. No credentials, no handshake — the OS already made the trust decision.

To grant a local service access, add its system user to the `tensor` OS group or grant it read/write access to the socket file directly.

---

## 2. Remote Authentication — API Keys

When accessing Tensor Database across a network boundary via QUIC, file permissions no longer apply. Remote clients must authenticate using cryptographically secure API keys passed as bearer tokens during the initial connection handshake.

API keys are not just passwords — they are bound directly to a `.tql` role. A leaked key only exposes the specific paths that role is permitted to access.

---

## 3. Path-Based Authorization

Tensor Database discards the legacy `GRANT SELECT ON database.table` syntax. Because namespaces are structured as a hierarchical virtual file system, IAM policies read like zero-trust rules — block-structured, wildcard-aware, and evaluated strictly top to bottom.

### Defining Roles
```tql
create role storefront
create role analytics
create role warehouse
```

### Granting Path Access
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

Deny rules always take absolute precedence over allow rules regardless of order. A path matched by both an `allow` and a `deny` is always denied.

### Generating API Keys

Keys are generated natively within the database and inherit the exact path restrictions of the bound role.
```tql
// Expirable key for the remote storefront service
create api_key for storefront expires in 90d

// Long-lived key for the internal analytics pipeline
create api_key for analytics expires in 365d
```

---

## 4. Bootstrapping

When installing or booting the database for the first time, the administrator runs:
```bash
tensor db start --setup
```

This commands the engine to:

1. Create the default `admin` role with `*` access to all paths.
2. Print a one-time randomly generated `SuperAdmin` API key to stdout.
3. Bind the local socket to the current user's workspace.

The administrator uses this key to run initial `.tql` migration scripts, establishing the application roles, keys, and logical paths before the key is discarded.