// TQLParser.g4
// Parser for Tensor Query Language (.tql)
//
// Design principle: the parser catches structural errors that can be determined
// from syntax alone. Errors that require symbol tables, type information, or
// runtime context are deferred to the semantic analysis phase in the engine.
// See the "Parser vs Engine" comment block at the bottom of this file for the
// full boundary specification.

parser grammar TQLParser;

options { tokenVocab = TQLLexer; }

// ════════════════════════════════════════════════════════════════════════════
// File entry point
// ════════════════════════════════════════════════════════════════════════════
// A .tql file is either:
//   (a) a package definition file  → packageDecl followed by typeDecl*
//   (b) an executable file         → importDecl* followed by statement+
//
// The two forms are mutually exclusive by grammar construction. A file that
// begins with the 'package' keyword is a package file; everything else is
// treated as an executable. The semantic phase validates that package files
// contain only type declarations and that executable files reference only
// imported packages.

file
    : packageDecl typeDecl* EOF      # packageFile
    | importDecl* statement+ EOF     # executableFile
    ;

// ════════════════════════════════════════════════════════════════════════════
// Package definition  (package files only)
// ════════════════════════════════════════════════════════════════════════════

packageDecl
    : PACKAGE IDENTIFIER
    ;

// A type block defines the shape of one logical entity. Field order determines
// wire layout in the .sst. Nullable fields are marked with '?' (QUESTION).
typeDecl
    : TYPE IDENTIFIER LBRACE fieldDecl+ RBRACE
    ;

fieldDecl
    : IDENTIFIER COLON typeExpr
    ;

// ════════════════════════════════════════════════════════════════════════════
// Imports  (executable files only)
// ════════════════════════════════════════════════════════════════════════════
// Parser rules enforced here:
//   - One import per line. Multi-package import syntax does not exist in the
//     grammar, so 'import "a", "b"' is a parse error.
//   - Imports precede all statements (enforced by rule ordering in 'file').
//   - The 'as' alias on import is not valid TQL syntax (absent from grammar).
//
// Deferred to the semantic phase:
//   - Whether the string path resolves to a real .tql package file.
//   - Whether the package file exports the types referenced in this file.

importDecl
    : IMPORT STRING_LIT
    ;

// ════════════════════════════════════════════════════════════════════════════
// Top-level statements
// ════════════════════════════════════════════════════════════════════════════

statement
    : queryStatement
    | insertStatement
    | updateStatement
    | deleteStatement
    | upsertStatement
    | createTableStatement
    | createRoleStatement
    | grantStatement
    | createApiKeyStatement
    | revokeApiKeyStatement
    | truncateStatement
    ;

// ════════════════════════════════════════════════════════════════════════════
// Type expressions
// ════════════════════════════════════════════════════════════════════════════
// The QUESTION suffix (nullable '?') is a syntactic annotation parsed here.
// Enforcement — that non-nullable fields always receive a value at write sites
// and that null is never assigned to a non-nullable binding — is a semantic
// responsibility of the engine.

typeExpr
    : scalarType QUESTION?                                               # scalarTypeExpr
    | VECTOR_KW LPAREN INTEGER_LIT RPAREN QUESTION?                      # vectorTypeExpr
    | ARRAY_KW LT arrayElementType GT QUESTION?                         # arrayTypeExpr
    | JSON_KW (LT jsonTypeParam GT)? QUESTION?                          # jsonTypeExpr
    | qualifiedTypeName QUESTION?                                        # userDefinedTypeExpr
    ;

// Array element types are restricted to scalars at parse time.
// 'array<array<T>>', 'array<json>', 'array<vector(n)>' are parse errors by
// the absence of those alternatives here — matching the language spec:
// "T cannot itself be an array, json, or vector type."
arrayElementType
    : INT32
    | INT64
    | FLOAT32
    | FLOAT64
    | DECIMAL_KW LPAREN INTEGER_LIT COMMA INTEGER_LIT RPAREN
    | BOOL_KW
    | TEXT_KW
    | UUID_KW
    | TIMESTAMP_KW
    ;

scalarType
    : INT32
    | INT64
    | FLOAT32
    | FLOAT64
    | DECIMAL_KW LPAREN INTEGER_LIT COMMA INTEGER_LIT RPAREN
    | BOOL_KW
    | TEXT_KW
    | UUID_KW
    | TIMESTAMP_KW
    ;

// Inner type parameter for json<T>. Supports:
//   json<int32>                 → scalar-constrained json
//   json<map[text]bool>         → typed map
//   json<map[text]array<int32>> → typed map of arrays
jsonTypeParam
    : scalarType
    | MAP_KW LBRACKET typeExpr RBRACKET typeExpr      // map[K]V (recursive)
    | ARRAY_KW LT typeExpr GT
    ;

// Package-qualified or simple type name: commerce.Product, identity.User, MyType
qualifiedTypeName
    : IDENTIFIER (DOT IDENTIFIER)?
    ;

// ════════════════════════════════════════════════════════════════════════════
// Path bindings
// ════════════════════════════════════════════════════════════════════════════
// Syntax:  "path" as [varName:] TypeName
//
// The variable alias is optional syntactically (some insert forms omit it).
// The semantic phase requires an alias whenever a 'returning' block is
// present — a variable is needed to qualify field references.
//
// Disambiguation: after AS, the parser looks one token ahead.
//   IDENTIFIER followed by COLON → varBinding with alias
//   Anything else                → type-only binding

pathBinding
    : STRING_LIT AS varBinding
    ;

varBinding
    : IDENTIFIER COLON qualifiedTypeName     // aliased:  p: commerce.Product
    | qualifiedTypeName                       // type-only: commerce.Product
    ;

// ════════════════════════════════════════════════════════════════════════════
// Query pipeline
// ════════════════════════════════════════════════════════════════════════════
// Full pipeline superset:
//   [let]* from [join]* [where] ([group by] [let]* [having])? [let]* select [order by] [limit]
//
// Stage ordering is enforced by rule structure — using a stage out of order is
// a parse error. The aggregationBlock groups 'group by', post-group 'let'
// bindings, and 'having' so they are always treated as a coherent unit.

queryStatement
    : letClause*
      fromClause
      joinClause*
      whereClause?
      aggregationBlock?
      letClause*
      selectClause
      orderByClause?
      limitClause?
    ;

// Groups the aggregation stages so their ordering relative to each other is
// enforced and they can only appear together, never interleaved with other stages.
aggregationBlock
    : groupByClause letClause* havingClause?
    ;

fromClause : FROM pathBinding ;

joinClause
    : JOIN      pathBinding ON expr    # innerJoin
    | LEFT JOIN pathBinding ON expr    # leftOuterJoin
    ;

whereClause  : WHERE expr ;
groupByClause : GROUP BY fieldRef (COMMA fieldRef)* ;
havingClause  : HAVING expr ;

letClause
    : LET IDENTIFIER COLON typeExpr ASSIGN expr
    ;
    // Parser enforces: type annotation is mandatory. 'let x = 5' is a parse
    // error. This matches the language spec: "The compiler rejects any let
    // declaration where the type is absent."

// ── Select ───────────────────────────────────────────────────────────────────
selectClause
    : SELECT LBRACE selectField (COMMA selectField)* COMMA? RBRACE
    ;

selectField
    : IDENTIFIER COLON selectValue    # namedSelectField
    | IDENTIFIER                      # bareSelectField
    // bareSelectField: shorthand for let-binding references in select blocks.
    // e.g. 'total_spent' instead of 'total_spent: total_spent'.
    // Validated by the semantic phase (must reference a let-bound name).
    ;

selectValue
    : expr
    | LBRACE selectField (COMMA selectField)* COMMA? RBRACE    // inline nested object
    ;

// ── Order by ─────────────────────────────────────────────────────────────────
// VEC_DIST (<->) appears ONLY in vectorOrderByItem. Excluding it from the
// general 'expr' grammar makes '<->' outside 'order by' a parse error, encoding
// the language spec rule at the grammar level rather than the semantic phase.
orderByClause
    : ORDER BY orderByItem (COMMA orderByItem)*
    ;

orderByItem
    : expr VEC_DIST expr (ASC | DESC)?    # vectorOrderByItem
    | expr              (ASC | DESC)?    # scalarOrderByItem
    ;

limitClause : LIMIT INTEGER_LIT ;

// ════════════════════════════════════════════════════════════════════════════
// Insert
// ════════════════════════════════════════════════════════════════════════════
// Two forms share the INSERT INTO pathBinding prefix:
//   Literal: path binding followed immediately by a row literal block
//   From:    path binding followed by a source query pipeline
//
// Disambiguation is LL(1): after the pathBinding, LBRACE → literal;
// FROM → from-source.

insertStatement
    : INSERT INTO pathBinding insertBody returningClause?
    ;

insertBody
    : insertRows         # insertLiteralBody
    | insertFromBody     # insertFromBodyAlt
    ;

// Single-row and multi-row are distinguished by LL(1) lookahead on the token
// immediately after the outer LBRACE:
//   IDENTIFIER → single row ('field: expr, ...')
//   LBRACE     → multi-row ('{ field: expr }, { field: expr }')
insertRows
    : LBRACE rowField  (COMMA rowField )*  COMMA? RBRACE    # singleRowInsert
    | LBRACE rowBlock  (COMMA rowBlock )*  COMMA? RBRACE    # multiRowInsert
    ;

rowBlock : LBRACE rowField (COMMA rowField)* COMMA? RBRACE ;
rowField : IDENTIFIER COLON expr ;

// The insert-from pipeline is a query without aggregation, order, or limit —
// it is purely a source of rows to write.
insertFromBody
    : fromClause
      joinClause*
      whereClause?
      letClause*
      selectClause
    ;

// ════════════════════════════════════════════════════════════════════════════
// Update
// ════════════════════════════════════════════════════════════════════════════
// The 'where' clause is optional syntactically — unfiltered updates are
// valid (they touch every row). Contrast with delete, where 'where' is required.

updateStatement
    : UPDATE pathBinding
      whereClause?
      letClause*
      setClause
      returningClause?
    ;

setClause
    : SET LBRACE setField (COMMA setField)* COMMA? RBRACE
    ;

setField : IDENTIFIER COLON expr ;

// ════════════════════════════════════════════════════════════════════════════
// Delete
// ════════════════════════════════════════════════════════════════════════════
// The 'where' clause is REQUIRED by grammar construction — its absence is a
// parse error, not a semantic error. This directly encodes the language spec:
// "A delete without a where clause will not compile."
// 'truncate' is the deliberate alternative for full-path wipes.

deleteStatement
    : DELETE FROM pathBinding whereClause returningClause?
    ;

// ════════════════════════════════════════════════════════════════════════════
// Upsert
// ════════════════════════════════════════════════════════════════════════════

upsertStatement
    : UPSERT INTO pathBinding
      CONFLICT ON IDENTIFIER
      VALUES rowBlock
      CONFLICT SET LBRACE setField (COMMA setField)* COMMA? RBRACE
      returningClause?
    ;

// ════════════════════════════════════════════════════════════════════════════
// Returning clause
// ════════════════════════════════════════════════════════════════════════════
// 'returning' uses a stricter field grammar than 'select':
//   - Only the 'key: expr' form is accepted (no bare shorthand names).
//   - The sole exception is MUTATION_FIELD (_mutation), which is compiler-
//     provided and has no variable owner.
//
// This distinction is enforced at parse time. Attempting to write:
//   returning { id, name }   ← parse error (bare names not in returningField)
// must become:
//   returning { id: p.id, name: p.name }

returningClause
    : RETURNING LBRACE returningField (COMMA returningField)* COMMA? RBRACE
    ;

returningField
    : IDENTIFIER COLON expr    # namedReturningField
    | MUTATION_FIELD           # mutationReturningField
    ;

// ════════════════════════════════════════════════════════════════════════════
// DDL — create table
// ════════════════════════════════════════════════════════════════════════════

createTableStatement
    : CREATE TABLE STRING_LIT AS qualifiedTypeName
    ;

// ════════════════════════════════════════════════════════════════════════════
// DDL — roles
// ════════════════════════════════════════════════════════════════════════════
// Role name uniqueness is a semantic constraint (requires a symbol table).
// The parser only validates structural correctness.

createRoleStatement
    : CREATE ROLE IDENTIFIER
    ;

// ════════════════════════════════════════════════════════════════════════════
// DDL — grants
// ════════════════════════════════════════════════════════════════════════════
// The 'deny always wins' evaluation rule is a runtime semantic concern.
// The parser records every allow/deny rule in order (top-to-bottom) as
// grantRule nodes; the IAM engine evaluates them at access-check time.

grantStatement
    : GRANT TO IDENTIFIER LBRACE grantRule+ RBRACE
    ;

grantRule
    : (ALLOW | DENY) operationList ON STRING_LIT
    ;

operationList
    : operation (COMMA operation)*
    ;

// STAR here means 'all operations' (the grant wildcard), not multiplication.
operation : READ | WRITE | STAR ;

// ════════════════════════════════════════════════════════════════════════════
// DDL — API keys
// ════════════════════════════════════════════════════════════════════════════

createApiKeyStatement
    : CREATE API_KEY FOR IDENTIFIER EXPIRES IN DURATION_LIT
    ;

revokeApiKeyStatement
    : REVOKE API_KEY STRING_LIT
    ;

// ════════════════════════════════════════════════════════════════════════════
// DDL — truncate
// ════════════════════════════════════════════════════════════════════════════

truncateStatement
    : TRUNCATE STRING_LIT
    ;

// ════════════════════════════════════════════════════════════════════════════
// Field references and qualified names
// ════════════════════════════════════════════════════════════════════════════

// Used in 'group by': always a dotted path like o.customer_id or p.id.
fieldRef : qualifiedName ;

// General dotted name: variable.field, tensor.SEARCH, package.Type, etc.
// Accepts one or more IDENTIFIER segments separated by DOT.
qualifiedName
    : IDENTIFIER (DOT IDENTIFIER)*
    ;

// ════════════════════════════════════════════════════════════════════════════
// Expressions
// ════════════════════════════════════════════════════════════════════════════
// VEC_DIST (<->) is intentionally excluded from this rule. It appears only in
// orderByItem above. Writing 'where p.x <-> embed("q") < 0.5' is therefore a
// parse error — the restriction from operators.md is enforced structurally.
//
// ANTLR4 implicit precedence for left-recursive alternatives:
// earlier alternative = tighter binding (higher precedence). This directly
// encodes the operator precedence table from operators.md (levels 1–9):
//
//   1  ()           parenExpr          (non-recursive)
//   2  - (unary)    unaryNegExpr       (non-recursive)
//   3  not          notExpr            (non-recursive)
//   4  * /          mulDivExpr         (left-recursive, level 1)
//   5  + -          addSubExpr         (left-recursive, level 2)
//   6  == != < > <= >=  comparisonExpr (left-recursive, level 3)
//   7  and          andExpr            (left-recursive, level 4)
//   8  or           orExpr             (left-recursive, level 5, lowest)

expr
    : LPAREN expr RPAREN                                          # parenExpr
    | MINUS expr                                                  # unaryNegExpr
    | NOT expr                                                    # notExpr
    | expr (STAR | SLASH) expr                                    # mulDivExpr
    | expr (PLUS | MINUS) expr                                    # addSubExpr
    | expr (EQ | NEQ | LT | GT | LTE | GTE) expr                 # comparisonExpr
    | expr AND expr                                               # andExpr
    | expr OR expr                                                # orExpr
    | functionCall                                                # funcCallExpr
    | qualifiedName                                               # nameExpr
    | literal                                                     # literalExpr
    | arrayLiteral                                                # arrayLiteralExpr
    ;

// ════════════════════════════════════════════════════════════════════════════
// Built-in function calls
// ════════════════════════════════════════════════════════════════════════════
// Each built-in has a fixed arity and argument type contract encoded in the
// grammar. Calling gen_uuid() with arguments, or omitting the mode constant
// from prompt(), is a parse error.
//
// Semantic phase responsibilities for function calls:
//   - match() field argument must be of type 'text'
//   - embed() dimension must match the vector field's declared dimension
//   - prompt() output type annotation must be an imported package type
//   - count/sum/avg/min/max require 'group by' to be present in the pipeline

functionCall
    : GEN_UUID LPAREN RPAREN                                                        # genUuidCall
    | NOW      LPAREN RPAREN                                                        # nowCall
    | MATCH_FN LPAREN expr COMMA STRING_LIT RPAREN                                  # matchCall
    | EMBED    LPAREN STRING_LIT (COMMA qualifiedName)? RPAREN                      # embedCall
    | PROMPT   LPAREN expr COMMA STRING_LIT COMMA qualifiedName RPAREN              # promptCall
    | COUNT    LPAREN (STAR | expr) RPAREN                                          # countCall
    | SUM      LPAREN expr RPAREN                                                   # sumCall
    | AVG      LPAREN expr RPAREN                                                   # avgCall
    | MIN_FN   LPAREN expr RPAREN                                                   # minCall
    | MAX_FN   LPAREN expr RPAREN                                                   # maxCall
    ;

// ════════════════════════════════════════════════════════════════════════════
// Literals
// ════════════════════════════════════════════════════════════════════════════

literal
    : STRING_LIT           # stringLit
    | SINGLE_STRING_LIT    # jsonValueLit    // json<> inline values only
    | FLOAT_LIT            # floatLit
    | INTEGER_LIT          # intLit
    | TRUE                 # trueLit
    | FALSE                # falseLit
    | NULL                 # nullLit
    ;

arrayLiteral
    : LBRACKET (expr (COMMA expr)* COMMA?)? RBRACKET
    ;

// ════════════════════════════════════════════════════════════════════════════
// PARSER VS ENGINE BOUNDARY
// ════════════════════════════════════════════════════════════════════════════
//
// WHAT THE PARSER CATCHES (syntactic / structural — no symbol table needed)
// ─────────────────────────────────────────────────────────────────────────
//  1. Pipeline stage ordering violations
//       from must precede join, join must precede where, etc.
//       'group by' without 'having' is fine; 'having' without 'group by' is a
//       parse error because aggregationBlock requires groupByClause first.
//
//  2. Mandatory 'where' on delete
//       deleteStatement requires whereClause — an unfiltered delete does not
//       parse. This is the "unfiltered delete is a compile-time error" rule.
//
//  3. VEC_DIST (<->) restricted to order by
//       '<->' is absent from the expr rule; it only appears in vectorOrderByItem.
//       Writing 'where x <-> embed("q") < 0.5' is a parse error.
//
//  4. Mandatory type annotation on let
//       letClause requires ': typeExpr' — 'let x = 5' does not parse.
//
//  5. Returning fields require 'key: expr' form
//       bareSelectField shorthand is absent from returningField. Bare names
//       other than _mutation are a parse error inside returning blocks.
//
//  6. Nested array types are illegal
//       arrayElementType lists only scalar types. 'array<array<int32>>',
//       'array<json>', 'array<vector(n)>' are parse errors.
//
//  7. One import per line; no alias on import
//       The grammar has no multi-import or 'import ... as' production.
//
//  8. Block comments are illegal
//       The lexer only defines '//' line comments. '/* */' produces a lex error.
//
//  9. Operator precedence
//       Encoded in the expr rule ordering. The AST reflects the correct
//       binding without any post-parse rewriting.
//
// 10. Function call arity
//       gen_uuid(), now() take no arguments; prompt() requires exactly three.
//       Wrong arity is a parse error.
//
// 11. Duration literal format
//       DURATION_LIT matches /[0-9]+d/ only. '30h' is a lex error (no 'h' unit).
//
// WHAT THE ENGINE CATCHES (semantic — requires symbol table, types, or runtime)
// ─────────────────────────────────────────────────────────────────────────────
//  1. Package / type resolution
//       Does 'commerce.Product' exist? Is it exported by the imported package?
//       Does "store/products" name a path created by 'create table'?
//
//  2. Type compatibility
//       Comparing int32 with text, mixed-type arithmetic, assigning a decimal
//       to a bool field. The parser builds the AST; the engine type-checks it.
//
//  3. Vector dimensionality
//       Both sides of '<->' must be vector(n) with the same n.
//       embed() must produce a vector matching the field's declared dimension.
//
//  4. IAM / permission checks
//       Does the API key's role allow read/write on the requested path?
//       Applied at execution time after successful parsing and type checking.
//
//  5. match() field type constraint
//       match(field, "token") requires field to be type 'text'. The parser
//       accepts any expr as the first argument; the engine rejects non-text.
//
//  6. Aggregate context
//       count/sum/avg/min/max are syntactically valid anywhere in an expr, but
//       the engine rejects aggregate function calls outside a group-by pipeline.
//       Bare (non-aggregated) field references in select after group by are also
//       caught here — requires knowing which fields are in the grouping key.
//
//  7. prompt() output type
//       The let binding's declared type must be a package-imported type, not a
//       primitive. The engine validates this when resolving the let clause.
//
//  8. Role name uniqueness
//       'create role storefront' when storefront already exists is a semantic
//       error checked against the instance's role registry.
//
//  9. _mutation outside returning
//       The MUTATION_FIELD token is syntactically valid only inside
//       returningField (grammar), but the engine additionally enforces it
//       cannot be referenced in where, having, set, or any other stage.
//
// 10. Variable alias requirement in returning context
//       The grammar allows a type-only pathBinding (no alias). The engine
//       rejects this when a returning clause is present and needs a variable
//       to qualify field references.
//
// 11. Unfiltered update semantics
//       update without where is syntactically valid (touches all rows). The
//       engine may optionally warn; it does not reject.