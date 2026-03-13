// Pass 2 — Scope resolution.
// Walks the stage list in declaration order, builds the SymbolTable,
// and validates that every variable and field reference is in scope.
// Field existence on UserDefined types is validated only when the type's
// TypeDecl is present in the registry.

#include "semantic.hpp"
#include <optional>

namespace tensor::tql {

// ── SymbolTable methods ───────────────────────────────────────────────────

const VarEntry* SymbolTable::find_var(std::string_view name) const noexcept {
    for (const auto& [k, v] : vars)
        if (k == name) return &v;
    return nullptr;
}

const LetEntry* SymbolTable::find_let(std::string_view name) const noexcept {
    for (const auto& [k, v] : lets)
        if (k == name) return &v;
    return nullptr;
}

// ── Scope validation helpers ──────────────────────────────────────────────

namespace {

static std::optional<Error> check_field_ref(
    const FieldRefExpr&    ref,
    const SymbolTable&     sym,
    const PackageRegistry& reg
) {
    if (!ref.var.empty()) {
        const VarEntry* var = sym.find_var(ref.var);
        if (!var)
            return Error{ "undeclared variable '" + ref.var + "'", 0, 0 };

        // Validate field existence when the type's declaration is in the registry.
        if (var->type.kind == TypeRef::Kind::UserDefined) {
            const TypeDecl* decl = reg.find(var->type);
            if (decl && !decl->find_field(ref.field))
                return Error{
                    "type '" + var->type.qualified_name() +
                    "' has no field '" + ref.field + "'",
                    0, 0
                };
        }
    } else {
        // Unqualified reference — must be a let-bound name.
        if (!sym.find_let(ref.field))
            return Error{
                "undeclared name '" + ref.field +
                "' (unqualified references must be let-bound names)",
                0, 0
            };
    }
    return std::nullopt;
}

static std::optional<Error> check_expr(
    const ExprPtr&         e,
    const SymbolTable&     sym,
    const PackageRegistry& reg
) {
    if (!e) return std::nullopt;

    return std::visit([&](const auto& n) -> std::optional<Error> {
        using T = std::decay_t<decltype(n)>;

        if constexpr (std::is_same_v<T, FieldRefExpr>)
            return check_field_ref(n, sym, reg);

        else if constexpr (std::is_same_v<T, BinaryExpr>) {
            if (auto e = check_expr(n.lhs, sym, reg)) return e;
            return check_expr(n.rhs, sym, reg);
        }
        else if constexpr (std::is_same_v<T, UnaryExpr>)
            return check_expr(n.operand, sym, reg);

        else if constexpr (std::is_same_v<T, MatchExpr>)
            return check_expr(n.field, sym, reg);

        else if constexpr (std::is_same_v<T, PromptExpr>)
            return check_expr(n.source_field, sym, reg);

        else if constexpr (std::is_same_v<T, AggExpr>) {
            if (!n.count_star) return check_expr(n.arg, sym, reg);
            return std::nullopt;
        }

        // LiteralExpr, GenUuidExpr, NowExpr, EmbedExpr — no variable refs.
        return std::nullopt;
    }, e->node);
}

static std::optional<Error> check_projected_field(
    const ProjectedField&  f,
    const SymbolTable&     sym,
    const PackageRegistry& reg
) {
    if (f.is_nested) {
        for (const auto& nested : f.nested)
            if (auto e = check_projected_field(nested, sym, reg)) return e;
        return std::nullopt;
    }
    return check_expr(f.value, sym, reg);
}

} // anonymous namespace

// ── Pass 2 entry point ────────────────────────────────────────────────────

Result<SymbolTable> check_scope(
    const std::vector<Stage>&          stages,
    std::string_view                   from_var,
    const TypeRef&                     from_type,
    const std::vector<ReturningField>& returning,
    const PackageRegistry&             registry
) {
    SymbolTable sym;

    // Primary from binding enters scope immediately.
    if (!from_var.empty())
        sym.vars.push_back({ std::string(from_var), VarEntry{ "", from_type } });

    for (size_t i = 0; i < stages.size(); ++i) {
        const Stage& stage = stages[i];

        switch (stage.kind()) {

            case Stage::Kind::Join: {
                const auto& j = stage.as<JoinStage>();
                // Join var enters scope BEFORE the ON condition is checked.
                // The ON condition must be able to reference both the existing
                // scope (e.g. 'o') and the table being joined (e.g. 'p').
                if (!j.binding.var.empty())
                    sym.vars.push_back({ j.binding.var,
                                        VarEntry{ j.binding.path, j.binding.type } });
                if (auto err = check_expr(j.condition, sym, registry))
                    return Result<SymbolTable>::failure(std::move(*err));
                break;
            }

            case Stage::Kind::Filter: {
                if (auto err = check_expr(stage.as<FilterStage>().predicate, sym, registry))
                    return Result<SymbolTable>::failure(std::move(*err));
                break;
            }

            case Stage::Kind::GroupBy: {
                const auto& g = stage.as<GroupByStage>();
                sym.has_group_by   = true;
                sym.group_by_stage = i;
                for (const auto& key : g.keys) {
                    if (auto err = check_field_ref(key, sym, registry))
                        return Result<SymbolTable>::failure(std::move(*err));
                    sym.group_by_keys.push_back(key);
                }
                break;
            }

            case Stage::Kind::Having: {
                if (auto err = check_expr(stage.as<HavingStage>().predicate, sym, registry))
                    return Result<SymbolTable>::failure(std::move(*err));
                break;
            }

            case Stage::Kind::Let: {
                const auto& l = stage.as<LetStage>();
                // Expression is validated before the name enters scope
                // so self-references produce a clear error.
                if (auto err = check_expr(l.expr, sym, registry))
                    return Result<SymbolTable>::failure(std::move(*err));
                sym.lets.push_back({ l.name, LetEntry{ l.type } });
                break;
            }

            case Stage::Kind::Project: {
                for (const auto& f : stage.as<ProjectStage>().fields)
                    if (auto err = check_projected_field(f, sym, registry))
                        return Result<SymbolTable>::failure(std::move(*err));
                break;
            }

            case Stage::Kind::OrderBy: {
                const auto& o = stage.as<OrderByStage>();
                for (const auto& item : o.items) {
                    if (auto err = check_expr(item.expr, sym, registry))
                        return Result<SymbolTable>::failure(std::move(*err));
                    if (item.is_vector)
                        if (auto err = check_expr(item.vector_query, sym, registry))
                            return Result<SymbolTable>::failure(std::move(*err));
                }
                break;
            }

            case Stage::Kind::Limit:
                break;
        }
    }

    // Returning clause — checked after all stages are in scope.
    for (const auto& rf : returning)
        if (!rf.is_mutation_field)
            if (auto err = check_expr(rf.value, sym, registry))
                return Result<SymbolTable>::failure(std::move(*err));

    return Result<SymbolTable>::success(std::move(sym));
}

} // namespace tensor::tql