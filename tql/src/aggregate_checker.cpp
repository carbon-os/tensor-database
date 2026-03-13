// Pass 4 — Aggregate context validation.
// Enforces:
//   - Aggregate functions (count/sum/avg/min/max) never appear in 'where'
//     or join 'on' conditions.
//   - Aggregate functions in 'let' or 'select' require a preceding 'group by'.
//   - 'having' requires a preceding 'group by'.

#include "semantic.hpp"

namespace tensor::tql {

namespace {

static bool has_agg(const ExprPtr& e);

static bool node_has_agg(const ExprNode& node) {
    return std::visit([](const auto& n) -> bool {
        using T = std::decay_t<decltype(n)>;
        if constexpr (std::is_same_v<T, AggExpr>)    return true;
        if constexpr (std::is_same_v<T, BinaryExpr>) return has_agg(n.lhs) || has_agg(n.rhs);
        if constexpr (std::is_same_v<T, UnaryExpr>)  return has_agg(n.operand);
        if constexpr (std::is_same_v<T, MatchExpr>)  return has_agg(n.field);
        if constexpr (std::is_same_v<T, PromptExpr>) return has_agg(n.source_field);
        return false;
    }, node);
}

static bool has_agg(const ExprPtr& e) {
    return e && node_has_agg(e->node);
}

static bool projected_has_agg(const ProjectedField& f) {
    if (f.is_nested) {
        for (const auto& n : f.nested)
            if (projected_has_agg(n)) return true;
        return false;
    }
    return has_agg(f.value);
}

} // anonymous namespace

// ── Pass 4 entry point ────────────────────────────────────────────────────

Result<void> check_aggregates(const std::vector<Stage>& stages) {
    bool after_group_by = false;

    for (const Stage& stage : stages) {
        switch (stage.kind()) {

            case Stage::Kind::GroupBy:
                after_group_by = true;
                break;

            case Stage::Kind::Filter:
                // Aggregates are never valid in 'where', regardless of context.
                if (has_agg(stage.as<FilterStage>().predicate))
                    return Result<void>::failure(Error{
                        "aggregate function cannot be used in 'where' — use 'having' instead",
                        0, 0 });
                break;

            case Stage::Kind::Join:
                if (has_agg(stage.as<JoinStage>().condition))
                    return Result<void>::failure(Error{
                        "aggregate function cannot be used in a join condition",
                        0, 0 });
                break;

            case Stage::Kind::Having:
                if (!after_group_by)
                    return Result<void>::failure(Error{
                        "'having' requires a preceding 'group by'", 0, 0 });
                break;

            case Stage::Kind::Let:
                if (!after_group_by && has_agg(stage.as<LetStage>().expr))
                    return Result<void>::failure(Error{
                        "aggregate function in 'let' requires a preceding 'group by'",
                        0, 0 });
                break;

            case Stage::Kind::Project:
                if (!after_group_by) {
                    for (const auto& f : stage.as<ProjectStage>().fields)
                        if (projected_has_agg(f))
                            return Result<void>::failure(Error{
                                "aggregate function in 'select' requires a preceding 'group by'",
                                0, 0 });
                }
                break;

            case Stage::Kind::OrderBy:
            case Stage::Kind::Limit:
                break;
        }
    }

    return Result<void>::success();
}

} // namespace tensor::tql