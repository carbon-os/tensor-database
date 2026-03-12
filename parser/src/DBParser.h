
// Generated from DBParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  DBParser : public antlr4::Parser {
public:
  enum {
    IMPORT = 1, FROM = 2, AS = 3, WHERE = 4, LET = 5, SELECT = 6, ORDER = 7, 
    BY = 8, LIMIT = 9, GROUP = 10, HAVING = 11, JOIN = 12, LEFT = 13, ON = 14, 
    ASC = 15, DESC = 16, CONTAINS = 17, INSERT = 18, INTO = 19, UPDATE = 20, 
    SET = 21, DELETE = 22, UPSERT = 23, CONFLICT = 24, RETURNING = 25, TRUNCATE = 26, 
    CREATE = 27, TABLE = 28, PACKAGE = 29, TYPE = 30, ROLE = 31, GRANT = 32, 
    TO = 33, ALLOW = 34, DENY = 35, READ = 36, WRITE = 37, API_KEY = 38, 
    FOR = 39, EXPIRES = 40, IN = 41, K_INT32 = 42, K_INT64 = 43, K_FLOAT32 = 44, 
    K_FLOAT64 = 45, K_DECIMAL = 46, K_BOOL = 47, K_TEXT = 48, K_UUID = 49, 
    K_TIMESTAMP = 50, K_JSON = 51, K_ARRAY = 52, K_VECTOR = 53, K_MAP = 54, 
    TRUE = 55, FALSE = 56, NULL_ = 57, AND = 58, OR = 59, NOT = 60, DISTANCE = 61, 
    EQ = 62, NEQ = 63, LEQ = 64, GEQ = 65, LT = 66, GT = 67, PLUS = 68, 
    MINUS = 69, STAR = 70, SLASH = 71, ASSIGN = 72, DOT = 73, COMMA = 74, 
    COLON = 75, QUESTION = 76, LPAREN = 77, RPAREN = 78, LBRACE = 79, RBRACE = 80, 
    LBRACKET = 81, RBRACKET = 82, INTEGER_LIT = 83, DECIMAL_LIT = 84, STRING_LIT = 85, 
    SINGLE_STRING_LIT = 86, DURATION_LIT = 87, IDENTIFIER = 88, LINE_COMMENT = 89, 
    BLOCK_COMMENT = 90, WS = 91
  };

  enum {
    RuleScript = 0, RuleStatement = 1, RuleImportStmt = 2, RulePackageDecl = 3, 
    RuleTypeDecl = 4, RuleFieldDecl = 5, RuleTypeRef = 6, RuleTypeArg = 7, 
    RulePrimitiveType = 8, RuleQualifiedName = 9, RuleCreateTableStmt = 10, 
    RuleCreateRoleStmt = 11, RuleCreateApiKeyStmt = 12, RuleGrantStmt = 13, 
    RuleIamRule = 14, RuleIamPermList = 15, RuleIamPerm = 16, RuleIamPermOrStar = 17, 
    RuleQueryStmt = 18, RuleFromClause = 19, RuleJoinClause = 20, RuleWhereClause = 21, 
    RuleGroupByClause = 22, RuleHavingClause = 23, RuleSelectClause = 24, 
    RuleProjectionBlock = 25, RuleProjectionEntry = 26, RuleOrderByClause = 27, 
    RuleOrderItem = 28, RuleLimitClause = 29, RuleLetBinding = 30, RuleInsertStmt = 31, 
    RuleLiteralInsertBody = 32, RulePipelineInsertBody = 33, RuleValueBlock = 34, 
    RuleValueEntry = 35, RuleUpdateStmt = 36, RuleSetClause = 37, RuleSetEntry = 38, 
    RuleDeleteStmt = 39, RuleTruncateStmt = 40, RuleUpsertStmt = 41, RuleReturningClause = 42, 
    RuleExpr = 43, RulePrimary = 44, RuleFunctionCall = 45, RuleArgList = 46, 
    RuleAggregateCall = 47, RuleAggregateFn = 48, RuleLiteral = 49, RuleArrayLiteral = 50, 
    RuleExprList = 51
  };

  explicit DBParser(antlr4::TokenStream *input);

  DBParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~DBParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ScriptContext;
  class StatementContext;
  class ImportStmtContext;
  class PackageDeclContext;
  class TypeDeclContext;
  class FieldDeclContext;
  class TypeRefContext;
  class TypeArgContext;
  class PrimitiveTypeContext;
  class QualifiedNameContext;
  class CreateTableStmtContext;
  class CreateRoleStmtContext;
  class CreateApiKeyStmtContext;
  class GrantStmtContext;
  class IamRuleContext;
  class IamPermListContext;
  class IamPermContext;
  class IamPermOrStarContext;
  class QueryStmtContext;
  class FromClauseContext;
  class JoinClauseContext;
  class WhereClauseContext;
  class GroupByClauseContext;
  class HavingClauseContext;
  class SelectClauseContext;
  class ProjectionBlockContext;
  class ProjectionEntryContext;
  class OrderByClauseContext;
  class OrderItemContext;
  class LimitClauseContext;
  class LetBindingContext;
  class InsertStmtContext;
  class LiteralInsertBodyContext;
  class PipelineInsertBodyContext;
  class ValueBlockContext;
  class ValueEntryContext;
  class UpdateStmtContext;
  class SetClauseContext;
  class SetEntryContext;
  class DeleteStmtContext;
  class TruncateStmtContext;
  class UpsertStmtContext;
  class ReturningClauseContext;
  class ExprContext;
  class PrimaryContext;
  class FunctionCallContext;
  class ArgListContext;
  class AggregateCallContext;
  class AggregateFnContext;
  class LiteralContext;
  class ArrayLiteralContext;
  class ExprListContext; 

  class  ScriptContext : public antlr4::ParserRuleContext {
  public:
    ScriptContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ScriptContext* script();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ImportStmtContext *importStmt();
    PackageDeclContext *packageDecl();
    TypeDeclContext *typeDecl();
    CreateTableStmtContext *createTableStmt();
    CreateRoleStmtContext *createRoleStmt();
    GrantStmtContext *grantStmt();
    CreateApiKeyStmtContext *createApiKeyStmt();
    QueryStmtContext *queryStmt();
    InsertStmtContext *insertStmt();
    UpdateStmtContext *updateStmt();
    DeleteStmtContext *deleteStmt();
    UpsertStmtContext *upsertStmt();
    TruncateStmtContext *truncateStmt();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  ImportStmtContext : public antlr4::ParserRuleContext {
  public:
    ImportStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    antlr4::tree::TerminalNode *STRING_LIT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportStmtContext* importStmt();

  class  PackageDeclContext : public antlr4::ParserRuleContext {
  public:
    PackageDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PACKAGE();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PackageDeclContext* packageDecl();

  class  TypeDeclContext : public antlr4::ParserRuleContext {
  public:
    TypeDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<FieldDeclContext *> fieldDecl();
    FieldDeclContext* fieldDecl(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeDeclContext* typeDecl();

  class  FieldDeclContext : public antlr4::ParserRuleContext {
  public:
    FieldDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    TypeRefContext *typeRef();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FieldDeclContext* fieldDecl();

  class  TypeRefContext : public antlr4::ParserRuleContext {
  public:
    TypeRefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TypeRefContext() = default;
    void copyFrom(TypeRefContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DecimalTypeContext : public TypeRefContext {
  public:
    DecimalTypeContext(TypeRefContext *ctx);

    antlr4::tree::TerminalNode *K_DECIMAL();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<antlr4::tree::TerminalNode *> INTEGER_LIT();
    antlr4::tree::TerminalNode* INTEGER_LIT(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *QUESTION();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArrayTypeContext : public TypeRefContext {
  public:
    ArrayTypeContext(TypeRefContext *ctx);

    antlr4::tree::TerminalNode *K_ARRAY();
    antlr4::tree::TerminalNode *LT();
    TypeRefContext *typeRef();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *QUESTION();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VectorTypeContext : public TypeRefContext {
  public:
    VectorTypeContext(TypeRefContext *ctx);

    antlr4::tree::TerminalNode *K_VECTOR();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *INTEGER_LIT();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *QUESTION();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MapTypeContext : public TypeRefContext {
  public:
    MapTypeContext(TypeRefContext *ctx);

    antlr4::tree::TerminalNode *K_MAP();
    antlr4::tree::TerminalNode *LBRACKET();
    std::vector<TypeRefContext *> typeRef();
    TypeRefContext* typeRef(size_t i);
    antlr4::tree::TerminalNode *RBRACKET();
    antlr4::tree::TerminalNode *QUESTION();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  JsonTypeContext : public TypeRefContext {
  public:
    JsonTypeContext(TypeRefContext *ctx);

    antlr4::tree::TerminalNode *K_JSON();
    antlr4::tree::TerminalNode *LT();
    TypeArgContext *typeArg();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *QUESTION();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NullablePrimitiveContext : public TypeRefContext {
  public:
    NullablePrimitiveContext(TypeRefContext *ctx);

    PrimitiveTypeContext *primitiveType();
    antlr4::tree::TerminalNode *QUESTION();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TypeRefContext* typeRef();

  class  TypeArgContext : public antlr4::ParserRuleContext {
  public:
    TypeArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeRefContext *typeRef();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeArgContext* typeArg();

  class  PrimitiveTypeContext : public antlr4::ParserRuleContext {
  public:
    PrimitiveTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_INT32();
    antlr4::tree::TerminalNode *K_INT64();
    antlr4::tree::TerminalNode *K_FLOAT32();
    antlr4::tree::TerminalNode *K_FLOAT64();
    antlr4::tree::TerminalNode *K_BOOL();
    antlr4::tree::TerminalNode *K_TEXT();
    antlr4::tree::TerminalNode *K_UUID();
    antlr4::tree::TerminalNode *K_TIMESTAMP();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimitiveTypeContext* primitiveType();

  class  QualifiedNameContext : public antlr4::ParserRuleContext {
  public:
    QualifiedNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QualifiedNameContext* qualifiedName();

  class  CreateTableStmtContext : public antlr4::ParserRuleContext {
  public:
    CreateTableStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CREATE();
    antlr4::tree::TerminalNode *TABLE();
    antlr4::tree::TerminalNode *STRING_LIT();
    antlr4::tree::TerminalNode *AS();
    QualifiedNameContext *qualifiedName();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreateTableStmtContext* createTableStmt();

  class  CreateRoleStmtContext : public antlr4::ParserRuleContext {
  public:
    CreateRoleStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CREATE();
    antlr4::tree::TerminalNode *ROLE();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreateRoleStmtContext* createRoleStmt();

  class  CreateApiKeyStmtContext : public antlr4::ParserRuleContext {
  public:
    CreateApiKeyStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CREATE();
    antlr4::tree::TerminalNode *API_KEY();
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *EXPIRES();
    antlr4::tree::TerminalNode *IN();
    antlr4::tree::TerminalNode *DURATION_LIT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreateApiKeyStmtContext* createApiKeyStmt();

  class  GrantStmtContext : public antlr4::ParserRuleContext {
  public:
    GrantStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GRANT();
    antlr4::tree::TerminalNode *TO();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<IamRuleContext *> iamRule();
    IamRuleContext* iamRule(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GrantStmtContext* grantStmt();

  class  IamRuleContext : public antlr4::ParserRuleContext {
  public:
    IamRuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    IamRuleContext() = default;
    void copyFrom(IamRuleContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DenyRuleContext : public IamRuleContext {
  public:
    DenyRuleContext(IamRuleContext *ctx);

    antlr4::tree::TerminalNode *DENY();
    IamPermOrStarContext *iamPermOrStar();
    antlr4::tree::TerminalNode *ON();
    antlr4::tree::TerminalNode *STRING_LIT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AllowRuleContext : public IamRuleContext {
  public:
    AllowRuleContext(IamRuleContext *ctx);

    antlr4::tree::TerminalNode *ALLOW();
    IamPermListContext *iamPermList();
    antlr4::tree::TerminalNode *ON();
    antlr4::tree::TerminalNode *STRING_LIT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  IamRuleContext* iamRule();

  class  IamPermListContext : public antlr4::ParserRuleContext {
  public:
    IamPermListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IamPermContext *> iamPerm();
    IamPermContext* iamPerm(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IamPermListContext* iamPermList();

  class  IamPermContext : public antlr4::ParserRuleContext {
  public:
    IamPermContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *READ();
    antlr4::tree::TerminalNode *WRITE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IamPermContext* iamPerm();

  class  IamPermOrStarContext : public antlr4::ParserRuleContext {
  public:
    IamPermOrStarContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IamPermContext *> iamPerm();
    IamPermContext* iamPerm(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *STAR();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IamPermOrStarContext* iamPermOrStar();

  class  QueryStmtContext : public antlr4::ParserRuleContext {
  public:
    QueryStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FromClauseContext *fromClause();
    SelectClauseContext *selectClause();
    std::vector<LetBindingContext *> letBinding();
    LetBindingContext* letBinding(size_t i);
    std::vector<JoinClauseContext *> joinClause();
    JoinClauseContext* joinClause(size_t i);
    WhereClauseContext *whereClause();
    GroupByClauseContext *groupByClause();
    HavingClauseContext *havingClause();
    OrderByClauseContext *orderByClause();
    LimitClauseContext *limitClause();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QueryStmtContext* queryStmt();

  class  FromClauseContext : public antlr4::ParserRuleContext {
  public:
    FromClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FROM();
    antlr4::tree::TerminalNode *STRING_LIT();
    antlr4::tree::TerminalNode *AS();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    QualifiedNameContext *qualifiedName();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FromClauseContext* fromClause();

  class  JoinClauseContext : public antlr4::ParserRuleContext {
  public:
    JoinClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *JOIN();
    antlr4::tree::TerminalNode *STRING_LIT();
    antlr4::tree::TerminalNode *AS();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    QualifiedNameContext *qualifiedName();
    antlr4::tree::TerminalNode *ON();
    ExprContext *expr();
    antlr4::tree::TerminalNode *LEFT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  JoinClauseContext* joinClause();

  class  WhereClauseContext : public antlr4::ParserRuleContext {
  public:
    WhereClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHERE();
    ExprContext *expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WhereClauseContext* whereClause();

  class  GroupByClauseContext : public antlr4::ParserRuleContext {
  public:
    GroupByClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GROUP();
    antlr4::tree::TerminalNode *BY();
    ExprListContext *exprList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GroupByClauseContext* groupByClause();

  class  HavingClauseContext : public antlr4::ParserRuleContext {
  public:
    HavingClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HAVING();
    ExprContext *expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  HavingClauseContext* havingClause();

  class  SelectClauseContext : public antlr4::ParserRuleContext {
  public:
    SelectClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SELECT();
    ProjectionBlockContext *projectionBlock();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectClauseContext* selectClause();

  class  ProjectionBlockContext : public antlr4::ParserRuleContext {
  public:
    ProjectionBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<ProjectionEntryContext *> projectionEntry();
    ProjectionEntryContext* projectionEntry(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProjectionBlockContext* projectionBlock();

  class  ProjectionEntryContext : public antlr4::ParserRuleContext {
  public:
    ProjectionEntryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ProjectionEntryContext() = default;
    void copyFrom(ProjectionEntryContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  LabeledProjectionContext : public ProjectionEntryContext {
  public:
    LabeledProjectionContext(ProjectionEntryContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NestedProjectionContext : public ProjectionEntryContext {
  public:
    NestedProjectionContext(ProjectionEntryContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    ProjectionBlockContext *projectionBlock();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ShorthandProjectionContext : public ProjectionEntryContext {
  public:
    ShorthandProjectionContext(ProjectionEntryContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ProjectionEntryContext* projectionEntry();

  class  OrderByClauseContext : public antlr4::ParserRuleContext {
  public:
    OrderByClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ORDER();
    antlr4::tree::TerminalNode *BY();
    std::vector<OrderItemContext *> orderItem();
    OrderItemContext* orderItem(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OrderByClauseContext* orderByClause();

  class  OrderItemContext : public antlr4::ParserRuleContext {
  public:
    OrderItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    antlr4::tree::TerminalNode *ASC();
    antlr4::tree::TerminalNode *DESC();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OrderItemContext* orderItem();

  class  LimitClauseContext : public antlr4::ParserRuleContext {
  public:
    LimitClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LIMIT();
    antlr4::tree::TerminalNode *INTEGER_LIT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LimitClauseContext* limitClause();

  class  LetBindingContext : public antlr4::ParserRuleContext {
  public:
    LetBindingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LET();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *COLON();
    TypeRefContext *typeRef();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LetBindingContext* letBinding();

  class  InsertStmtContext : public antlr4::ParserRuleContext {
  public:
    InsertStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INSERT();
    antlr4::tree::TerminalNode *INTO();
    antlr4::tree::TerminalNode *STRING_LIT();
    antlr4::tree::TerminalNode *AS();
    QualifiedNameContext *qualifiedName();
    LiteralInsertBodyContext *literalInsertBody();
    PipelineInsertBodyContext *pipelineInsertBody();
    ReturningClauseContext *returningClause();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InsertStmtContext* insertStmt();

  class  LiteralInsertBodyContext : public antlr4::ParserRuleContext {
  public:
    LiteralInsertBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ValueBlockContext *> valueBlock();
    ValueBlockContext* valueBlock(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralInsertBodyContext* literalInsertBody();

  class  PipelineInsertBodyContext : public antlr4::ParserRuleContext {
  public:
    PipelineInsertBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FromClauseContext *fromClause();
    SelectClauseContext *selectClause();
    std::vector<JoinClauseContext *> joinClause();
    JoinClauseContext* joinClause(size_t i);
    WhereClauseContext *whereClause();
    std::vector<LetBindingContext *> letBinding();
    LetBindingContext* letBinding(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PipelineInsertBodyContext* pipelineInsertBody();

  class  ValueBlockContext : public antlr4::ParserRuleContext {
  public:
    ValueBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<ValueEntryContext *> valueEntry();
    ValueEntryContext* valueEntry(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ValueBlockContext* valueBlock();

  class  ValueEntryContext : public antlr4::ParserRuleContext {
  public:
    ValueEntryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    ExprContext *expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ValueEntryContext* valueEntry();

  class  UpdateStmtContext : public antlr4::ParserRuleContext {
  public:
    UpdateStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UPDATE();
    antlr4::tree::TerminalNode *STRING_LIT();
    antlr4::tree::TerminalNode *AS();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    QualifiedNameContext *qualifiedName();
    SetClauseContext *setClause();
    WhereClauseContext *whereClause();
    std::vector<LetBindingContext *> letBinding();
    LetBindingContext* letBinding(size_t i);
    ReturningClauseContext *returningClause();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UpdateStmtContext* updateStmt();

  class  SetClauseContext : public antlr4::ParserRuleContext {
  public:
    SetClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SET();
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<SetEntryContext *> setEntry();
    SetEntryContext* setEntry(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SetClauseContext* setClause();

  class  SetEntryContext : public antlr4::ParserRuleContext {
  public:
    SetEntryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    ExprContext *expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SetEntryContext* setEntry();

  class  DeleteStmtContext : public antlr4::ParserRuleContext {
  public:
    DeleteStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DELETE();
    antlr4::tree::TerminalNode *FROM();
    antlr4::tree::TerminalNode *STRING_LIT();
    antlr4::tree::TerminalNode *AS();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    QualifiedNameContext *qualifiedName();
    WhereClauseContext *whereClause();
    ReturningClauseContext *returningClause();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeleteStmtContext* deleteStmt();

  class  TruncateStmtContext : public antlr4::ParserRuleContext {
  public:
    TruncateStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TRUNCATE();
    antlr4::tree::TerminalNode *STRING_LIT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TruncateStmtContext* truncateStmt();

  class  UpsertStmtContext : public antlr4::ParserRuleContext {
  public:
    UpsertStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UPSERT();
    antlr4::tree::TerminalNode *INTO();
    antlr4::tree::TerminalNode *STRING_LIT();
    antlr4::tree::TerminalNode *AS();
    QualifiedNameContext *qualifiedName();
    std::vector<antlr4::tree::TerminalNode *> CONFLICT();
    antlr4::tree::TerminalNode* CONFLICT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ON();
    antlr4::tree::TerminalNode* ON(size_t i);
    antlr4::tree::TerminalNode *IDENTIFIER();
    ValueBlockContext *valueBlock();
    antlr4::tree::TerminalNode *SET();
    SetClauseContext *setClause();
    ReturningClauseContext *returningClause();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UpsertStmtContext* upsertStmt();

  class  ReturningClauseContext : public antlr4::ParserRuleContext {
  public:
    ReturningClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RETURNING();
    ProjectionBlockContext *projectionBlock();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReturningClauseContext* returningClause();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExprContext() = default;
    void copyFrom(ExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  NotExprContext : public ExprContext {
  public:
    NotExprContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *NOT();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnaryMinusExprContext : public ExprContext {
  public:
    UnaryMinusExprContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *MINUS();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PrimaryExprContext : public ExprContext {
  public:
    PrimaryExprContext(ExprContext *ctx);

    PrimaryContext *primary();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OrExprContext : public ExprContext {
  public:
    OrExprContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *OR();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ComparisonExprContext : public ExprContext {
  public:
    ComparisonExprContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NEQ();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *LEQ();
    antlr4::tree::TerminalNode *GEQ();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DistanceExprContext : public ExprContext {
  public:
    DistanceExprContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *DISTANCE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AdditiveExprContext : public ExprContext {
  public:
    AdditiveExprContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ContainsExprContext : public ExprContext {
  public:
    ContainsExprContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *CONTAINS();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MultiplicativeExprContext : public ExprContext {
  public:
    MultiplicativeExprContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *SLASH();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AndExprContext : public ExprContext {
  public:
    AndExprContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *AND();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExprContext* expr();
  ExprContext* expr(int precedence);
  class  PrimaryContext : public antlr4::ParserRuleContext {
  public:
    PrimaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PrimaryContext() = default;
    void copyFrom(PrimaryContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ParenPrimaryContext : public PrimaryContext {
  public:
    ParenPrimaryContext(PrimaryContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralPrimaryContext : public PrimaryContext {
  public:
    LiteralPrimaryContext(PrimaryContext *ctx);

    LiteralContext *literal();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FunctionCallPrimaryContext : public PrimaryContext {
  public:
    FunctionCallPrimaryContext(PrimaryContext *ctx);

    FunctionCallContext *functionCall();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AggregateCallPrimaryContext : public PrimaryContext {
  public:
    AggregateCallPrimaryContext(PrimaryContext *ctx);

    AggregateCallContext *aggregateCall();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NamePrimaryContext : public PrimaryContext {
  public:
    NamePrimaryContext(PrimaryContext *ctx);

    QualifiedNameContext *qualifiedName();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  PrimaryContext* primary();

  class  FunctionCallContext : public antlr4::ParserRuleContext {
  public:
    FunctionCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ArgListContext *argList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionCallContext* functionCall();

  class  ArgListContext : public antlr4::ParserRuleContext {
  public:
    ArgListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgListContext* argList();

  class  AggregateCallContext : public antlr4::ParserRuleContext {
  public:
    AggregateCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AggregateCallContext() = default;
    void copyFrom(AggregateCallContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  AggregateFnCallContext : public AggregateCallContext {
  public:
    AggregateFnCallContext(AggregateCallContext *ctx);

    AggregateFnContext *aggregateFn();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CountStarCallContext : public AggregateCallContext {
  public:
    CountStarCallContext(AggregateCallContext *ctx);

    AggregateFnContext *aggregateFn();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AggregateCallContext* aggregateCall();

  class  AggregateFnContext : public antlr4::ParserRuleContext {
  public:
    AggregateFnContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AggregateFnContext* aggregateFn();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER_LIT();
    antlr4::tree::TerminalNode *DECIMAL_LIT();
    antlr4::tree::TerminalNode *STRING_LIT();
    antlr4::tree::TerminalNode *SINGLE_STRING_LIT();
    antlr4::tree::TerminalNode *TRUE();
    antlr4::tree::TerminalNode *FALSE();
    antlr4::tree::TerminalNode *NULL_();
    ArrayLiteralContext *arrayLiteral();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralContext* literal();

  class  ArrayLiteralContext : public antlr4::ParserRuleContext {
  public:
    ArrayLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *RBRACKET();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayLiteralContext* arrayLiteral();

  class  ExprListContext : public antlr4::ParserRuleContext {
  public:
    ExprListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprListContext* exprList();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

