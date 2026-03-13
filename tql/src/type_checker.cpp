// Pass 3 — Type checking.
// Infers the type of every expression in the stage list and enforces the
// type rules specified in the language grammar and operators.md.

#include "semantic.hpp"
#include <optional>

namespace tensor::tql {

namespace {

// Forward declaration — infer_type and infer_node_type are mutually recursive.
static Result<TypeRef> infer_type(
    const ExprPtr&         e,
    const SymbolTable&     sym,
    const PackageRegistry& reg
);

static Result<TypeRef> infer_node_type(
    const ExprNode&        node,
    const SymbolTable&     sym,
    const PackageRegistry& reg
) {
    return std::visit([&](const auto& n) -> Result<TypeRef> {
        using T = std::decay_t<decltype(n)>;

        // ── Literals ──────────────────────────────────────────────────────
        if constexpr (std::is_same_v<T, LiteralExpr>) {
            switch (n.kind) {
                case LiteralExpr::Kind::Int:    return Result<TypeRef>::success(TypeRef::make_int64());
                case LiteralExpr::Kind::Float:  return Result<TypeRef>::success(TypeRef::make_float64());
                case LiteralExpr::Kind::String: return Result<TypeRef>::success(TypeRef::make_text());
                case LiteralExpr::Kind::Bool:   return Result<TypeRef>::success(TypeRef::make_bool());
                case LiteralExpr::Kind::Null: {
                    TypeRef t = TypeRef::make_int32();
                    t.nullable = true;
                    return Result<TypeRef>::success(t);
                }
            }
        }

        // ── Field references ──────────────────────────────────────────────
        else if constexpr (std::is_same_v<T, FieldRefExpr>) {
            if (!n.var.empty()) {
                const VarEntry* var = sym.find_var(n.var);
                if (!var)
                    return Result<TypeRef>::failure(
                        Error{ "undeclared variable '" + n.var + "'", 0, 0 });

                if (var->type.kind == TypeRef::Kind::UserDefined) {
                    const TypeDecl* decl = reg.find(var->type);
                    if (!decl)
                        // Registry empty (no resolver) — return the base type as-is.
                        // The scope checker already accepted this; skip field type lookup.
                        return Result<TypeRef>::success(var->type);

                    const FieldDef* field = decl->find_field(n.field);
                    if (!field)
                        return Result<TypeRef>::failure(Error{
                            "type '" + var->type.qualified_name() +
                            "' has no field '" + n.field + "'", 0, 0 });
                    return Result<TypeRef>::success(field->type);
                }
                // Scalar variable with field access — semantic error.
                return Result<TypeRef>::failure(Error{
                    "cannot access field '" + n.field + "' on a scalar-typed variable '"
                    + n.var + "'", 0, 0 });
            } else {
                // Unqualified — must be a let-bound name.
                const LetEntry* let = sym.find_let(n.field);
                if (!let)
                    return Result<TypeRef>::failure(
                        Error{ "undeclared name '" + n.field + "'", 0, 0 });
                return Result<TypeRef>::success(let->type);
            }
        }

        // ── Binary expressions ────────────────────────────────────────────
        else if constexpr (std::is_same_v<T, BinaryExpr>) {
            auto lr = infer_type(n.lhs, sym, reg);
            if (!lr.ok()) return lr;
            auto rr = infer_type(n.rhs, sym, reg);
            if (!rr.ok()) return rr;

            const TypeRef& lt = lr.value();
            const TypeRef& rt = rr.value();

            // Skip deeper checks when either operand is unresolved.
            if (lt.is_unresolved() || rt.is_unresolved())
                return Result<TypeRef>::success(TypeRef::make_bool());

            using Op = BinaryExpr::Op;
            switch (n.op) {
                case Op::And: case Op::Or:
                    if (!lt.is_bool() || !rt.is_bool())
                        return Result<TypeRef>::failure(Error{
                            "'and'/'or' operands must be bool", 0, 0 });
                    return Result<TypeRef>::success(TypeRef::make_bool());

                case Op::Eq: case Op::Neq:
                    return Result<TypeRef>::success(TypeRef::make_bool());

                case Op::Lt: case Op::Gt: case Op::Lte: case Op::Gte:
                    if (!lt.is_comparable())
                        return Result<TypeRef>::failure(Error{
                            "comparison operator requires a comparable type on the left side", 0, 0 });
                    return Result<TypeRef>::success(TypeRef::make_bool());

                case Op::Add: case Op::Sub: case Op::Mul: case Op::Div:
                    if (!lt.is_numeric())
                        return Result<TypeRef>::failure(Error{
                            "arithmetic operator requires numeric operands", 0, 0 });
                    if (!rt.is_numeric())
                        return Result<TypeRef>::failure(Error{
                            "arithmetic operator requires numeric operands", 0, 0 });
                    // Widening: float64 > float32 > decimal > int64 > int32
                    if (lt.kind == TypeRef::Kind::Float64 || rt.kind == TypeRef::Kind::Float64)
                        return Result<TypeRef>::success(TypeRef::make_float64());
                    if (lt.kind == TypeRef::Kind::Float32 || rt.kind == TypeRef::Kind::Float32) {
                        TypeRef t; t.kind = TypeRef::Kind::Float32; return Result<TypeRef>::success(t);
                    }
                    if (lt.kind == TypeRef::Kind::Decimal || rt.kind == TypeRef::Kind::Decimal) {
                        TypeRef t; t.kind = TypeRef::Kind::Decimal;
                        t.decimal = (lt.kind == TypeRef::Kind::Decimal) ? lt.decimal : rt.decimal;
                        return Result<TypeRef>::success(t);
                    }
                    if (lt.kind == TypeRef::Kind::Int64 || rt.kind == TypeRef::Kind::Int64)
                        return Result<TypeRef>::success(TypeRef::make_int64());
                    return Result<TypeRef>::success(TypeRef::make_int32());
            }
        }

        // ── Unary expressions ─────────────────────────────────────────────
        else if constexpr (std::is_same_v<T, UnaryExpr>) {
            auto or_ = infer_type(n.operand, sym, reg);
            if (!or_.ok()) return or_;
            const TypeRef& ot = or_.value();
            if (ot.is_unresolved()) return or_;

            if (n.op == UnaryExpr::Op::Not) {
                if (!ot.is_bool())
                    return Result<TypeRef>::failure(Error{ "'not' requires a bool operand", 0, 0 });
                return Result<TypeRef>::success(TypeRef::make_bool());
            } else {
                if (!ot.is_numeric())
                    return Result<TypeRef>::failure(Error{
                        "unary '-' requires a numeric operand", 0, 0 });
                return or_;
            }
        }

        // ── Built-in calls ────────────────────────────────────────────────
        else if constexpr (std::is_same_v<T, GenUuidExpr>)
            return Result<TypeRef>::success(TypeRef::make_uuid());

        else if constexpr (std::is_same_v<T, NowExpr>)
            return Result<TypeRef>::success(TypeRef::make_timestamp());

        else if constexpr (std::is_same_v<T, MatchExpr>) {
            auto fr = infer_type(n.field, sym, reg);
            if (!fr.ok()) return fr;
            if (!fr.value().is_unresolved() && !fr.value().is_text())
                return Result<TypeRef>::failure(Error{
                    "match() first argument must be of type 'text'", 0, 0 });
            return Result<TypeRef>::success(TypeRef::make_bool());
        }

        else if constexpr (std::is_same_v<T, EmbedExpr>) {
            // Dimension is model-dependent — resolved at execution time.
            // Return vector(0) as a compile-time sentinel.
            TypeRef t; t.kind = TypeRef::Kind::Vector; t.vector_dim = 0;
            return Result<TypeRef>::success(t);
        }

        else if constexpr (std::is_same_v<T, PromptExpr>)
            // Output type was stamped onto PromptExpr by the compiler from
            // the enclosing let annotation.
            return Result<TypeRef>::success(n.output_type);

        else if constexpr (std::is_same_v<T, AggExpr>) {
            if (n.func == AggExpr::Func::Count)
                return Result<TypeRef>::success(TypeRef::make_int64());
            if (n.count_star)
                return Result<TypeRef>::failure(Error{ "only count() accepts '*'", 0, 0 });
            auto ar = infer_type(n.arg, sym, reg);
            if (!ar.ok()) return ar;
            if (n.func == AggExpr::Func::Avg)
                return Result<TypeRef>::success(TypeRef::make_float64());
            return ar; // sum/min/max preserve the argument type
        }

        return Result<TypeRef>::success(TypeRef{});
    }, node);
}

static Result<TypeRef> infer_type(
    const ExprPtr&         e,
    const SymbolTable&     sym,
    const PackageRegistry& reg
) {
    if (!e) return Result<TypeRef>::success(TypeRef{});
    return infer_node_type(e->node, sym, reg);
}

// ── Predicate helpers ─────────────────────────────────────────────────────

static Result<void> require_bool(
    const ExprPtr&         e,
    const SymbolTable&     sym,
    const PackageRegistry& reg,
    const char*            context
) {
    auto r = infer_type(e, sym, reg);
    if (!r.ok()) return Result<void>::failure(r.error());
    const TypeRef& t = r.value();
    if (!t.is_unresolved() && !t.is_bool())
        return Result<void>::failure(Error{
            std::string(context) + " predicate must be of type 'bool'", 0, 0 });
    return Result<void>::success();
}

static Result<void> check_projected_types(
    const ProjectedField&  f,
    const SymbolTable&     sym,
    const PackageRegistry& reg
) {
    if (f.is_nested) {
        for (const auto& n : f.nested)
            if (auto r = check_projected_types(n, sym, reg); !r.ok()) return r;
        return Result<void>::success();
    }
    auto r = infer_type(f.value, sym, reg);
    if (!r.ok()) return Result<void>::failure(r.error());
    return Result<void>::success();
}

} // anonymous namespace

// ── Pass 3 entry point ────────────────────────────────────────────────────

Result<void> check_types(
    const std::vector<Stage>& stages,
    const SymbolTable&        sym,
    const PackageRegistry&    reg
) {
    for (const Stage& stage : stages) {
        switch (stage.kind()) {

            case Stage::Kind::Filter:
                if (auto r = require_bool(stage.as<FilterStage>().predicate,
                                          sym, reg, "where"); !r.ok()) return r;
                break;

            case Stage::Kind::Join:
                if (auto r = require_bool(stage.as<JoinStage>().condition,
                                          sym, reg, "join on"); !r.ok()) return r;
                break;

            case Stage::Kind::Having:
                if (auto r = require_bool(stage.as<HavingStage>().predicate,
                                          sym, reg, "having"); !r.ok()) return r;
                break;

            case Stage::Kind::Let: {
                const auto& l = stage.as<LetStage>();
                auto r = infer_type(l.expr, sym, reg);
                if (!r.ok()) return Result<void>::failure(r.error());

                const TypeRef& inferred = r.value();
                const TypeRef& declared = l.type;

                // Skip when the inferred type is unresolved (field type from
                // a package that wasn't loaded — resolver was null).
                if (inferred.is_unresolved()) break;

                // Allow numeric widening between any numeric kinds.
                if (inferred.kind != declared.kind) {
                    if (!(inferred.is_numeric() && declared.is_numeric()))
                        return Result<void>::failure(Error{
                            "let '" + l.name + "': expression type is incompatible"
                            " with the declared type", 0, 0 });
                }
                break;
            }

            case Stage::Kind::Project:
                for (const auto& f : stage.as<ProjectStage>().fields)
                    if (auto r = check_projected_types(f, sym, reg); !r.ok()) return r;
                break;

            case Stage::Kind::OrderBy:
                for (const auto& item : stage.as<OrderByStage>().items) {
                    auto r = infer_type(item.expr, sym, reg);
                    if (!r.ok()) return Result<void>::failure(r.error());
                    if (item.is_vector) {
                        if (!r.value().is_unresolved() && !r.value().is_vector())
                            return Result<void>::failure(Error{
                                "left side of <-> must be a vector field", 0, 0 });
                        auto qr = infer_type(item.vector_query, sym, reg);
                        if (!qr.ok()) return Result<void>::failure(qr.error());
                        if (!qr.value().is_unresolved() && !qr.value().is_vector())
                            return Result<void>::failure(Error{
                                "right side of <-> must produce a vector (e.g. embed(...))", 0, 0 });
                    }
                }
                break;

            case Stage::Kind::GroupBy:
            case Stage::Kind::Limit:
                break;
        }
    }

    return Result<void>::success();
}

} // namespace tensor::tql