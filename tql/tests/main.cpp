#include <tensor/tql/pipeline.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace tensor::tql;

// ════════════════════════════════════════════════════════════════════════════
// Printing helpers
// ════════════════════════════════════════════════════════════════════════════

static std::string indent(int depth) {
    return std::string(depth * 2, ' ');
}

static std::string type_ref_str(const TypeRef& t) {
    switch (t.kind) {
        case TypeRef::Kind::Int32:     return t.nullable ? "int32?"     : "int32";
        case TypeRef::Kind::Int64:     return t.nullable ? "int64?"     : "int64";
        case TypeRef::Kind::Float32:   return t.nullable ? "float32?"   : "float32";
        case TypeRef::Kind::Float64:   return t.nullable ? "float64?"   : "float64";
        case TypeRef::Kind::Bool:      return t.nullable ? "bool?"      : "bool";
        case TypeRef::Kind::Text:      return t.nullable ? "text?"      : "text";
        case TypeRef::Kind::Uuid:      return t.nullable ? "uuid?"      : "uuid";
        case TypeRef::Kind::Timestamp: return t.nullable ? "timestamp?" : "timestamp";
        case TypeRef::Kind::Json:      return t.nullable ? "json?"      : "json";
        case TypeRef::Kind::Array:     return t.nullable ? "array?"     : "array";
        case TypeRef::Kind::Vector:
            return "vector(" + std::to_string(t.vector_dim) + ")" + (t.nullable ? "?" : "");
        case TypeRef::Kind::Decimal:
            return "decimal(" + std::to_string(t.decimal.precision) + ","
                              + std::to_string(t.decimal.scale) + ")"
                              + (t.nullable ? "?" : "");
        case TypeRef::Kind::UserDefined:
            return t.qualified_name() + (t.nullable ? "?" : "");
    }
    return "?";
}

static std::string mutation_str(Mutation m) {
    switch (m) {
        case Mutation::None:     return "none";
        case Mutation::Insert:   return "insert";
        case Mutation::Update:   return "update";
        case Mutation::Delete:   return "delete";
        case Mutation::Upsert:   return "upsert";
        case Mutation::Truncate: return "truncate";
    }
    return "?";
}

// ── Expression printer ────────────────────────────────────────────────────

static std::string expr_str(const ExprPtr& e, int depth = 0);

static std::string expr_node_str(const ExprNode& node, int depth) {
    return std::visit([&](const auto& n) -> std::string {
        using T = std::decay_t<decltype(n)>;

        if constexpr (std::is_same_v<T, LiteralExpr>) {
            switch (n.kind) {
                case LiteralExpr::Kind::String: return "\"" + n.string_val + "\"";
                case LiteralExpr::Kind::Int:    return std::to_string(n.int_val);
                case LiteralExpr::Kind::Float:  return std::to_string(n.float_val);
                case LiteralExpr::Kind::Bool:   return n.bool_val ? "true" : "false";
                case LiteralExpr::Kind::Null:   return "null";
            }
        }
        else if constexpr (std::is_same_v<T, FieldRefExpr>) {
            return n.var.empty() ? n.field : n.var + "." + n.field;
        }
        else if constexpr (std::is_same_v<T, BinaryExpr>) {
            static const char* ops[] = {
                "+", "-", "*", "/", "==", "!=", "<", ">", "<=", ">=", "and", "or"
            };
            return "(" + expr_str(n.lhs, depth)
                + " " + ops[static_cast<int>(n.op)]
                + " " + expr_str(n.rhs, depth) + ")";
        }
        else if constexpr (std::is_same_v<T, UnaryExpr>) {
            return (n.op == UnaryExpr::Op::Neg ? "-" : "not ")
                + expr_str(n.operand, depth);
        }
        else if constexpr (std::is_same_v<T, GenUuidExpr>) { return "gen_uuid()"; }
        else if constexpr (std::is_same_v<T, NowExpr>)     { return "now()"; }
        else if constexpr (std::is_same_v<T, MatchExpr>) {
            return "match(" + expr_str(n.field, depth) + ", \"" + n.token + "\")";
        }
        else if constexpr (std::is_same_v<T, EmbedExpr>) {
            return "embed(\"" + n.query + "\", " + n.constant + ")";
        }
        else if constexpr (std::is_same_v<T, PromptExpr>) {
            return "prompt(" + expr_str(n.source_field, depth)
                + ", \"" + n.query + "\", " + n.constant
                + ") -> " + type_ref_str(n.output_type);
        }
        else if constexpr (std::is_same_v<T, AggExpr>) {
            static const char* fns[] = { "count", "sum", "avg", "min", "max" };
            std::string arg = n.count_star ? "*" : expr_str(n.arg, depth);
            return std::string(fns[static_cast<int>(n.func)]) + "(" + arg + ")";
        }
        return "?";
    }, node);
}

static std::string expr_str(const ExprPtr& e, int depth) {
    if (!e) return "<null>";
    return expr_node_str(e->node, depth);
}

// ── Projected field printer ───────────────────────────────────────────────

static void print_projected_field(const ProjectedField& f, int depth) {
    if (f.is_nested) {
        std::cout << indent(depth) << f.name << ": {\n";
        for (const auto& nested : f.nested)
            print_projected_field(nested, depth + 1);
        std::cout << indent(depth) << "}\n";
    } else {
        std::cout << indent(depth) << f.name << ": " << expr_str(f.value) << "\n";
    }
}

// ── Stage printer ─────────────────────────────────────────────────────────

static void print_stage(const Stage& stage, int i) {
    std::cout << "  [" << i << "] ";

    switch (stage.kind()) {

        case Stage::Kind::Filter: {
            const auto& s = stage.as<FilterStage>();
            std::cout << "Filter\n";
            std::cout << "        predicate: " << expr_str(s.predicate) << "\n";
            break;
        }

        case Stage::Kind::Join: {
            const auto& s = stage.as<JoinStage>();
            std::cout << "Join (" << (s.kind == JoinStage::Kind::Left ? "left" : "inner") << ")\n";
            std::cout << "        path:      " << s.binding.path << "\n";
            std::cout << "        var:       " << s.binding.var  << "\n";
            std::cout << "        type:      " << type_ref_str(s.binding.type) << "\n";
            std::cout << "        on:        " << expr_str(s.condition) << "\n";
            break;
        }

        case Stage::Kind::GroupBy: {
            const auto& s = stage.as<GroupByStage>();
            std::cout << "GroupBy\n";
            std::cout << "        keys:      ";
            for (size_t k = 0; k < s.keys.size(); ++k) {
                const auto& key = s.keys[k];
                std::cout << (key.var.empty() ? key.field : key.var + "." + key.field);
                if (k + 1 < s.keys.size()) std::cout << ", ";
            }
            std::cout << "\n";
            break;
        }

        case Stage::Kind::Having: {
            const auto& s = stage.as<HavingStage>();
            std::cout << "Having\n";
            std::cout << "        predicate: " << expr_str(s.predicate) << "\n";
            break;
        }

        case Stage::Kind::Let: {
            const auto& s = stage.as<LetStage>();
            std::cout << "Let\n";
            std::cout << "        name:      " << s.name << "\n";
            std::cout << "        type:      " << type_ref_str(s.type) << "\n";
            std::cout << "        expr:      " << expr_str(s.expr) << "\n";
            break;
        }

        case Stage::Kind::Project: {
            const auto& s = stage.as<ProjectStage>();
            std::cout << "Project\n";
            for (const auto& f : s.fields)
                print_projected_field(f, 4);
            break;
        }

        case Stage::Kind::OrderBy: {
            const auto& s = stage.as<OrderByStage>();
            std::cout << "OrderBy\n";
            for (const auto& item : s.items) {
                std::cout << "        - ";
                if (item.is_vector) {
                    std::cout << expr_str(item.expr)
                              << " <-> " << expr_str(item.vector_query);
                } else {
                    std::cout << expr_str(item.expr);
                }
                std::cout << " "
                          << (item.direction == OrderByStage::Item::Direction::Desc
                              ? "desc" : "asc")
                          << "\n";
            }
            break;
        }

        case Stage::Kind::Limit: {
            const auto& s = stage.as<LimitStage>();
            std::cout << "Limit\n";
            std::cout << "        count:     " << s.count << "\n";
            break;
        }
    }
}

// ════════════════════════════════════════════════════════════════════════════
// Main
// ════════════════════════════════════════════════════════════════════════════

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "usage: tql-test <file.tql>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "error: cannot open '" << argv[1] << "'\n";
        return 1;
    }

    std::ostringstream buf;
    buf << file.rdbuf();
    std::string source = buf.str();

    std::cout << "═══════════════════════════════════════════════\n";
    std::cout << "  source: " << argv[1] << "\n";
    std::cout << "═══════════════════════════════════════════════\n\n";
    std::cout << source << "\n";
    std::cout << "───────────────────────────────────────────────\n\n";

    // No resolver in the test harness — imports are skipped.
    // Scope, type, aggregate, and constant-folding passes still run.
    auto result = Pipeline::compile(source);

    if (!result.ok()) {
        const auto& err = result.error();
        std::cerr << "compile error at "
                  << err.line << ":" << err.column
                  << " — " << err.message << "\n";
        return 1;
    }

    const auto& p = result.value();

    // ── Pipeline header ───────────────────────────────────────────────────
    std::cout << "target:   " << p.target()             << "\n";
    std::cout << "from_var: " << p.from_var()            << "\n";
    std::cout << "type:     " << type_ref_str(p.type())  << "\n";
    std::cout << "mutation: " << mutation_str(p.mutation()) << "\n";

    // ── Registry — only printed when imports were resolved ────────────────
    // (always empty in the test harness since no resolver is provided)
    if (!p.registry().empty()) {
        std::cout << "registry: (populated)\n";
    } else {
        std::cout << "registry: (no resolver — imports skipped)\n";
    }

    std::cout << "stages:   " << p.stages().size() << "\n\n";

    // ── Stages ────────────────────────────────────────────────────────────
    for (size_t i = 0; i < p.stages().size(); ++i)
        print_stage(p.stages()[i], static_cast<int>(i));

    // ── Returning clause ──────────────────────────────────────────────────
    if (p.has_returning()) {
        std::cout << "\nreturning:\n";
        for (const auto& f : p.returning_fields()) {
            if (f.is_mutation_field) {
                std::cout << "  _mutation\n";
            } else {
                std::cout << "  " << f.name << ": " << expr_str(f.value) << "\n";
            }
        }
    }

    // ── Insert payload summary ────────────────────────────────────────────
    if (const auto* ins = p.insert_payload()) {
        if (!ins->is_from_query) {
            std::cout << "\ninsert rows: " << ins->rows.size() << "\n";
            for (size_t r = 0; r < ins->rows.size(); ++r) {
                std::cout << "  [" << r << "]\n";
                for (const auto& f : ins->rows[r])
                    std::cout << "    " << f.name << ": " << expr_str(f.value) << "\n";
            }
        } else {
            std::cout << "\ninsert from query\n";
        }
    }

    // ── Update payload summary ────────────────────────────────────────────
    if (const auto* upd = p.update_payload()) {
        std::cout << "\nset fields:\n";
        for (const auto& f : upd->set_fields)
            std::cout << "  " << f.name << ": " << expr_str(f.value) << "\n";
    }

    // ── Upsert payload summary ────────────────────────────────────────────
    if (const auto* ups = p.upsert_payload()) {
        std::cout << "\nupsert conflict on: " << ups->conflict_field << "\n";
        std::cout << "values:\n";
        for (const auto& f : ups->values)
            std::cout << "  " << f.name << ": " << expr_str(f.value) << "\n";
        std::cout << "conflict set:\n";
        for (const auto& f : ups->conflict_set)
            std::cout << "  " << f.name << ": " << expr_str(f.value) << "\n";
    }

    std::cout << "\n═══════════════════════════════════════════════\n";
    std::cout << "  ok\n";
    std::cout << "═══════════════════════════════════════════════\n";

    return 0;
}