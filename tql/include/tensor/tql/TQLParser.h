
// Generated from /home/user/tensor-database/parser/TQLParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  TQLParser : public antlr4::Parser {
public:
  enum {
    FROM = 1, JOIN = 2, LEFT = 3, WHERE = 4, GROUP = 5, BY = 6, LET = 7, 
    HAVING = 8, SELECT = 9, ORDER = 10, ASC = 11, DESC = 12, LIMIT = 13, 
    AS = 14, ON = 15, INSERT = 16, INTO = 17, UPDATE = 18, SET = 19, DELETE = 20, 
    RETURNING = 21, UPSERT = 22, CONFLICT = 23, VALUES = 24, CREATE = 25, 
    TABLE = 26, ROLE = 27, GRANT = 28, TO = 29, ALLOW = 30, DENY = 31, READ = 32, 
    WRITE = 33, REVOKE = 34, API_KEY = 35, FOR = 36, EXPIRES = 37, IN = 38, 
    TRUNCATE = 39, IMPORT = 40, PACKAGE = 41, TYPE = 42, INT32 = 43, INT64 = 44, 
    FLOAT32 = 45, FLOAT64 = 46, DECIMAL_KW = 47, BOOL_KW = 48, TEXT_KW = 49, 
    UUID_KW = 50, TIMESTAMP_KW = 51, JSON_KW = 52, ARRAY_KW = 53, VECTOR_KW = 54, 
    MAP_KW = 55, NULL_ = 56, TRUE = 57, FALSE = 58, AND = 59, OR = 60, NOT = 61, 
    GEN_UUID = 62, NOW = 63, MATCH_FN = 64, EMBED = 65, PROMPT = 66, COUNT = 67, 
    SUM = 68, AVG = 69, MIN_FN = 70, MAX_FN = 71, MUTATION_FIELD = 72, VEC_DIST = 73, 
    EQ = 74, NEQ = 75, LTE = 76, GTE = 77, ASSIGN = 78, LT = 79, GT = 80, 
    STAR = 81, SLASH = 82, PLUS = 83, MINUS = 84, LPAREN = 85, RPAREN = 86, 
    LBRACE = 87, RBRACE = 88, LBRACKET = 89, RBRACKET = 90, COMMA = 91, 
    COLON = 92, DOT = 93, QUESTION = 94, DURATION_LIT = 95, FLOAT_LIT = 96, 
    INTEGER_LIT = 97, STRING_LIT = 98, SINGLE_STRING_LIT = 99, IDENTIFIER = 100, 
    LINE_COMMENT = 101, WS = 102
  };

  enum {
    RuleFile = 0, RulePackageDecl = 1, RuleTypeDecl = 2, RuleFieldDecl = 3, 
    RuleImportDecl = 4, RuleStatement = 5, RuleTypeExpr = 6, RuleArrayElementType = 7, 
    RuleScalarType = 8, RuleJsonTypeParam = 9, RuleQualifiedTypeName = 10, 
    RulePathBinding = 11, RuleVarBinding = 12, RuleQueryStatement = 13, 
    RuleAggregationBlock = 14, RuleFromClause = 15, RuleJoinClause = 16, 
    RuleWhereClause = 17, RuleGroupByClause = 18, RuleHavingClause = 19, 
    RuleLetClause = 20, RuleSelectClause = 21, RuleSelectField = 22, RuleSelectValue = 23, 
    RuleOrderByClause = 24, RuleOrderByItem = 25, RuleLimitClause = 26, 
    RuleInsertStatement = 27, RuleInsertBody = 28, RuleInsertRows = 29, 
    RuleRowBlock = 30, RuleRowField = 31, RuleInsertFromBody = 32, RuleUpdateStatement = 33, 
    RuleSetClause = 34, RuleSetField = 35, RuleDeleteStatement = 36, RuleUpsertStatement = 37, 
    RuleReturningClause = 38, RuleReturningField = 39, RuleCreateTableStatement = 40, 
    RuleCreateRoleStatement = 41, RuleGrantStatement = 42, RuleGrantRule = 43, 
    RuleOperationList = 44, RuleOperation = 45, RuleCreateApiKeyStatement = 46, 
    RuleRevokeApiKeyStatement = 47, RuleTruncateStatement = 48, RuleFieldRef = 49, 
    RuleQualifiedName = 50, RuleExpr = 51, RuleFunctionCall = 52, RuleLiteral = 53, 
    RuleArrayLiteral = 54
  };

  explicit TQLParser(antlr4::TokenStream *input);

  TQLParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~TQLParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class FileContext;
  class PackageDeclContext;
  class TypeDeclContext;
  class FieldDeclContext;
  class ImportDeclContext;
  class StatementContext;
  class TypeExprContext;
  class ArrayElementTypeContext;
  class ScalarTypeContext;
  class JsonTypeParamContext;
  class QualifiedTypeNameContext;
  class PathBindingContext;
  class VarBindingContext;
  class QueryStatementContext;
  class AggregationBlockContext;
  class FromClauseContext;
  class JoinClauseContext;
  class WhereClauseContext;
  class GroupByClauseContext;
  class HavingClauseContext;
  class LetClauseContext;
  class SelectClauseContext;
  class SelectFieldContext;
  class SelectValueContext;
  class OrderByClauseContext;
  class OrderByItemContext;
  class LimitClauseContext;
  class InsertStatementContext;
  class InsertBodyContext;
  class InsertRowsContext;
  class RowBlockContext;
  class RowFieldContext;
  class InsertFromBodyContext;
  class UpdateStatementContext;
  class SetClauseContext;
  class SetFieldContext;
  class DeleteStatementContext;
  class UpsertStatementContext;
  class ReturningClauseContext;
  class ReturningFieldContext;
  class CreateTableStatementContext;
  class CreateRoleStatementContext;
  class GrantStatementContext;
  class GrantRuleContext;
  class OperationListContext;
  class OperationContext;
  class CreateApiKeyStatementContext;
  class RevokeApiKeyStatementContext;
  class TruncateStatementContext;
  class FieldRefContext;
  class QualifiedNameContext;
  class ExprContext;
  class FunctionCallContext;
  class LiteralContext;
  class ArrayLiteralContext; 

  class  FileContext : public antlr4::ParserRuleContext {
  public:
    FileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    FileContext() = default;
    void copyFrom(FileContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ExecutableFileContext : public FileContext {
  public:
    ExecutableFileContext(FileContext *ctx);

    antlr4::tree::TerminalNode *EOF();
    std::vector<ImportDeclContext *> importDecl();
    ImportDeclContext* importDecl(size_t i);
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PackageFileContext : public FileContext {
  public:
    PackageFileContext(FileContext *ctx);

    PackageDeclContext *packageDecl();
    antlr4::tree::TerminalNode *EOF();
    std::vector<TypeDeclContext *> typeDecl();
    TypeDeclContext* typeDecl(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  FileContext* file();

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
    TypeExprContext *typeExpr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FieldDeclContext* fieldDecl();

  class  ImportDeclContext : public antlr4::ParserRuleContext {
  public:
    ImportDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    antlr4::tree::TerminalNode *STRING_LIT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportDeclContext* importDecl();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    QueryStatementContext *queryStatement();
    InsertStatementContext *insertStatement();
    UpdateStatementContext *updateStatement();
    DeleteStatementContext *deleteStatement();
    UpsertStatementContext *upsertStatement();
    CreateTableStatementContext *createTableStatement();
    CreateRoleStatementContext *createRoleStatement();
    GrantStatementContext *grantStatement();
    CreateApiKeyStatementContext *createApiKeyStatement();
    RevokeApiKeyStatementContext *revokeApiKeyStatement();
    TruncateStatementContext *truncateStatement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  TypeExprContext : public antlr4::ParserRuleContext {
  public:
    TypeExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TypeExprContext() = default;
    void copyFrom(TypeExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ArrayTypeExprContext : public TypeExprContext {
  public:
    ArrayTypeExprContext(TypeExprContext *ctx);

    antlr4::tree::TerminalNode *ARRAY_KW();
    antlr4::tree::TerminalNode *LT();
    ArrayElementTypeContext *arrayElementType();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *QUESTION();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ScalarTypeExprContext : public TypeExprContext {
  public:
    ScalarTypeExprContext(TypeExprContext *ctx);

    ScalarTypeContext *scalarType();
    antlr4::tree::TerminalNode *QUESTION();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UserDefinedTypeExprContext : public TypeExprContext {
  public:
    UserDefinedTypeExprContext(TypeExprContext *ctx);

    QualifiedTypeNameContext *qualifiedTypeName();
    antlr4::tree::TerminalNode *QUESTION();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VectorTypeExprContext : public TypeExprContext {
  public:
    VectorTypeExprContext(TypeExprContext *ctx);

    antlr4::tree::TerminalNode *VECTOR_KW();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *INTEGER_LIT();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *QUESTION();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  JsonTypeExprContext : public TypeExprContext {
  public:
    JsonTypeExprContext(TypeExprContext *ctx);

    antlr4::tree::TerminalNode *JSON_KW();
    antlr4::tree::TerminalNode *LT();
    JsonTypeParamContext *jsonTypeParam();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *QUESTION();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TypeExprContext* typeExpr();

  class  ArrayElementTypeContext : public antlr4::ParserRuleContext {
  public:
    ArrayElementTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT32();
    antlr4::tree::TerminalNode *INT64();
    antlr4::tree::TerminalNode *FLOAT32();
    antlr4::tree::TerminalNode *FLOAT64();
    antlr4::tree::TerminalNode *DECIMAL_KW();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<antlr4::tree::TerminalNode *> INTEGER_LIT();
    antlr4::tree::TerminalNode* INTEGER_LIT(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *BOOL_KW();
    antlr4::tree::TerminalNode *TEXT_KW();
    antlr4::tree::TerminalNode *UUID_KW();
    antlr4::tree::TerminalNode *TIMESTAMP_KW();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayElementTypeContext* arrayElementType();

  class  ScalarTypeContext : public antlr4::ParserRuleContext {
  public:
    ScalarTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT32();
    antlr4::tree::TerminalNode *INT64();
    antlr4::tree::TerminalNode *FLOAT32();
    antlr4::tree::TerminalNode *FLOAT64();
    antlr4::tree::TerminalNode *DECIMAL_KW();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<antlr4::tree::TerminalNode *> INTEGER_LIT();
    antlr4::tree::TerminalNode* INTEGER_LIT(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *BOOL_KW();
    antlr4::tree::TerminalNode *TEXT_KW();
    antlr4::tree::TerminalNode *UUID_KW();
    antlr4::tree::TerminalNode *TIMESTAMP_KW();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ScalarTypeContext* scalarType();

  class  JsonTypeParamContext : public antlr4::ParserRuleContext {
  public:
    JsonTypeParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ScalarTypeContext *scalarType();
    antlr4::tree::TerminalNode *MAP_KW();
    antlr4::tree::TerminalNode *LBRACKET();
    std::vector<TypeExprContext *> typeExpr();
    TypeExprContext* typeExpr(size_t i);
    antlr4::tree::TerminalNode *RBRACKET();
    antlr4::tree::TerminalNode *ARRAY_KW();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *GT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  JsonTypeParamContext* jsonTypeParam();

  class  QualifiedTypeNameContext : public antlr4::ParserRuleContext {
  public:
    QualifiedTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    antlr4::tree::TerminalNode *DOT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QualifiedTypeNameContext* qualifiedTypeName();

  class  PathBindingContext : public antlr4::ParserRuleContext {
  public:
    PathBindingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LIT();
    antlr4::tree::TerminalNode *AS();
    VarBindingContext *varBinding();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PathBindingContext* pathBinding();

  class  VarBindingContext : public antlr4::ParserRuleContext {
  public:
    VarBindingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    QualifiedTypeNameContext *qualifiedTypeName();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarBindingContext* varBinding();

  class  QueryStatementContext : public antlr4::ParserRuleContext {
  public:
    QueryStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FromClauseContext *fromClause();
    SelectClauseContext *selectClause();
    std::vector<LetClauseContext *> letClause();
    LetClauseContext* letClause(size_t i);
    std::vector<JoinClauseContext *> joinClause();
    JoinClauseContext* joinClause(size_t i);
    WhereClauseContext *whereClause();
    AggregationBlockContext *aggregationBlock();
    OrderByClauseContext *orderByClause();
    LimitClauseContext *limitClause();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QueryStatementContext* queryStatement();

  class  AggregationBlockContext : public antlr4::ParserRuleContext {
  public:
    AggregationBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GroupByClauseContext *groupByClause();
    std::vector<LetClauseContext *> letClause();
    LetClauseContext* letClause(size_t i);
    HavingClauseContext *havingClause();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AggregationBlockContext* aggregationBlock();

  class  FromClauseContext : public antlr4::ParserRuleContext {
  public:
    FromClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FROM();
    PathBindingContext *pathBinding();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FromClauseContext* fromClause();

  class  JoinClauseContext : public antlr4::ParserRuleContext {
  public:
    JoinClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    JoinClauseContext() = default;
    void copyFrom(JoinClauseContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  InnerJoinContext : public JoinClauseContext {
  public:
    InnerJoinContext(JoinClauseContext *ctx);

    antlr4::tree::TerminalNode *JOIN();
    PathBindingContext *pathBinding();
    antlr4::tree::TerminalNode *ON();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LeftOuterJoinContext : public JoinClauseContext {
  public:
    LeftOuterJoinContext(JoinClauseContext *ctx);

    antlr4::tree::TerminalNode *LEFT();
    antlr4::tree::TerminalNode *JOIN();
    PathBindingContext *pathBinding();
    antlr4::tree::TerminalNode *ON();
    ExprContext *expr();

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
    std::vector<FieldRefContext *> fieldRef();
    FieldRefContext* fieldRef(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


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

  class  LetClauseContext : public antlr4::ParserRuleContext {
  public:
    LetClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LET();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    TypeExprContext *typeExpr();
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LetClauseContext* letClause();

  class  SelectClauseContext : public antlr4::ParserRuleContext {
  public:
    SelectClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SELECT();
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<SelectFieldContext *> selectField();
    SelectFieldContext* selectField(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectClauseContext* selectClause();

  class  SelectFieldContext : public antlr4::ParserRuleContext {
  public:
    SelectFieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    SelectFieldContext() = default;
    void copyFrom(SelectFieldContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  NamedSelectFieldContext : public SelectFieldContext {
  public:
    NamedSelectFieldContext(SelectFieldContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    SelectValueContext *selectValue();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BareSelectFieldContext : public SelectFieldContext {
  public:
    BareSelectFieldContext(SelectFieldContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  SelectFieldContext* selectField();

  class  SelectValueContext : public antlr4::ParserRuleContext {
  public:
    SelectValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<SelectFieldContext *> selectField();
    SelectFieldContext* selectField(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectValueContext* selectValue();

  class  OrderByClauseContext : public antlr4::ParserRuleContext {
  public:
    OrderByClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ORDER();
    antlr4::tree::TerminalNode *BY();
    std::vector<OrderByItemContext *> orderByItem();
    OrderByItemContext* orderByItem(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OrderByClauseContext* orderByClause();

  class  OrderByItemContext : public antlr4::ParserRuleContext {
  public:
    OrderByItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    OrderByItemContext() = default;
    void copyFrom(OrderByItemContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ScalarOrderByItemContext : public OrderByItemContext {
  public:
    ScalarOrderByItemContext(OrderByItemContext *ctx);

    ExprContext *expr();
    antlr4::tree::TerminalNode *ASC();
    antlr4::tree::TerminalNode *DESC();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VectorOrderByItemContext : public OrderByItemContext {
  public:
    VectorOrderByItemContext(OrderByItemContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *VEC_DIST();
    antlr4::tree::TerminalNode *ASC();
    antlr4::tree::TerminalNode *DESC();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  OrderByItemContext* orderByItem();

  class  LimitClauseContext : public antlr4::ParserRuleContext {
  public:
    LimitClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LIMIT();
    antlr4::tree::TerminalNode *INTEGER_LIT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LimitClauseContext* limitClause();

  class  InsertStatementContext : public antlr4::ParserRuleContext {
  public:
    InsertStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INSERT();
    antlr4::tree::TerminalNode *INTO();
    PathBindingContext *pathBinding();
    InsertBodyContext *insertBody();
    ReturningClauseContext *returningClause();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InsertStatementContext* insertStatement();

  class  InsertBodyContext : public antlr4::ParserRuleContext {
  public:
    InsertBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    InsertBodyContext() = default;
    void copyFrom(InsertBodyContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  InsertLiteralBodyContext : public InsertBodyContext {
  public:
    InsertLiteralBodyContext(InsertBodyContext *ctx);

    InsertRowsContext *insertRows();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InsertFromBodyAltContext : public InsertBodyContext {
  public:
    InsertFromBodyAltContext(InsertBodyContext *ctx);

    InsertFromBodyContext *insertFromBody();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  InsertBodyContext* insertBody();

  class  InsertRowsContext : public antlr4::ParserRuleContext {
  public:
    InsertRowsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    InsertRowsContext() = default;
    void copyFrom(InsertRowsContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  SingleRowInsertContext : public InsertRowsContext {
  public:
    SingleRowInsertContext(InsertRowsContext *ctx);

    antlr4::tree::TerminalNode *LBRACE();
    std::vector<RowFieldContext *> rowField();
    RowFieldContext* rowField(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MultiRowInsertContext : public InsertRowsContext {
  public:
    MultiRowInsertContext(InsertRowsContext *ctx);

    antlr4::tree::TerminalNode *LBRACE();
    std::vector<RowBlockContext *> rowBlock();
    RowBlockContext* rowBlock(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  InsertRowsContext* insertRows();

  class  RowBlockContext : public antlr4::ParserRuleContext {
  public:
    RowBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<RowFieldContext *> rowField();
    RowFieldContext* rowField(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RowBlockContext* rowBlock();

  class  RowFieldContext : public antlr4::ParserRuleContext {
  public:
    RowFieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    ExprContext *expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RowFieldContext* rowField();

  class  InsertFromBodyContext : public antlr4::ParserRuleContext {
  public:
    InsertFromBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FromClauseContext *fromClause();
    SelectClauseContext *selectClause();
    std::vector<JoinClauseContext *> joinClause();
    JoinClauseContext* joinClause(size_t i);
    WhereClauseContext *whereClause();
    std::vector<LetClauseContext *> letClause();
    LetClauseContext* letClause(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InsertFromBodyContext* insertFromBody();

  class  UpdateStatementContext : public antlr4::ParserRuleContext {
  public:
    UpdateStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UPDATE();
    PathBindingContext *pathBinding();
    SetClauseContext *setClause();
    WhereClauseContext *whereClause();
    std::vector<LetClauseContext *> letClause();
    LetClauseContext* letClause(size_t i);
    ReturningClauseContext *returningClause();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UpdateStatementContext* updateStatement();

  class  SetClauseContext : public antlr4::ParserRuleContext {
  public:
    SetClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SET();
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<SetFieldContext *> setField();
    SetFieldContext* setField(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SetClauseContext* setClause();

  class  SetFieldContext : public antlr4::ParserRuleContext {
  public:
    SetFieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    ExprContext *expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SetFieldContext* setField();

  class  DeleteStatementContext : public antlr4::ParserRuleContext {
  public:
    DeleteStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DELETE();
    antlr4::tree::TerminalNode *FROM();
    PathBindingContext *pathBinding();
    WhereClauseContext *whereClause();
    ReturningClauseContext *returningClause();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeleteStatementContext* deleteStatement();

  class  UpsertStatementContext : public antlr4::ParserRuleContext {
  public:
    UpsertStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UPSERT();
    antlr4::tree::TerminalNode *INTO();
    PathBindingContext *pathBinding();
    std::vector<antlr4::tree::TerminalNode *> CONFLICT();
    antlr4::tree::TerminalNode* CONFLICT(size_t i);
    antlr4::tree::TerminalNode *ON();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *VALUES();
    RowBlockContext *rowBlock();
    antlr4::tree::TerminalNode *SET();
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<SetFieldContext *> setField();
    SetFieldContext* setField(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    ReturningClauseContext *returningClause();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UpsertStatementContext* upsertStatement();

  class  ReturningClauseContext : public antlr4::ParserRuleContext {
  public:
    ReturningClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RETURNING();
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<ReturningFieldContext *> returningField();
    ReturningFieldContext* returningField(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReturningClauseContext* returningClause();

  class  ReturningFieldContext : public antlr4::ParserRuleContext {
  public:
    ReturningFieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ReturningFieldContext() = default;
    void copyFrom(ReturningFieldContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  NamedReturningFieldContext : public ReturningFieldContext {
  public:
    NamedReturningFieldContext(ReturningFieldContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MutationReturningFieldContext : public ReturningFieldContext {
  public:
    MutationReturningFieldContext(ReturningFieldContext *ctx);

    antlr4::tree::TerminalNode *MUTATION_FIELD();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ReturningFieldContext* returningField();

  class  CreateTableStatementContext : public antlr4::ParserRuleContext {
  public:
    CreateTableStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CREATE();
    antlr4::tree::TerminalNode *TABLE();
    antlr4::tree::TerminalNode *STRING_LIT();
    antlr4::tree::TerminalNode *AS();
    QualifiedTypeNameContext *qualifiedTypeName();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreateTableStatementContext* createTableStatement();

  class  CreateRoleStatementContext : public antlr4::ParserRuleContext {
  public:
    CreateRoleStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CREATE();
    antlr4::tree::TerminalNode *ROLE();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreateRoleStatementContext* createRoleStatement();

  class  GrantStatementContext : public antlr4::ParserRuleContext {
  public:
    GrantStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GRANT();
    antlr4::tree::TerminalNode *TO();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<GrantRuleContext *> grantRule();
    GrantRuleContext* grantRule(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GrantStatementContext* grantStatement();

  class  GrantRuleContext : public antlr4::ParserRuleContext {
  public:
    GrantRuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OperationListContext *operationList();
    antlr4::tree::TerminalNode *ON();
    antlr4::tree::TerminalNode *STRING_LIT();
    antlr4::tree::TerminalNode *ALLOW();
    antlr4::tree::TerminalNode *DENY();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GrantRuleContext* grantRule();

  class  OperationListContext : public antlr4::ParserRuleContext {
  public:
    OperationListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<OperationContext *> operation();
    OperationContext* operation(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OperationListContext* operationList();

  class  OperationContext : public antlr4::ParserRuleContext {
  public:
    OperationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *READ();
    antlr4::tree::TerminalNode *WRITE();
    antlr4::tree::TerminalNode *STAR();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OperationContext* operation();

  class  CreateApiKeyStatementContext : public antlr4::ParserRuleContext {
  public:
    CreateApiKeyStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
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

  CreateApiKeyStatementContext* createApiKeyStatement();

  class  RevokeApiKeyStatementContext : public antlr4::ParserRuleContext {
  public:
    RevokeApiKeyStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REVOKE();
    antlr4::tree::TerminalNode *API_KEY();
    antlr4::tree::TerminalNode *STRING_LIT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RevokeApiKeyStatementContext* revokeApiKeyStatement();

  class  TruncateStatementContext : public antlr4::ParserRuleContext {
  public:
    TruncateStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TRUNCATE();
    antlr4::tree::TerminalNode *STRING_LIT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TruncateStatementContext* truncateStatement();

  class  FieldRefContext : public antlr4::ParserRuleContext {
  public:
    FieldRefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    QualifiedNameContext *qualifiedName();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FieldRefContext* fieldRef();

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

  class  AddSubExprContext : public ExprContext {
  public:
    AddSubExprContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralExprContext : public ExprContext {
  public:
    LiteralExprContext(ExprContext *ctx);

    LiteralContext *literal();

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
    antlr4::tree::TerminalNode *LTE();
    antlr4::tree::TerminalNode *GTE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnaryNegExprContext : public ExprContext {
  public:
    UnaryNegExprContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *MINUS();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FuncCallExprContext : public ExprContext {
  public:
    FuncCallExprContext(ExprContext *ctx);

    FunctionCallContext *functionCall();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArrayLiteralExprContext : public ExprContext {
  public:
    ArrayLiteralExprContext(ExprContext *ctx);

    ArrayLiteralContext *arrayLiteral();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MulDivExprContext : public ExprContext {
  public:
    MulDivExprContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *SLASH();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenExprContext : public ExprContext {
  public:
    ParenExprContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NameExprContext : public ExprContext {
  public:
    NameExprContext(ExprContext *ctx);

    QualifiedNameContext *qualifiedName();

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
  class  FunctionCallContext : public antlr4::ParserRuleContext {
  public:
    FunctionCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    FunctionCallContext() = default;
    void copyFrom(FunctionCallContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  NowCallContext : public FunctionCallContext {
  public:
    NowCallContext(FunctionCallContext *ctx);

    antlr4::tree::TerminalNode *NOW();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MatchCallContext : public FunctionCallContext {
  public:
    MatchCallContext(FunctionCallContext *ctx);

    antlr4::tree::TerminalNode *MATCH_FN();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *STRING_LIT();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MinCallContext : public FunctionCallContext {
  public:
    MinCallContext(FunctionCallContext *ctx);

    antlr4::tree::TerminalNode *MIN_FN();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AvgCallContext : public FunctionCallContext {
  public:
    AvgCallContext(FunctionCallContext *ctx);

    antlr4::tree::TerminalNode *AVG();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PromptCallContext : public FunctionCallContext {
  public:
    PromptCallContext(FunctionCallContext *ctx);

    antlr4::tree::TerminalNode *PROMPT();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *STRING_LIT();
    QualifiedNameContext *qualifiedName();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CountCallContext : public FunctionCallContext {
  public:
    CountCallContext(FunctionCallContext *ctx);

    antlr4::tree::TerminalNode *COUNT();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *STAR();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  GenUuidCallContext : public FunctionCallContext {
  public:
    GenUuidCallContext(FunctionCallContext *ctx);

    antlr4::tree::TerminalNode *GEN_UUID();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EmbedCallContext : public FunctionCallContext {
  public:
    EmbedCallContext(FunctionCallContext *ctx);

    antlr4::tree::TerminalNode *EMBED();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *STRING_LIT();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *COMMA();
    QualifiedNameContext *qualifiedName();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SumCallContext : public FunctionCallContext {
  public:
    SumCallContext(FunctionCallContext *ctx);

    antlr4::tree::TerminalNode *SUM();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MaxCallContext : public FunctionCallContext {
  public:
    MaxCallContext(FunctionCallContext *ctx);

    antlr4::tree::TerminalNode *MAX_FN();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  FunctionCallContext* functionCall();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LiteralContext() = default;
    void copyFrom(LiteralContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  StringLitContext : public LiteralContext {
  public:
    StringLitContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *STRING_LIT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TrueLitContext : public LiteralContext {
  public:
    TrueLitContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *TRUE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FloatLitContext : public LiteralContext {
  public:
    FloatLitContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *FLOAT_LIT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FalseLitContext : public LiteralContext {
  public:
    FalseLitContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *FALSE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IntLitContext : public LiteralContext {
  public:
    IntLitContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *INTEGER_LIT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NullLitContext : public LiteralContext {
  public:
    NullLitContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *NULL_();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  JsonValueLitContext : public LiteralContext {
  public:
    JsonValueLitContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *SINGLE_STRING_LIT();

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


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

