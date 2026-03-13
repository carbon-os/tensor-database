
// Generated from /home/user/tensor-database/parser/TQLParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "TQLParserVisitor.h"


/**
 * This class provides an empty implementation of TQLParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  TQLParserBaseVisitor : public TQLParserVisitor {
public:

  virtual std::any visitPackageFile(TQLParser::PackageFileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExecutableFile(TQLParser::ExecutableFileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPackageDecl(TQLParser::PackageDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeDecl(TQLParser::TypeDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFieldDecl(TQLParser::FieldDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportDecl(TQLParser::ImportDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(TQLParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScalarTypeExpr(TQLParser::ScalarTypeExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVectorTypeExpr(TQLParser::VectorTypeExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayTypeExpr(TQLParser::ArrayTypeExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitJsonTypeExpr(TQLParser::JsonTypeExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUserDefinedTypeExpr(TQLParser::UserDefinedTypeExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayElementType(TQLParser::ArrayElementTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScalarType(TQLParser::ScalarTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitJsonTypeParam(TQLParser::JsonTypeParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQualifiedTypeName(TQLParser::QualifiedTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPathBinding(TQLParser::PathBindingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarBinding(TQLParser::VarBindingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQueryStatement(TQLParser::QueryStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAggregationBlock(TQLParser::AggregationBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFromClause(TQLParser::FromClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInnerJoin(TQLParser::InnerJoinContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLeftOuterJoin(TQLParser::LeftOuterJoinContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhereClause(TQLParser::WhereClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGroupByClause(TQLParser::GroupByClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitHavingClause(TQLParser::HavingClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLetClause(TQLParser::LetClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectClause(TQLParser::SelectClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamedSelectField(TQLParser::NamedSelectFieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBareSelectField(TQLParser::BareSelectFieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectValue(TQLParser::SelectValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOrderByClause(TQLParser::OrderByClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVectorOrderByItem(TQLParser::VectorOrderByItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScalarOrderByItem(TQLParser::ScalarOrderByItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLimitClause(TQLParser::LimitClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInsertStatement(TQLParser::InsertStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInsertLiteralBody(TQLParser::InsertLiteralBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInsertFromBodyAlt(TQLParser::InsertFromBodyAltContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSingleRowInsert(TQLParser::SingleRowInsertContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiRowInsert(TQLParser::MultiRowInsertContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRowBlock(TQLParser::RowBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRowField(TQLParser::RowFieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInsertFromBody(TQLParser::InsertFromBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUpdateStatement(TQLParser::UpdateStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSetClause(TQLParser::SetClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSetField(TQLParser::SetFieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeleteStatement(TQLParser::DeleteStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUpsertStatement(TQLParser::UpsertStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturningClause(TQLParser::ReturningClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamedReturningField(TQLParser::NamedReturningFieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMutationReturningField(TQLParser::MutationReturningFieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCreateTableStatement(TQLParser::CreateTableStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCreateRoleStatement(TQLParser::CreateRoleStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGrantStatement(TQLParser::GrantStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGrantRule(TQLParser::GrantRuleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOperationList(TQLParser::OperationListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOperation(TQLParser::OperationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCreateApiKeyStatement(TQLParser::CreateApiKeyStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRevokeApiKeyStatement(TQLParser::RevokeApiKeyStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTruncateStatement(TQLParser::TruncateStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFieldRef(TQLParser::FieldRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQualifiedName(TQLParser::QualifiedNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNotExpr(TQLParser::NotExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddSubExpr(TQLParser::AddSubExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralExpr(TQLParser::LiteralExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOrExpr(TQLParser::OrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComparisonExpr(TQLParser::ComparisonExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryNegExpr(TQLParser::UnaryNegExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncCallExpr(TQLParser::FuncCallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayLiteralExpr(TQLParser::ArrayLiteralExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulDivExpr(TQLParser::MulDivExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenExpr(TQLParser::ParenExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNameExpr(TQLParser::NameExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAndExpr(TQLParser::AndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGenUuidCall(TQLParser::GenUuidCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNowCall(TQLParser::NowCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMatchCall(TQLParser::MatchCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmbedCall(TQLParser::EmbedCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPromptCall(TQLParser::PromptCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCountCall(TQLParser::CountCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSumCall(TQLParser::SumCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAvgCall(TQLParser::AvgCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMinCall(TQLParser::MinCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMaxCall(TQLParser::MaxCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStringLit(TQLParser::StringLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitJsonValueLit(TQLParser::JsonValueLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFloatLit(TQLParser::FloatLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntLit(TQLParser::IntLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTrueLit(TQLParser::TrueLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFalseLit(TQLParser::FalseLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNullLit(TQLParser::NullLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayLiteral(TQLParser::ArrayLiteralContext *ctx) override {
    return visitChildren(ctx);
  }


};

