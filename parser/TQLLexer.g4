// TQLLexer.g4
// Lexer for Tensor Query Language (.tql)
//
// Token ordering is significant in ANTLR4: for equal-length matches the first
// rule wins. Multi-character operators (VEC_DIST, EQ, NEQ, LTE, GTE) must
// appear before their single-character prefixes (LT, GT). All keyword tokens
// must appear before IDENTIFIER so they are never consumed as user identifiers.

lexer grammar TQLLexer;

// ── Query pipeline keywords ──────────────────────────────────────────────────
FROM         : 'from';
JOIN         : 'join';
LEFT         : 'left';
WHERE        : 'where';
GROUP        : 'group';
BY           : 'by';
LET          : 'let';
HAVING       : 'having';
SELECT       : 'select';
ORDER        : 'order';
ASC          : 'asc';
DESC         : 'desc';
LIMIT        : 'limit';
AS           : 'as';
ON           : 'on';

// ── Mutation keywords ────────────────────────────────────────────────────────
INSERT       : 'insert';
INTO         : 'into';
UPDATE       : 'update';
SET          : 'set';
DELETE       : 'delete';
RETURNING    : 'returning';
UPSERT       : 'upsert';
CONFLICT     : 'conflict';
VALUES       : 'values';

// ── DDL keywords ─────────────────────────────────────────────────────────────
CREATE       : 'create';
TABLE        : 'table';
ROLE         : 'role';
GRANT        : 'grant';
TO           : 'to';
ALLOW        : 'allow';
DENY         : 'deny';
READ         : 'read';
WRITE        : 'write';
REVOKE       : 'revoke';
API_KEY      : 'api_key';
FOR          : 'for';
EXPIRES      : 'expires';
IN           : 'in';
TRUNCATE     : 'truncate';

// ── Package / type definition keywords ───────────────────────────────────────
IMPORT       : 'import';
PACKAGE      : 'package';
TYPE         : 'type';

// ── Scalar type keywords ─────────────────────────────────────────────────────
INT32        : 'int32';
INT64        : 'int64';
FLOAT32      : 'float32';
FLOAT64      : 'float64';
DECIMAL_KW   : 'decimal';
BOOL_KW      : 'bool';
TEXT_KW      : 'text';
UUID_KW      : 'uuid';
TIMESTAMP_KW : 'timestamp';
JSON_KW      : 'json';
ARRAY_KW     : 'array';
VECTOR_KW    : 'vector';
MAP_KW       : 'map';

// ── Boolean and null literals ─────────────────────────────────────────────────
NULL         : 'null';
TRUE         : 'true';
FALSE        : 'false';

// ── Keyword operators ─────────────────────────────────────────────────────────
AND          : 'and';
OR           : 'or';
NOT          : 'not';

// ── Built-in function names ───────────────────────────────────────────────────
// Reserved as keywords so they are never tokenised as IDENTIFIER. Users cannot
// name variables gen_uuid, now, match, embed, prompt, count, sum, avg, min, max.
GEN_UUID     : 'gen_uuid';
NOW          : 'now';
MATCH_FN     : 'match';
EMBED        : 'embed';
PROMPT       : 'prompt';
COUNT        : 'count';
SUM          : 'sum';
AVG          : 'avg';
MIN_FN       : 'min';
MAX_FN       : 'max';

// ── Compiler-provided special identifier ─────────────────────────────────────
// Must precede IDENTIFIER so '_mutation' is never tokenised as a user identifier.
MUTATION_FIELD : '_mutation';

// ── Multi-character operators (longest-match must precede single-char prefix) ─
VEC_DIST     : '<->';   // vector distance — valid ONLY in order by (enforced by parser)
EQ           : '==';
NEQ          : '!=';
LTE          : '<=';
GTE          : '>=';

// ── Assignment operator ───────────────────────────────────────────────────────
// Used exclusively in let clauses. Defined after EQ ('==') so that '=='
// is never tokenised as ASSIGN + ASSIGN.
ASSIGN       : '=';

// ── Single-character operators ────────────────────────────────────────────────
LT           : '<';    // also used for array<T> and json<T> angle brackets
GT           : '>';
STAR         : '*';    // multiplication, count(*), and grant wildcard operation
SLASH        : '/';
PLUS         : '+';
MINUS        : '-';

// ── Punctuation ───────────────────────────────────────────────────────────────
LPAREN       : '(';
RPAREN       : ')';
LBRACE       : '{';
RBRACE       : '}';
LBRACKET     : '[';
RBRACKET     : ']';
COMMA        : ',';
COLON        : ':';
DOT          : '.';
QUESTION     : '?';   // nullable type suffix: text?

// ── Duration literal ──────────────────────────────────────────────────────────
// Must precede INTEGER_LIT — otherwise '90d' tokenises as INTEGER_LIT + IDENTIFIER.
// Currently only 'd' (days) is supported; the rule is defined as a pattern so
// future units (h, w) can be added here without touching the parser.
DURATION_LIT : [0-9]+ 'd';

// ── Numeric literals ──────────────────────────────────────────────────────────
// FLOAT_LIT must precede INTEGER_LIT to prevent '3.14' tokenising as '3' + '.' + '14'.
FLOAT_LIT    : [0-9]+ '.' [0-9]+;
INTEGER_LIT  : [0-9]+;

// ── String literals ───────────────────────────────────────────────────────────
// Double-quoted: used for logical paths, text values, and API key identifiers.
// Supports backslash escapes inside the string body.
STRING_LIT        : '"' (~["\\\r\n] | '\\' .)* '"';

// Single-quoted: used exclusively for inline json<> values.
// e.g.  let cfg: json = '{"debug": true}'
SINGLE_STRING_LIT : '\'' (~['\\\r\n] | '\\' .)* '\'';

// ── Identifier ────────────────────────────────────────────────────────────────
// Must follow all keyword rules. Any name that matches a keyword token is
// tokenised as that keyword, never as IDENTIFIER.
IDENTIFIER   : [a-zA-Z_][a-zA-Z0-9_]*;

// ── Whitespace and comments ───────────────────────────────────────────────────
// Block comments (/* */) are not valid TQL syntax — only line comments.
LINE_COMMENT : '//' ~[\r\n]* -> skip;
WS           : [ \t\r\n]+    -> skip;