// ============================================================
//  DBLexer.g4
//  Tensor Query Language — Lexer Grammar
//
//  Responsibility boundary:
//    The lexer is purely responsible for tokenizing the raw
//    character stream into a flat token sequence. It does NOT
//    know whether an identifier names a valid path, type, or
//    field. That is the engine's job during semantic analysis.
//
//    Notable decisions:
//      - Keywords are case-sensitive and all lowercase.
//      - Path strings ("store/products") are plain STRING_LIT;
//        the engine resolves and validates the path.
//      - DURATION_LIT handles "90d", "365d" etc. as a single
//        token so the parser never has to stitch INTEGER + ID.
//      - STAR is reused across multiply, count(*), and IAM
//        wildcard — context is resolved by the parser rules.
//      - The <-> distance operator is a single three-character
//        token to avoid ambiguity with < and >.
// ============================================================

lexer grammar DBLexer;


// ── Pipeline keywords ────────────────────────────────────────

IMPORT      : 'import';
FROM        : 'from';
AS          : 'as';
WHERE       : 'where';
LET         : 'let';
SELECT      : 'select';
ORDER       : 'order';
BY          : 'by';
LIMIT       : 'limit';
GROUP       : 'group';
HAVING      : 'having';
JOIN        : 'join';
LEFT        : 'left';
ON          : 'on';
ASC         : 'asc';
DESC        : 'desc';
CONTAINS    : 'contains';


// ── Mutation keywords ────────────────────────────────────────

INSERT      : 'insert';
INTO        : 'into';
UPDATE      : 'update';
SET         : 'set';
DELETE      : 'delete';
UPSERT      : 'upsert';
CONFLICT    : 'conflict';
RETURNING   : 'returning';
TRUNCATE    : 'truncate';


// ── Schema & IAM keywords ────────────────────────────────────

CREATE      : 'create';
TABLE       : 'table';
PACKAGE     : 'package';
TYPE        : 'type';
ROLE        : 'role';
GRANT       : 'grant';
TO          : 'to';
ALLOW       : 'allow';
DENY        : 'deny';
READ        : 'read';
WRITE       : 'write';
API_KEY     : 'api_key';
FOR         : 'for';
EXPIRES     : 'expires';
IN          : 'in';


// ── Primitive type keywords ──────────────────────────────────
//    These are keywords, not identifiers, so the lexer must
//    emit them as distinct token types. The parser uses them
//    in typeRef rules only; the engine validates usage context.

K_INT32     : 'int32';
K_INT64     : 'int64';
K_FLOAT32   : 'float32';
K_FLOAT64   : 'float64';
K_DECIMAL   : 'decimal';
K_BOOL      : 'bool';
K_TEXT      : 'text';
K_UUID      : 'uuid';
K_TIMESTAMP : 'timestamp';
K_JSON      : 'json';
K_ARRAY     : 'array';
K_VECTOR    : 'vector';
K_MAP       : 'map';


// ── Boolean & null literals ──────────────────────────────────

TRUE        : 'true';
FALSE       : 'false';
NULL        : 'null';


// ── Logical operators ────────────────────────────────────────

AND         : 'and';
OR          : 'or';
NOT         : 'not';


// ── Comparison operators ─────────────────────────────────────
//    <-> must be matched BEFORE < and > are considered so the
//    lexer does not emit LT, MINUS, GT for the distance op.

DISTANCE    : '<->';
EQ          : '==';
NEQ         : '!=';
LEQ         : '<=';
GEQ         : '>=';
LT          : '<';
GT          : '>';


// ── Arithmetic operators ─────────────────────────────────────

PLUS        : '+';
MINUS       : '-';
STAR        : '*';   // multiply / count(*) / IAM wildcard
SLASH       : '/';


// ── Assignment & misc punctuation ────────────────────────────

ASSIGN      : '=';
DOT         : '.';
COMMA       : ',';
COLON       : ':';
QUESTION    : '?';   // nullable type suffix: text?


// ── Delimiters ───────────────────────────────────────────────

LPAREN      : '(';
RPAREN      : ')';
LBRACE      : '{';
RBRACE      : '}';
LBRACKET    : '[';
RBRACKET    : ']';


// ── Literals ─────────────────────────────────────────────────

//  Integer literal — used in type params (vector(1536)),
//  decimal params (decimal(10,2)), and general expressions.
INTEGER_LIT
    : [0-9]+
    ;

//  Decimal literal — matched before INTEGER_LIT would consume
//  leading digits. Covers prices, coordinates, thresholds.
DECIMAL_LIT
    : [0-9]+ '.' [0-9]+
    ;

//  String literal — double-quoted UTF-8. Used for logical
//  paths ("store/products"), string values, and timestamps
//  expressed as ISO-8601 strings. Escape \" inside.
STRING_LIT
    : '"' ( '\\' . | ~["\\\r\n] )* '"'
    ;

//  Single-quoted string — used for embed() model hints and
//  some inline string values.
SINGLE_STRING_LIT
    : '\'' ( '\\' . | ~['\\\r\n] )* '\''
    ;

//  Duration literal — e.g. 90d, 365d, 24h, 60m, 30s.
//  Emitting this as one token keeps parser rules simple and
//  prevents the engine from having to reassemble two tokens.
DURATION_LIT
    : [0-9]+ ( 'd' | 'h' | 'm' | 's' )
    ;


// ── Identifiers ──────────────────────────────────────────────
//    Must come AFTER all keyword rules so keywords are not
//    misidentified as identifiers by the lexer.

IDENTIFIER
    : [a-zA-Z_] [a-zA-Z0-9_]*
    ;


// ── Whitespace & comments ────────────────────────────────────
//    Skipped entirely; the parser never sees them.

LINE_COMMENT
    : '//' ~[\r\n]* -> skip
    ;

BLOCK_COMMENT
    : '/*' .*? '*/' -> skip
    ;

WS
    : [ \t\r\n]+ -> skip
    ;