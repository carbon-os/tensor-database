#include <tensor/tql/pipeline.hpp>

#include "TQLLexer.h"
#include "TQLParser.h"
#include "TQLParserBaseVisitor.h"
#include "semantic.hpp"

#include <antlr4-runtime.h>
#include <stdexcept>

namespace tensor::tql {

// ════════════════════════════════════════════════════════════════════════════
// Helpers
// ════════════════════════════════════════════════════════════════════════════

static std::string strip_quotes(const std::string& s) {
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
        return s.substr(1, s.size() - 2);
    if (s.size() >= 2 && s.front() == '\'' && s.back() == '\'')
        return s.substr(1, s.size() - 2);
    return s;
}

// ════════════════════════════════════════════════════════════════════════════
// Compiler — walks the ANTLR parse tree and builds an unverified Pipeline.
// Semantic validation is performed by the five passes in Pipeline::compile.
// ════════════════════════════════════════════════════════════════════════════

class Compiler : public TQLParserBaseVisitor {
public:
    Pipeline             pipeline;
    std::optional<Error> error;

    // ── Types ─────────────────────────────────────────────────────────────

    std::any visitScalarType(TQLParser::ScalarTypeContext* ctx) override {
        TypeRef t;
        if      (ctx->INT32())        t.kind = TypeRef::Kind::Int32;
        else if (ctx->INT64())        t.kind = TypeRef::Kind::Int64;
        else if (ctx->FLOAT32())      t.kind = TypeRef::Kind::Float32;
        else if (ctx->FLOAT64())      t.kind = TypeRef::Kind::Float64;
        else if (ctx->BOOL_KW())      t.kind = TypeRef::Kind::Bool;
        else if (ctx->TEXT_KW())      t.kind = TypeRef::Kind::Text;
        else if (ctx->UUID_KW())      t.kind = TypeRef::Kind::Uuid;
        else if (ctx->TIMESTAMP_KW()) t.kind = TypeRef::Kind::Timestamp;
        else if (ctx->DECIMAL_KW()) {
            t.kind = TypeRef::Kind::Decimal;
            auto lits = ctx->INTEGER_LIT();
            t.decimal.precision = static_cast<uint8_t>(std::stoi(lits[0]->getText()));
            t.decimal.scale     = static_cast<uint8_t>(std::stoi(lits[1]->getText()));
        }
        return t;
    }

    std::any visitScalarTypeExpr(TQLParser::ScalarTypeExprContext* ctx) override {
        auto t = std::any_cast<TypeRef>(visitScalarType(ctx->scalarType()));
        t.nullable = ctx->QUESTION() != nullptr;
        return t;
    }

    std::any visitVectorTypeExpr(TQLParser::VectorTypeExprContext* ctx) override {
        TypeRef t;
        t.kind       = TypeRef::Kind::Vector;
        t.vector_dim = static_cast<uint32_t>(std::stoul(ctx->INTEGER_LIT()->getText()));
        t.nullable   = ctx->QUESTION() != nullptr;
        return t;
    }

    std::any visitArrayTypeExpr(TQLParser::ArrayTypeExprContext* ctx) override {
        TypeRef t; t.kind = TypeRef::Kind::Array; t.nullable = ctx->QUESTION() != nullptr;
        return t;
    }

    std::any visitJsonTypeExpr(TQLParser::JsonTypeExprContext* ctx) override {
        TypeRef t; t.kind = TypeRef::Kind::Json; t.nullable = ctx->QUESTION() != nullptr;
        return t;
    }

    std::any visitUserDefinedTypeExpr(TQLParser::UserDefinedTypeExprContext* ctx) override {
        auto t = std::any_cast<TypeRef>(visitQualifiedTypeName(ctx->qualifiedTypeName()));
        t.nullable = ctx->QUESTION() != nullptr;
        return t;
    }

    std::any visitQualifiedTypeName(TQLParser::QualifiedTypeNameContext* ctx) override {
        TypeRef t; t.kind = TypeRef::Kind::UserDefined;
        auto ids = ctx->IDENTIFIER();
        if (ids.size() == 2) { t.package = ids[0]->getText(); t.name = ids[1]->getText(); }
        else                 { t.name = ids[0]->getText(); }
        return t;
    }

    TypeRef resolve_type(TQLParser::TypeExprContext* ctx) {
        return std::any_cast<TypeRef>(visit(ctx));
    }

    // ── Path binding ──────────────────────────────────────────────────────

    std::any visitPathBinding(TQLParser::PathBindingContext* ctx) override {
        PathBinding b;
        b.path = strip_quotes(ctx->STRING_LIT()->getText());
        auto* vb = ctx->varBinding();
        if (vb->IDENTIFIER()) {
            b.var  = vb->IDENTIFIER()->getText();
            b.type = std::any_cast<TypeRef>(visitQualifiedTypeName(vb->qualifiedTypeName()));
        } else {
            b.type = std::any_cast<TypeRef>(visitQualifiedTypeName(vb->qualifiedTypeName()));
        }
        return b;
    }

    // ── Expressions ───────────────────────────────────────────────────────

    ExprPtr build_expr(TQLParser::ExprContext* ctx) {
        return std::any_cast<ExprPtr>(visit(ctx));
    }

    std::any visitLiteralExpr(TQLParser::LiteralExprContext* ctx) override {
        return std::any_cast<ExprPtr>(visit(ctx->literal()));
    }

    std::any visitStringLit(TQLParser::StringLitContext* ctx) override {
        LiteralExpr lit; lit.kind = LiteralExpr::Kind::String;
        lit.string_val = strip_quotes(ctx->STRING_LIT()->getText());
        return make_expr(lit);
    }

    std::any visitJsonValueLit(TQLParser::JsonValueLitContext* ctx) override {
        LiteralExpr lit; lit.kind = LiteralExpr::Kind::String;
        lit.string_val = strip_quotes(ctx->SINGLE_STRING_LIT()->getText());
        return make_expr(lit);
    }

    std::any visitIntLit(TQLParser::IntLitContext* ctx) override {
        LiteralExpr lit; lit.kind = LiteralExpr::Kind::Int;
        lit.int_val = std::stoll(ctx->INTEGER_LIT()->getText());
        return make_expr(lit);
    }

    std::any visitFloatLit(TQLParser::FloatLitContext* ctx) override {
        LiteralExpr lit; lit.kind = LiteralExpr::Kind::Float;
        lit.float_val = std::stod(ctx->FLOAT_LIT()->getText());
        return make_expr(lit);
    }

    std::any visitTrueLit(TQLParser::TrueLitContext*) override {
        LiteralExpr lit; lit.kind = LiteralExpr::Kind::Bool; lit.bool_val = true;
        return make_expr(lit);
    }

    std::any visitFalseLit(TQLParser::FalseLitContext*) override {
        LiteralExpr lit; lit.kind = LiteralExpr::Kind::Bool; lit.bool_val = false;
        return make_expr(lit);
    }

    std::any visitNullLit(TQLParser::NullLitContext*) override {
        return make_expr(LiteralExpr{LiteralExpr::Kind::Null});
    }

    std::any visitNameExpr(TQLParser::NameExprContext* ctx) override {
        auto ids = ctx->qualifiedName()->IDENTIFIER();
        FieldRefExpr ref;
        if (ids.size() == 2) { ref.var = ids[0]->getText(); ref.field = ids[1]->getText(); }
        else                 { ref.field = ids[0]->getText(); }
        return make_expr(ref);
    }

    std::any visitParenExpr(TQLParser::ParenExprContext* ctx) override {
        return visit(ctx->expr());
    }

    std::any visitUnaryNegExpr(TQLParser::UnaryNegExprContext* ctx) override {
        UnaryExpr u; u.op = UnaryExpr::Op::Neg; u.operand = build_expr(ctx->expr());
        return make_expr(u);
    }

    std::any visitNotExpr(TQLParser::NotExprContext* ctx) override {
        UnaryExpr u; u.op = UnaryExpr::Op::Not; u.operand = build_expr(ctx->expr());
        return make_expr(u);
    }

    std::any visitMulDivExpr(TQLParser::MulDivExprContext* ctx) override {
        BinaryExpr b;
        b.op  = ctx->STAR() ? BinaryExpr::Op::Mul : BinaryExpr::Op::Div;
        b.lhs = build_expr(ctx->expr(0)); b.rhs = build_expr(ctx->expr(1));
        return make_expr(b);
    }

    std::any visitAddSubExpr(TQLParser::AddSubExprContext* ctx) override {
        BinaryExpr b;
        b.op  = ctx->PLUS() ? BinaryExpr::Op::Add : BinaryExpr::Op::Sub;
        b.lhs = build_expr(ctx->expr(0)); b.rhs = build_expr(ctx->expr(1));
        return make_expr(b);
    }

    std::any visitComparisonExpr(TQLParser::ComparisonExprContext* ctx) override {
        BinaryExpr b;
        if      (ctx->EQ())  b.op = BinaryExpr::Op::Eq;
        else if (ctx->NEQ()) b.op = BinaryExpr::Op::Neq;
        else if (ctx->LT())  b.op = BinaryExpr::Op::Lt;
        else if (ctx->GT())  b.op = BinaryExpr::Op::Gt;
        else if (ctx->LTE()) b.op = BinaryExpr::Op::Lte;
        else                 b.op = BinaryExpr::Op::Gte;
        b.lhs = build_expr(ctx->expr(0)); b.rhs = build_expr(ctx->expr(1));
        return make_expr(b);
    }

    std::any visitAndExpr(TQLParser::AndExprContext* ctx) override {
        BinaryExpr b; b.op = BinaryExpr::Op::And;
        b.lhs = build_expr(ctx->expr(0)); b.rhs = build_expr(ctx->expr(1));
        return make_expr(b);
    }

    std::any visitOrExpr(TQLParser::OrExprContext* ctx) override {
        BinaryExpr b; b.op = BinaryExpr::Op::Or;
        b.lhs = build_expr(ctx->expr(0)); b.rhs = build_expr(ctx->expr(1));
        return make_expr(b);
    }

    std::any visitArrayLiteralExpr(TQLParser::ArrayLiteralExprContext* ctx) override {
        LiteralExpr lit; lit.kind = LiteralExpr::Kind::String;
        lit.string_val = ctx->arrayLiteral()->getText();
        return make_expr(lit);
    }

    // ── Function calls ────────────────────────────────────────────────────

    std::any visitFuncCallExpr(TQLParser::FuncCallExprContext* ctx) override {
        return visit(ctx->functionCall());
    }

    std::any visitGenUuidCall(TQLParser::GenUuidCallContext*) override {
        return make_expr(GenUuidExpr{});
    }

    std::any visitNowCall(TQLParser::NowCallContext*) override {
        return make_expr(NowExpr{});
    }

    std::any visitMatchCall(TQLParser::MatchCallContext* ctx) override {
        MatchExpr m; m.field = build_expr(ctx->expr());
        m.token = strip_quotes(ctx->STRING_LIT()->getText());
        return make_expr(m);
    }

    std::any visitEmbedCall(TQLParser::EmbedCallContext* ctx) override {
        EmbedExpr e;
        e.query    = strip_quotes(ctx->STRING_LIT()->getText());
        e.constant = ctx->qualifiedName() ? ctx->qualifiedName()->getText() : "tensor.SEARCH";
        return make_expr(e);
    }

    std::any visitPromptCall(TQLParser::PromptCallContext* ctx) override {
        PromptExpr p;
        p.source_field = build_expr(ctx->expr());
        p.query        = strip_quotes(ctx->STRING_LIT()->getText());
        p.constant     = ctx->qualifiedName()->getText();
        return make_expr(p);
    }

    std::any visitCountCall(TQLParser::CountCallContext* ctx) override {
        AggExpr a; a.func = AggExpr::Func::Count;
        a.count_star = ctx->STAR() != nullptr;
        if (!a.count_star) a.arg = build_expr(ctx->expr());
        return make_expr(a);
    }

    std::any visitSumCall(TQLParser::SumCallContext* ctx) override {
        return make_expr(AggExpr{ AggExpr::Func::Sum, build_expr(ctx->expr()) });
    }

    std::any visitAvgCall(TQLParser::AvgCallContext* ctx) override {
        return make_expr(AggExpr{ AggExpr::Func::Avg, build_expr(ctx->expr()) });
    }

    std::any visitMinCall(TQLParser::MinCallContext* ctx) override {
        return make_expr(AggExpr{ AggExpr::Func::Min, build_expr(ctx->expr()) });
    }

    std::any visitMaxCall(TQLParser::MaxCallContext* ctx) override {
        return make_expr(AggExpr{ AggExpr::Func::Max, build_expr(ctx->expr()) });
    }

    // ── Pipeline stages ───────────────────────────────────────────────────

    std::any visitWhereClause(TQLParser::WhereClauseContext* ctx) override {
        pipeline.stages_.push_back(Stage::make_filter(FilterStage{ build_expr(ctx->expr()) }));
        return {};
    }

    std::any visitInnerJoin(TQLParser::InnerJoinContext* ctx) override {
        JoinStage j; j.kind = JoinStage::Kind::Inner;
        j.binding   = std::any_cast<PathBinding>(visitPathBinding(ctx->pathBinding()));
        j.condition = build_expr(ctx->expr());
        pipeline.stages_.push_back(Stage::make_join(std::move(j)));
        return {};
    }

    std::any visitLeftOuterJoin(TQLParser::LeftOuterJoinContext* ctx) override {
        JoinStage j; j.kind = JoinStage::Kind::Left;
        j.binding   = std::any_cast<PathBinding>(visitPathBinding(ctx->pathBinding()));
        j.condition = build_expr(ctx->expr());
        pipeline.stages_.push_back(Stage::make_join(std::move(j)));
        return {};
    }

    std::any visitGroupByClause(TQLParser::GroupByClauseContext* ctx) override {
        GroupByStage g;
        for (auto* ref : ctx->fieldRef()) {
            auto ids = ref->qualifiedName()->IDENTIFIER();
            FieldRefExpr f;
            if (ids.size() == 2) { f.var = ids[0]->getText(); f.field = ids[1]->getText(); }
            else                 { f.field = ids[0]->getText(); }
            g.keys.push_back(std::move(f));
        }
        pipeline.stages_.push_back(Stage::make_group_by(std::move(g)));
        return {};
    }

    std::any visitHavingClause(TQLParser::HavingClauseContext* ctx) override {
        pipeline.stages_.push_back(Stage::make_having(HavingStage{ build_expr(ctx->expr()) }));
        return {};
    }

    std::any visitLetClause(TQLParser::LetClauseContext* ctx) override {
        LetStage s;
        s.name = ctx->IDENTIFIER()->getText();
        s.type = resolve_type(ctx->typeExpr());
        s.expr = build_expr(ctx->expr());
        if (std::holds_alternative<PromptExpr>(s.expr->node))
            std::get<PromptExpr>(s.expr->node).output_type = s.type;
        pipeline.stages_.push_back(Stage::make_let(std::move(s)));
        return {};
    }

    std::any visitSelectClause(TQLParser::SelectClauseContext* ctx) override {
        ProjectStage p;
        for (auto* f : ctx->selectField())
            p.fields.push_back(build_projected_field(f));
        pipeline.stages_.push_back(Stage::make_project(std::move(p)));
        return {};
    }

    std::any visitOrderByClause(TQLParser::OrderByClauseContext* ctx) override {
        OrderByStage o;
        for (auto* item : ctx->orderByItem()) {
            if (auto* v = dynamic_cast<TQLParser::VectorOrderByItemContext*>(item)) {
                OrderByStage::Item i; i.is_vector = true;
                i.expr         = build_expr(v->expr(0));
                i.vector_query = build_expr(v->expr(1));
                i.direction    = v->DESC() ? OrderByStage::Item::Direction::Desc
                                           : OrderByStage::Item::Direction::Asc;
                o.items.push_back(std::move(i));
            } else if (auto* s = dynamic_cast<TQLParser::ScalarOrderByItemContext*>(item)) {
                OrderByStage::Item i; i.is_vector = false;
                i.expr      = build_expr(s->expr());
                i.direction = s->DESC() ? OrderByStage::Item::Direction::Desc
                                        : OrderByStage::Item::Direction::Asc;
                o.items.push_back(std::move(i));
            }
        }
        pipeline.stages_.push_back(Stage::make_order_by(std::move(o)));
        return {};
    }

    std::any visitLimitClause(TQLParser::LimitClauseContext* ctx) override {
        pipeline.stages_.push_back(
            Stage::make_limit(LimitStage{ std::stoull(ctx->INTEGER_LIT()->getText()) }));
        return {};
    }

    // ── Projected field helper ────────────────────────────────────────────

    ProjectedField build_projected_field(TQLParser::SelectFieldContext* ctx) {
        ProjectedField f;
        if (auto* named = dynamic_cast<TQLParser::NamedSelectFieldContext*>(ctx)) {
            f.name = named->IDENTIFIER()->getText();
            auto* val = named->selectValue();
            if (val->expr()) {
                f.value = build_expr(val->expr());
            } else {
                f.is_nested = true;
                for (auto* nested : val->selectField())
                    f.nested.push_back(build_projected_field(nested));
            }
        } else if (auto* bare = dynamic_cast<TQLParser::BareSelectFieldContext*>(ctx)) {
            f.name = bare->IDENTIFIER()->getText();
            FieldRefExpr ref; ref.field = f.name;
            f.value = make_expr(ref);
        }
        return f;
    }

    // ── Returning clause ──────────────────────────────────────────────────

    std::any visitReturningClause(TQLParser::ReturningClauseContext* ctx) override {
        for (auto* f : ctx->returningField()) {
            if (auto* named = dynamic_cast<TQLParser::NamedReturningFieldContext*>(f)) {
                pipeline.returning_.push_back(ReturningField{
                    named->IDENTIFIER()->getText(), build_expr(named->expr()), false
                });
            } else if (dynamic_cast<TQLParser::MutationReturningFieldContext*>(f)) {
                pipeline.returning_.push_back(ReturningField{ "_mutation", nullptr, true });
            }
        }
        return {};
    }

    // ── Query statement ───────────────────────────────────────────────────

    std::any visitQueryStatement(TQLParser::QueryStatementContext* ctx) override {
        for (auto* let : ctx->letClause())
            visitLetClause(let);

        auto binding = std::any_cast<PathBinding>(
            visitPathBinding(ctx->fromClause()->pathBinding()));
        pipeline.target_   = binding.path;
        pipeline.from_var_ = binding.var;
        pipeline.type_     = binding.type;
        pipeline.mutation_ = Mutation::None;

        for (auto* j : ctx->joinClause()) visit(j);

        if (ctx->whereClause()) visitWhereClause(ctx->whereClause());

        if (ctx->aggregationBlock()) {
            auto* agg = ctx->aggregationBlock();
            visitGroupByClause(agg->groupByClause());
            for (auto* let : agg->letClause()) visitLetClause(let);
            if (agg->havingClause()) visitHavingClause(agg->havingClause());
        }

        visitSelectClause(ctx->selectClause());
        if (ctx->orderByClause()) visitOrderByClause(ctx->orderByClause());
        if (ctx->limitClause())   visitLimitClause(ctx->limitClause());
        return {};
    }

    // ── Insert ────────────────────────────────────────────────────────────

    std::any visitInsertStatement(TQLParser::InsertStatementContext* ctx) override {
        auto binding = std::any_cast<PathBinding>(visitPathBinding(ctx->pathBinding()));
        pipeline.target_   = binding.path;
        pipeline.from_var_ = binding.var;
        pipeline.type_     = binding.type;
        pipeline.mutation_ = Mutation::Insert;

        InsertPayload payload;
        auto* body = ctx->insertBody();

        if (auto* lit = dynamic_cast<TQLParser::InsertLiteralBodyContext*>(body)) {
            auto* rows = lit->insertRows();
            if (auto* single = dynamic_cast<TQLParser::SingleRowInsertContext*>(rows)) {
                std::vector<RowField> row;
                for (auto* f : single->rowField())
                    row.push_back({ f->IDENTIFIER()->getText(), build_expr(f->expr()) });
                payload.rows.push_back(std::move(row));
            } else if (auto* multi = dynamic_cast<TQLParser::MultiRowInsertContext*>(rows)) {
                for (auto* block : multi->rowBlock()) {
                    std::vector<RowField> row;
                    for (auto* f : block->rowField())
                        row.push_back({ f->IDENTIFIER()->getText(), build_expr(f->expr()) });
                    payload.rows.push_back(std::move(row));
                }
            }
        } else if (auto* from = dynamic_cast<TQLParser::InsertFromBodyAltContext*>(body)) {
            payload.is_from_query = true;
            auto* fb = from->insertFromBody();
            for (auto* j : fb->joinClause()) visit(j);
            if (fb->whereClause()) visitWhereClause(fb->whereClause());
            for (auto* let : fb->letClause()) visitLetClause(let);
            visitSelectClause(fb->selectClause());
        }

        pipeline.insert_ = std::move(payload);
        if (ctx->returningClause()) visitReturningClause(ctx->returningClause());
        return {};
    }

    // ── Update ────────────────────────────────────────────────────────────

    std::any visitUpdateStatement(TQLParser::UpdateStatementContext* ctx) override {
        auto binding = std::any_cast<PathBinding>(visitPathBinding(ctx->pathBinding()));
        pipeline.target_   = binding.path;
        pipeline.from_var_ = binding.var;
        pipeline.type_     = binding.type;
        pipeline.mutation_ = Mutation::Update;

        if (ctx->whereClause()) visitWhereClause(ctx->whereClause());
        for (auto* let : ctx->letClause()) visitLetClause(let);

        UpdatePayload payload;
        for (auto* f : ctx->setClause()->setField())
            payload.set_fields.push_back({ f->IDENTIFIER()->getText(), build_expr(f->expr()) });
        pipeline.update_ = std::move(payload);

        if (ctx->returningClause()) visitReturningClause(ctx->returningClause());
        return {};
    }

    // ── Delete ────────────────────────────────────────────────────────────

    std::any visitDeleteStatement(TQLParser::DeleteStatementContext* ctx) override {
        auto binding = std::any_cast<PathBinding>(visitPathBinding(ctx->pathBinding()));
        pipeline.target_   = binding.path;
        pipeline.from_var_ = binding.var;
        pipeline.type_     = binding.type;
        pipeline.mutation_ = Mutation::Delete;

        visitWhereClause(ctx->whereClause());
        if (ctx->returningClause()) visitReturningClause(ctx->returningClause());
        return {};
    }

    // ── Upsert ────────────────────────────────────────────────────────────

    std::any visitUpsertStatement(TQLParser::UpsertStatementContext* ctx) override {
        auto binding = std::any_cast<PathBinding>(visitPathBinding(ctx->pathBinding()));
        pipeline.target_   = binding.path;
        pipeline.from_var_ = binding.var;
        pipeline.type_     = binding.type;
        pipeline.mutation_ = Mutation::Upsert;

        UpsertPayload payload;
        payload.conflict_field = ctx->IDENTIFIER()->getText();
        for (auto* f : ctx->rowBlock()->rowField())
            payload.values.push_back({ f->IDENTIFIER()->getText(), build_expr(f->expr()) });
        for (auto* f : ctx->setField())
            payload.conflict_set.push_back({ f->IDENTIFIER()->getText(), build_expr(f->expr()) });
        pipeline.upsert_ = std::move(payload);

        if (ctx->returningClause()) visitReturningClause(ctx->returningClause());
        return {};
    }

    // ── Truncate ──────────────────────────────────────────────────────────

    std::any visitTruncateStatement(TQLParser::TruncateStatementContext* ctx) override {
        pipeline.target_   = strip_quotes(ctx->STRING_LIT()->getText());
        pipeline.mutation_ = Mutation::Truncate;
        return {};
    }

    // ── DDL — no pipeline stages; handled by db::Engine off the parse tree ─
    std::any visitCreateTableStatement (TQLParser::CreateTableStatementContext*)  override { return {}; }
    std::any visitCreateRoleStatement  (TQLParser::CreateRoleStatementContext*)   override { return {}; }
    std::any visitGrantStatement       (TQLParser::GrantStatementContext*)        override { return {}; }
    std::any visitCreateApiKeyStatement(TQLParser::CreateApiKeyStatementContext*) override { return {}; }
    std::any visitRevokeApiKeyStatement(TQLParser::RevokeApiKeyStatementContext*) override { return {}; }
};

// ════════════════════════════════════════════════════════════════════════════
// Error listener
// ════════════════════════════════════════════════════════════════════════════

class ErrorListener : public antlr4::BaseErrorListener {
public:
    std::optional<Error> error;

    void syntaxError(
        antlr4::Recognizer*,
        antlr4::Token*,
        size_t line, size_t column,
        const std::string& msg,
        std::exception_ptr
    ) override {
        if (!error) error = Error{ msg, line, column };
    }
};

// ════════════════════════════════════════════════════════════════════════════
// Pipeline::compile — chains all five passes
// ════════════════════════════════════════════════════════════════════════════

Result<Pipeline> Pipeline::compile(std::string_view source, PackageResolver* resolver) {

    // ── Pass 0: ANTLR parse ───────────────────────────────────────────────
    antlr4::ANTLRInputStream  input(source.data(), source.size());
    TQLLexer                  lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    TQLParser                 parser(&tokens);

    ErrorListener errors;
    lexer.removeErrorListeners();   lexer.addErrorListener(&errors);
    parser.removeErrorListeners();  parser.addErrorListener(&errors);

    auto* tree = parser.file();
    if (errors.error)
        return Result<Pipeline>::failure(std::move(*errors.error));

    // ── Pass 1: Import resolution ─────────────────────────────────────────
    PackageRegistry registry;
    if (auto* exec = dynamic_cast<TQLParser::ExecutableFileContext*>(tree)) {
        auto reg_result = resolve_imports(exec, resolver);
        if (!reg_result.ok())
            return Result<Pipeline>::failure(reg_result.error());
        registry = std::move(reg_result.value());
    }

    // ── Compiler: build unverified Pipeline ───────────────────────────────
    Compiler compiler;
    compiler.visit(tree);
    if (compiler.error)
        return Result<Pipeline>::failure(std::move(*compiler.error));

    Pipeline pipeline       = std::move(compiler.pipeline);
    pipeline.registry_      = std::move(registry);

    // ── Pass 2: Scope resolution ──────────────────────────────────────────
    auto scope_result = check_scope(
        pipeline.stages_,
        pipeline.from_var_,
        pipeline.type_,
        pipeline.returning_,
        pipeline.registry_
    );
    if (!scope_result.ok())
        return Result<Pipeline>::failure(scope_result.error());

    const SymbolTable& sym = scope_result.value();

    // ── Pass 3: Type checking ─────────────────────────────────────────────
    if (auto r = check_types(pipeline.stages_, sym, pipeline.registry_); !r.ok())
        return Result<Pipeline>::failure(r.error());

    // ── Pass 4: Aggregate context ─────────────────────────────────────────
    if (auto r = check_aggregates(pipeline.stages_); !r.ok())
        return Result<Pipeline>::failure(r.error());

    // ── Pass 5: Constant folding ──────────────────────────────────────────
    fold_constants(pipeline.stages_);

    if (pipeline.insert_.has_value())
        for (auto& row : pipeline.insert_->rows)
            fold_row_fields(row);

    if (pipeline.update_.has_value())
        fold_row_fields(pipeline.update_->set_fields);

    if (pipeline.upsert_.has_value()) {
        fold_row_fields(pipeline.upsert_->values);
        fold_row_fields(pipeline.upsert_->conflict_set);
    }

    fold_returning_fields(pipeline.returning_);

    return Result<Pipeline>::success(std::move(pipeline));
}

} // namespace tensor::tql