// ============================================================
//  DBParser.g4
//  Tensor Query Language — Parser Grammar
//
//  Responsibility boundary:
//    The parser is responsible for SYNTACTIC validity only:
//      - Are the tokens in a legal order?
//      - Are blocks balanced?
//      - Does operator precedence resolve unambiguously?
//
//    The parser does NOT enforce:
//      - Whether an import path resolves to a real file
//      - Whether a field name exists on the bound type
//      - Whether a bare field in select violates a group by
//      - Whether a select shape matches an insert target type
//      - Whether aggregate functions appear only after group by
//      - Whether order by / limit appear at the end
//      - Type compatibility between expression operands
//
//    All of the above are ENGINE concerns handled in the
//    semantic analysis and query planning passes that walk
//    the AST produced here.
//
//  Pipeline stage ordering:
//    The grammar encodes the LEGAL SHAPE of each pipeline
//    variant but intentionally does not enforce strict stage
//    ordering as a grammar constraint (e.g. it does not
//    prevent a second `where` after `select`). Stage ordering
//    is a semantic rule — the engine validates it with a
//    single linear scan of the AST after parsing, giving far
//    better error messages than a grammar rejection.
//
//  Naming conventions:
//    - Rules ending in Stmt    → top-level statement
//    - Rules ending in Clause  → optional pipeline stage
//    - Rules ending in Block   → brace-delimited content
//    - Rules ending in Ref     → a reference to a named thing
// ============================================================

parser grammar DBParser;

options { tokenVocab = DBLexer; }


// ── Top-level entry point ────────────────────────────────────

script
    : statement* EOF
    ;

statement
    : importStmt
    | packageDecl
    | typeDecl
    | createTableStmt
    | createRoleStmt
    | grantStmt
    | createApiKeyStmt
    | queryStmt
    | insertStmt
    | updateStmt
    | deleteStmt
    | upsertStmt
    | truncateStmt
    ;


// ── Import ───────────────────────────────────────────────────

importStmt
    : IMPORT STRING_LIT
    ;


// ── Package & type declarations ──────────────────────────────
//    These live in shared .tql package files. The engine
//    registers each declared type into its schema catalog
//    at import-resolution time.

packageDecl
    : PACKAGE IDENTIFIER
    ;

typeDecl
    : TYPE IDENTIFIER LBRACE fieldDecl* RBRACE
    ;

fieldDecl
    : IDENTIFIER COLON typeRef
    ;


// ── Type references ──────────────────────────────────────────
//    Covers all built-in types, parameterized types, and the
//    nullable suffix. The engine validates that parameterized
//    forms receive the correct argument kinds (e.g. vector
//    must have an integer dimension, decimal needs p and s).
//
//    map[K]V is only valid as a type argument inside json<>.
//    That constraint is semantic, not syntactic.

typeRef
    : primitiveType QUESTION?                        # nullablePrimitive
    | K_DECIMAL LPAREN INTEGER_LIT COMMA INTEGER_LIT RPAREN QUESTION?
                                                     # decimalType
    | K_JSON ( LT typeArg GT )? QUESTION?            # jsonType
    | K_ARRAY LT typeRef GT QUESTION?                # arrayType
    | K_VECTOR LPAREN INTEGER_LIT RPAREN QUESTION?   # vectorType
    | K_MAP LBRACKET typeRef RBRACKET typeRef QUESTION?
                                                     # mapType
    ;

typeArg
    : typeRef
    ;

primitiveType
    : K_INT32
    | K_INT64
    | K_FLOAT32
    | K_FLOAT64
    | K_BOOL
    | K_TEXT
    | K_UUID
    | K_TIMESTAMP
    ;


// ── Qualified names ──────────────────────────────────────────
//    commerce.Product, o.customer_id, p.embedding, etc.
//    The engine resolves what each segment refers to.

qualifiedName
    : IDENTIFIER ( DOT IDENTIFIER )*
    ;


// ── Schema statements ────────────────────────────────────────

createTableStmt
    : CREATE TABLE STRING_LIT AS qualifiedName
    ;


// ── IAM statements ───────────────────────────────────────────

createRoleStmt
    : CREATE ROLE IDENTIFIER
    ;

//  API key generation. The engine validates that the role
//  name exists and that expires duration is positive.
createApiKeyStmt
    : CREATE API_KEY FOR IDENTIFIER EXPIRES IN DURATION_LIT
    ;

grantStmt
    : GRANT TO IDENTIFIER LBRACE iamRule* RBRACE
    ;

iamRule
    : ALLOW iamPermList ON STRING_LIT   # allowRule
    | DENY  iamPermOrStar ON STRING_LIT  # denyRule
    ;

iamPermList
    : iamPerm ( COMMA iamPerm )*
    ;

iamPerm
    : READ
    | WRITE
    ;

//  STAR used as wildcard permission in deny rules.
iamPermOrStar
    : iamPerm ( COMMA iamPerm )*
    | STAR
    ;


// ── Query pipeline ───────────────────────────────────────────
//    A standalone read pipeline. Stage ordering is syntactically
//    permissive here; the engine enforces legal ordering.

queryStmt
    : letBinding*
      fromClause
      joinClause*
      whereClause?
      groupByClause?
      letBinding*
      havingClause?
      selectClause
      orderByClause?
      limitClause?
    ;

fromClause
    : FROM STRING_LIT AS IDENTIFIER COLON qualifiedName
    ;

joinClause
    : LEFT? JOIN STRING_LIT AS IDENTIFIER COLON qualifiedName ON expr
    ;

whereClause
    : WHERE expr
    ;

groupByClause
    : GROUP BY exprList
    ;

havingClause
    : HAVING expr
    ;

//  select produces a named projection block. Engine validates
//  that every key-value entry is a valid field reference or
//  expression given the bound types in scope.
selectClause
    : SELECT projectionBlock
    ;

projectionBlock
    : LBRACE projectionEntry ( COMMA projectionEntry )* COMMA? RBRACE
    ;

projectionEntry
    : IDENTIFIER COLON expr         # labeledProjection
    | IDENTIFIER                    # shorthandProjection    // { total_spent }
    | IDENTIFIER COLON projectionBlock  # nestedProjection   // { inventory: { ... } }
    ;

orderByClause
    : ORDER BY orderItem ( COMMA orderItem )*
    ;

orderItem
    : expr ( ASC | DESC )?
    ;

limitClause
    : LIMIT INTEGER_LIT
    ;


// ── Let bindings ─────────────────────────────────────────────
//    Can appear before `from` (global, computed once) or
//    between `where` and `select` (row-level, per-row).
//    The grammar allows both positions; the engine assigns
//    evaluation scope based on position in the AST.

letBinding
    : LET IDENTIFIER ( COLON typeRef )? ASSIGN expr
    ;


// ── Mutation statements ──────────────────────────────────────

// ── INSERT ───────────────────────────────────────────────────

insertStmt
    : INSERT INTO STRING_LIT AS qualifiedName
      ( literalInsertBody | pipelineInsertBody )
      returningClause?
    ;

//  One or more literal value blocks. Engine validates each
//  block's shape against the target type contract.
literalInsertBody
    : valueBlock ( COMMA valueBlock )*
    ;

//  Insert from a query pipeline. The select shape must match
//  the target type — enforced by the engine, not the grammar.
pipelineInsertBody
    : fromClause
      joinClause*
      whereClause?
      letBinding*
      selectClause
    ;

valueBlock
    : LBRACE valueEntry ( COMMA valueEntry )* COMMA? RBRACE
    ;

valueEntry
    : IDENTIFIER COLON expr
    ;


// ── UPDATE ───────────────────────────────────────────────────

updateStmt
    : UPDATE STRING_LIT AS IDENTIFIER COLON qualifiedName
      whereClause?
      letBinding*
      setClause
      returningClause?
    ;

setClause
    : SET LBRACE setEntry ( COMMA setEntry )* COMMA? RBRACE
    ;

setEntry
    : IDENTIFIER COLON expr
    ;


// ── DELETE ───────────────────────────────────────────────────
//    The engine rejects a delete with no whereClause at
//    semantic analysis time. The grammar does not enforce
//    this because the error message from the engine ("unfiltered
//    delete is not permitted — use truncate") is far more
//    actionable than a parse error.

deleteStmt
    : DELETE FROM STRING_LIT AS IDENTIFIER COLON qualifiedName
      whereClause?
      returningClause?
    ;


// ── TRUNCATE ─────────────────────────────────────────────────

truncateStmt
    : TRUNCATE STRING_LIT
    ;


// ── UPSERT ───────────────────────────────────────────────────

upsertStmt
    : UPSERT INTO STRING_LIT AS qualifiedName
      CONFLICT ON IDENTIFIER
      valueBlock
      ON CONFLICT SET setClause
      returningClause?
    ;


// ── RETURNING ────────────────────────────────────────────────
//    Identical shape to selectClause. Uses the same
//    projectionBlock rule — the engine provides the same
//    field resolution and type inference for both contexts.
//    The _mutation synthetic field (upsert) is recognized
//    by the engine, not declared in the type package.

returningClause
    : RETURNING projectionBlock
    ;


// ── Expressions ──────────────────────────────────────────────
//    Precedence encoded via rule hierarchy (lowest → highest).
//    The engine handles type checking of every operation;
//    the grammar only ensures the token structure is legal.
//
//    Precedence ladder (lowest to highest):
//      1. or
//      2. and
//      3. not  (prefix unary)
//      4. contains  (text membership)
//      5. comparison  (==  !=  <  >  <=  >=)
//      6. distance  (<->)   semantic proximity
//      7. additive  (+ -)
//      8. multiplicative  (* /)
//      9. unary  (-)
//     10. primary  (literals, calls, field access, parens)

expr
    : expr OR  expr                         # orExpr
    | expr AND expr                         # andExpr
    | NOT expr                              # notExpr
    | expr CONTAINS expr                    # containsExpr
    | expr ( EQ | NEQ | LT | GT | LEQ | GEQ ) expr
                                            # comparisonExpr
    | expr DISTANCE expr                    # distanceExpr
    | expr ( PLUS  | MINUS ) expr           # additiveExpr
    | expr ( STAR  | SLASH ) expr           # multiplicativeExpr
    | MINUS expr                            # unaryMinusExpr
    | primary                               # primaryExpr
    ;

primary
    : literal                               # literalPrimary
    | functionCall                          # functionCallPrimary
    | aggregateCall                         # aggregateCallPrimary
    | qualifiedName                         # namePrimary
    | LPAREN expr RPAREN                    # parenPrimary
    ;


// ── Function calls ───────────────────────────────────────────
//    Covers built-ins (gen_uuid, now, embed) and any future
//    user-defined or engine-provided functions.
//    The engine validates arity, argument types, and that
//    embed() only appears in valid semantic-search contexts.

functionCall
    : IDENTIFIER LPAREN argList? RPAREN
    ;

argList
    : expr ( COMMA expr )*
    ;


// ── Aggregate function calls ─────────────────────────────────
//    count(*) requires special grammar treatment because STAR
//    is not a valid expression. All others share regular
//    single-argument form. The engine validates these appear
//    only in select/having/let after a group by, or in a
//    global aggregation (no group by, full stream collapse).

aggregateCall
    : aggregateFn LPAREN STAR RPAREN       # countStarCall
    | aggregateFn LPAREN expr RPAREN       # aggregateFnCall
    ;

aggregateFn
    : IDENTIFIER   // count, sum, avg, min, max — engine validates name
    ;


// ── Literals ─────────────────────────────────────────────────

literal
    : INTEGER_LIT
    | DECIMAL_LIT
    | STRING_LIT
    | SINGLE_STRING_LIT
    | TRUE
    | FALSE
    | NULL
    | arrayLiteral
    ;

arrayLiteral
    : LBRACKET ( expr ( COMMA expr )* COMMA? )? RBRACKET
    ;


// ── Helper rules ─────────────────────────────────────────────

exprList
    : expr ( COMMA expr )*
    ;