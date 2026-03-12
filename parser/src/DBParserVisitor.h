
// Generated from DBParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "DBParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by DBParser.
 */
class  DBParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by DBParser.
   */
    virtual std::any visitScript(DBParser::ScriptContext *context) = 0;

    virtual std::any visitStatement(DBParser::StatementContext *context) = 0;

    virtual std::any visitImportStmt(DBParser::ImportStmtContext *context) = 0;

    virtual std::any visitPackageDecl(DBParser::PackageDeclContext *context) = 0;

    virtual std::any visitTypeDecl(DBParser::TypeDeclContext *context) = 0;

    virtual std::any visitFieldDecl(DBParser::FieldDeclContext *context) = 0;

    virtual std::any visitNullablePrimitive(DBParser::NullablePrimitiveContext *context) = 0;

    virtual std::any visitDecimalType(DBParser::DecimalTypeContext *context) = 0;

    virtual std::any visitJsonType(DBParser::JsonTypeContext *context) = 0;

    virtual std::any visitArrayType(DBParser::ArrayTypeContext *context) = 0;

    virtual std::any visitVectorType(DBParser::VectorTypeContext *context) = 0;

    virtual std::any visitMapType(DBParser::MapTypeContext *context) = 0;

    virtual std::any visitTypeArg(DBParser::TypeArgContext *context) = 0;

    virtual std::any visitPrimitiveType(DBParser::PrimitiveTypeContext *context) = 0;

    virtual std::any visitQualifiedName(DBParser::QualifiedNameContext *context) = 0;

    virtual std::any visitCreateTableStmt(DBParser::CreateTableStmtContext *context) = 0;

    virtual std::any visitCreateRoleStmt(DBParser::CreateRoleStmtContext *context) = 0;

    virtual std::any visitCreateApiKeyStmt(DBParser::CreateApiKeyStmtContext *context) = 0;

    virtual std::any visitGrantStmt(DBParser::GrantStmtContext *context) = 0;

    virtual std::any visitAllowRule(DBParser::AllowRuleContext *context) = 0;

    virtual std::any visitDenyRule(DBParser::DenyRuleContext *context) = 0;

    virtual std::any visitIamPermList(DBParser::IamPermListContext *context) = 0;

    virtual std::any visitIamPerm(DBParser::IamPermContext *context) = 0;

    virtual std::any visitIamPermOrStar(DBParser::IamPermOrStarContext *context) = 0;

    virtual std::any visitQueryStmt(DBParser::QueryStmtContext *context) = 0;

    virtual std::any visitFromClause(DBParser::FromClauseContext *context) = 0;

    virtual std::any visitJoinClause(DBParser::JoinClauseContext *context) = 0;

    virtual std::any visitWhereClause(DBParser::WhereClauseContext *context) = 0;

    virtual std::any visitGroupByClause(DBParser::GroupByClauseContext *context) = 0;

    virtual std::any visitHavingClause(DBParser::HavingClauseContext *context) = 0;

    virtual std::any visitSelectClause(DBParser::SelectClauseContext *context) = 0;

    virtual std::any visitProjectionBlock(DBParser::ProjectionBlockContext *context) = 0;

    virtual std::any visitLabeledProjection(DBParser::LabeledProjectionContext *context) = 0;

    virtual std::any visitShorthandProjection(DBParser::ShorthandProjectionContext *context) = 0;

    virtual std::any visitNestedProjection(DBParser::NestedProjectionContext *context) = 0;

    virtual std::any visitOrderByClause(DBParser::OrderByClauseContext *context) = 0;

    virtual std::any visitOrderItem(DBParser::OrderItemContext *context) = 0;

    virtual std::any visitLimitClause(DBParser::LimitClauseContext *context) = 0;

    virtual std::any visitLetBinding(DBParser::LetBindingContext *context) = 0;

    virtual std::any visitInsertStmt(DBParser::InsertStmtContext *context) = 0;

    virtual std::any visitLiteralInsertBody(DBParser::LiteralInsertBodyContext *context) = 0;

    virtual std::any visitPipelineInsertBody(DBParser::PipelineInsertBodyContext *context) = 0;

    virtual std::any visitValueBlock(DBParser::ValueBlockContext *context) = 0;

    virtual std::any visitValueEntry(DBParser::ValueEntryContext *context) = 0;

    virtual std::any visitUpdateStmt(DBParser::UpdateStmtContext *context) = 0;

    virtual std::any visitSetClause(DBParser::SetClauseContext *context) = 0;

    virtual std::any visitSetEntry(DBParser::SetEntryContext *context) = 0;

    virtual std::any visitDeleteStmt(DBParser::DeleteStmtContext *context) = 0;

    virtual std::any visitTruncateStmt(DBParser::TruncateStmtContext *context) = 0;

    virtual std::any visitUpsertStmt(DBParser::UpsertStmtContext *context) = 0;

    virtual std::any visitReturningClause(DBParser::ReturningClauseContext *context) = 0;

    virtual std::any visitNotExpr(DBParser::NotExprContext *context) = 0;

    virtual std::any visitUnaryMinusExpr(DBParser::UnaryMinusExprContext *context) = 0;

    virtual std::any visitPrimaryExpr(DBParser::PrimaryExprContext *context) = 0;

    virtual std::any visitOrExpr(DBParser::OrExprContext *context) = 0;

    virtual std::any visitComparisonExpr(DBParser::ComparisonExprContext *context) = 0;

    virtual std::any visitDistanceExpr(DBParser::DistanceExprContext *context) = 0;

    virtual std::any visitAdditiveExpr(DBParser::AdditiveExprContext *context) = 0;

    virtual std::any visitContainsExpr(DBParser::ContainsExprContext *context) = 0;

    virtual std::any visitMultiplicativeExpr(DBParser::MultiplicativeExprContext *context) = 0;

    virtual std::any visitAndExpr(DBParser::AndExprContext *context) = 0;

    virtual std::any visitLiteralPrimary(DBParser::LiteralPrimaryContext *context) = 0;

    virtual std::any visitFunctionCallPrimary(DBParser::FunctionCallPrimaryContext *context) = 0;

    virtual std::any visitAggregateCallPrimary(DBParser::AggregateCallPrimaryContext *context) = 0;

    virtual std::any visitNamePrimary(DBParser::NamePrimaryContext *context) = 0;

    virtual std::any visitParenPrimary(DBParser::ParenPrimaryContext *context) = 0;

    virtual std::any visitFunctionCall(DBParser::FunctionCallContext *context) = 0;

    virtual std::any visitArgList(DBParser::ArgListContext *context) = 0;

    virtual std::any visitCountStarCall(DBParser::CountStarCallContext *context) = 0;

    virtual std::any visitAggregateFnCall(DBParser::AggregateFnCallContext *context) = 0;

    virtual std::any visitAggregateFn(DBParser::AggregateFnContext *context) = 0;

    virtual std::any visitLiteral(DBParser::LiteralContext *context) = 0;

    virtual std::any visitArrayLiteral(DBParser::ArrayLiteralContext *context) = 0;

    virtual std::any visitExprList(DBParser::ExprListContext *context) = 0;


};

