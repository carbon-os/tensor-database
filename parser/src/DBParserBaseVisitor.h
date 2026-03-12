
// Generated from DBParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "DBParserVisitor.h"


/**
 * This class provides an empty implementation of DBParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  DBParserBaseVisitor : public DBParserVisitor {
public:

  virtual std::any visitScript(DBParser::ScriptContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(DBParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportStmt(DBParser::ImportStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPackageDecl(DBParser::PackageDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeDecl(DBParser::TypeDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFieldDecl(DBParser::FieldDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNullablePrimitive(DBParser::NullablePrimitiveContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDecimalType(DBParser::DecimalTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitJsonType(DBParser::JsonTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayType(DBParser::ArrayTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVectorType(DBParser::VectorTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMapType(DBParser::MapTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeArg(DBParser::TypeArgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimitiveType(DBParser::PrimitiveTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQualifiedName(DBParser::QualifiedNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCreateTableStmt(DBParser::CreateTableStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCreateRoleStmt(DBParser::CreateRoleStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCreateApiKeyStmt(DBParser::CreateApiKeyStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGrantStmt(DBParser::GrantStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAllowRule(DBParser::AllowRuleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDenyRule(DBParser::DenyRuleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIamPermList(DBParser::IamPermListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIamPerm(DBParser::IamPermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIamPermOrStar(DBParser::IamPermOrStarContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQueryStmt(DBParser::QueryStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFromClause(DBParser::FromClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitJoinClause(DBParser::JoinClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhereClause(DBParser::WhereClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGroupByClause(DBParser::GroupByClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitHavingClause(DBParser::HavingClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectClause(DBParser::SelectClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProjectionBlock(DBParser::ProjectionBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLabeledProjection(DBParser::LabeledProjectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShorthandProjection(DBParser::ShorthandProjectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNestedProjection(DBParser::NestedProjectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOrderByClause(DBParser::OrderByClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOrderItem(DBParser::OrderItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLimitClause(DBParser::LimitClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLetBinding(DBParser::LetBindingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInsertStmt(DBParser::InsertStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralInsertBody(DBParser::LiteralInsertBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPipelineInsertBody(DBParser::PipelineInsertBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitValueBlock(DBParser::ValueBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitValueEntry(DBParser::ValueEntryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUpdateStmt(DBParser::UpdateStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSetClause(DBParser::SetClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSetEntry(DBParser::SetEntryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeleteStmt(DBParser::DeleteStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTruncateStmt(DBParser::TruncateStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUpsertStmt(DBParser::UpsertStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturningClause(DBParser::ReturningClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNotExpr(DBParser::NotExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryMinusExpr(DBParser::UnaryMinusExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExpr(DBParser::PrimaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOrExpr(DBParser::OrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComparisonExpr(DBParser::ComparisonExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDistanceExpr(DBParser::DistanceExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditiveExpr(DBParser::AdditiveExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContainsExpr(DBParser::ContainsExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicativeExpr(DBParser::MultiplicativeExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAndExpr(DBParser::AndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralPrimary(DBParser::LiteralPrimaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCallPrimary(DBParser::FunctionCallPrimaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAggregateCallPrimary(DBParser::AggregateCallPrimaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamePrimary(DBParser::NamePrimaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenPrimary(DBParser::ParenPrimaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCall(DBParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgList(DBParser::ArgListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCountStarCall(DBParser::CountStarCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAggregateFnCall(DBParser::AggregateFnCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAggregateFn(DBParser::AggregateFnContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(DBParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayLiteral(DBParser::ArrayLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprList(DBParser::ExprListContext *ctx) override {
    return visitChildren(ctx);
  }


};

