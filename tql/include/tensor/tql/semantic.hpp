// tql/src/semantic.hpp
// Internal header — not installed, not included by any public header.
// Declares the five semantic analysis passes and the SymbolTable they share.

#pragma once

#include <tensor/tql/pipeline.hpp>
#include "TQLParser.h"

namespace tensor::tql {

// ════════════════════════════════════════════════════════════════════════════
// SymbolTable — built by Pass 2, consumed by Pass 3
// ════════════════════════════════════════════════════════════════════════════

struct VarEntry {
    std::string path;   // physical path (e.g. "store/orders")
    TypeRef     type;   // declared type (may be UserDefined and unresolved)
};

struct LetEntry {
    TypeRef type;
};

struct SymbolTable {
    // Variable bindings in declaration order (from binding, then each join).
    std::vector<std::pair<std::string, VarEntry>> vars;

    // Let bindings in declaration order.
    std::vector<std::pair<std::string, LetEntry>> lets;

    // GroupBy context — needed by Pass 4.
    bool                      has_group_by   = false;
    size_t                    group_by_stage = SIZE_MAX;
    std::vector<FieldRefExpr> group_by_keys;

    const VarEntry* find_var(std::string_view name) const noexcept;
    const LetEntry* find_let(std::string_view name) const noexcept;
};

// ════════════════════════════════════════════════════════════════════════════
// Pass 1 — Import resolution
// ════════════════════════════════════════════════════════════════════════════
// Walks importDecl nodes, calls PackageResolver, parses package files, and
// returns a populated PackageRegistry.
// If resolver is null, imports are silently skipped → empty registry returned.

Result<PackageRegistry> resolve_imports(
    TQLParser::ExecutableFileContext* ctx,
    PackageResolver*                  resolver
);

// ════════════════════════════════════════════════════════════════════════════
// Pass 2 — Scope resolution
// ════════════════════════════════════════════════════════════════════════════
// Walks the stage list in order, builds the SymbolTable, and validates that
// every FieldRefExpr references a name that is in scope at that point.
// Field existence on UserDefined types is checked only when the type's
// TypeDecl is present in the registry (skipped when resolver was null).

Result<SymbolTable> check_scope(
    const std::vector<Stage>&          stages,
    std::string_view                   from_var,
    const TypeRef&                     from_type,
    const std::vector<ReturningField>& returning,
    const PackageRegistry&             registry
);

// ════════════════════════════════════════════════════════════════════════════
// Pass 3 — Type checking
// ════════════════════════════════════════════════════════════════════════════
// Infers the type of every expression in the stage list and enforces:
//   - where/having/join-on predicates must be bool
//   - arithmetic operands must be numeric
//   - match() first argument must be text
//   - vector <-> operands must be vector
//   - let declared type must be compatible with the inferred expression type

Result<void> check_types(
    const std::vector<Stage>& stages,
    const SymbolTable&        sym,
    const PackageRegistry&    registry
);

// ════════════════════════════════════════════════════════════════════════════
// Pass 4 — Aggregate context validation
// ════════════════════════════════════════════════════════════════════════════
// Enforces:
//   - aggregate functions never appear in where or join conditions
//   - aggregate functions in let/select require a preceding group by
//   - having requires a preceding group by

Result<void> check_aggregates(
    const std::vector<Stage>& stages
);

// ════════════════════════════════════════════════════════════════════════════
// Pass 5 — Constant folding
// ════════════════════════════════════════════════════════════════════════════
// Mutates stage expressions in place. Never fails.

void fold_constants(std::vector<Stage>& stages);

// Mutation payload helpers — called by Pipeline::compile for insert/update/upsert.
void fold_row_fields(std::vector<RowField>& fields);
void fold_returning_fields(std::vector<ReturningField>& fields);

} // namespace tensor::tql