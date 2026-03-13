
// Generated from /home/user/tensor-database/parser/TQLParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "TQLParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by TQLParser.
 */
class  TQLParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by TQLParser.
   */
    virtual std::any visitPackageFile(TQLParser::PackageFileContext *context) = 0;

    virtual std::any visitExecutableFile(TQLParser::ExecutableFileContext *context) = 0;

    virtual std::any visitPackageDecl(TQLParser::PackageDeclContext *context) = 0;

    virtual std::any visitTypeDecl(TQLParser::TypeDeclContext *context) = 0;

    virtual std::any visitFieldDecl(TQLParser::FieldDeclContext *context) = 0;

    virtual std::any visitImportDecl(TQLParser::ImportDeclContext *context) = 0;

    virtual std::any visitStatement(TQLParser::StatementContext *context) = 0;

    virtual std::any visitScalarTypeExpr(TQLParser::ScalarTypeExprContext *context) = 0;

    virtual std::any visitVectorTypeExpr(TQLParser::VectorTypeExprContext *context) = 0;

    virtual std::any visitArrayTypeExpr(TQLParser::ArrayTypeExprContext *context) = 0;

    virtual std::any visitJsonTypeExpr(TQLParser::JsonTypeExprContext *context) = 0;

    virtual std::any visitUserDefinedTypeExpr(TQLParser::UserDefinedTypeExprContext *context) = 0;

    virtual std::any visitArrayElementType(TQLParser::ArrayElementTypeContext *context) = 0;

    virtual std::any visitScalarType(TQLParser::ScalarTypeContext *context) = 0;

    virtual std::any visitJsonTypeParam(TQLParser::JsonTypeParamContext *context) = 0;

    virtual std::any visitQualifiedTypeName(TQLParser::QualifiedTypeNameContext *context) = 0;

    virtual std::any visitPathBinding(TQLParser::PathBindingContext *context) = 0;

    virtual std::any visitVarBinding(TQLParser::VarBindingContext *context) = 0;

    virtual std::any visitQueryStatement(TQLParser::QueryStatementContext *context) = 0;

    virtual std::any visitAggregationBlock(TQLParser::AggregationBlockContext *context) = 0;

    virtual std::any visitFromClause(TQLParser::FromClauseContext *context) = 0;

    virtual std::any visitInnerJoin(TQLParser::InnerJoinContext *context) = 0;

    virtual std::any visitLeftOuterJoin(TQLParser::LeftOuterJoinContext *context) = 0;

    virtual std::any visitWhereClause(TQLParser::WhereClauseContext *context) = 0;

    virtual std::any visitGroupByClause(TQLParser::GroupByClauseContext *context) = 0;

    virtual std::any visitHavingClause(TQLParser::HavingClauseContext *context) = 0;

    virtual std::any visitLetClause(TQLParser::LetClauseContext *context) = 0;

    virtual std::any visitSelectClause(TQLParser::SelectClauseContext *context) = 0;

    virtual std::any visitNamedSelectField(TQLParser::NamedSelectFieldContext *context) = 0;

    virtual std::any visitBareSelectField(TQLParser::BareSelectFieldContext *context) = 0;

    virtual std::any visitSelectValue(TQLParser::SelectValueContext *context) = 0;

    virtual std::any visitOrderByClause(TQLParser::OrderByClauseContext *context) = 0;

    virtual std::any visitVectorOrderByItem(TQLParser::VectorOrderByItemContext *context) = 0;

    virtual std::any visitScalarOrderByItem(TQLParser::ScalarOrderByItemContext *context) = 0;

    virtual std::any visitLimitClause(TQLParser::LimitClauseContext *context) = 0;

    virtual std::any visitInsertStatement(TQLParser::InsertStatementContext *context) = 0;

    virtual std::any visitInsertLiteralBody(TQLParser::InsertLiteralBodyContext *context) = 0;

    virtual std::any visitInsertFromBodyAlt(TQLParser::InsertFromBodyAltContext *context) = 0;

    virtual std::any visitSingleRowInsert(TQLParser::SingleRowInsertContext *context) = 0;

    virtual std::any visitMultiRowInsert(TQLParser::MultiRowInsertContext *context) = 0;

    virtual std::any visitRowBlock(TQLParser::RowBlockContext *context) = 0;

    virtual std::any visitRowField(TQLParser::RowFieldContext *context) = 0;

    virtual std::any visitInsertFromBody(TQLParser::InsertFromBodyContext *context) = 0;

    virtual std::any visitUpdateStatement(TQLParser::UpdateStatementContext *context) = 0;

    virtual std::any visitSetClause(TQLParser::SetClauseContext *context) = 0;

    virtual std::any visitSetField(TQLParser::SetFieldContext *context) = 0;

    virtual std::any visitDeleteStatement(TQLParser::DeleteStatementContext *context) = 0;

    virtual std::any visitUpsertStatement(TQLParser::UpsertStatementContext *context) = 0;

    virtual std::any visitReturningClause(TQLParser::ReturningClauseContext *context) = 0;

    virtual std::any visitNamedReturningField(TQLParser::NamedReturningFieldContext *context) = 0;

    virtual std::any visitMutationReturningField(TQLParser::MutationReturningFieldContext *context) = 0;

    virtual std::any visitCreateTableStatement(TQLParser::CreateTableStatementContext *context) = 0;

    virtual std::any visitCreateRoleStatement(TQLParser::CreateRoleStatementContext *context) = 0;

    virtual std::any visitGrantStatement(TQLParser::GrantStatementContext *context) = 0;

    virtual std::any visitGrantRule(TQLParser::GrantRuleContext *context) = 0;

    virtual std::any visitOperationList(TQLParser::OperationListContext *context) = 0;

    virtual std::any visitOperation(TQLParser::OperationContext *context) = 0;

    virtual std::any visitCreateApiKeyStatement(TQLParser::CreateApiKeyStatementContext *context) = 0;

    virtual std::any visitRevokeApiKeyStatement(TQLParser::RevokeApiKeyStatementContext *context) = 0;

    virtual std::any visitTruncateStatement(TQLParser::TruncateStatementContext *context) = 0;

    virtual std::any visitFieldRef(TQLParser::FieldRefContext *context) = 0;

    virtual std::any visitQualifiedName(TQLParser::QualifiedNameContext *context) = 0;

    virtual std::any visitNotExpr(TQLParser::NotExprContext *context) = 0;

    virtual std::any visitAddSubExpr(TQLParser::AddSubExprContext *context) = 0;

    virtual std::any visitLiteralExpr(TQLParser::LiteralExprContext *context) = 0;

    virtual std::any visitOrExpr(TQLParser::OrExprContext *context) = 0;

    virtual std::any visitComparisonExpr(TQLParser::ComparisonExprContext *context) = 0;

    virtual std::any visitUnaryNegExpr(TQLParser::UnaryNegExprContext *context) = 0;

    virtual std::any visitFuncCallExpr(TQLParser::FuncCallExprContext *context) = 0;

    virtual std::any visitArrayLiteralExpr(TQLParser::ArrayLiteralExprContext *context) = 0;

    virtual std::any visitMulDivExpr(TQLParser::MulDivExprContext *context) = 0;

    virtual std::any visitParenExpr(TQLParser::ParenExprContext *context) = 0;

    virtual std::any visitNameExpr(TQLParser::NameExprContext *context) = 0;

    virtual std::any visitAndExpr(TQLParser::AndExprContext *context) = 0;

    virtual std::any visitGenUuidCall(TQLParser::GenUuidCallContext *context) = 0;

    virtual std::any visitNowCall(TQLParser::NowCallContext *context) = 0;

    virtual std::any visitMatchCall(TQLParser::MatchCallContext *context) = 0;

    virtual std::any visitEmbedCall(TQLParser::EmbedCallContext *context) = 0;

    virtual std::any visitPromptCall(TQLParser::PromptCallContext *context) = 0;

    virtual std::any visitCountCall(TQLParser::CountCallContext *context) = 0;

    virtual std::any visitSumCall(TQLParser::SumCallContext *context) = 0;

    virtual std::any visitAvgCall(TQLParser::AvgCallContext *context) = 0;

    virtual std::any visitMinCall(TQLParser::MinCallContext *context) = 0;

    virtual std::any visitMaxCall(TQLParser::MaxCallContext *context) = 0;

    virtual std::any visitStringLit(TQLParser::StringLitContext *context) = 0;

    virtual std::any visitJsonValueLit(TQLParser::JsonValueLitContext *context) = 0;

    virtual std::any visitFloatLit(TQLParser::FloatLitContext *context) = 0;

    virtual std::any visitIntLit(TQLParser::IntLitContext *context) = 0;

    virtual std::any visitTrueLit(TQLParser::TrueLitContext *context) = 0;

    virtual std::any visitFalseLit(TQLParser::FalseLitContext *context) = 0;

    virtual std::any visitNullLit(TQLParser::NullLitContext *context) = 0;

    virtual std::any visitArrayLiteral(TQLParser::ArrayLiteralContext *context) = 0;


};

