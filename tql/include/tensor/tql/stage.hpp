#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <variant>
#include <vector>
#include "types.hpp"

namespace tensor::tql {

// ════════════════════════════════════════════════════════════════════════════
// Expression tree
// ════════════════════════════════════════════════════════════════════════════

struct Expr;
using ExprPtr = std::shared_ptr<Expr>;

// ── Leaf nodes ────────────────────────────────────────────────────────────

struct LiteralExpr {
    enum class Kind { String, Int, Float, Bool, Null };
    Kind        kind       = Kind::Null;
    std::string string_val;
    int64_t     int_val    = 0;
    double      float_val  = 0.0;
    bool        bool_val   = false;
};

struct FieldRefExpr {
    std::string var;
    std::string field;
};

// ── Operator nodes ────────────────────────────────────────────────────────

struct BinaryExpr {
    enum class Op {
        Add, Sub, Mul, Div,
        Eq, Neq, Lt, Gt, Lte, Gte,
        And, Or,
    };
    Op      op;
    ExprPtr lhs;
    ExprPtr rhs;
};

struct UnaryExpr {
    enum class Op { Neg, Not };
    Op      op;
    ExprPtr operand;
};

// ── Built-in function call nodes ──────────────────────────────────────────

struct GenUuidExpr {};
struct NowExpr     {};

struct MatchExpr {
    ExprPtr     field;
    std::string token;
};

struct EmbedExpr {
    std::string query;
    std::string constant;
};

struct PromptExpr {
    ExprPtr     source_field;
    std::string query;
    std::string constant;
    TypeRef     output_type;
};

struct AggExpr {
    enum class Func { Count, Sum, Avg, Min, Max };
    Func    func;
    ExprPtr arg;
    bool    count_star = false;
};

// ── Expr variant — '<' must be on the same line as std::variant ───────────

using ExprNode = std::variant<
    LiteralExpr,
    FieldRefExpr,
    BinaryExpr,
    UnaryExpr,
    GenUuidExpr,
    NowExpr,
    MatchExpr,
    EmbedExpr,
    PromptExpr,
    AggExpr
>;

struct Expr {
    ExprNode node;
};

inline ExprPtr make_expr(ExprNode n) {
    return std::make_shared<Expr>(Expr{std::move(n)});
}

// ════════════════════════════════════════════════════════════════════════════
// Stage data structs
// ════════════════════════════════════════════════════════════════════════════

struct PathBinding {
    std::string path;
    std::string var;
    TypeRef     type;
};

struct FilterStage {
    ExprPtr predicate;
};

struct JoinStage {
    enum class Kind { Inner, Left };
    Kind        kind;
    PathBinding binding;
    ExprPtr     condition;
};

struct GroupByStage {
    std::vector<FieldRefExpr> keys;
};

struct HavingStage {
    ExprPtr predicate;
};

struct LetStage {
    std::string name;
    TypeRef     type;
    ExprPtr     expr;
};

struct ProjectedField {
    std::string                 name;
    ExprPtr                     value;
    std::vector<ProjectedField> nested;
    bool                        is_nested = false;
};

struct ProjectStage {
    std::vector<ProjectedField> fields;
};

struct OrderByStage {
    struct Item {
        enum class Direction { Asc, Desc };
        ExprPtr   expr;
        ExprPtr   vector_query;
        Direction direction = Direction::Asc;
        bool      is_vector = false;
    };
    std::vector<Item> items;
};

struct LimitStage {
    uint64_t count = 0;
};

// ── StageData variant — '<' must be on the same line as std::variant ──────

using StageData = std::variant<
    FilterStage,
    JoinStage,
    GroupByStage,
    HavingStage,
    LetStage,
    ProjectStage,
    OrderByStage,
    LimitStage
>;

// ════════════════════════════════════════════════════════════════════════════
// Stage
// ════════════════════════════════════════════════════════════════════════════

class Stage {
public:
    enum class Kind {
        Filter,
        Join,
        GroupBy,
        Having,
        Let,
        Project,
        OrderBy,
        Limit,
    };

    [[nodiscard]] Kind kind() const noexcept { return kind_; }

    template <typename T>
    [[nodiscard]] const T& as() const { return std::get<T>(data_); }

    template <typename T>
    [[nodiscard]] T& as() { return std::get<T>(data_); }

    static Stage make_filter  (FilterStage   s) { return {Kind::Filter,   std::move(s)}; }
    static Stage make_join    (JoinStage     s) { return {Kind::Join,     std::move(s)}; }
    static Stage make_group_by(GroupByStage  s) { return {Kind::GroupBy,  std::move(s)}; }
    static Stage make_having  (HavingStage   s) { return {Kind::Having,   std::move(s)}; }
    static Stage make_let     (LetStage      s) { return {Kind::Let,      std::move(s)}; }
    static Stage make_project (ProjectStage  s) { return {Kind::Project,  std::move(s)}; }
    static Stage make_order_by(OrderByStage  s) { return {Kind::OrderBy,  std::move(s)}; }
    static Stage make_limit   (LimitStage    s) { return {Kind::Limit,    std::move(s)}; }

private:
    Stage(Kind k, StageData d) : kind_(k), data_(std::move(d)) {}

    Kind      kind_;
    StageData data_;
};

} // namespace tensor::tql