// Pass 5 — Constant folding.
// Recursively reduces literal sub-expressions at compile time:
//   int op int → int,  float op numeric → float,  bool and/or bool → bool,
//   unary -(int|float) → negated literal,  not bool → bool.
// Division by zero is never folded.
// This pass never fails.

#include "semantic.hpp"

namespace tensor::tql {

namespace {

static ExprPtr fold(ExprPtr e) {
    if (!e) return e;

    // Fold sub-expressions bottom-up.
    std::visit([](auto& n) {
        using T = std::decay_t<decltype(n)>;
        if constexpr (std::is_same_v<T, BinaryExpr>) {
            n.lhs = fold(n.lhs);
            n.rhs = fold(n.rhs);
        } else if constexpr (std::is_same_v<T, UnaryExpr>) {
            n.operand = fold(n.operand);
        } else if constexpr (std::is_same_v<T, MatchExpr>) {
            n.field = fold(n.field);
        } else if constexpr (std::is_same_v<T, PromptExpr>) {
            n.source_field = fold(n.source_field);
        } else if constexpr (std::is_same_v<T, AggExpr>) {
            if (!n.count_star) n.arg = fold(n.arg);
        }
    }, e->node);

    // Try to collapse this node.
    if (auto* b = std::get_if<BinaryExpr>(&e->node)) {
        const auto* ll = std::get_if<LiteralExpr>(&b->lhs->node);
        const auto* rl = std::get_if<LiteralExpr>(&b->rhs->node);
        if (!ll || !rl) return e;

        using K  = LiteralExpr::Kind;
        using Op = BinaryExpr::Op;

        // int op int → int
        if (ll->kind == K::Int && rl->kind == K::Int) {
            LiteralExpr r; r.kind = K::Int;
            switch (b->op) {
                case Op::Add: r.int_val = ll->int_val + rl->int_val; return make_expr(r);
                case Op::Sub: r.int_val = ll->int_val - rl->int_val; return make_expr(r);
                case Op::Mul: r.int_val = ll->int_val * rl->int_val; return make_expr(r);
                case Op::Div:
                    if (rl->int_val != 0) { r.int_val = ll->int_val / rl->int_val; return make_expr(r); }
                    break;
                default: break;
            }
        }

        // float or mixed numeric → float
        const bool l_num = ll->kind == K::Int || ll->kind == K::Float;
        const bool r_num = rl->kind == K::Int || rl->kind == K::Float;
        if (l_num && r_num && (ll->kind == K::Float || rl->kind == K::Float)) {
            const double lv = ll->kind == K::Float ? ll->float_val : static_cast<double>(ll->int_val);
            const double rv = rl->kind == K::Float ? rl->float_val : static_cast<double>(rl->int_val);
            LiteralExpr r; r.kind = K::Float;
            switch (b->op) {
                case Op::Add: r.float_val = lv + rv; return make_expr(r);
                case Op::Sub: r.float_val = lv - rv; return make_expr(r);
                case Op::Mul: r.float_val = lv * rv; return make_expr(r);
                case Op::Div:
                    if (rv != 0.0) { r.float_val = lv / rv; return make_expr(r); }
                    break;
                default: break;
            }
        }

        // bool and/or bool → bool
        if (ll->kind == K::Bool && rl->kind == K::Bool) {
            LiteralExpr r; r.kind = K::Bool;
            switch (b->op) {
                case Op::And: r.bool_val = ll->bool_val && rl->bool_val; return make_expr(r);
                case Op::Or:  r.bool_val = ll->bool_val || rl->bool_val; return make_expr(r);
                default: break;
            }
        }
    }
    else if (auto* u = std::get_if<UnaryExpr>(&e->node)) {
        const auto* lit = std::get_if<LiteralExpr>(&u->operand->node);
        if (!lit) return e;
        using K = LiteralExpr::Kind;
        if (u->op == UnaryExpr::Op::Neg) {
            if (lit->kind == K::Int) {
                LiteralExpr r; r.kind = K::Int; r.int_val = -lit->int_val;
                return make_expr(r);
            }
            if (lit->kind == K::Float) {
                LiteralExpr r; r.kind = K::Float; r.float_val = -lit->float_val;
                return make_expr(r);
            }
        }
        if (u->op == UnaryExpr::Op::Not && lit->kind == K::Bool) {
            LiteralExpr r; r.kind = K::Bool; r.bool_val = !lit->bool_val;
            return make_expr(r);
        }
    }

    return e;
}

static void fold_projected_field(ProjectedField& f) {
    if (f.is_nested) {
        for (auto& n : f.nested) fold_projected_field(n);
    } else {
        f.value = fold(f.value);
    }
}

} // anonymous namespace

// ── Pass 5 entry points ───────────────────────────────────────────────────

void fold_constants(std::vector<Stage>& stages) {
    for (Stage& stage : stages) {
        switch (stage.kind()) {
            case Stage::Kind::Filter:
                stage.as<FilterStage>().predicate = fold(stage.as<FilterStage>().predicate);
                break;
            case Stage::Kind::Join:
                stage.as<JoinStage>().condition = fold(stage.as<JoinStage>().condition);
                break;
            case Stage::Kind::Having:
                stage.as<HavingStage>().predicate = fold(stage.as<HavingStage>().predicate);
                break;
            case Stage::Kind::Let:
                stage.as<LetStage>().expr = fold(stage.as<LetStage>().expr);
                break;
            case Stage::Kind::Project:
                for (auto& f : stage.as<ProjectStage>().fields)
                    fold_projected_field(f);
                break;
            case Stage::Kind::OrderBy:
                for (auto& item : stage.as<OrderByStage>().items) {
                    item.expr = fold(item.expr);
                    if (item.is_vector) item.vector_query = fold(item.vector_query);
                }
                break;
            default:
                break;
        }
    }
}

void fold_row_fields(std::vector<RowField>& fields) {
    for (auto& rf : fields)
        rf.value = fold(rf.value);
}

void fold_returning_fields(std::vector<ReturningField>& fields) {
    for (auto& rf : fields)
        if (!rf.is_mutation_field) rf.value = fold(rf.value);
}

} // namespace tensor::tql