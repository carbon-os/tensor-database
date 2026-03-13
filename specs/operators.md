# Operator Precedence (`operators.md`)

---

## Precedence Table

Operators are listed from highest precedence to lowest. Operators on the same
row share the same precedence level and follow the associativity column.

| Level | Operator(s) | Description | Associativity |
|---|---|---|---|
| 1 | `()` | Grouping | — |
| 2 | `-` | Unary negation | Right |
| 3 | `not` | Logical negation | Right |
| 4 | `*` `/` | Multiplication, division | Left |
| 5 | `+` `-` | Addition, subtraction | Left |
| 6 | `<->` | Vector distance | Left |
| 7 | `==` `!=` `<` `>` `<=` `>=` | Comparison | Left |
| 8 | `and` | Logical AND | Left |
| 9 | `or` | Logical OR | Left |

---

## Rules

**Higher level number means lower precedence.** An operator at level 4
binds more tightly than one at level 8.

**Associativity is left unless stated otherwise.** `a + b + c` is evaluated
as `(a + b) + c`. Unary operators are right-associative — `not not x` is
`not (not x)`.

**Use parentheses to override.** When precedence is non-obvious, parentheses
are always valid and encouraged for readability.

---

## Examples

### Arithmetic before comparison
```tql
where p.price * 0.90 < 50.00
// evaluated as: (p.price * 0.90) < 50.00
```

### Comparison before `and`
```tql
where p.stock > 0 and p.price < 50.00
// evaluated as: (p.stock > 0) and (p.price < 50.00)
```

### `and` before `or`
```tql
where p.stock > 0 and p.price < 50.00 or p.featured == true
// evaluated as: ((p.stock > 0) and (p.price < 50.00)) or (p.featured == true)

// if the intended meaning is different, use parentheses explicitly
where p.stock > 0 and (p.price < 50.00 or p.featured == true)
```

### `not` before `and`
```tql
where not p.archived == true and p.stock > 0
// evaluated as: (not (p.archived == true)) and (p.stock > 0)
```

### `<->` in `order by`
```tql
order by p.embedding <-> embed("waterproof outdoor gear")
// <->  produces a distance scalar — the result is then sorted by order by
// <-> is not valid in a where clause, only in order by
```

### Unary negation
```tql
let discount = -0.10
let adjusted = p.price * -0.10
// evaluated as: p.price * (-0.10)
```

---

## `<->` Restrictions

The vector distance operator `<->` is only valid as the expression passed
directly to `order by`. It is not valid in `where`, `let`, `select`,
`having`, or any other pipeline stage.

```tql
// correct
order by p.embedding <-> embed("query")

// not valid — distance operator outside of order by
where p.embedding <-> embed("query") < 0.5
```

---

## Operator Reference

### Arithmetic

| Operator | Types | Returns |
|---|---|---|
| `+` | `int32`, `int64`, `float32`, `float64`, `decimal` | Same as operands |
| `-` | `int32`, `int64`, `float32`, `float64`, `decimal` | Same as operands |
| `*` | `int32`, `int64`, `float32`, `float64`, `decimal` | Same as operands |
| `/` | `int32`, `int64`, `float32`, `float64`, `decimal` | Same as operands |
| `-` (unary) | `int32`, `int64`, `float32`, `float64`, `decimal` | Same as operand |

Mixed-type arithmetic is not implicitly coerced. Both operands must be the
same type. Use an explicit cast if types differ.

### Comparison

| Operator | Types | Returns |
|---|---|---|
| `==` | Any | `bool` |
| `!=` | Any | `bool` |
| `<` | Numeric, `timestamp`, `text` | `bool` |
| `>` | Numeric, `timestamp`, `text` | `bool` |
| `<=` | Numeric, `timestamp`, `text` | `bool` |
| `>=` | Numeric, `timestamp`, `text` | `bool` |

Comparing across incompatible types is a compile-time error.

### Logical

| Operator | Operands | Returns |
|---|---|---|
| `and` | `bool`, `bool` | `bool` |
| `or` | `bool`, `bool` | `bool` |
| `not` | `bool` | `bool` |

There is no implicit integer coercion to `bool`. Operands must be strictly
`bool`. The compiler rejects expressions like `where p.stock` — the condition
must be an explicit boolean expression.

### Vector Distance

| Operator | Left | Right | Returns |
|---|---|---|---|
| `<->` | `vector(n)` | `vector(n)` | `float32` |

Both operands must be vectors of identical dimensionality. Comparing a
`vector(768)` against a `vector(384)` is a compile-time error.