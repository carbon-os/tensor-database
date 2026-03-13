
// Generated from /home/user/tensor-database/parser/TQLParser.g4 by ANTLR 4.13.2


#include "TQLParserVisitor.h"

#include "TQLParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct TQLParserStaticData final {
  TQLParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  TQLParserStaticData(const TQLParserStaticData&) = delete;
  TQLParserStaticData(TQLParserStaticData&&) = delete;
  TQLParserStaticData& operator=(const TQLParserStaticData&) = delete;
  TQLParserStaticData& operator=(TQLParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag tqlparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<TQLParserStaticData> tqlparserParserStaticData = nullptr;

void tqlparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (tqlparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(tqlparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<TQLParserStaticData>(
    std::vector<std::string>{
      "file", "packageDecl", "typeDecl", "fieldDecl", "importDecl", "statement", 
      "typeExpr", "arrayElementType", "scalarType", "jsonTypeParam", "qualifiedTypeName", 
      "pathBinding", "varBinding", "queryStatement", "aggregationBlock", 
      "fromClause", "joinClause", "whereClause", "groupByClause", "havingClause", 
      "letClause", "selectClause", "selectField", "selectValue", "orderByClause", 
      "orderByItem", "limitClause", "insertStatement", "insertBody", "insertRows", 
      "rowBlock", "rowField", "insertFromBody", "updateStatement", "setClause", 
      "setField", "deleteStatement", "upsertStatement", "returningClause", 
      "returningField", "createTableStatement", "createRoleStatement", "grantStatement", 
      "grantRule", "operationList", "operation", "createApiKeyStatement", 
      "revokeApiKeyStatement", "truncateStatement", "fieldRef", "qualifiedName", 
      "expr", "functionCall", "literal", "arrayLiteral"
    },
    std::vector<std::string>{
      "", "'from'", "'join'", "'left'", "'where'", "'group'", "'by'", "'let'", 
      "'having'", "'select'", "'order'", "'asc'", "'desc'", "'limit'", "'as'", 
      "'on'", "'insert'", "'into'", "'update'", "'set'", "'delete'", "'returning'", 
      "'upsert'", "'conflict'", "'values'", "'create'", "'table'", "'role'", 
      "'grant'", "'to'", "'allow'", "'deny'", "'read'", "'write'", "'revoke'", 
      "'api_key'", "'for'", "'expires'", "'in'", "'truncate'", "'import'", 
      "'package'", "'type'", "'int32'", "'int64'", "'float32'", "'float64'", 
      "'decimal'", "'bool'", "'text'", "'uuid'", "'timestamp'", "'json'", 
      "'array'", "'vector'", "'map'", "'null'", "'true'", "'false'", "'and'", 
      "'or'", "'not'", "'gen_uuid'", "'now'", "'match'", "'embed'", "'prompt'", 
      "'count'", "'sum'", "'avg'", "'min'", "'max'", "'_mutation'", "'<->'", 
      "'=='", "'!='", "'<='", "'>='", "'='", "'<'", "'>'", "'*'", "'/'", 
      "'+'", "'-'", "'('", "')'", "'{'", "'}'", "'['", "']'", "','", "':'", 
      "'.'", "'\\u003F'"
    },
    std::vector<std::string>{
      "", "FROM", "JOIN", "LEFT", "WHERE", "GROUP", "BY", "LET", "HAVING", 
      "SELECT", "ORDER", "ASC", "DESC", "LIMIT", "AS", "ON", "INSERT", "INTO", 
      "UPDATE", "SET", "DELETE", "RETURNING", "UPSERT", "CONFLICT", "VALUES", 
      "CREATE", "TABLE", "ROLE", "GRANT", "TO", "ALLOW", "DENY", "READ", 
      "WRITE", "REVOKE", "API_KEY", "FOR", "EXPIRES", "IN", "TRUNCATE", 
      "IMPORT", "PACKAGE", "TYPE", "INT32", "INT64", "FLOAT32", "FLOAT64", 
      "DECIMAL_KW", "BOOL_KW", "TEXT_KW", "UUID_KW", "TIMESTAMP_KW", "JSON_KW", 
      "ARRAY_KW", "VECTOR_KW", "MAP_KW", "NULL", "TRUE", "FALSE", "AND", 
      "OR", "NOT", "GEN_UUID", "NOW", "MATCH_FN", "EMBED", "PROMPT", "COUNT", 
      "SUM", "AVG", "MIN_FN", "MAX_FN", "MUTATION_FIELD", "VEC_DIST", "EQ", 
      "NEQ", "LTE", "GTE", "ASSIGN", "LT", "GT", "STAR", "SLASH", "PLUS", 
      "MINUS", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", 
      "COMMA", "COLON", "DOT", "QUESTION", "DURATION_LIT", "FLOAT_LIT", 
      "INTEGER_LIT", "STRING_LIT", "SINGLE_STRING_LIT", "IDENTIFIER", "LINE_COMMENT", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,102,752,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,1,0,1,0,5,0,113,
  	8,0,10,0,12,0,116,9,0,1,0,1,0,1,0,5,0,121,8,0,10,0,12,0,124,9,0,1,0,4,
  	0,127,8,0,11,0,12,0,128,1,0,1,0,3,0,133,8,0,1,1,1,1,1,1,1,2,1,2,1,2,1,
  	2,4,2,142,8,2,11,2,12,2,143,1,2,1,2,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,166,8,5,1,6,1,6,3,6,170,8,6,
  	1,6,1,6,1,6,1,6,1,6,3,6,177,8,6,1,6,1,6,1,6,1,6,1,6,3,6,184,8,6,1,6,1,
  	6,1,6,1,6,1,6,3,6,191,8,6,1,6,3,6,194,8,6,1,6,1,6,3,6,198,8,6,3,6,200,
  	8,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,216,8,
  	7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,232,8,8,
  	1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,246,8,9,1,10,1,10,
  	1,10,3,10,251,8,10,1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,3,12,261,8,
  	12,1,13,5,13,264,8,13,10,13,12,13,267,9,13,1,13,1,13,5,13,271,8,13,10,
  	13,12,13,274,9,13,1,13,3,13,277,8,13,1,13,3,13,280,8,13,1,13,5,13,283,
  	8,13,10,13,12,13,286,9,13,1,13,1,13,3,13,290,8,13,1,13,3,13,293,8,13,
  	1,14,1,14,5,14,297,8,14,10,14,12,14,300,9,14,1,14,3,14,303,8,14,1,15,
  	1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,3,16,
  	319,8,16,1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,5,18,329,8,18,10,18,
  	12,18,332,9,18,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,21,
  	1,21,1,21,1,21,1,21,5,21,349,8,21,10,21,12,21,352,9,21,1,21,3,21,355,
  	8,21,1,21,1,21,1,22,1,22,1,22,1,22,3,22,363,8,22,1,23,1,23,1,23,1,23,
  	1,23,5,23,370,8,23,10,23,12,23,373,9,23,1,23,3,23,376,8,23,1,23,1,23,
  	3,23,380,8,23,1,24,1,24,1,24,1,24,1,24,5,24,387,8,24,10,24,12,24,390,
  	9,24,1,25,1,25,1,25,1,25,3,25,396,8,25,1,25,1,25,3,25,400,8,25,3,25,402,
  	8,25,1,26,1,26,1,26,1,27,1,27,1,27,1,27,1,27,3,27,412,8,27,1,28,1,28,
  	3,28,416,8,28,1,29,1,29,1,29,1,29,5,29,422,8,29,10,29,12,29,425,9,29,
  	1,29,3,29,428,8,29,1,29,1,29,1,29,1,29,1,29,1,29,5,29,436,8,29,10,29,
  	12,29,439,9,29,1,29,3,29,442,8,29,1,29,1,29,3,29,446,8,29,1,30,1,30,1,
  	30,1,30,5,30,452,8,30,10,30,12,30,455,9,30,1,30,3,30,458,8,30,1,30,1,
  	30,1,31,1,31,1,31,1,31,1,32,1,32,5,32,468,8,32,10,32,12,32,471,9,32,1,
  	32,3,32,474,8,32,1,32,5,32,477,8,32,10,32,12,32,480,9,32,1,32,1,32,1,
  	33,1,33,1,33,3,33,487,8,33,1,33,5,33,490,8,33,10,33,12,33,493,9,33,1,
  	33,1,33,3,33,497,8,33,1,34,1,34,1,34,1,34,1,34,5,34,504,8,34,10,34,12,
  	34,507,9,34,1,34,3,34,510,8,34,1,34,1,34,1,35,1,35,1,35,1,35,1,36,1,36,
  	1,36,1,36,1,36,3,36,523,8,36,1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,
  	1,37,1,37,1,37,1,37,1,37,1,37,5,37,539,8,37,10,37,12,37,542,9,37,1,37,
  	3,37,545,8,37,1,37,1,37,3,37,549,8,37,1,38,1,38,1,38,1,38,1,38,5,38,556,
  	8,38,10,38,12,38,559,9,38,1,38,3,38,562,8,38,1,38,1,38,1,39,1,39,1,39,
  	1,39,3,39,570,8,39,1,40,1,40,1,40,1,40,1,40,1,40,1,41,1,41,1,41,1,41,
  	1,42,1,42,1,42,1,42,1,42,4,42,587,8,42,11,42,12,42,588,1,42,1,42,1,43,
  	1,43,1,43,1,43,1,43,1,44,1,44,1,44,5,44,601,8,44,10,44,12,44,604,9,44,
  	1,45,1,45,1,46,1,46,1,46,1,46,1,46,1,46,1,46,1,46,1,47,1,47,1,47,1,47,
  	1,48,1,48,1,48,1,49,1,49,1,50,1,50,1,50,5,50,628,8,50,10,50,12,50,631,
  	9,50,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	3,51,646,8,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	1,51,1,51,1,51,1,51,5,51,663,8,51,10,51,12,51,666,9,51,1,52,1,52,1,52,
  	1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,
  	1,52,3,52,686,8,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,
  	1,52,1,52,1,52,1,52,3,52,702,8,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,
  	1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,
  	3,52,725,8,52,1,53,1,53,1,53,1,53,1,53,1,53,1,53,3,53,734,8,53,1,54,1,
  	54,1,54,1,54,5,54,740,8,54,10,54,12,54,743,9,54,1,54,3,54,746,8,54,3,
  	54,748,8,54,1,54,1,54,1,54,0,1,102,55,0,2,4,6,8,10,12,14,16,18,20,22,
  	24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,
  	70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,0,6,
  	1,0,11,12,1,0,30,31,2,0,32,33,81,81,1,0,81,82,1,0,83,84,2,0,74,77,79,
  	80,820,0,132,1,0,0,0,2,134,1,0,0,0,4,137,1,0,0,0,6,147,1,0,0,0,8,151,
  	1,0,0,0,10,165,1,0,0,0,12,199,1,0,0,0,14,215,1,0,0,0,16,231,1,0,0,0,18,
  	245,1,0,0,0,20,247,1,0,0,0,22,252,1,0,0,0,24,260,1,0,0,0,26,265,1,0,0,
  	0,28,294,1,0,0,0,30,304,1,0,0,0,32,318,1,0,0,0,34,320,1,0,0,0,36,323,
  	1,0,0,0,38,333,1,0,0,0,40,336,1,0,0,0,42,343,1,0,0,0,44,362,1,0,0,0,46,
  	379,1,0,0,0,48,381,1,0,0,0,50,401,1,0,0,0,52,403,1,0,0,0,54,406,1,0,0,
  	0,56,415,1,0,0,0,58,445,1,0,0,0,60,447,1,0,0,0,62,461,1,0,0,0,64,465,
  	1,0,0,0,66,483,1,0,0,0,68,498,1,0,0,0,70,513,1,0,0,0,72,517,1,0,0,0,74,
  	524,1,0,0,0,76,550,1,0,0,0,78,569,1,0,0,0,80,571,1,0,0,0,82,577,1,0,0,
  	0,84,581,1,0,0,0,86,592,1,0,0,0,88,597,1,0,0,0,90,605,1,0,0,0,92,607,
  	1,0,0,0,94,615,1,0,0,0,96,619,1,0,0,0,98,622,1,0,0,0,100,624,1,0,0,0,
  	102,645,1,0,0,0,104,724,1,0,0,0,106,733,1,0,0,0,108,735,1,0,0,0,110,114,
  	3,2,1,0,111,113,3,4,2,0,112,111,1,0,0,0,113,116,1,0,0,0,114,112,1,0,0,
  	0,114,115,1,0,0,0,115,117,1,0,0,0,116,114,1,0,0,0,117,118,5,0,0,1,118,
  	133,1,0,0,0,119,121,3,8,4,0,120,119,1,0,0,0,121,124,1,0,0,0,122,120,1,
  	0,0,0,122,123,1,0,0,0,123,126,1,0,0,0,124,122,1,0,0,0,125,127,3,10,5,
  	0,126,125,1,0,0,0,127,128,1,0,0,0,128,126,1,0,0,0,128,129,1,0,0,0,129,
  	130,1,0,0,0,130,131,5,0,0,1,131,133,1,0,0,0,132,110,1,0,0,0,132,122,1,
  	0,0,0,133,1,1,0,0,0,134,135,5,41,0,0,135,136,5,100,0,0,136,3,1,0,0,0,
  	137,138,5,42,0,0,138,139,5,100,0,0,139,141,5,87,0,0,140,142,3,6,3,0,141,
  	140,1,0,0,0,142,143,1,0,0,0,143,141,1,0,0,0,143,144,1,0,0,0,144,145,1,
  	0,0,0,145,146,5,88,0,0,146,5,1,0,0,0,147,148,5,100,0,0,148,149,5,92,0,
  	0,149,150,3,12,6,0,150,7,1,0,0,0,151,152,5,40,0,0,152,153,5,98,0,0,153,
  	9,1,0,0,0,154,166,3,26,13,0,155,166,3,54,27,0,156,166,3,66,33,0,157,166,
  	3,72,36,0,158,166,3,74,37,0,159,166,3,80,40,0,160,166,3,82,41,0,161,166,
  	3,84,42,0,162,166,3,92,46,0,163,166,3,94,47,0,164,166,3,96,48,0,165,154,
  	1,0,0,0,165,155,1,0,0,0,165,156,1,0,0,0,165,157,1,0,0,0,165,158,1,0,0,
  	0,165,159,1,0,0,0,165,160,1,0,0,0,165,161,1,0,0,0,165,162,1,0,0,0,165,
  	163,1,0,0,0,165,164,1,0,0,0,166,11,1,0,0,0,167,169,3,16,8,0,168,170,5,
  	94,0,0,169,168,1,0,0,0,169,170,1,0,0,0,170,200,1,0,0,0,171,172,5,54,0,
  	0,172,173,5,85,0,0,173,174,5,97,0,0,174,176,5,86,0,0,175,177,5,94,0,0,
  	176,175,1,0,0,0,176,177,1,0,0,0,177,200,1,0,0,0,178,179,5,53,0,0,179,
  	180,5,79,0,0,180,181,3,14,7,0,181,183,5,80,0,0,182,184,5,94,0,0,183,182,
  	1,0,0,0,183,184,1,0,0,0,184,200,1,0,0,0,185,190,5,52,0,0,186,187,5,79,
  	0,0,187,188,3,18,9,0,188,189,5,80,0,0,189,191,1,0,0,0,190,186,1,0,0,0,
  	190,191,1,0,0,0,191,193,1,0,0,0,192,194,5,94,0,0,193,192,1,0,0,0,193,
  	194,1,0,0,0,194,200,1,0,0,0,195,197,3,20,10,0,196,198,5,94,0,0,197,196,
  	1,0,0,0,197,198,1,0,0,0,198,200,1,0,0,0,199,167,1,0,0,0,199,171,1,0,0,
  	0,199,178,1,0,0,0,199,185,1,0,0,0,199,195,1,0,0,0,200,13,1,0,0,0,201,
  	216,5,43,0,0,202,216,5,44,0,0,203,216,5,45,0,0,204,216,5,46,0,0,205,206,
  	5,47,0,0,206,207,5,85,0,0,207,208,5,97,0,0,208,209,5,91,0,0,209,210,5,
  	97,0,0,210,216,5,86,0,0,211,216,5,48,0,0,212,216,5,49,0,0,213,216,5,50,
  	0,0,214,216,5,51,0,0,215,201,1,0,0,0,215,202,1,0,0,0,215,203,1,0,0,0,
  	215,204,1,0,0,0,215,205,1,0,0,0,215,211,1,0,0,0,215,212,1,0,0,0,215,213,
  	1,0,0,0,215,214,1,0,0,0,216,15,1,0,0,0,217,232,5,43,0,0,218,232,5,44,
  	0,0,219,232,5,45,0,0,220,232,5,46,0,0,221,222,5,47,0,0,222,223,5,85,0,
  	0,223,224,5,97,0,0,224,225,5,91,0,0,225,226,5,97,0,0,226,232,5,86,0,0,
  	227,232,5,48,0,0,228,232,5,49,0,0,229,232,5,50,0,0,230,232,5,51,0,0,231,
  	217,1,0,0,0,231,218,1,0,0,0,231,219,1,0,0,0,231,220,1,0,0,0,231,221,1,
  	0,0,0,231,227,1,0,0,0,231,228,1,0,0,0,231,229,1,0,0,0,231,230,1,0,0,0,
  	232,17,1,0,0,0,233,246,3,16,8,0,234,235,5,55,0,0,235,236,5,89,0,0,236,
  	237,3,12,6,0,237,238,5,90,0,0,238,239,3,12,6,0,239,246,1,0,0,0,240,241,
  	5,53,0,0,241,242,5,79,0,0,242,243,3,12,6,0,243,244,5,80,0,0,244,246,1,
  	0,0,0,245,233,1,0,0,0,245,234,1,0,0,0,245,240,1,0,0,0,246,19,1,0,0,0,
  	247,250,5,100,0,0,248,249,5,93,0,0,249,251,5,100,0,0,250,248,1,0,0,0,
  	250,251,1,0,0,0,251,21,1,0,0,0,252,253,5,98,0,0,253,254,5,14,0,0,254,
  	255,3,24,12,0,255,23,1,0,0,0,256,257,5,100,0,0,257,258,5,92,0,0,258,261,
  	3,20,10,0,259,261,3,20,10,0,260,256,1,0,0,0,260,259,1,0,0,0,261,25,1,
  	0,0,0,262,264,3,40,20,0,263,262,1,0,0,0,264,267,1,0,0,0,265,263,1,0,0,
  	0,265,266,1,0,0,0,266,268,1,0,0,0,267,265,1,0,0,0,268,272,3,30,15,0,269,
  	271,3,32,16,0,270,269,1,0,0,0,271,274,1,0,0,0,272,270,1,0,0,0,272,273,
  	1,0,0,0,273,276,1,0,0,0,274,272,1,0,0,0,275,277,3,34,17,0,276,275,1,0,
  	0,0,276,277,1,0,0,0,277,279,1,0,0,0,278,280,3,28,14,0,279,278,1,0,0,0,
  	279,280,1,0,0,0,280,284,1,0,0,0,281,283,3,40,20,0,282,281,1,0,0,0,283,
  	286,1,0,0,0,284,282,1,0,0,0,284,285,1,0,0,0,285,287,1,0,0,0,286,284,1,
  	0,0,0,287,289,3,42,21,0,288,290,3,48,24,0,289,288,1,0,0,0,289,290,1,0,
  	0,0,290,292,1,0,0,0,291,293,3,52,26,0,292,291,1,0,0,0,292,293,1,0,0,0,
  	293,27,1,0,0,0,294,298,3,36,18,0,295,297,3,40,20,0,296,295,1,0,0,0,297,
  	300,1,0,0,0,298,296,1,0,0,0,298,299,1,0,0,0,299,302,1,0,0,0,300,298,1,
  	0,0,0,301,303,3,38,19,0,302,301,1,0,0,0,302,303,1,0,0,0,303,29,1,0,0,
  	0,304,305,5,1,0,0,305,306,3,22,11,0,306,31,1,0,0,0,307,308,5,2,0,0,308,
  	309,3,22,11,0,309,310,5,15,0,0,310,311,3,102,51,0,311,319,1,0,0,0,312,
  	313,5,3,0,0,313,314,5,2,0,0,314,315,3,22,11,0,315,316,5,15,0,0,316,317,
  	3,102,51,0,317,319,1,0,0,0,318,307,1,0,0,0,318,312,1,0,0,0,319,33,1,0,
  	0,0,320,321,5,4,0,0,321,322,3,102,51,0,322,35,1,0,0,0,323,324,5,5,0,0,
  	324,325,5,6,0,0,325,330,3,98,49,0,326,327,5,91,0,0,327,329,3,98,49,0,
  	328,326,1,0,0,0,329,332,1,0,0,0,330,328,1,0,0,0,330,331,1,0,0,0,331,37,
  	1,0,0,0,332,330,1,0,0,0,333,334,5,8,0,0,334,335,3,102,51,0,335,39,1,0,
  	0,0,336,337,5,7,0,0,337,338,5,100,0,0,338,339,5,92,0,0,339,340,3,12,6,
  	0,340,341,5,78,0,0,341,342,3,102,51,0,342,41,1,0,0,0,343,344,5,9,0,0,
  	344,345,5,87,0,0,345,350,3,44,22,0,346,347,5,91,0,0,347,349,3,44,22,0,
  	348,346,1,0,0,0,349,352,1,0,0,0,350,348,1,0,0,0,350,351,1,0,0,0,351,354,
  	1,0,0,0,352,350,1,0,0,0,353,355,5,91,0,0,354,353,1,0,0,0,354,355,1,0,
  	0,0,355,356,1,0,0,0,356,357,5,88,0,0,357,43,1,0,0,0,358,359,5,100,0,0,
  	359,360,5,92,0,0,360,363,3,46,23,0,361,363,5,100,0,0,362,358,1,0,0,0,
  	362,361,1,0,0,0,363,45,1,0,0,0,364,380,3,102,51,0,365,366,5,87,0,0,366,
  	371,3,44,22,0,367,368,5,91,0,0,368,370,3,44,22,0,369,367,1,0,0,0,370,
  	373,1,0,0,0,371,369,1,0,0,0,371,372,1,0,0,0,372,375,1,0,0,0,373,371,1,
  	0,0,0,374,376,5,91,0,0,375,374,1,0,0,0,375,376,1,0,0,0,376,377,1,0,0,
  	0,377,378,5,88,0,0,378,380,1,0,0,0,379,364,1,0,0,0,379,365,1,0,0,0,380,
  	47,1,0,0,0,381,382,5,10,0,0,382,383,5,6,0,0,383,388,3,50,25,0,384,385,
  	5,91,0,0,385,387,3,50,25,0,386,384,1,0,0,0,387,390,1,0,0,0,388,386,1,
  	0,0,0,388,389,1,0,0,0,389,49,1,0,0,0,390,388,1,0,0,0,391,392,3,102,51,
  	0,392,393,5,73,0,0,393,395,3,102,51,0,394,396,7,0,0,0,395,394,1,0,0,0,
  	395,396,1,0,0,0,396,402,1,0,0,0,397,399,3,102,51,0,398,400,7,0,0,0,399,
  	398,1,0,0,0,399,400,1,0,0,0,400,402,1,0,0,0,401,391,1,0,0,0,401,397,1,
  	0,0,0,402,51,1,0,0,0,403,404,5,13,0,0,404,405,5,97,0,0,405,53,1,0,0,0,
  	406,407,5,16,0,0,407,408,5,17,0,0,408,409,3,22,11,0,409,411,3,56,28,0,
  	410,412,3,76,38,0,411,410,1,0,0,0,411,412,1,0,0,0,412,55,1,0,0,0,413,
  	416,3,58,29,0,414,416,3,64,32,0,415,413,1,0,0,0,415,414,1,0,0,0,416,57,
  	1,0,0,0,417,418,5,87,0,0,418,423,3,62,31,0,419,420,5,91,0,0,420,422,3,
  	62,31,0,421,419,1,0,0,0,422,425,1,0,0,0,423,421,1,0,0,0,423,424,1,0,0,
  	0,424,427,1,0,0,0,425,423,1,0,0,0,426,428,5,91,0,0,427,426,1,0,0,0,427,
  	428,1,0,0,0,428,429,1,0,0,0,429,430,5,88,0,0,430,446,1,0,0,0,431,432,
  	5,87,0,0,432,437,3,60,30,0,433,434,5,91,0,0,434,436,3,60,30,0,435,433,
  	1,0,0,0,436,439,1,0,0,0,437,435,1,0,0,0,437,438,1,0,0,0,438,441,1,0,0,
  	0,439,437,1,0,0,0,440,442,5,91,0,0,441,440,1,0,0,0,441,442,1,0,0,0,442,
  	443,1,0,0,0,443,444,5,88,0,0,444,446,1,0,0,0,445,417,1,0,0,0,445,431,
  	1,0,0,0,446,59,1,0,0,0,447,448,5,87,0,0,448,453,3,62,31,0,449,450,5,91,
  	0,0,450,452,3,62,31,0,451,449,1,0,0,0,452,455,1,0,0,0,453,451,1,0,0,0,
  	453,454,1,0,0,0,454,457,1,0,0,0,455,453,1,0,0,0,456,458,5,91,0,0,457,
  	456,1,0,0,0,457,458,1,0,0,0,458,459,1,0,0,0,459,460,5,88,0,0,460,61,1,
  	0,0,0,461,462,5,100,0,0,462,463,5,92,0,0,463,464,3,102,51,0,464,63,1,
  	0,0,0,465,469,3,30,15,0,466,468,3,32,16,0,467,466,1,0,0,0,468,471,1,0,
  	0,0,469,467,1,0,0,0,469,470,1,0,0,0,470,473,1,0,0,0,471,469,1,0,0,0,472,
  	474,3,34,17,0,473,472,1,0,0,0,473,474,1,0,0,0,474,478,1,0,0,0,475,477,
  	3,40,20,0,476,475,1,0,0,0,477,480,1,0,0,0,478,476,1,0,0,0,478,479,1,0,
  	0,0,479,481,1,0,0,0,480,478,1,0,0,0,481,482,3,42,21,0,482,65,1,0,0,0,
  	483,484,5,18,0,0,484,486,3,22,11,0,485,487,3,34,17,0,486,485,1,0,0,0,
  	486,487,1,0,0,0,487,491,1,0,0,0,488,490,3,40,20,0,489,488,1,0,0,0,490,
  	493,1,0,0,0,491,489,1,0,0,0,491,492,1,0,0,0,492,494,1,0,0,0,493,491,1,
  	0,0,0,494,496,3,68,34,0,495,497,3,76,38,0,496,495,1,0,0,0,496,497,1,0,
  	0,0,497,67,1,0,0,0,498,499,5,19,0,0,499,500,5,87,0,0,500,505,3,70,35,
  	0,501,502,5,91,0,0,502,504,3,70,35,0,503,501,1,0,0,0,504,507,1,0,0,0,
  	505,503,1,0,0,0,505,506,1,0,0,0,506,509,1,0,0,0,507,505,1,0,0,0,508,510,
  	5,91,0,0,509,508,1,0,0,0,509,510,1,0,0,0,510,511,1,0,0,0,511,512,5,88,
  	0,0,512,69,1,0,0,0,513,514,5,100,0,0,514,515,5,92,0,0,515,516,3,102,51,
  	0,516,71,1,0,0,0,517,518,5,20,0,0,518,519,5,1,0,0,519,520,3,22,11,0,520,
  	522,3,34,17,0,521,523,3,76,38,0,522,521,1,0,0,0,522,523,1,0,0,0,523,73,
  	1,0,0,0,524,525,5,22,0,0,525,526,5,17,0,0,526,527,3,22,11,0,527,528,5,
  	23,0,0,528,529,5,15,0,0,529,530,5,100,0,0,530,531,5,24,0,0,531,532,3,
  	60,30,0,532,533,5,23,0,0,533,534,5,19,0,0,534,535,5,87,0,0,535,540,3,
  	70,35,0,536,537,5,91,0,0,537,539,3,70,35,0,538,536,1,0,0,0,539,542,1,
  	0,0,0,540,538,1,0,0,0,540,541,1,0,0,0,541,544,1,0,0,0,542,540,1,0,0,0,
  	543,545,5,91,0,0,544,543,1,0,0,0,544,545,1,0,0,0,545,546,1,0,0,0,546,
  	548,5,88,0,0,547,549,3,76,38,0,548,547,1,0,0,0,548,549,1,0,0,0,549,75,
  	1,0,0,0,550,551,5,21,0,0,551,552,5,87,0,0,552,557,3,78,39,0,553,554,5,
  	91,0,0,554,556,3,78,39,0,555,553,1,0,0,0,556,559,1,0,0,0,557,555,1,0,
  	0,0,557,558,1,0,0,0,558,561,1,0,0,0,559,557,1,0,0,0,560,562,5,91,0,0,
  	561,560,1,0,0,0,561,562,1,0,0,0,562,563,1,0,0,0,563,564,5,88,0,0,564,
  	77,1,0,0,0,565,566,5,100,0,0,566,567,5,92,0,0,567,570,3,102,51,0,568,
  	570,5,72,0,0,569,565,1,0,0,0,569,568,1,0,0,0,570,79,1,0,0,0,571,572,5,
  	25,0,0,572,573,5,26,0,0,573,574,5,98,0,0,574,575,5,14,0,0,575,576,3,20,
  	10,0,576,81,1,0,0,0,577,578,5,25,0,0,578,579,5,27,0,0,579,580,5,100,0,
  	0,580,83,1,0,0,0,581,582,5,28,0,0,582,583,5,29,0,0,583,584,5,100,0,0,
  	584,586,5,87,0,0,585,587,3,86,43,0,586,585,1,0,0,0,587,588,1,0,0,0,588,
  	586,1,0,0,0,588,589,1,0,0,0,589,590,1,0,0,0,590,591,5,88,0,0,591,85,1,
  	0,0,0,592,593,7,1,0,0,593,594,3,88,44,0,594,595,5,15,0,0,595,596,5,98,
  	0,0,596,87,1,0,0,0,597,602,3,90,45,0,598,599,5,91,0,0,599,601,3,90,45,
  	0,600,598,1,0,0,0,601,604,1,0,0,0,602,600,1,0,0,0,602,603,1,0,0,0,603,
  	89,1,0,0,0,604,602,1,0,0,0,605,606,7,2,0,0,606,91,1,0,0,0,607,608,5,25,
  	0,0,608,609,5,35,0,0,609,610,5,36,0,0,610,611,5,100,0,0,611,612,5,37,
  	0,0,612,613,5,38,0,0,613,614,5,95,0,0,614,93,1,0,0,0,615,616,5,34,0,0,
  	616,617,5,35,0,0,617,618,5,98,0,0,618,95,1,0,0,0,619,620,5,39,0,0,620,
  	621,5,98,0,0,621,97,1,0,0,0,622,623,3,100,50,0,623,99,1,0,0,0,624,629,
  	5,100,0,0,625,626,5,93,0,0,626,628,5,100,0,0,627,625,1,0,0,0,628,631,
  	1,0,0,0,629,627,1,0,0,0,629,630,1,0,0,0,630,101,1,0,0,0,631,629,1,0,0,
  	0,632,633,6,51,-1,0,633,634,5,85,0,0,634,635,3,102,51,0,635,636,5,86,
  	0,0,636,646,1,0,0,0,637,638,5,84,0,0,638,646,3,102,51,11,639,640,5,61,
  	0,0,640,646,3,102,51,10,641,646,3,104,52,0,642,646,3,100,50,0,643,646,
  	3,106,53,0,644,646,3,108,54,0,645,632,1,0,0,0,645,637,1,0,0,0,645,639,
  	1,0,0,0,645,641,1,0,0,0,645,642,1,0,0,0,645,643,1,0,0,0,645,644,1,0,0,
  	0,646,664,1,0,0,0,647,648,10,9,0,0,648,649,7,3,0,0,649,663,3,102,51,10,
  	650,651,10,8,0,0,651,652,7,4,0,0,652,663,3,102,51,9,653,654,10,7,0,0,
  	654,655,7,5,0,0,655,663,3,102,51,8,656,657,10,6,0,0,657,658,5,59,0,0,
  	658,663,3,102,51,7,659,660,10,5,0,0,660,661,5,60,0,0,661,663,3,102,51,
  	6,662,647,1,0,0,0,662,650,1,0,0,0,662,653,1,0,0,0,662,656,1,0,0,0,662,
  	659,1,0,0,0,663,666,1,0,0,0,664,662,1,0,0,0,664,665,1,0,0,0,665,103,1,
  	0,0,0,666,664,1,0,0,0,667,668,5,62,0,0,668,669,5,85,0,0,669,725,5,86,
  	0,0,670,671,5,63,0,0,671,672,5,85,0,0,672,725,5,86,0,0,673,674,5,64,0,
  	0,674,675,5,85,0,0,675,676,3,102,51,0,676,677,5,91,0,0,677,678,5,98,0,
  	0,678,679,5,86,0,0,679,725,1,0,0,0,680,681,5,65,0,0,681,682,5,85,0,0,
  	682,685,5,98,0,0,683,684,5,91,0,0,684,686,3,100,50,0,685,683,1,0,0,0,
  	685,686,1,0,0,0,686,687,1,0,0,0,687,725,5,86,0,0,688,689,5,66,0,0,689,
  	690,5,85,0,0,690,691,3,102,51,0,691,692,5,91,0,0,692,693,5,98,0,0,693,
  	694,5,91,0,0,694,695,3,100,50,0,695,696,5,86,0,0,696,725,1,0,0,0,697,
  	698,5,67,0,0,698,701,5,85,0,0,699,702,5,81,0,0,700,702,3,102,51,0,701,
  	699,1,0,0,0,701,700,1,0,0,0,702,703,1,0,0,0,703,725,5,86,0,0,704,705,
  	5,68,0,0,705,706,5,85,0,0,706,707,3,102,51,0,707,708,5,86,0,0,708,725,
  	1,0,0,0,709,710,5,69,0,0,710,711,5,85,0,0,711,712,3,102,51,0,712,713,
  	5,86,0,0,713,725,1,0,0,0,714,715,5,70,0,0,715,716,5,85,0,0,716,717,3,
  	102,51,0,717,718,5,86,0,0,718,725,1,0,0,0,719,720,5,71,0,0,720,721,5,
  	85,0,0,721,722,3,102,51,0,722,723,5,86,0,0,723,725,1,0,0,0,724,667,1,
  	0,0,0,724,670,1,0,0,0,724,673,1,0,0,0,724,680,1,0,0,0,724,688,1,0,0,0,
  	724,697,1,0,0,0,724,704,1,0,0,0,724,709,1,0,0,0,724,714,1,0,0,0,724,719,
  	1,0,0,0,725,105,1,0,0,0,726,734,5,98,0,0,727,734,5,99,0,0,728,734,5,96,
  	0,0,729,734,5,97,0,0,730,734,5,57,0,0,731,734,5,58,0,0,732,734,5,56,0,
  	0,733,726,1,0,0,0,733,727,1,0,0,0,733,728,1,0,0,0,733,729,1,0,0,0,733,
  	730,1,0,0,0,733,731,1,0,0,0,733,732,1,0,0,0,734,107,1,0,0,0,735,747,5,
  	89,0,0,736,741,3,102,51,0,737,738,5,91,0,0,738,740,3,102,51,0,739,737,
  	1,0,0,0,740,743,1,0,0,0,741,739,1,0,0,0,741,742,1,0,0,0,742,745,1,0,0,
  	0,743,741,1,0,0,0,744,746,5,91,0,0,745,744,1,0,0,0,745,746,1,0,0,0,746,
  	748,1,0,0,0,747,736,1,0,0,0,747,748,1,0,0,0,748,749,1,0,0,0,749,750,5,
  	90,0,0,750,109,1,0,0,0,76,114,122,128,132,143,165,169,176,183,190,193,
  	197,199,215,231,245,250,260,265,272,276,279,284,289,292,298,302,318,330,
  	350,354,362,371,375,379,388,395,399,401,411,415,423,427,437,441,445,453,
  	457,469,473,478,486,491,496,505,509,522,540,544,548,557,561,569,588,602,
  	629,645,662,664,685,701,724,733,741,745,747
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  tqlparserParserStaticData = std::move(staticData);
}

}

TQLParser::TQLParser(TokenStream *input) : TQLParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

TQLParser::TQLParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  TQLParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *tqlparserParserStaticData->atn, tqlparserParserStaticData->decisionToDFA, tqlparserParserStaticData->sharedContextCache, options);
}

TQLParser::~TQLParser() {
  delete _interpreter;
}

const atn::ATN& TQLParser::getATN() const {
  return *tqlparserParserStaticData->atn;
}

std::string TQLParser::getGrammarFileName() const {
  return "TQLParser.g4";
}

const std::vector<std::string>& TQLParser::getRuleNames() const {
  return tqlparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& TQLParser::getVocabulary() const {
  return tqlparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView TQLParser::getSerializedATN() const {
  return tqlparserParserStaticData->serializedATN;
}


//----------------- FileContext ------------------------------------------------------------------

TQLParser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t TQLParser::FileContext::getRuleIndex() const {
  return TQLParser::RuleFile;
}

void TQLParser::FileContext::copyFrom(FileContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExecutableFileContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::ExecutableFileContext::EOF() {
  return getToken(TQLParser::EOF, 0);
}

std::vector<TQLParser::ImportDeclContext *> TQLParser::ExecutableFileContext::importDecl() {
  return getRuleContexts<TQLParser::ImportDeclContext>();
}

TQLParser::ImportDeclContext* TQLParser::ExecutableFileContext::importDecl(size_t i) {
  return getRuleContext<TQLParser::ImportDeclContext>(i);
}

std::vector<TQLParser::StatementContext *> TQLParser::ExecutableFileContext::statement() {
  return getRuleContexts<TQLParser::StatementContext>();
}

TQLParser::StatementContext* TQLParser::ExecutableFileContext::statement(size_t i) {
  return getRuleContext<TQLParser::StatementContext>(i);
}

TQLParser::ExecutableFileContext::ExecutableFileContext(FileContext *ctx) { copyFrom(ctx); }


std::any TQLParser::ExecutableFileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitExecutableFile(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PackageFileContext ------------------------------------------------------------------

TQLParser::PackageDeclContext* TQLParser::PackageFileContext::packageDecl() {
  return getRuleContext<TQLParser::PackageDeclContext>(0);
}

tree::TerminalNode* TQLParser::PackageFileContext::EOF() {
  return getToken(TQLParser::EOF, 0);
}

std::vector<TQLParser::TypeDeclContext *> TQLParser::PackageFileContext::typeDecl() {
  return getRuleContexts<TQLParser::TypeDeclContext>();
}

TQLParser::TypeDeclContext* TQLParser::PackageFileContext::typeDecl(size_t i) {
  return getRuleContext<TQLParser::TypeDeclContext>(i);
}

TQLParser::PackageFileContext::PackageFileContext(FileContext *ctx) { copyFrom(ctx); }


std::any TQLParser::PackageFileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitPackageFile(this);
  else
    return visitor->visitChildren(this);
}
TQLParser::FileContext* TQLParser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, TQLParser::RuleFile);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(132);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TQLParser::PACKAGE: {
        _localctx = _tracker.createInstance<TQLParser::PackageFileContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(110);
        packageDecl();
        setState(114);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == TQLParser::TYPE) {
          setState(111);
          typeDecl();
          setState(116);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(117);
        match(TQLParser::EOF);
        break;
      }

      case TQLParser::FROM:
      case TQLParser::LET:
      case TQLParser::INSERT:
      case TQLParser::UPDATE:
      case TQLParser::DELETE:
      case TQLParser::UPSERT:
      case TQLParser::CREATE:
      case TQLParser::GRANT:
      case TQLParser::REVOKE:
      case TQLParser::TRUNCATE:
      case TQLParser::IMPORT: {
        _localctx = _tracker.createInstance<TQLParser::ExecutableFileContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(122);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == TQLParser::IMPORT) {
          setState(119);
          importDecl();
          setState(124);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(126); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(125);
          statement();
          setState(128); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 567243243650) != 0));
        setState(130);
        match(TQLParser::EOF);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PackageDeclContext ------------------------------------------------------------------

TQLParser::PackageDeclContext::PackageDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::PackageDeclContext::PACKAGE() {
  return getToken(TQLParser::PACKAGE, 0);
}

tree::TerminalNode* TQLParser::PackageDeclContext::IDENTIFIER() {
  return getToken(TQLParser::IDENTIFIER, 0);
}


size_t TQLParser::PackageDeclContext::getRuleIndex() const {
  return TQLParser::RulePackageDecl;
}


std::any TQLParser::PackageDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitPackageDecl(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::PackageDeclContext* TQLParser::packageDecl() {
  PackageDeclContext *_localctx = _tracker.createInstance<PackageDeclContext>(_ctx, getState());
  enterRule(_localctx, 2, TQLParser::RulePackageDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(134);
    match(TQLParser::PACKAGE);
    setState(135);
    match(TQLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeDeclContext ------------------------------------------------------------------

TQLParser::TypeDeclContext::TypeDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::TypeDeclContext::TYPE() {
  return getToken(TQLParser::TYPE, 0);
}

tree::TerminalNode* TQLParser::TypeDeclContext::IDENTIFIER() {
  return getToken(TQLParser::IDENTIFIER, 0);
}

tree::TerminalNode* TQLParser::TypeDeclContext::LBRACE() {
  return getToken(TQLParser::LBRACE, 0);
}

tree::TerminalNode* TQLParser::TypeDeclContext::RBRACE() {
  return getToken(TQLParser::RBRACE, 0);
}

std::vector<TQLParser::FieldDeclContext *> TQLParser::TypeDeclContext::fieldDecl() {
  return getRuleContexts<TQLParser::FieldDeclContext>();
}

TQLParser::FieldDeclContext* TQLParser::TypeDeclContext::fieldDecl(size_t i) {
  return getRuleContext<TQLParser::FieldDeclContext>(i);
}


size_t TQLParser::TypeDeclContext::getRuleIndex() const {
  return TQLParser::RuleTypeDecl;
}


std::any TQLParser::TypeDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitTypeDecl(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::TypeDeclContext* TQLParser::typeDecl() {
  TypeDeclContext *_localctx = _tracker.createInstance<TypeDeclContext>(_ctx, getState());
  enterRule(_localctx, 4, TQLParser::RuleTypeDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(137);
    match(TQLParser::TYPE);
    setState(138);
    match(TQLParser::IDENTIFIER);
    setState(139);
    match(TQLParser::LBRACE);
    setState(141); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(140);
      fieldDecl();
      setState(143); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == TQLParser::IDENTIFIER);
    setState(145);
    match(TQLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FieldDeclContext ------------------------------------------------------------------

TQLParser::FieldDeclContext::FieldDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::FieldDeclContext::IDENTIFIER() {
  return getToken(TQLParser::IDENTIFIER, 0);
}

tree::TerminalNode* TQLParser::FieldDeclContext::COLON() {
  return getToken(TQLParser::COLON, 0);
}

TQLParser::TypeExprContext* TQLParser::FieldDeclContext::typeExpr() {
  return getRuleContext<TQLParser::TypeExprContext>(0);
}


size_t TQLParser::FieldDeclContext::getRuleIndex() const {
  return TQLParser::RuleFieldDecl;
}


std::any TQLParser::FieldDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitFieldDecl(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::FieldDeclContext* TQLParser::fieldDecl() {
  FieldDeclContext *_localctx = _tracker.createInstance<FieldDeclContext>(_ctx, getState());
  enterRule(_localctx, 6, TQLParser::RuleFieldDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(147);
    match(TQLParser::IDENTIFIER);
    setState(148);
    match(TQLParser::COLON);
    setState(149);
    typeExpr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportDeclContext ------------------------------------------------------------------

TQLParser::ImportDeclContext::ImportDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::ImportDeclContext::IMPORT() {
  return getToken(TQLParser::IMPORT, 0);
}

tree::TerminalNode* TQLParser::ImportDeclContext::STRING_LIT() {
  return getToken(TQLParser::STRING_LIT, 0);
}


size_t TQLParser::ImportDeclContext::getRuleIndex() const {
  return TQLParser::RuleImportDecl;
}


std::any TQLParser::ImportDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitImportDecl(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::ImportDeclContext* TQLParser::importDecl() {
  ImportDeclContext *_localctx = _tracker.createInstance<ImportDeclContext>(_ctx, getState());
  enterRule(_localctx, 8, TQLParser::RuleImportDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(151);
    match(TQLParser::IMPORT);
    setState(152);
    match(TQLParser::STRING_LIT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

TQLParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TQLParser::QueryStatementContext* TQLParser::StatementContext::queryStatement() {
  return getRuleContext<TQLParser::QueryStatementContext>(0);
}

TQLParser::InsertStatementContext* TQLParser::StatementContext::insertStatement() {
  return getRuleContext<TQLParser::InsertStatementContext>(0);
}

TQLParser::UpdateStatementContext* TQLParser::StatementContext::updateStatement() {
  return getRuleContext<TQLParser::UpdateStatementContext>(0);
}

TQLParser::DeleteStatementContext* TQLParser::StatementContext::deleteStatement() {
  return getRuleContext<TQLParser::DeleteStatementContext>(0);
}

TQLParser::UpsertStatementContext* TQLParser::StatementContext::upsertStatement() {
  return getRuleContext<TQLParser::UpsertStatementContext>(0);
}

TQLParser::CreateTableStatementContext* TQLParser::StatementContext::createTableStatement() {
  return getRuleContext<TQLParser::CreateTableStatementContext>(0);
}

TQLParser::CreateRoleStatementContext* TQLParser::StatementContext::createRoleStatement() {
  return getRuleContext<TQLParser::CreateRoleStatementContext>(0);
}

TQLParser::GrantStatementContext* TQLParser::StatementContext::grantStatement() {
  return getRuleContext<TQLParser::GrantStatementContext>(0);
}

TQLParser::CreateApiKeyStatementContext* TQLParser::StatementContext::createApiKeyStatement() {
  return getRuleContext<TQLParser::CreateApiKeyStatementContext>(0);
}

TQLParser::RevokeApiKeyStatementContext* TQLParser::StatementContext::revokeApiKeyStatement() {
  return getRuleContext<TQLParser::RevokeApiKeyStatementContext>(0);
}

TQLParser::TruncateStatementContext* TQLParser::StatementContext::truncateStatement() {
  return getRuleContext<TQLParser::TruncateStatementContext>(0);
}


size_t TQLParser::StatementContext::getRuleIndex() const {
  return TQLParser::RuleStatement;
}


std::any TQLParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::StatementContext* TQLParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 10, TQLParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(165);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(154);
      queryStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(155);
      insertStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(156);
      updateStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(157);
      deleteStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(158);
      upsertStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(159);
      createTableStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(160);
      createRoleStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(161);
      grantStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(162);
      createApiKeyStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(163);
      revokeApiKeyStatement();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(164);
      truncateStatement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeExprContext ------------------------------------------------------------------

TQLParser::TypeExprContext::TypeExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t TQLParser::TypeExprContext::getRuleIndex() const {
  return TQLParser::RuleTypeExpr;
}

void TQLParser::TypeExprContext::copyFrom(TypeExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ArrayTypeExprContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::ArrayTypeExprContext::ARRAY_KW() {
  return getToken(TQLParser::ARRAY_KW, 0);
}

tree::TerminalNode* TQLParser::ArrayTypeExprContext::LT() {
  return getToken(TQLParser::LT, 0);
}

TQLParser::ArrayElementTypeContext* TQLParser::ArrayTypeExprContext::arrayElementType() {
  return getRuleContext<TQLParser::ArrayElementTypeContext>(0);
}

tree::TerminalNode* TQLParser::ArrayTypeExprContext::GT() {
  return getToken(TQLParser::GT, 0);
}

tree::TerminalNode* TQLParser::ArrayTypeExprContext::QUESTION() {
  return getToken(TQLParser::QUESTION, 0);
}

TQLParser::ArrayTypeExprContext::ArrayTypeExprContext(TypeExprContext *ctx) { copyFrom(ctx); }


std::any TQLParser::ArrayTypeExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitArrayTypeExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ScalarTypeExprContext ------------------------------------------------------------------

TQLParser::ScalarTypeContext* TQLParser::ScalarTypeExprContext::scalarType() {
  return getRuleContext<TQLParser::ScalarTypeContext>(0);
}

tree::TerminalNode* TQLParser::ScalarTypeExprContext::QUESTION() {
  return getToken(TQLParser::QUESTION, 0);
}

TQLParser::ScalarTypeExprContext::ScalarTypeExprContext(TypeExprContext *ctx) { copyFrom(ctx); }


std::any TQLParser::ScalarTypeExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitScalarTypeExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UserDefinedTypeExprContext ------------------------------------------------------------------

TQLParser::QualifiedTypeNameContext* TQLParser::UserDefinedTypeExprContext::qualifiedTypeName() {
  return getRuleContext<TQLParser::QualifiedTypeNameContext>(0);
}

tree::TerminalNode* TQLParser::UserDefinedTypeExprContext::QUESTION() {
  return getToken(TQLParser::QUESTION, 0);
}

TQLParser::UserDefinedTypeExprContext::UserDefinedTypeExprContext(TypeExprContext *ctx) { copyFrom(ctx); }


std::any TQLParser::UserDefinedTypeExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitUserDefinedTypeExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VectorTypeExprContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::VectorTypeExprContext::VECTOR_KW() {
  return getToken(TQLParser::VECTOR_KW, 0);
}

tree::TerminalNode* TQLParser::VectorTypeExprContext::LPAREN() {
  return getToken(TQLParser::LPAREN, 0);
}

tree::TerminalNode* TQLParser::VectorTypeExprContext::INTEGER_LIT() {
  return getToken(TQLParser::INTEGER_LIT, 0);
}

tree::TerminalNode* TQLParser::VectorTypeExprContext::RPAREN() {
  return getToken(TQLParser::RPAREN, 0);
}

tree::TerminalNode* TQLParser::VectorTypeExprContext::QUESTION() {
  return getToken(TQLParser::QUESTION, 0);
}

TQLParser::VectorTypeExprContext::VectorTypeExprContext(TypeExprContext *ctx) { copyFrom(ctx); }


std::any TQLParser::VectorTypeExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitVectorTypeExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- JsonTypeExprContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::JsonTypeExprContext::JSON_KW() {
  return getToken(TQLParser::JSON_KW, 0);
}

tree::TerminalNode* TQLParser::JsonTypeExprContext::LT() {
  return getToken(TQLParser::LT, 0);
}

TQLParser::JsonTypeParamContext* TQLParser::JsonTypeExprContext::jsonTypeParam() {
  return getRuleContext<TQLParser::JsonTypeParamContext>(0);
}

tree::TerminalNode* TQLParser::JsonTypeExprContext::GT() {
  return getToken(TQLParser::GT, 0);
}

tree::TerminalNode* TQLParser::JsonTypeExprContext::QUESTION() {
  return getToken(TQLParser::QUESTION, 0);
}

TQLParser::JsonTypeExprContext::JsonTypeExprContext(TypeExprContext *ctx) { copyFrom(ctx); }


std::any TQLParser::JsonTypeExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitJsonTypeExpr(this);
  else
    return visitor->visitChildren(this);
}
TQLParser::TypeExprContext* TQLParser::typeExpr() {
  TypeExprContext *_localctx = _tracker.createInstance<TypeExprContext>(_ctx, getState());
  enterRule(_localctx, 12, TQLParser::RuleTypeExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(199);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TQLParser::INT32:
      case TQLParser::INT64:
      case TQLParser::FLOAT32:
      case TQLParser::FLOAT64:
      case TQLParser::DECIMAL_KW:
      case TQLParser::BOOL_KW:
      case TQLParser::TEXT_KW:
      case TQLParser::UUID_KW:
      case TQLParser::TIMESTAMP_KW: {
        _localctx = _tracker.createInstance<TQLParser::ScalarTypeExprContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(167);
        scalarType();
        setState(169);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == TQLParser::QUESTION) {
          setState(168);
          match(TQLParser::QUESTION);
        }
        break;
      }

      case TQLParser::VECTOR_KW: {
        _localctx = _tracker.createInstance<TQLParser::VectorTypeExprContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(171);
        match(TQLParser::VECTOR_KW);
        setState(172);
        match(TQLParser::LPAREN);
        setState(173);
        match(TQLParser::INTEGER_LIT);
        setState(174);
        match(TQLParser::RPAREN);
        setState(176);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == TQLParser::QUESTION) {
          setState(175);
          match(TQLParser::QUESTION);
        }
        break;
      }

      case TQLParser::ARRAY_KW: {
        _localctx = _tracker.createInstance<TQLParser::ArrayTypeExprContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(178);
        match(TQLParser::ARRAY_KW);
        setState(179);
        match(TQLParser::LT);
        setState(180);
        arrayElementType();
        setState(181);
        match(TQLParser::GT);
        setState(183);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == TQLParser::QUESTION) {
          setState(182);
          match(TQLParser::QUESTION);
        }
        break;
      }

      case TQLParser::JSON_KW: {
        _localctx = _tracker.createInstance<TQLParser::JsonTypeExprContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(185);
        match(TQLParser::JSON_KW);
        setState(190);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == TQLParser::LT) {
          setState(186);
          match(TQLParser::LT);
          setState(187);
          jsonTypeParam();
          setState(188);
          match(TQLParser::GT);
        }
        setState(193);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == TQLParser::QUESTION) {
          setState(192);
          match(TQLParser::QUESTION);
        }
        break;
      }

      case TQLParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<TQLParser::UserDefinedTypeExprContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(195);
        qualifiedTypeName();
        setState(197);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == TQLParser::QUESTION) {
          setState(196);
          match(TQLParser::QUESTION);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayElementTypeContext ------------------------------------------------------------------

TQLParser::ArrayElementTypeContext::ArrayElementTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::ArrayElementTypeContext::INT32() {
  return getToken(TQLParser::INT32, 0);
}

tree::TerminalNode* TQLParser::ArrayElementTypeContext::INT64() {
  return getToken(TQLParser::INT64, 0);
}

tree::TerminalNode* TQLParser::ArrayElementTypeContext::FLOAT32() {
  return getToken(TQLParser::FLOAT32, 0);
}

tree::TerminalNode* TQLParser::ArrayElementTypeContext::FLOAT64() {
  return getToken(TQLParser::FLOAT64, 0);
}

tree::TerminalNode* TQLParser::ArrayElementTypeContext::DECIMAL_KW() {
  return getToken(TQLParser::DECIMAL_KW, 0);
}

tree::TerminalNode* TQLParser::ArrayElementTypeContext::LPAREN() {
  return getToken(TQLParser::LPAREN, 0);
}

std::vector<tree::TerminalNode *> TQLParser::ArrayElementTypeContext::INTEGER_LIT() {
  return getTokens(TQLParser::INTEGER_LIT);
}

tree::TerminalNode* TQLParser::ArrayElementTypeContext::INTEGER_LIT(size_t i) {
  return getToken(TQLParser::INTEGER_LIT, i);
}

tree::TerminalNode* TQLParser::ArrayElementTypeContext::COMMA() {
  return getToken(TQLParser::COMMA, 0);
}

tree::TerminalNode* TQLParser::ArrayElementTypeContext::RPAREN() {
  return getToken(TQLParser::RPAREN, 0);
}

tree::TerminalNode* TQLParser::ArrayElementTypeContext::BOOL_KW() {
  return getToken(TQLParser::BOOL_KW, 0);
}

tree::TerminalNode* TQLParser::ArrayElementTypeContext::TEXT_KW() {
  return getToken(TQLParser::TEXT_KW, 0);
}

tree::TerminalNode* TQLParser::ArrayElementTypeContext::UUID_KW() {
  return getToken(TQLParser::UUID_KW, 0);
}

tree::TerminalNode* TQLParser::ArrayElementTypeContext::TIMESTAMP_KW() {
  return getToken(TQLParser::TIMESTAMP_KW, 0);
}


size_t TQLParser::ArrayElementTypeContext::getRuleIndex() const {
  return TQLParser::RuleArrayElementType;
}


std::any TQLParser::ArrayElementTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitArrayElementType(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::ArrayElementTypeContext* TQLParser::arrayElementType() {
  ArrayElementTypeContext *_localctx = _tracker.createInstance<ArrayElementTypeContext>(_ctx, getState());
  enterRule(_localctx, 14, TQLParser::RuleArrayElementType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(215);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TQLParser::INT32: {
        enterOuterAlt(_localctx, 1);
        setState(201);
        match(TQLParser::INT32);
        break;
      }

      case TQLParser::INT64: {
        enterOuterAlt(_localctx, 2);
        setState(202);
        match(TQLParser::INT64);
        break;
      }

      case TQLParser::FLOAT32: {
        enterOuterAlt(_localctx, 3);
        setState(203);
        match(TQLParser::FLOAT32);
        break;
      }

      case TQLParser::FLOAT64: {
        enterOuterAlt(_localctx, 4);
        setState(204);
        match(TQLParser::FLOAT64);
        break;
      }

      case TQLParser::DECIMAL_KW: {
        enterOuterAlt(_localctx, 5);
        setState(205);
        match(TQLParser::DECIMAL_KW);
        setState(206);
        match(TQLParser::LPAREN);
        setState(207);
        match(TQLParser::INTEGER_LIT);
        setState(208);
        match(TQLParser::COMMA);
        setState(209);
        match(TQLParser::INTEGER_LIT);
        setState(210);
        match(TQLParser::RPAREN);
        break;
      }

      case TQLParser::BOOL_KW: {
        enterOuterAlt(_localctx, 6);
        setState(211);
        match(TQLParser::BOOL_KW);
        break;
      }

      case TQLParser::TEXT_KW: {
        enterOuterAlt(_localctx, 7);
        setState(212);
        match(TQLParser::TEXT_KW);
        break;
      }

      case TQLParser::UUID_KW: {
        enterOuterAlt(_localctx, 8);
        setState(213);
        match(TQLParser::UUID_KW);
        break;
      }

      case TQLParser::TIMESTAMP_KW: {
        enterOuterAlt(_localctx, 9);
        setState(214);
        match(TQLParser::TIMESTAMP_KW);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScalarTypeContext ------------------------------------------------------------------

TQLParser::ScalarTypeContext::ScalarTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::ScalarTypeContext::INT32() {
  return getToken(TQLParser::INT32, 0);
}

tree::TerminalNode* TQLParser::ScalarTypeContext::INT64() {
  return getToken(TQLParser::INT64, 0);
}

tree::TerminalNode* TQLParser::ScalarTypeContext::FLOAT32() {
  return getToken(TQLParser::FLOAT32, 0);
}

tree::TerminalNode* TQLParser::ScalarTypeContext::FLOAT64() {
  return getToken(TQLParser::FLOAT64, 0);
}

tree::TerminalNode* TQLParser::ScalarTypeContext::DECIMAL_KW() {
  return getToken(TQLParser::DECIMAL_KW, 0);
}

tree::TerminalNode* TQLParser::ScalarTypeContext::LPAREN() {
  return getToken(TQLParser::LPAREN, 0);
}

std::vector<tree::TerminalNode *> TQLParser::ScalarTypeContext::INTEGER_LIT() {
  return getTokens(TQLParser::INTEGER_LIT);
}

tree::TerminalNode* TQLParser::ScalarTypeContext::INTEGER_LIT(size_t i) {
  return getToken(TQLParser::INTEGER_LIT, i);
}

tree::TerminalNode* TQLParser::ScalarTypeContext::COMMA() {
  return getToken(TQLParser::COMMA, 0);
}

tree::TerminalNode* TQLParser::ScalarTypeContext::RPAREN() {
  return getToken(TQLParser::RPAREN, 0);
}

tree::TerminalNode* TQLParser::ScalarTypeContext::BOOL_KW() {
  return getToken(TQLParser::BOOL_KW, 0);
}

tree::TerminalNode* TQLParser::ScalarTypeContext::TEXT_KW() {
  return getToken(TQLParser::TEXT_KW, 0);
}

tree::TerminalNode* TQLParser::ScalarTypeContext::UUID_KW() {
  return getToken(TQLParser::UUID_KW, 0);
}

tree::TerminalNode* TQLParser::ScalarTypeContext::TIMESTAMP_KW() {
  return getToken(TQLParser::TIMESTAMP_KW, 0);
}


size_t TQLParser::ScalarTypeContext::getRuleIndex() const {
  return TQLParser::RuleScalarType;
}


std::any TQLParser::ScalarTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitScalarType(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::ScalarTypeContext* TQLParser::scalarType() {
  ScalarTypeContext *_localctx = _tracker.createInstance<ScalarTypeContext>(_ctx, getState());
  enterRule(_localctx, 16, TQLParser::RuleScalarType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(231);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TQLParser::INT32: {
        enterOuterAlt(_localctx, 1);
        setState(217);
        match(TQLParser::INT32);
        break;
      }

      case TQLParser::INT64: {
        enterOuterAlt(_localctx, 2);
        setState(218);
        match(TQLParser::INT64);
        break;
      }

      case TQLParser::FLOAT32: {
        enterOuterAlt(_localctx, 3);
        setState(219);
        match(TQLParser::FLOAT32);
        break;
      }

      case TQLParser::FLOAT64: {
        enterOuterAlt(_localctx, 4);
        setState(220);
        match(TQLParser::FLOAT64);
        break;
      }

      case TQLParser::DECIMAL_KW: {
        enterOuterAlt(_localctx, 5);
        setState(221);
        match(TQLParser::DECIMAL_KW);
        setState(222);
        match(TQLParser::LPAREN);
        setState(223);
        match(TQLParser::INTEGER_LIT);
        setState(224);
        match(TQLParser::COMMA);
        setState(225);
        match(TQLParser::INTEGER_LIT);
        setState(226);
        match(TQLParser::RPAREN);
        break;
      }

      case TQLParser::BOOL_KW: {
        enterOuterAlt(_localctx, 6);
        setState(227);
        match(TQLParser::BOOL_KW);
        break;
      }

      case TQLParser::TEXT_KW: {
        enterOuterAlt(_localctx, 7);
        setState(228);
        match(TQLParser::TEXT_KW);
        break;
      }

      case TQLParser::UUID_KW: {
        enterOuterAlt(_localctx, 8);
        setState(229);
        match(TQLParser::UUID_KW);
        break;
      }

      case TQLParser::TIMESTAMP_KW: {
        enterOuterAlt(_localctx, 9);
        setState(230);
        match(TQLParser::TIMESTAMP_KW);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JsonTypeParamContext ------------------------------------------------------------------

TQLParser::JsonTypeParamContext::JsonTypeParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TQLParser::ScalarTypeContext* TQLParser::JsonTypeParamContext::scalarType() {
  return getRuleContext<TQLParser::ScalarTypeContext>(0);
}

tree::TerminalNode* TQLParser::JsonTypeParamContext::MAP_KW() {
  return getToken(TQLParser::MAP_KW, 0);
}

tree::TerminalNode* TQLParser::JsonTypeParamContext::LBRACKET() {
  return getToken(TQLParser::LBRACKET, 0);
}

std::vector<TQLParser::TypeExprContext *> TQLParser::JsonTypeParamContext::typeExpr() {
  return getRuleContexts<TQLParser::TypeExprContext>();
}

TQLParser::TypeExprContext* TQLParser::JsonTypeParamContext::typeExpr(size_t i) {
  return getRuleContext<TQLParser::TypeExprContext>(i);
}

tree::TerminalNode* TQLParser::JsonTypeParamContext::RBRACKET() {
  return getToken(TQLParser::RBRACKET, 0);
}

tree::TerminalNode* TQLParser::JsonTypeParamContext::ARRAY_KW() {
  return getToken(TQLParser::ARRAY_KW, 0);
}

tree::TerminalNode* TQLParser::JsonTypeParamContext::LT() {
  return getToken(TQLParser::LT, 0);
}

tree::TerminalNode* TQLParser::JsonTypeParamContext::GT() {
  return getToken(TQLParser::GT, 0);
}


size_t TQLParser::JsonTypeParamContext::getRuleIndex() const {
  return TQLParser::RuleJsonTypeParam;
}


std::any TQLParser::JsonTypeParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitJsonTypeParam(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::JsonTypeParamContext* TQLParser::jsonTypeParam() {
  JsonTypeParamContext *_localctx = _tracker.createInstance<JsonTypeParamContext>(_ctx, getState());
  enterRule(_localctx, 18, TQLParser::RuleJsonTypeParam);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(245);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TQLParser::INT32:
      case TQLParser::INT64:
      case TQLParser::FLOAT32:
      case TQLParser::FLOAT64:
      case TQLParser::DECIMAL_KW:
      case TQLParser::BOOL_KW:
      case TQLParser::TEXT_KW:
      case TQLParser::UUID_KW:
      case TQLParser::TIMESTAMP_KW: {
        enterOuterAlt(_localctx, 1);
        setState(233);
        scalarType();
        break;
      }

      case TQLParser::MAP_KW: {
        enterOuterAlt(_localctx, 2);
        setState(234);
        match(TQLParser::MAP_KW);
        setState(235);
        match(TQLParser::LBRACKET);
        setState(236);
        typeExpr();
        setState(237);
        match(TQLParser::RBRACKET);
        setState(238);
        typeExpr();
        break;
      }

      case TQLParser::ARRAY_KW: {
        enterOuterAlt(_localctx, 3);
        setState(240);
        match(TQLParser::ARRAY_KW);
        setState(241);
        match(TQLParser::LT);
        setState(242);
        typeExpr();
        setState(243);
        match(TQLParser::GT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QualifiedTypeNameContext ------------------------------------------------------------------

TQLParser::QualifiedTypeNameContext::QualifiedTypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> TQLParser::QualifiedTypeNameContext::IDENTIFIER() {
  return getTokens(TQLParser::IDENTIFIER);
}

tree::TerminalNode* TQLParser::QualifiedTypeNameContext::IDENTIFIER(size_t i) {
  return getToken(TQLParser::IDENTIFIER, i);
}

tree::TerminalNode* TQLParser::QualifiedTypeNameContext::DOT() {
  return getToken(TQLParser::DOT, 0);
}


size_t TQLParser::QualifiedTypeNameContext::getRuleIndex() const {
  return TQLParser::RuleQualifiedTypeName;
}


std::any TQLParser::QualifiedTypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitQualifiedTypeName(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::QualifiedTypeNameContext* TQLParser::qualifiedTypeName() {
  QualifiedTypeNameContext *_localctx = _tracker.createInstance<QualifiedTypeNameContext>(_ctx, getState());
  enterRule(_localctx, 20, TQLParser::RuleQualifiedTypeName);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(247);
    match(TQLParser::IDENTIFIER);
    setState(250);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TQLParser::DOT) {
      setState(248);
      match(TQLParser::DOT);
      setState(249);
      match(TQLParser::IDENTIFIER);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PathBindingContext ------------------------------------------------------------------

TQLParser::PathBindingContext::PathBindingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::PathBindingContext::STRING_LIT() {
  return getToken(TQLParser::STRING_LIT, 0);
}

tree::TerminalNode* TQLParser::PathBindingContext::AS() {
  return getToken(TQLParser::AS, 0);
}

TQLParser::VarBindingContext* TQLParser::PathBindingContext::varBinding() {
  return getRuleContext<TQLParser::VarBindingContext>(0);
}


size_t TQLParser::PathBindingContext::getRuleIndex() const {
  return TQLParser::RulePathBinding;
}


std::any TQLParser::PathBindingContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitPathBinding(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::PathBindingContext* TQLParser::pathBinding() {
  PathBindingContext *_localctx = _tracker.createInstance<PathBindingContext>(_ctx, getState());
  enterRule(_localctx, 22, TQLParser::RulePathBinding);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(252);
    match(TQLParser::STRING_LIT);
    setState(253);
    match(TQLParser::AS);
    setState(254);
    varBinding();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarBindingContext ------------------------------------------------------------------

TQLParser::VarBindingContext::VarBindingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::VarBindingContext::IDENTIFIER() {
  return getToken(TQLParser::IDENTIFIER, 0);
}

tree::TerminalNode* TQLParser::VarBindingContext::COLON() {
  return getToken(TQLParser::COLON, 0);
}

TQLParser::QualifiedTypeNameContext* TQLParser::VarBindingContext::qualifiedTypeName() {
  return getRuleContext<TQLParser::QualifiedTypeNameContext>(0);
}


size_t TQLParser::VarBindingContext::getRuleIndex() const {
  return TQLParser::RuleVarBinding;
}


std::any TQLParser::VarBindingContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitVarBinding(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::VarBindingContext* TQLParser::varBinding() {
  VarBindingContext *_localctx = _tracker.createInstance<VarBindingContext>(_ctx, getState());
  enterRule(_localctx, 24, TQLParser::RuleVarBinding);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(260);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(256);
      match(TQLParser::IDENTIFIER);
      setState(257);
      match(TQLParser::COLON);
      setState(258);
      qualifiedTypeName();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(259);
      qualifiedTypeName();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QueryStatementContext ------------------------------------------------------------------

TQLParser::QueryStatementContext::QueryStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TQLParser::FromClauseContext* TQLParser::QueryStatementContext::fromClause() {
  return getRuleContext<TQLParser::FromClauseContext>(0);
}

TQLParser::SelectClauseContext* TQLParser::QueryStatementContext::selectClause() {
  return getRuleContext<TQLParser::SelectClauseContext>(0);
}

std::vector<TQLParser::LetClauseContext *> TQLParser::QueryStatementContext::letClause() {
  return getRuleContexts<TQLParser::LetClauseContext>();
}

TQLParser::LetClauseContext* TQLParser::QueryStatementContext::letClause(size_t i) {
  return getRuleContext<TQLParser::LetClauseContext>(i);
}

std::vector<TQLParser::JoinClauseContext *> TQLParser::QueryStatementContext::joinClause() {
  return getRuleContexts<TQLParser::JoinClauseContext>();
}

TQLParser::JoinClauseContext* TQLParser::QueryStatementContext::joinClause(size_t i) {
  return getRuleContext<TQLParser::JoinClauseContext>(i);
}

TQLParser::WhereClauseContext* TQLParser::QueryStatementContext::whereClause() {
  return getRuleContext<TQLParser::WhereClauseContext>(0);
}

TQLParser::AggregationBlockContext* TQLParser::QueryStatementContext::aggregationBlock() {
  return getRuleContext<TQLParser::AggregationBlockContext>(0);
}

TQLParser::OrderByClauseContext* TQLParser::QueryStatementContext::orderByClause() {
  return getRuleContext<TQLParser::OrderByClauseContext>(0);
}

TQLParser::LimitClauseContext* TQLParser::QueryStatementContext::limitClause() {
  return getRuleContext<TQLParser::LimitClauseContext>(0);
}


size_t TQLParser::QueryStatementContext::getRuleIndex() const {
  return TQLParser::RuleQueryStatement;
}


std::any TQLParser::QueryStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitQueryStatement(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::QueryStatementContext* TQLParser::queryStatement() {
  QueryStatementContext *_localctx = _tracker.createInstance<QueryStatementContext>(_ctx, getState());
  enterRule(_localctx, 26, TQLParser::RuleQueryStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(265);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TQLParser::LET) {
      setState(262);
      letClause();
      setState(267);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(268);
    fromClause();
    setState(272);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TQLParser::JOIN

    || _la == TQLParser::LEFT) {
      setState(269);
      joinClause();
      setState(274);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(276);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TQLParser::WHERE) {
      setState(275);
      whereClause();
    }
    setState(279);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TQLParser::GROUP) {
      setState(278);
      aggregationBlock();
    }
    setState(284);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TQLParser::LET) {
      setState(281);
      letClause();
      setState(286);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(287);
    selectClause();
    setState(289);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TQLParser::ORDER) {
      setState(288);
      orderByClause();
    }
    setState(292);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TQLParser::LIMIT) {
      setState(291);
      limitClause();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AggregationBlockContext ------------------------------------------------------------------

TQLParser::AggregationBlockContext::AggregationBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TQLParser::GroupByClauseContext* TQLParser::AggregationBlockContext::groupByClause() {
  return getRuleContext<TQLParser::GroupByClauseContext>(0);
}

std::vector<TQLParser::LetClauseContext *> TQLParser::AggregationBlockContext::letClause() {
  return getRuleContexts<TQLParser::LetClauseContext>();
}

TQLParser::LetClauseContext* TQLParser::AggregationBlockContext::letClause(size_t i) {
  return getRuleContext<TQLParser::LetClauseContext>(i);
}

TQLParser::HavingClauseContext* TQLParser::AggregationBlockContext::havingClause() {
  return getRuleContext<TQLParser::HavingClauseContext>(0);
}


size_t TQLParser::AggregationBlockContext::getRuleIndex() const {
  return TQLParser::RuleAggregationBlock;
}


std::any TQLParser::AggregationBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitAggregationBlock(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::AggregationBlockContext* TQLParser::aggregationBlock() {
  AggregationBlockContext *_localctx = _tracker.createInstance<AggregationBlockContext>(_ctx, getState());
  enterRule(_localctx, 28, TQLParser::RuleAggregationBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(294);
    groupByClause();
    setState(298);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(295);
        letClause(); 
      }
      setState(300);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    }
    setState(302);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TQLParser::HAVING) {
      setState(301);
      havingClause();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FromClauseContext ------------------------------------------------------------------

TQLParser::FromClauseContext::FromClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::FromClauseContext::FROM() {
  return getToken(TQLParser::FROM, 0);
}

TQLParser::PathBindingContext* TQLParser::FromClauseContext::pathBinding() {
  return getRuleContext<TQLParser::PathBindingContext>(0);
}


size_t TQLParser::FromClauseContext::getRuleIndex() const {
  return TQLParser::RuleFromClause;
}


std::any TQLParser::FromClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitFromClause(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::FromClauseContext* TQLParser::fromClause() {
  FromClauseContext *_localctx = _tracker.createInstance<FromClauseContext>(_ctx, getState());
  enterRule(_localctx, 30, TQLParser::RuleFromClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(304);
    match(TQLParser::FROM);
    setState(305);
    pathBinding();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JoinClauseContext ------------------------------------------------------------------

TQLParser::JoinClauseContext::JoinClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t TQLParser::JoinClauseContext::getRuleIndex() const {
  return TQLParser::RuleJoinClause;
}

void TQLParser::JoinClauseContext::copyFrom(JoinClauseContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- InnerJoinContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::InnerJoinContext::JOIN() {
  return getToken(TQLParser::JOIN, 0);
}

TQLParser::PathBindingContext* TQLParser::InnerJoinContext::pathBinding() {
  return getRuleContext<TQLParser::PathBindingContext>(0);
}

tree::TerminalNode* TQLParser::InnerJoinContext::ON() {
  return getToken(TQLParser::ON, 0);
}

TQLParser::ExprContext* TQLParser::InnerJoinContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}

TQLParser::InnerJoinContext::InnerJoinContext(JoinClauseContext *ctx) { copyFrom(ctx); }


std::any TQLParser::InnerJoinContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitInnerJoin(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LeftOuterJoinContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::LeftOuterJoinContext::LEFT() {
  return getToken(TQLParser::LEFT, 0);
}

tree::TerminalNode* TQLParser::LeftOuterJoinContext::JOIN() {
  return getToken(TQLParser::JOIN, 0);
}

TQLParser::PathBindingContext* TQLParser::LeftOuterJoinContext::pathBinding() {
  return getRuleContext<TQLParser::PathBindingContext>(0);
}

tree::TerminalNode* TQLParser::LeftOuterJoinContext::ON() {
  return getToken(TQLParser::ON, 0);
}

TQLParser::ExprContext* TQLParser::LeftOuterJoinContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}

TQLParser::LeftOuterJoinContext::LeftOuterJoinContext(JoinClauseContext *ctx) { copyFrom(ctx); }


std::any TQLParser::LeftOuterJoinContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitLeftOuterJoin(this);
  else
    return visitor->visitChildren(this);
}
TQLParser::JoinClauseContext* TQLParser::joinClause() {
  JoinClauseContext *_localctx = _tracker.createInstance<JoinClauseContext>(_ctx, getState());
  enterRule(_localctx, 32, TQLParser::RuleJoinClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(318);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TQLParser::JOIN: {
        _localctx = _tracker.createInstance<TQLParser::InnerJoinContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(307);
        match(TQLParser::JOIN);
        setState(308);
        pathBinding();
        setState(309);
        match(TQLParser::ON);
        setState(310);
        expr(0);
        break;
      }

      case TQLParser::LEFT: {
        _localctx = _tracker.createInstance<TQLParser::LeftOuterJoinContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(312);
        match(TQLParser::LEFT);
        setState(313);
        match(TQLParser::JOIN);
        setState(314);
        pathBinding();
        setState(315);
        match(TQLParser::ON);
        setState(316);
        expr(0);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhereClauseContext ------------------------------------------------------------------

TQLParser::WhereClauseContext::WhereClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::WhereClauseContext::WHERE() {
  return getToken(TQLParser::WHERE, 0);
}

TQLParser::ExprContext* TQLParser::WhereClauseContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}


size_t TQLParser::WhereClauseContext::getRuleIndex() const {
  return TQLParser::RuleWhereClause;
}


std::any TQLParser::WhereClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitWhereClause(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::WhereClauseContext* TQLParser::whereClause() {
  WhereClauseContext *_localctx = _tracker.createInstance<WhereClauseContext>(_ctx, getState());
  enterRule(_localctx, 34, TQLParser::RuleWhereClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(320);
    match(TQLParser::WHERE);
    setState(321);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GroupByClauseContext ------------------------------------------------------------------

TQLParser::GroupByClauseContext::GroupByClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::GroupByClauseContext::GROUP() {
  return getToken(TQLParser::GROUP, 0);
}

tree::TerminalNode* TQLParser::GroupByClauseContext::BY() {
  return getToken(TQLParser::BY, 0);
}

std::vector<TQLParser::FieldRefContext *> TQLParser::GroupByClauseContext::fieldRef() {
  return getRuleContexts<TQLParser::FieldRefContext>();
}

TQLParser::FieldRefContext* TQLParser::GroupByClauseContext::fieldRef(size_t i) {
  return getRuleContext<TQLParser::FieldRefContext>(i);
}

std::vector<tree::TerminalNode *> TQLParser::GroupByClauseContext::COMMA() {
  return getTokens(TQLParser::COMMA);
}

tree::TerminalNode* TQLParser::GroupByClauseContext::COMMA(size_t i) {
  return getToken(TQLParser::COMMA, i);
}


size_t TQLParser::GroupByClauseContext::getRuleIndex() const {
  return TQLParser::RuleGroupByClause;
}


std::any TQLParser::GroupByClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitGroupByClause(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::GroupByClauseContext* TQLParser::groupByClause() {
  GroupByClauseContext *_localctx = _tracker.createInstance<GroupByClauseContext>(_ctx, getState());
  enterRule(_localctx, 36, TQLParser::RuleGroupByClause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(323);
    match(TQLParser::GROUP);
    setState(324);
    match(TQLParser::BY);
    setState(325);
    fieldRef();
    setState(330);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TQLParser::COMMA) {
      setState(326);
      match(TQLParser::COMMA);
      setState(327);
      fieldRef();
      setState(332);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HavingClauseContext ------------------------------------------------------------------

TQLParser::HavingClauseContext::HavingClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::HavingClauseContext::HAVING() {
  return getToken(TQLParser::HAVING, 0);
}

TQLParser::ExprContext* TQLParser::HavingClauseContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}


size_t TQLParser::HavingClauseContext::getRuleIndex() const {
  return TQLParser::RuleHavingClause;
}


std::any TQLParser::HavingClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitHavingClause(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::HavingClauseContext* TQLParser::havingClause() {
  HavingClauseContext *_localctx = _tracker.createInstance<HavingClauseContext>(_ctx, getState());
  enterRule(_localctx, 38, TQLParser::RuleHavingClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(333);
    match(TQLParser::HAVING);
    setState(334);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LetClauseContext ------------------------------------------------------------------

TQLParser::LetClauseContext::LetClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::LetClauseContext::LET() {
  return getToken(TQLParser::LET, 0);
}

tree::TerminalNode* TQLParser::LetClauseContext::IDENTIFIER() {
  return getToken(TQLParser::IDENTIFIER, 0);
}

tree::TerminalNode* TQLParser::LetClauseContext::COLON() {
  return getToken(TQLParser::COLON, 0);
}

TQLParser::TypeExprContext* TQLParser::LetClauseContext::typeExpr() {
  return getRuleContext<TQLParser::TypeExprContext>(0);
}

tree::TerminalNode* TQLParser::LetClauseContext::ASSIGN() {
  return getToken(TQLParser::ASSIGN, 0);
}

TQLParser::ExprContext* TQLParser::LetClauseContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}


size_t TQLParser::LetClauseContext::getRuleIndex() const {
  return TQLParser::RuleLetClause;
}


std::any TQLParser::LetClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitLetClause(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::LetClauseContext* TQLParser::letClause() {
  LetClauseContext *_localctx = _tracker.createInstance<LetClauseContext>(_ctx, getState());
  enterRule(_localctx, 40, TQLParser::RuleLetClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(336);
    match(TQLParser::LET);
    setState(337);
    match(TQLParser::IDENTIFIER);
    setState(338);
    match(TQLParser::COLON);
    setState(339);
    typeExpr();
    setState(340);
    match(TQLParser::ASSIGN);
    setState(341);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectClauseContext ------------------------------------------------------------------

TQLParser::SelectClauseContext::SelectClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::SelectClauseContext::SELECT() {
  return getToken(TQLParser::SELECT, 0);
}

tree::TerminalNode* TQLParser::SelectClauseContext::LBRACE() {
  return getToken(TQLParser::LBRACE, 0);
}

std::vector<TQLParser::SelectFieldContext *> TQLParser::SelectClauseContext::selectField() {
  return getRuleContexts<TQLParser::SelectFieldContext>();
}

TQLParser::SelectFieldContext* TQLParser::SelectClauseContext::selectField(size_t i) {
  return getRuleContext<TQLParser::SelectFieldContext>(i);
}

tree::TerminalNode* TQLParser::SelectClauseContext::RBRACE() {
  return getToken(TQLParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> TQLParser::SelectClauseContext::COMMA() {
  return getTokens(TQLParser::COMMA);
}

tree::TerminalNode* TQLParser::SelectClauseContext::COMMA(size_t i) {
  return getToken(TQLParser::COMMA, i);
}


size_t TQLParser::SelectClauseContext::getRuleIndex() const {
  return TQLParser::RuleSelectClause;
}


std::any TQLParser::SelectClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitSelectClause(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::SelectClauseContext* TQLParser::selectClause() {
  SelectClauseContext *_localctx = _tracker.createInstance<SelectClauseContext>(_ctx, getState());
  enterRule(_localctx, 42, TQLParser::RuleSelectClause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(343);
    match(TQLParser::SELECT);
    setState(344);
    match(TQLParser::LBRACE);
    setState(345);
    selectField();
    setState(350);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(346);
        match(TQLParser::COMMA);
        setState(347);
        selectField(); 
      }
      setState(352);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    }
    setState(354);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TQLParser::COMMA) {
      setState(353);
      match(TQLParser::COMMA);
    }
    setState(356);
    match(TQLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectFieldContext ------------------------------------------------------------------

TQLParser::SelectFieldContext::SelectFieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t TQLParser::SelectFieldContext::getRuleIndex() const {
  return TQLParser::RuleSelectField;
}

void TQLParser::SelectFieldContext::copyFrom(SelectFieldContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- NamedSelectFieldContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::NamedSelectFieldContext::IDENTIFIER() {
  return getToken(TQLParser::IDENTIFIER, 0);
}

tree::TerminalNode* TQLParser::NamedSelectFieldContext::COLON() {
  return getToken(TQLParser::COLON, 0);
}

TQLParser::SelectValueContext* TQLParser::NamedSelectFieldContext::selectValue() {
  return getRuleContext<TQLParser::SelectValueContext>(0);
}

TQLParser::NamedSelectFieldContext::NamedSelectFieldContext(SelectFieldContext *ctx) { copyFrom(ctx); }


std::any TQLParser::NamedSelectFieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitNamedSelectField(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BareSelectFieldContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::BareSelectFieldContext::IDENTIFIER() {
  return getToken(TQLParser::IDENTIFIER, 0);
}

TQLParser::BareSelectFieldContext::BareSelectFieldContext(SelectFieldContext *ctx) { copyFrom(ctx); }


std::any TQLParser::BareSelectFieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitBareSelectField(this);
  else
    return visitor->visitChildren(this);
}
TQLParser::SelectFieldContext* TQLParser::selectField() {
  SelectFieldContext *_localctx = _tracker.createInstance<SelectFieldContext>(_ctx, getState());
  enterRule(_localctx, 44, TQLParser::RuleSelectField);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(362);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<TQLParser::NamedSelectFieldContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(358);
      match(TQLParser::IDENTIFIER);
      setState(359);
      match(TQLParser::COLON);
      setState(360);
      selectValue();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<TQLParser::BareSelectFieldContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(361);
      match(TQLParser::IDENTIFIER);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectValueContext ------------------------------------------------------------------

TQLParser::SelectValueContext::SelectValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TQLParser::ExprContext* TQLParser::SelectValueContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}

tree::TerminalNode* TQLParser::SelectValueContext::LBRACE() {
  return getToken(TQLParser::LBRACE, 0);
}

std::vector<TQLParser::SelectFieldContext *> TQLParser::SelectValueContext::selectField() {
  return getRuleContexts<TQLParser::SelectFieldContext>();
}

TQLParser::SelectFieldContext* TQLParser::SelectValueContext::selectField(size_t i) {
  return getRuleContext<TQLParser::SelectFieldContext>(i);
}

tree::TerminalNode* TQLParser::SelectValueContext::RBRACE() {
  return getToken(TQLParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> TQLParser::SelectValueContext::COMMA() {
  return getTokens(TQLParser::COMMA);
}

tree::TerminalNode* TQLParser::SelectValueContext::COMMA(size_t i) {
  return getToken(TQLParser::COMMA, i);
}


size_t TQLParser::SelectValueContext::getRuleIndex() const {
  return TQLParser::RuleSelectValue;
}


std::any TQLParser::SelectValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitSelectValue(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::SelectValueContext* TQLParser::selectValue() {
  SelectValueContext *_localctx = _tracker.createInstance<SelectValueContext>(_ctx, getState());
  enterRule(_localctx, 46, TQLParser::RuleSelectValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(379);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TQLParser::NULL_:
      case TQLParser::TRUE:
      case TQLParser::FALSE:
      case TQLParser::NOT:
      case TQLParser::GEN_UUID:
      case TQLParser::NOW:
      case TQLParser::MATCH_FN:
      case TQLParser::EMBED:
      case TQLParser::PROMPT:
      case TQLParser::COUNT:
      case TQLParser::SUM:
      case TQLParser::AVG:
      case TQLParser::MIN_FN:
      case TQLParser::MAX_FN:
      case TQLParser::MINUS:
      case TQLParser::LPAREN:
      case TQLParser::LBRACKET:
      case TQLParser::FLOAT_LIT:
      case TQLParser::INTEGER_LIT:
      case TQLParser::STRING_LIT:
      case TQLParser::SINGLE_STRING_LIT:
      case TQLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(364);
        expr(0);
        break;
      }

      case TQLParser::LBRACE: {
        enterOuterAlt(_localctx, 2);
        setState(365);
        match(TQLParser::LBRACE);
        setState(366);
        selectField();
        setState(371);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(367);
            match(TQLParser::COMMA);
            setState(368);
            selectField(); 
          }
          setState(373);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
        }
        setState(375);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == TQLParser::COMMA) {
          setState(374);
          match(TQLParser::COMMA);
        }
        setState(377);
        match(TQLParser::RBRACE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OrderByClauseContext ------------------------------------------------------------------

TQLParser::OrderByClauseContext::OrderByClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::OrderByClauseContext::ORDER() {
  return getToken(TQLParser::ORDER, 0);
}

tree::TerminalNode* TQLParser::OrderByClauseContext::BY() {
  return getToken(TQLParser::BY, 0);
}

std::vector<TQLParser::OrderByItemContext *> TQLParser::OrderByClauseContext::orderByItem() {
  return getRuleContexts<TQLParser::OrderByItemContext>();
}

TQLParser::OrderByItemContext* TQLParser::OrderByClauseContext::orderByItem(size_t i) {
  return getRuleContext<TQLParser::OrderByItemContext>(i);
}

std::vector<tree::TerminalNode *> TQLParser::OrderByClauseContext::COMMA() {
  return getTokens(TQLParser::COMMA);
}

tree::TerminalNode* TQLParser::OrderByClauseContext::COMMA(size_t i) {
  return getToken(TQLParser::COMMA, i);
}


size_t TQLParser::OrderByClauseContext::getRuleIndex() const {
  return TQLParser::RuleOrderByClause;
}


std::any TQLParser::OrderByClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitOrderByClause(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::OrderByClauseContext* TQLParser::orderByClause() {
  OrderByClauseContext *_localctx = _tracker.createInstance<OrderByClauseContext>(_ctx, getState());
  enterRule(_localctx, 48, TQLParser::RuleOrderByClause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(381);
    match(TQLParser::ORDER);
    setState(382);
    match(TQLParser::BY);
    setState(383);
    orderByItem();
    setState(388);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TQLParser::COMMA) {
      setState(384);
      match(TQLParser::COMMA);
      setState(385);
      orderByItem();
      setState(390);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OrderByItemContext ------------------------------------------------------------------

TQLParser::OrderByItemContext::OrderByItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t TQLParser::OrderByItemContext::getRuleIndex() const {
  return TQLParser::RuleOrderByItem;
}

void TQLParser::OrderByItemContext::copyFrom(OrderByItemContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ScalarOrderByItemContext ------------------------------------------------------------------

TQLParser::ExprContext* TQLParser::ScalarOrderByItemContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}

tree::TerminalNode* TQLParser::ScalarOrderByItemContext::ASC() {
  return getToken(TQLParser::ASC, 0);
}

tree::TerminalNode* TQLParser::ScalarOrderByItemContext::DESC() {
  return getToken(TQLParser::DESC, 0);
}

TQLParser::ScalarOrderByItemContext::ScalarOrderByItemContext(OrderByItemContext *ctx) { copyFrom(ctx); }


std::any TQLParser::ScalarOrderByItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitScalarOrderByItem(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VectorOrderByItemContext ------------------------------------------------------------------

std::vector<TQLParser::ExprContext *> TQLParser::VectorOrderByItemContext::expr() {
  return getRuleContexts<TQLParser::ExprContext>();
}

TQLParser::ExprContext* TQLParser::VectorOrderByItemContext::expr(size_t i) {
  return getRuleContext<TQLParser::ExprContext>(i);
}

tree::TerminalNode* TQLParser::VectorOrderByItemContext::VEC_DIST() {
  return getToken(TQLParser::VEC_DIST, 0);
}

tree::TerminalNode* TQLParser::VectorOrderByItemContext::ASC() {
  return getToken(TQLParser::ASC, 0);
}

tree::TerminalNode* TQLParser::VectorOrderByItemContext::DESC() {
  return getToken(TQLParser::DESC, 0);
}

TQLParser::VectorOrderByItemContext::VectorOrderByItemContext(OrderByItemContext *ctx) { copyFrom(ctx); }


std::any TQLParser::VectorOrderByItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitVectorOrderByItem(this);
  else
    return visitor->visitChildren(this);
}
TQLParser::OrderByItemContext* TQLParser::orderByItem() {
  OrderByItemContext *_localctx = _tracker.createInstance<OrderByItemContext>(_ctx, getState());
  enterRule(_localctx, 50, TQLParser::RuleOrderByItem);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(401);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<TQLParser::VectorOrderByItemContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(391);
      expr(0);
      setState(392);
      match(TQLParser::VEC_DIST);
      setState(393);
      expr(0);
      setState(395);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == TQLParser::ASC

      || _la == TQLParser::DESC) {
        setState(394);
        _la = _input->LA(1);
        if (!(_la == TQLParser::ASC

        || _la == TQLParser::DESC)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
      }
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<TQLParser::ScalarOrderByItemContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(397);
      expr(0);
      setState(399);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == TQLParser::ASC

      || _la == TQLParser::DESC) {
        setState(398);
        _la = _input->LA(1);
        if (!(_la == TQLParser::ASC

        || _la == TQLParser::DESC)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
      }
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LimitClauseContext ------------------------------------------------------------------

TQLParser::LimitClauseContext::LimitClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::LimitClauseContext::LIMIT() {
  return getToken(TQLParser::LIMIT, 0);
}

tree::TerminalNode* TQLParser::LimitClauseContext::INTEGER_LIT() {
  return getToken(TQLParser::INTEGER_LIT, 0);
}


size_t TQLParser::LimitClauseContext::getRuleIndex() const {
  return TQLParser::RuleLimitClause;
}


std::any TQLParser::LimitClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitLimitClause(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::LimitClauseContext* TQLParser::limitClause() {
  LimitClauseContext *_localctx = _tracker.createInstance<LimitClauseContext>(_ctx, getState());
  enterRule(_localctx, 52, TQLParser::RuleLimitClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(403);
    match(TQLParser::LIMIT);
    setState(404);
    match(TQLParser::INTEGER_LIT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertStatementContext ------------------------------------------------------------------

TQLParser::InsertStatementContext::InsertStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::InsertStatementContext::INSERT() {
  return getToken(TQLParser::INSERT, 0);
}

tree::TerminalNode* TQLParser::InsertStatementContext::INTO() {
  return getToken(TQLParser::INTO, 0);
}

TQLParser::PathBindingContext* TQLParser::InsertStatementContext::pathBinding() {
  return getRuleContext<TQLParser::PathBindingContext>(0);
}

TQLParser::InsertBodyContext* TQLParser::InsertStatementContext::insertBody() {
  return getRuleContext<TQLParser::InsertBodyContext>(0);
}

TQLParser::ReturningClauseContext* TQLParser::InsertStatementContext::returningClause() {
  return getRuleContext<TQLParser::ReturningClauseContext>(0);
}


size_t TQLParser::InsertStatementContext::getRuleIndex() const {
  return TQLParser::RuleInsertStatement;
}


std::any TQLParser::InsertStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitInsertStatement(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::InsertStatementContext* TQLParser::insertStatement() {
  InsertStatementContext *_localctx = _tracker.createInstance<InsertStatementContext>(_ctx, getState());
  enterRule(_localctx, 54, TQLParser::RuleInsertStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(406);
    match(TQLParser::INSERT);
    setState(407);
    match(TQLParser::INTO);
    setState(408);
    pathBinding();
    setState(409);
    insertBody();
    setState(411);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TQLParser::RETURNING) {
      setState(410);
      returningClause();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertBodyContext ------------------------------------------------------------------

TQLParser::InsertBodyContext::InsertBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t TQLParser::InsertBodyContext::getRuleIndex() const {
  return TQLParser::RuleInsertBody;
}

void TQLParser::InsertBodyContext::copyFrom(InsertBodyContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- InsertLiteralBodyContext ------------------------------------------------------------------

TQLParser::InsertRowsContext* TQLParser::InsertLiteralBodyContext::insertRows() {
  return getRuleContext<TQLParser::InsertRowsContext>(0);
}

TQLParser::InsertLiteralBodyContext::InsertLiteralBodyContext(InsertBodyContext *ctx) { copyFrom(ctx); }


std::any TQLParser::InsertLiteralBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitInsertLiteralBody(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InsertFromBodyAltContext ------------------------------------------------------------------

TQLParser::InsertFromBodyContext* TQLParser::InsertFromBodyAltContext::insertFromBody() {
  return getRuleContext<TQLParser::InsertFromBodyContext>(0);
}

TQLParser::InsertFromBodyAltContext::InsertFromBodyAltContext(InsertBodyContext *ctx) { copyFrom(ctx); }


std::any TQLParser::InsertFromBodyAltContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitInsertFromBodyAlt(this);
  else
    return visitor->visitChildren(this);
}
TQLParser::InsertBodyContext* TQLParser::insertBody() {
  InsertBodyContext *_localctx = _tracker.createInstance<InsertBodyContext>(_ctx, getState());
  enterRule(_localctx, 56, TQLParser::RuleInsertBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(415);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TQLParser::LBRACE: {
        _localctx = _tracker.createInstance<TQLParser::InsertLiteralBodyContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(413);
        insertRows();
        break;
      }

      case TQLParser::FROM: {
        _localctx = _tracker.createInstance<TQLParser::InsertFromBodyAltContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(414);
        insertFromBody();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertRowsContext ------------------------------------------------------------------

TQLParser::InsertRowsContext::InsertRowsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t TQLParser::InsertRowsContext::getRuleIndex() const {
  return TQLParser::RuleInsertRows;
}

void TQLParser::InsertRowsContext::copyFrom(InsertRowsContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SingleRowInsertContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::SingleRowInsertContext::LBRACE() {
  return getToken(TQLParser::LBRACE, 0);
}

std::vector<TQLParser::RowFieldContext *> TQLParser::SingleRowInsertContext::rowField() {
  return getRuleContexts<TQLParser::RowFieldContext>();
}

TQLParser::RowFieldContext* TQLParser::SingleRowInsertContext::rowField(size_t i) {
  return getRuleContext<TQLParser::RowFieldContext>(i);
}

tree::TerminalNode* TQLParser::SingleRowInsertContext::RBRACE() {
  return getToken(TQLParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> TQLParser::SingleRowInsertContext::COMMA() {
  return getTokens(TQLParser::COMMA);
}

tree::TerminalNode* TQLParser::SingleRowInsertContext::COMMA(size_t i) {
  return getToken(TQLParser::COMMA, i);
}

TQLParser::SingleRowInsertContext::SingleRowInsertContext(InsertRowsContext *ctx) { copyFrom(ctx); }


std::any TQLParser::SingleRowInsertContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitSingleRowInsert(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MultiRowInsertContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::MultiRowInsertContext::LBRACE() {
  return getToken(TQLParser::LBRACE, 0);
}

std::vector<TQLParser::RowBlockContext *> TQLParser::MultiRowInsertContext::rowBlock() {
  return getRuleContexts<TQLParser::RowBlockContext>();
}

TQLParser::RowBlockContext* TQLParser::MultiRowInsertContext::rowBlock(size_t i) {
  return getRuleContext<TQLParser::RowBlockContext>(i);
}

tree::TerminalNode* TQLParser::MultiRowInsertContext::RBRACE() {
  return getToken(TQLParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> TQLParser::MultiRowInsertContext::COMMA() {
  return getTokens(TQLParser::COMMA);
}

tree::TerminalNode* TQLParser::MultiRowInsertContext::COMMA(size_t i) {
  return getToken(TQLParser::COMMA, i);
}

TQLParser::MultiRowInsertContext::MultiRowInsertContext(InsertRowsContext *ctx) { copyFrom(ctx); }


std::any TQLParser::MultiRowInsertContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitMultiRowInsert(this);
  else
    return visitor->visitChildren(this);
}
TQLParser::InsertRowsContext* TQLParser::insertRows() {
  InsertRowsContext *_localctx = _tracker.createInstance<InsertRowsContext>(_ctx, getState());
  enterRule(_localctx, 58, TQLParser::RuleInsertRows);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(445);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<TQLParser::SingleRowInsertContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(417);
      match(TQLParser::LBRACE);
      setState(418);
      rowField();
      setState(423);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(419);
          match(TQLParser::COMMA);
          setState(420);
          rowField(); 
        }
        setState(425);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
      }
      setState(427);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == TQLParser::COMMA) {
        setState(426);
        match(TQLParser::COMMA);
      }
      setState(429);
      match(TQLParser::RBRACE);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<TQLParser::MultiRowInsertContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(431);
      match(TQLParser::LBRACE);
      setState(432);
      rowBlock();
      setState(437);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(433);
          match(TQLParser::COMMA);
          setState(434);
          rowBlock(); 
        }
        setState(439);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
      }
      setState(441);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == TQLParser::COMMA) {
        setState(440);
        match(TQLParser::COMMA);
      }
      setState(443);
      match(TQLParser::RBRACE);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RowBlockContext ------------------------------------------------------------------

TQLParser::RowBlockContext::RowBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::RowBlockContext::LBRACE() {
  return getToken(TQLParser::LBRACE, 0);
}

std::vector<TQLParser::RowFieldContext *> TQLParser::RowBlockContext::rowField() {
  return getRuleContexts<TQLParser::RowFieldContext>();
}

TQLParser::RowFieldContext* TQLParser::RowBlockContext::rowField(size_t i) {
  return getRuleContext<TQLParser::RowFieldContext>(i);
}

tree::TerminalNode* TQLParser::RowBlockContext::RBRACE() {
  return getToken(TQLParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> TQLParser::RowBlockContext::COMMA() {
  return getTokens(TQLParser::COMMA);
}

tree::TerminalNode* TQLParser::RowBlockContext::COMMA(size_t i) {
  return getToken(TQLParser::COMMA, i);
}


size_t TQLParser::RowBlockContext::getRuleIndex() const {
  return TQLParser::RuleRowBlock;
}


std::any TQLParser::RowBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitRowBlock(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::RowBlockContext* TQLParser::rowBlock() {
  RowBlockContext *_localctx = _tracker.createInstance<RowBlockContext>(_ctx, getState());
  enterRule(_localctx, 60, TQLParser::RuleRowBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(447);
    match(TQLParser::LBRACE);
    setState(448);
    rowField();
    setState(453);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(449);
        match(TQLParser::COMMA);
        setState(450);
        rowField(); 
      }
      setState(455);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx);
    }
    setState(457);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TQLParser::COMMA) {
      setState(456);
      match(TQLParser::COMMA);
    }
    setState(459);
    match(TQLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RowFieldContext ------------------------------------------------------------------

TQLParser::RowFieldContext::RowFieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::RowFieldContext::IDENTIFIER() {
  return getToken(TQLParser::IDENTIFIER, 0);
}

tree::TerminalNode* TQLParser::RowFieldContext::COLON() {
  return getToken(TQLParser::COLON, 0);
}

TQLParser::ExprContext* TQLParser::RowFieldContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}


size_t TQLParser::RowFieldContext::getRuleIndex() const {
  return TQLParser::RuleRowField;
}


std::any TQLParser::RowFieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitRowField(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::RowFieldContext* TQLParser::rowField() {
  RowFieldContext *_localctx = _tracker.createInstance<RowFieldContext>(_ctx, getState());
  enterRule(_localctx, 62, TQLParser::RuleRowField);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(461);
    match(TQLParser::IDENTIFIER);
    setState(462);
    match(TQLParser::COLON);
    setState(463);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertFromBodyContext ------------------------------------------------------------------

TQLParser::InsertFromBodyContext::InsertFromBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TQLParser::FromClauseContext* TQLParser::InsertFromBodyContext::fromClause() {
  return getRuleContext<TQLParser::FromClauseContext>(0);
}

TQLParser::SelectClauseContext* TQLParser::InsertFromBodyContext::selectClause() {
  return getRuleContext<TQLParser::SelectClauseContext>(0);
}

std::vector<TQLParser::JoinClauseContext *> TQLParser::InsertFromBodyContext::joinClause() {
  return getRuleContexts<TQLParser::JoinClauseContext>();
}

TQLParser::JoinClauseContext* TQLParser::InsertFromBodyContext::joinClause(size_t i) {
  return getRuleContext<TQLParser::JoinClauseContext>(i);
}

TQLParser::WhereClauseContext* TQLParser::InsertFromBodyContext::whereClause() {
  return getRuleContext<TQLParser::WhereClauseContext>(0);
}

std::vector<TQLParser::LetClauseContext *> TQLParser::InsertFromBodyContext::letClause() {
  return getRuleContexts<TQLParser::LetClauseContext>();
}

TQLParser::LetClauseContext* TQLParser::InsertFromBodyContext::letClause(size_t i) {
  return getRuleContext<TQLParser::LetClauseContext>(i);
}


size_t TQLParser::InsertFromBodyContext::getRuleIndex() const {
  return TQLParser::RuleInsertFromBody;
}


std::any TQLParser::InsertFromBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitInsertFromBody(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::InsertFromBodyContext* TQLParser::insertFromBody() {
  InsertFromBodyContext *_localctx = _tracker.createInstance<InsertFromBodyContext>(_ctx, getState());
  enterRule(_localctx, 64, TQLParser::RuleInsertFromBody);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(465);
    fromClause();
    setState(469);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TQLParser::JOIN

    || _la == TQLParser::LEFT) {
      setState(466);
      joinClause();
      setState(471);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(473);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TQLParser::WHERE) {
      setState(472);
      whereClause();
    }
    setState(478);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TQLParser::LET) {
      setState(475);
      letClause();
      setState(480);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(481);
    selectClause();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UpdateStatementContext ------------------------------------------------------------------

TQLParser::UpdateStatementContext::UpdateStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::UpdateStatementContext::UPDATE() {
  return getToken(TQLParser::UPDATE, 0);
}

TQLParser::PathBindingContext* TQLParser::UpdateStatementContext::pathBinding() {
  return getRuleContext<TQLParser::PathBindingContext>(0);
}

TQLParser::SetClauseContext* TQLParser::UpdateStatementContext::setClause() {
  return getRuleContext<TQLParser::SetClauseContext>(0);
}

TQLParser::WhereClauseContext* TQLParser::UpdateStatementContext::whereClause() {
  return getRuleContext<TQLParser::WhereClauseContext>(0);
}

std::vector<TQLParser::LetClauseContext *> TQLParser::UpdateStatementContext::letClause() {
  return getRuleContexts<TQLParser::LetClauseContext>();
}

TQLParser::LetClauseContext* TQLParser::UpdateStatementContext::letClause(size_t i) {
  return getRuleContext<TQLParser::LetClauseContext>(i);
}

TQLParser::ReturningClauseContext* TQLParser::UpdateStatementContext::returningClause() {
  return getRuleContext<TQLParser::ReturningClauseContext>(0);
}


size_t TQLParser::UpdateStatementContext::getRuleIndex() const {
  return TQLParser::RuleUpdateStatement;
}


std::any TQLParser::UpdateStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitUpdateStatement(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::UpdateStatementContext* TQLParser::updateStatement() {
  UpdateStatementContext *_localctx = _tracker.createInstance<UpdateStatementContext>(_ctx, getState());
  enterRule(_localctx, 66, TQLParser::RuleUpdateStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(483);
    match(TQLParser::UPDATE);
    setState(484);
    pathBinding();
    setState(486);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TQLParser::WHERE) {
      setState(485);
      whereClause();
    }
    setState(491);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TQLParser::LET) {
      setState(488);
      letClause();
      setState(493);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(494);
    setClause();
    setState(496);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TQLParser::RETURNING) {
      setState(495);
      returningClause();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SetClauseContext ------------------------------------------------------------------

TQLParser::SetClauseContext::SetClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::SetClauseContext::SET() {
  return getToken(TQLParser::SET, 0);
}

tree::TerminalNode* TQLParser::SetClauseContext::LBRACE() {
  return getToken(TQLParser::LBRACE, 0);
}

std::vector<TQLParser::SetFieldContext *> TQLParser::SetClauseContext::setField() {
  return getRuleContexts<TQLParser::SetFieldContext>();
}

TQLParser::SetFieldContext* TQLParser::SetClauseContext::setField(size_t i) {
  return getRuleContext<TQLParser::SetFieldContext>(i);
}

tree::TerminalNode* TQLParser::SetClauseContext::RBRACE() {
  return getToken(TQLParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> TQLParser::SetClauseContext::COMMA() {
  return getTokens(TQLParser::COMMA);
}

tree::TerminalNode* TQLParser::SetClauseContext::COMMA(size_t i) {
  return getToken(TQLParser::COMMA, i);
}


size_t TQLParser::SetClauseContext::getRuleIndex() const {
  return TQLParser::RuleSetClause;
}


std::any TQLParser::SetClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitSetClause(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::SetClauseContext* TQLParser::setClause() {
  SetClauseContext *_localctx = _tracker.createInstance<SetClauseContext>(_ctx, getState());
  enterRule(_localctx, 68, TQLParser::RuleSetClause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(498);
    match(TQLParser::SET);
    setState(499);
    match(TQLParser::LBRACE);
    setState(500);
    setField();
    setState(505);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(501);
        match(TQLParser::COMMA);
        setState(502);
        setField(); 
      }
      setState(507);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx);
    }
    setState(509);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TQLParser::COMMA) {
      setState(508);
      match(TQLParser::COMMA);
    }
    setState(511);
    match(TQLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SetFieldContext ------------------------------------------------------------------

TQLParser::SetFieldContext::SetFieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::SetFieldContext::IDENTIFIER() {
  return getToken(TQLParser::IDENTIFIER, 0);
}

tree::TerminalNode* TQLParser::SetFieldContext::COLON() {
  return getToken(TQLParser::COLON, 0);
}

TQLParser::ExprContext* TQLParser::SetFieldContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}


size_t TQLParser::SetFieldContext::getRuleIndex() const {
  return TQLParser::RuleSetField;
}


std::any TQLParser::SetFieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitSetField(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::SetFieldContext* TQLParser::setField() {
  SetFieldContext *_localctx = _tracker.createInstance<SetFieldContext>(_ctx, getState());
  enterRule(_localctx, 70, TQLParser::RuleSetField);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(513);
    match(TQLParser::IDENTIFIER);
    setState(514);
    match(TQLParser::COLON);
    setState(515);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeleteStatementContext ------------------------------------------------------------------

TQLParser::DeleteStatementContext::DeleteStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::DeleteStatementContext::DELETE() {
  return getToken(TQLParser::DELETE, 0);
}

tree::TerminalNode* TQLParser::DeleteStatementContext::FROM() {
  return getToken(TQLParser::FROM, 0);
}

TQLParser::PathBindingContext* TQLParser::DeleteStatementContext::pathBinding() {
  return getRuleContext<TQLParser::PathBindingContext>(0);
}

TQLParser::WhereClauseContext* TQLParser::DeleteStatementContext::whereClause() {
  return getRuleContext<TQLParser::WhereClauseContext>(0);
}

TQLParser::ReturningClauseContext* TQLParser::DeleteStatementContext::returningClause() {
  return getRuleContext<TQLParser::ReturningClauseContext>(0);
}


size_t TQLParser::DeleteStatementContext::getRuleIndex() const {
  return TQLParser::RuleDeleteStatement;
}


std::any TQLParser::DeleteStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitDeleteStatement(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::DeleteStatementContext* TQLParser::deleteStatement() {
  DeleteStatementContext *_localctx = _tracker.createInstance<DeleteStatementContext>(_ctx, getState());
  enterRule(_localctx, 72, TQLParser::RuleDeleteStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(517);
    match(TQLParser::DELETE);
    setState(518);
    match(TQLParser::FROM);
    setState(519);
    pathBinding();
    setState(520);
    whereClause();
    setState(522);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TQLParser::RETURNING) {
      setState(521);
      returningClause();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UpsertStatementContext ------------------------------------------------------------------

TQLParser::UpsertStatementContext::UpsertStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::UpsertStatementContext::UPSERT() {
  return getToken(TQLParser::UPSERT, 0);
}

tree::TerminalNode* TQLParser::UpsertStatementContext::INTO() {
  return getToken(TQLParser::INTO, 0);
}

TQLParser::PathBindingContext* TQLParser::UpsertStatementContext::pathBinding() {
  return getRuleContext<TQLParser::PathBindingContext>(0);
}

std::vector<tree::TerminalNode *> TQLParser::UpsertStatementContext::CONFLICT() {
  return getTokens(TQLParser::CONFLICT);
}

tree::TerminalNode* TQLParser::UpsertStatementContext::CONFLICT(size_t i) {
  return getToken(TQLParser::CONFLICT, i);
}

tree::TerminalNode* TQLParser::UpsertStatementContext::ON() {
  return getToken(TQLParser::ON, 0);
}

tree::TerminalNode* TQLParser::UpsertStatementContext::IDENTIFIER() {
  return getToken(TQLParser::IDENTIFIER, 0);
}

tree::TerminalNode* TQLParser::UpsertStatementContext::VALUES() {
  return getToken(TQLParser::VALUES, 0);
}

TQLParser::RowBlockContext* TQLParser::UpsertStatementContext::rowBlock() {
  return getRuleContext<TQLParser::RowBlockContext>(0);
}

tree::TerminalNode* TQLParser::UpsertStatementContext::SET() {
  return getToken(TQLParser::SET, 0);
}

tree::TerminalNode* TQLParser::UpsertStatementContext::LBRACE() {
  return getToken(TQLParser::LBRACE, 0);
}

std::vector<TQLParser::SetFieldContext *> TQLParser::UpsertStatementContext::setField() {
  return getRuleContexts<TQLParser::SetFieldContext>();
}

TQLParser::SetFieldContext* TQLParser::UpsertStatementContext::setField(size_t i) {
  return getRuleContext<TQLParser::SetFieldContext>(i);
}

tree::TerminalNode* TQLParser::UpsertStatementContext::RBRACE() {
  return getToken(TQLParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> TQLParser::UpsertStatementContext::COMMA() {
  return getTokens(TQLParser::COMMA);
}

tree::TerminalNode* TQLParser::UpsertStatementContext::COMMA(size_t i) {
  return getToken(TQLParser::COMMA, i);
}

TQLParser::ReturningClauseContext* TQLParser::UpsertStatementContext::returningClause() {
  return getRuleContext<TQLParser::ReturningClauseContext>(0);
}


size_t TQLParser::UpsertStatementContext::getRuleIndex() const {
  return TQLParser::RuleUpsertStatement;
}


std::any TQLParser::UpsertStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitUpsertStatement(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::UpsertStatementContext* TQLParser::upsertStatement() {
  UpsertStatementContext *_localctx = _tracker.createInstance<UpsertStatementContext>(_ctx, getState());
  enterRule(_localctx, 74, TQLParser::RuleUpsertStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(524);
    match(TQLParser::UPSERT);
    setState(525);
    match(TQLParser::INTO);
    setState(526);
    pathBinding();
    setState(527);
    match(TQLParser::CONFLICT);
    setState(528);
    match(TQLParser::ON);
    setState(529);
    match(TQLParser::IDENTIFIER);
    setState(530);
    match(TQLParser::VALUES);
    setState(531);
    rowBlock();
    setState(532);
    match(TQLParser::CONFLICT);
    setState(533);
    match(TQLParser::SET);
    setState(534);
    match(TQLParser::LBRACE);
    setState(535);
    setField();
    setState(540);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(536);
        match(TQLParser::COMMA);
        setState(537);
        setField(); 
      }
      setState(542);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx);
    }
    setState(544);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TQLParser::COMMA) {
      setState(543);
      match(TQLParser::COMMA);
    }
    setState(546);
    match(TQLParser::RBRACE);
    setState(548);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TQLParser::RETURNING) {
      setState(547);
      returningClause();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturningClauseContext ------------------------------------------------------------------

TQLParser::ReturningClauseContext::ReturningClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::ReturningClauseContext::RETURNING() {
  return getToken(TQLParser::RETURNING, 0);
}

tree::TerminalNode* TQLParser::ReturningClauseContext::LBRACE() {
  return getToken(TQLParser::LBRACE, 0);
}

std::vector<TQLParser::ReturningFieldContext *> TQLParser::ReturningClauseContext::returningField() {
  return getRuleContexts<TQLParser::ReturningFieldContext>();
}

TQLParser::ReturningFieldContext* TQLParser::ReturningClauseContext::returningField(size_t i) {
  return getRuleContext<TQLParser::ReturningFieldContext>(i);
}

tree::TerminalNode* TQLParser::ReturningClauseContext::RBRACE() {
  return getToken(TQLParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> TQLParser::ReturningClauseContext::COMMA() {
  return getTokens(TQLParser::COMMA);
}

tree::TerminalNode* TQLParser::ReturningClauseContext::COMMA(size_t i) {
  return getToken(TQLParser::COMMA, i);
}


size_t TQLParser::ReturningClauseContext::getRuleIndex() const {
  return TQLParser::RuleReturningClause;
}


std::any TQLParser::ReturningClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitReturningClause(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::ReturningClauseContext* TQLParser::returningClause() {
  ReturningClauseContext *_localctx = _tracker.createInstance<ReturningClauseContext>(_ctx, getState());
  enterRule(_localctx, 76, TQLParser::RuleReturningClause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(550);
    match(TQLParser::RETURNING);
    setState(551);
    match(TQLParser::LBRACE);
    setState(552);
    returningField();
    setState(557);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(553);
        match(TQLParser::COMMA);
        setState(554);
        returningField(); 
      }
      setState(559);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx);
    }
    setState(561);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TQLParser::COMMA) {
      setState(560);
      match(TQLParser::COMMA);
    }
    setState(563);
    match(TQLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturningFieldContext ------------------------------------------------------------------

TQLParser::ReturningFieldContext::ReturningFieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t TQLParser::ReturningFieldContext::getRuleIndex() const {
  return TQLParser::RuleReturningField;
}

void TQLParser::ReturningFieldContext::copyFrom(ReturningFieldContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- NamedReturningFieldContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::NamedReturningFieldContext::IDENTIFIER() {
  return getToken(TQLParser::IDENTIFIER, 0);
}

tree::TerminalNode* TQLParser::NamedReturningFieldContext::COLON() {
  return getToken(TQLParser::COLON, 0);
}

TQLParser::ExprContext* TQLParser::NamedReturningFieldContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}

TQLParser::NamedReturningFieldContext::NamedReturningFieldContext(ReturningFieldContext *ctx) { copyFrom(ctx); }


std::any TQLParser::NamedReturningFieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitNamedReturningField(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MutationReturningFieldContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::MutationReturningFieldContext::MUTATION_FIELD() {
  return getToken(TQLParser::MUTATION_FIELD, 0);
}

TQLParser::MutationReturningFieldContext::MutationReturningFieldContext(ReturningFieldContext *ctx) { copyFrom(ctx); }


std::any TQLParser::MutationReturningFieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitMutationReturningField(this);
  else
    return visitor->visitChildren(this);
}
TQLParser::ReturningFieldContext* TQLParser::returningField() {
  ReturningFieldContext *_localctx = _tracker.createInstance<ReturningFieldContext>(_ctx, getState());
  enterRule(_localctx, 78, TQLParser::RuleReturningField);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(569);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TQLParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<TQLParser::NamedReturningFieldContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(565);
        match(TQLParser::IDENTIFIER);
        setState(566);
        match(TQLParser::COLON);
        setState(567);
        expr(0);
        break;
      }

      case TQLParser::MUTATION_FIELD: {
        _localctx = _tracker.createInstance<TQLParser::MutationReturningFieldContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(568);
        match(TQLParser::MUTATION_FIELD);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateTableStatementContext ------------------------------------------------------------------

TQLParser::CreateTableStatementContext::CreateTableStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::CreateTableStatementContext::CREATE() {
  return getToken(TQLParser::CREATE, 0);
}

tree::TerminalNode* TQLParser::CreateTableStatementContext::TABLE() {
  return getToken(TQLParser::TABLE, 0);
}

tree::TerminalNode* TQLParser::CreateTableStatementContext::STRING_LIT() {
  return getToken(TQLParser::STRING_LIT, 0);
}

tree::TerminalNode* TQLParser::CreateTableStatementContext::AS() {
  return getToken(TQLParser::AS, 0);
}

TQLParser::QualifiedTypeNameContext* TQLParser::CreateTableStatementContext::qualifiedTypeName() {
  return getRuleContext<TQLParser::QualifiedTypeNameContext>(0);
}


size_t TQLParser::CreateTableStatementContext::getRuleIndex() const {
  return TQLParser::RuleCreateTableStatement;
}


std::any TQLParser::CreateTableStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitCreateTableStatement(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::CreateTableStatementContext* TQLParser::createTableStatement() {
  CreateTableStatementContext *_localctx = _tracker.createInstance<CreateTableStatementContext>(_ctx, getState());
  enterRule(_localctx, 80, TQLParser::RuleCreateTableStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(571);
    match(TQLParser::CREATE);
    setState(572);
    match(TQLParser::TABLE);
    setState(573);
    match(TQLParser::STRING_LIT);
    setState(574);
    match(TQLParser::AS);
    setState(575);
    qualifiedTypeName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateRoleStatementContext ------------------------------------------------------------------

TQLParser::CreateRoleStatementContext::CreateRoleStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::CreateRoleStatementContext::CREATE() {
  return getToken(TQLParser::CREATE, 0);
}

tree::TerminalNode* TQLParser::CreateRoleStatementContext::ROLE() {
  return getToken(TQLParser::ROLE, 0);
}

tree::TerminalNode* TQLParser::CreateRoleStatementContext::IDENTIFIER() {
  return getToken(TQLParser::IDENTIFIER, 0);
}


size_t TQLParser::CreateRoleStatementContext::getRuleIndex() const {
  return TQLParser::RuleCreateRoleStatement;
}


std::any TQLParser::CreateRoleStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitCreateRoleStatement(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::CreateRoleStatementContext* TQLParser::createRoleStatement() {
  CreateRoleStatementContext *_localctx = _tracker.createInstance<CreateRoleStatementContext>(_ctx, getState());
  enterRule(_localctx, 82, TQLParser::RuleCreateRoleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(577);
    match(TQLParser::CREATE);
    setState(578);
    match(TQLParser::ROLE);
    setState(579);
    match(TQLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GrantStatementContext ------------------------------------------------------------------

TQLParser::GrantStatementContext::GrantStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::GrantStatementContext::GRANT() {
  return getToken(TQLParser::GRANT, 0);
}

tree::TerminalNode* TQLParser::GrantStatementContext::TO() {
  return getToken(TQLParser::TO, 0);
}

tree::TerminalNode* TQLParser::GrantStatementContext::IDENTIFIER() {
  return getToken(TQLParser::IDENTIFIER, 0);
}

tree::TerminalNode* TQLParser::GrantStatementContext::LBRACE() {
  return getToken(TQLParser::LBRACE, 0);
}

tree::TerminalNode* TQLParser::GrantStatementContext::RBRACE() {
  return getToken(TQLParser::RBRACE, 0);
}

std::vector<TQLParser::GrantRuleContext *> TQLParser::GrantStatementContext::grantRule() {
  return getRuleContexts<TQLParser::GrantRuleContext>();
}

TQLParser::GrantRuleContext* TQLParser::GrantStatementContext::grantRule(size_t i) {
  return getRuleContext<TQLParser::GrantRuleContext>(i);
}


size_t TQLParser::GrantStatementContext::getRuleIndex() const {
  return TQLParser::RuleGrantStatement;
}


std::any TQLParser::GrantStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitGrantStatement(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::GrantStatementContext* TQLParser::grantStatement() {
  GrantStatementContext *_localctx = _tracker.createInstance<GrantStatementContext>(_ctx, getState());
  enterRule(_localctx, 84, TQLParser::RuleGrantStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(581);
    match(TQLParser::GRANT);
    setState(582);
    match(TQLParser::TO);
    setState(583);
    match(TQLParser::IDENTIFIER);
    setState(584);
    match(TQLParser::LBRACE);
    setState(586); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(585);
      grantRule();
      setState(588); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == TQLParser::ALLOW

    || _la == TQLParser::DENY);
    setState(590);
    match(TQLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GrantRuleContext ------------------------------------------------------------------

TQLParser::GrantRuleContext::GrantRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TQLParser::OperationListContext* TQLParser::GrantRuleContext::operationList() {
  return getRuleContext<TQLParser::OperationListContext>(0);
}

tree::TerminalNode* TQLParser::GrantRuleContext::ON() {
  return getToken(TQLParser::ON, 0);
}

tree::TerminalNode* TQLParser::GrantRuleContext::STRING_LIT() {
  return getToken(TQLParser::STRING_LIT, 0);
}

tree::TerminalNode* TQLParser::GrantRuleContext::ALLOW() {
  return getToken(TQLParser::ALLOW, 0);
}

tree::TerminalNode* TQLParser::GrantRuleContext::DENY() {
  return getToken(TQLParser::DENY, 0);
}


size_t TQLParser::GrantRuleContext::getRuleIndex() const {
  return TQLParser::RuleGrantRule;
}


std::any TQLParser::GrantRuleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitGrantRule(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::GrantRuleContext* TQLParser::grantRule() {
  GrantRuleContext *_localctx = _tracker.createInstance<GrantRuleContext>(_ctx, getState());
  enterRule(_localctx, 86, TQLParser::RuleGrantRule);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(592);
    _la = _input->LA(1);
    if (!(_la == TQLParser::ALLOW

    || _la == TQLParser::DENY)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(593);
    operationList();
    setState(594);
    match(TQLParser::ON);
    setState(595);
    match(TQLParser::STRING_LIT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperationListContext ------------------------------------------------------------------

TQLParser::OperationListContext::OperationListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<TQLParser::OperationContext *> TQLParser::OperationListContext::operation() {
  return getRuleContexts<TQLParser::OperationContext>();
}

TQLParser::OperationContext* TQLParser::OperationListContext::operation(size_t i) {
  return getRuleContext<TQLParser::OperationContext>(i);
}

std::vector<tree::TerminalNode *> TQLParser::OperationListContext::COMMA() {
  return getTokens(TQLParser::COMMA);
}

tree::TerminalNode* TQLParser::OperationListContext::COMMA(size_t i) {
  return getToken(TQLParser::COMMA, i);
}


size_t TQLParser::OperationListContext::getRuleIndex() const {
  return TQLParser::RuleOperationList;
}


std::any TQLParser::OperationListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitOperationList(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::OperationListContext* TQLParser::operationList() {
  OperationListContext *_localctx = _tracker.createInstance<OperationListContext>(_ctx, getState());
  enterRule(_localctx, 88, TQLParser::RuleOperationList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(597);
    operation();
    setState(602);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TQLParser::COMMA) {
      setState(598);
      match(TQLParser::COMMA);
      setState(599);
      operation();
      setState(604);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperationContext ------------------------------------------------------------------

TQLParser::OperationContext::OperationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::OperationContext::READ() {
  return getToken(TQLParser::READ, 0);
}

tree::TerminalNode* TQLParser::OperationContext::WRITE() {
  return getToken(TQLParser::WRITE, 0);
}

tree::TerminalNode* TQLParser::OperationContext::STAR() {
  return getToken(TQLParser::STAR, 0);
}


size_t TQLParser::OperationContext::getRuleIndex() const {
  return TQLParser::RuleOperation;
}


std::any TQLParser::OperationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitOperation(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::OperationContext* TQLParser::operation() {
  OperationContext *_localctx = _tracker.createInstance<OperationContext>(_ctx, getState());
  enterRule(_localctx, 90, TQLParser::RuleOperation);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(605);
    _la = _input->LA(1);
    if (!(((((_la - 32) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 32)) & 562949953421315) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateApiKeyStatementContext ------------------------------------------------------------------

TQLParser::CreateApiKeyStatementContext::CreateApiKeyStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::CreateApiKeyStatementContext::CREATE() {
  return getToken(TQLParser::CREATE, 0);
}

tree::TerminalNode* TQLParser::CreateApiKeyStatementContext::API_KEY() {
  return getToken(TQLParser::API_KEY, 0);
}

tree::TerminalNode* TQLParser::CreateApiKeyStatementContext::FOR() {
  return getToken(TQLParser::FOR, 0);
}

tree::TerminalNode* TQLParser::CreateApiKeyStatementContext::IDENTIFIER() {
  return getToken(TQLParser::IDENTIFIER, 0);
}

tree::TerminalNode* TQLParser::CreateApiKeyStatementContext::EXPIRES() {
  return getToken(TQLParser::EXPIRES, 0);
}

tree::TerminalNode* TQLParser::CreateApiKeyStatementContext::IN() {
  return getToken(TQLParser::IN, 0);
}

tree::TerminalNode* TQLParser::CreateApiKeyStatementContext::DURATION_LIT() {
  return getToken(TQLParser::DURATION_LIT, 0);
}


size_t TQLParser::CreateApiKeyStatementContext::getRuleIndex() const {
  return TQLParser::RuleCreateApiKeyStatement;
}


std::any TQLParser::CreateApiKeyStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitCreateApiKeyStatement(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::CreateApiKeyStatementContext* TQLParser::createApiKeyStatement() {
  CreateApiKeyStatementContext *_localctx = _tracker.createInstance<CreateApiKeyStatementContext>(_ctx, getState());
  enterRule(_localctx, 92, TQLParser::RuleCreateApiKeyStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(607);
    match(TQLParser::CREATE);
    setState(608);
    match(TQLParser::API_KEY);
    setState(609);
    match(TQLParser::FOR);
    setState(610);
    match(TQLParser::IDENTIFIER);
    setState(611);
    match(TQLParser::EXPIRES);
    setState(612);
    match(TQLParser::IN);
    setState(613);
    match(TQLParser::DURATION_LIT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RevokeApiKeyStatementContext ------------------------------------------------------------------

TQLParser::RevokeApiKeyStatementContext::RevokeApiKeyStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::RevokeApiKeyStatementContext::REVOKE() {
  return getToken(TQLParser::REVOKE, 0);
}

tree::TerminalNode* TQLParser::RevokeApiKeyStatementContext::API_KEY() {
  return getToken(TQLParser::API_KEY, 0);
}

tree::TerminalNode* TQLParser::RevokeApiKeyStatementContext::STRING_LIT() {
  return getToken(TQLParser::STRING_LIT, 0);
}


size_t TQLParser::RevokeApiKeyStatementContext::getRuleIndex() const {
  return TQLParser::RuleRevokeApiKeyStatement;
}


std::any TQLParser::RevokeApiKeyStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitRevokeApiKeyStatement(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::RevokeApiKeyStatementContext* TQLParser::revokeApiKeyStatement() {
  RevokeApiKeyStatementContext *_localctx = _tracker.createInstance<RevokeApiKeyStatementContext>(_ctx, getState());
  enterRule(_localctx, 94, TQLParser::RuleRevokeApiKeyStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(615);
    match(TQLParser::REVOKE);
    setState(616);
    match(TQLParser::API_KEY);
    setState(617);
    match(TQLParser::STRING_LIT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TruncateStatementContext ------------------------------------------------------------------

TQLParser::TruncateStatementContext::TruncateStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::TruncateStatementContext::TRUNCATE() {
  return getToken(TQLParser::TRUNCATE, 0);
}

tree::TerminalNode* TQLParser::TruncateStatementContext::STRING_LIT() {
  return getToken(TQLParser::STRING_LIT, 0);
}


size_t TQLParser::TruncateStatementContext::getRuleIndex() const {
  return TQLParser::RuleTruncateStatement;
}


std::any TQLParser::TruncateStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitTruncateStatement(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::TruncateStatementContext* TQLParser::truncateStatement() {
  TruncateStatementContext *_localctx = _tracker.createInstance<TruncateStatementContext>(_ctx, getState());
  enterRule(_localctx, 96, TQLParser::RuleTruncateStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(619);
    match(TQLParser::TRUNCATE);
    setState(620);
    match(TQLParser::STRING_LIT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FieldRefContext ------------------------------------------------------------------

TQLParser::FieldRefContext::FieldRefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TQLParser::QualifiedNameContext* TQLParser::FieldRefContext::qualifiedName() {
  return getRuleContext<TQLParser::QualifiedNameContext>(0);
}


size_t TQLParser::FieldRefContext::getRuleIndex() const {
  return TQLParser::RuleFieldRef;
}


std::any TQLParser::FieldRefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitFieldRef(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::FieldRefContext* TQLParser::fieldRef() {
  FieldRefContext *_localctx = _tracker.createInstance<FieldRefContext>(_ctx, getState());
  enterRule(_localctx, 98, TQLParser::RuleFieldRef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(622);
    qualifiedName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QualifiedNameContext ------------------------------------------------------------------

TQLParser::QualifiedNameContext::QualifiedNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> TQLParser::QualifiedNameContext::IDENTIFIER() {
  return getTokens(TQLParser::IDENTIFIER);
}

tree::TerminalNode* TQLParser::QualifiedNameContext::IDENTIFIER(size_t i) {
  return getToken(TQLParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> TQLParser::QualifiedNameContext::DOT() {
  return getTokens(TQLParser::DOT);
}

tree::TerminalNode* TQLParser::QualifiedNameContext::DOT(size_t i) {
  return getToken(TQLParser::DOT, i);
}


size_t TQLParser::QualifiedNameContext::getRuleIndex() const {
  return TQLParser::RuleQualifiedName;
}


std::any TQLParser::QualifiedNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitQualifiedName(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::QualifiedNameContext* TQLParser::qualifiedName() {
  QualifiedNameContext *_localctx = _tracker.createInstance<QualifiedNameContext>(_ctx, getState());
  enterRule(_localctx, 100, TQLParser::RuleQualifiedName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(624);
    match(TQLParser::IDENTIFIER);
    setState(629);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(625);
        match(TQLParser::DOT);
        setState(626);
        match(TQLParser::IDENTIFIER); 
      }
      setState(631);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

TQLParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t TQLParser::ExprContext::getRuleIndex() const {
  return TQLParser::RuleExpr;
}

void TQLParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- NotExprContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::NotExprContext::NOT() {
  return getToken(TQLParser::NOT, 0);
}

TQLParser::ExprContext* TQLParser::NotExprContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}

TQLParser::NotExprContext::NotExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any TQLParser::NotExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitNotExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AddSubExprContext ------------------------------------------------------------------

std::vector<TQLParser::ExprContext *> TQLParser::AddSubExprContext::expr() {
  return getRuleContexts<TQLParser::ExprContext>();
}

TQLParser::ExprContext* TQLParser::AddSubExprContext::expr(size_t i) {
  return getRuleContext<TQLParser::ExprContext>(i);
}

tree::TerminalNode* TQLParser::AddSubExprContext::PLUS() {
  return getToken(TQLParser::PLUS, 0);
}

tree::TerminalNode* TQLParser::AddSubExprContext::MINUS() {
  return getToken(TQLParser::MINUS, 0);
}

TQLParser::AddSubExprContext::AddSubExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any TQLParser::AddSubExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitAddSubExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LiteralExprContext ------------------------------------------------------------------

TQLParser::LiteralContext* TQLParser::LiteralExprContext::literal() {
  return getRuleContext<TQLParser::LiteralContext>(0);
}

TQLParser::LiteralExprContext::LiteralExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any TQLParser::LiteralExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitLiteralExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OrExprContext ------------------------------------------------------------------

std::vector<TQLParser::ExprContext *> TQLParser::OrExprContext::expr() {
  return getRuleContexts<TQLParser::ExprContext>();
}

TQLParser::ExprContext* TQLParser::OrExprContext::expr(size_t i) {
  return getRuleContext<TQLParser::ExprContext>(i);
}

tree::TerminalNode* TQLParser::OrExprContext::OR() {
  return getToken(TQLParser::OR, 0);
}

TQLParser::OrExprContext::OrExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any TQLParser::OrExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitOrExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ComparisonExprContext ------------------------------------------------------------------

std::vector<TQLParser::ExprContext *> TQLParser::ComparisonExprContext::expr() {
  return getRuleContexts<TQLParser::ExprContext>();
}

TQLParser::ExprContext* TQLParser::ComparisonExprContext::expr(size_t i) {
  return getRuleContext<TQLParser::ExprContext>(i);
}

tree::TerminalNode* TQLParser::ComparisonExprContext::EQ() {
  return getToken(TQLParser::EQ, 0);
}

tree::TerminalNode* TQLParser::ComparisonExprContext::NEQ() {
  return getToken(TQLParser::NEQ, 0);
}

tree::TerminalNode* TQLParser::ComparisonExprContext::LT() {
  return getToken(TQLParser::LT, 0);
}

tree::TerminalNode* TQLParser::ComparisonExprContext::GT() {
  return getToken(TQLParser::GT, 0);
}

tree::TerminalNode* TQLParser::ComparisonExprContext::LTE() {
  return getToken(TQLParser::LTE, 0);
}

tree::TerminalNode* TQLParser::ComparisonExprContext::GTE() {
  return getToken(TQLParser::GTE, 0);
}

TQLParser::ComparisonExprContext::ComparisonExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any TQLParser::ComparisonExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitComparisonExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryNegExprContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::UnaryNegExprContext::MINUS() {
  return getToken(TQLParser::MINUS, 0);
}

TQLParser::ExprContext* TQLParser::UnaryNegExprContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}

TQLParser::UnaryNegExprContext::UnaryNegExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any TQLParser::UnaryNegExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitUnaryNegExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FuncCallExprContext ------------------------------------------------------------------

TQLParser::FunctionCallContext* TQLParser::FuncCallExprContext::functionCall() {
  return getRuleContext<TQLParser::FunctionCallContext>(0);
}

TQLParser::FuncCallExprContext::FuncCallExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any TQLParser::FuncCallExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitFuncCallExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayLiteralExprContext ------------------------------------------------------------------

TQLParser::ArrayLiteralContext* TQLParser::ArrayLiteralExprContext::arrayLiteral() {
  return getRuleContext<TQLParser::ArrayLiteralContext>(0);
}

TQLParser::ArrayLiteralExprContext::ArrayLiteralExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any TQLParser::ArrayLiteralExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitArrayLiteralExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MulDivExprContext ------------------------------------------------------------------

std::vector<TQLParser::ExprContext *> TQLParser::MulDivExprContext::expr() {
  return getRuleContexts<TQLParser::ExprContext>();
}

TQLParser::ExprContext* TQLParser::MulDivExprContext::expr(size_t i) {
  return getRuleContext<TQLParser::ExprContext>(i);
}

tree::TerminalNode* TQLParser::MulDivExprContext::STAR() {
  return getToken(TQLParser::STAR, 0);
}

tree::TerminalNode* TQLParser::MulDivExprContext::SLASH() {
  return getToken(TQLParser::SLASH, 0);
}

TQLParser::MulDivExprContext::MulDivExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any TQLParser::MulDivExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitMulDivExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenExprContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::ParenExprContext::LPAREN() {
  return getToken(TQLParser::LPAREN, 0);
}

TQLParser::ExprContext* TQLParser::ParenExprContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}

tree::TerminalNode* TQLParser::ParenExprContext::RPAREN() {
  return getToken(TQLParser::RPAREN, 0);
}

TQLParser::ParenExprContext::ParenExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any TQLParser::ParenExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitParenExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NameExprContext ------------------------------------------------------------------

TQLParser::QualifiedNameContext* TQLParser::NameExprContext::qualifiedName() {
  return getRuleContext<TQLParser::QualifiedNameContext>(0);
}

TQLParser::NameExprContext::NameExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any TQLParser::NameExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitNameExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AndExprContext ------------------------------------------------------------------

std::vector<TQLParser::ExprContext *> TQLParser::AndExprContext::expr() {
  return getRuleContexts<TQLParser::ExprContext>();
}

TQLParser::ExprContext* TQLParser::AndExprContext::expr(size_t i) {
  return getRuleContext<TQLParser::ExprContext>(i);
}

tree::TerminalNode* TQLParser::AndExprContext::AND() {
  return getToken(TQLParser::AND, 0);
}

TQLParser::AndExprContext::AndExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any TQLParser::AndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitAndExpr(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::ExprContext* TQLParser::expr() {
   return expr(0);
}

TQLParser::ExprContext* TQLParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  TQLParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  TQLParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 102;
  enterRecursionRule(_localctx, 102, TQLParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(645);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TQLParser::LPAREN: {
        _localctx = _tracker.createInstance<ParenExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(633);
        match(TQLParser::LPAREN);
        setState(634);
        expr(0);
        setState(635);
        match(TQLParser::RPAREN);
        break;
      }

      case TQLParser::MINUS: {
        _localctx = _tracker.createInstance<UnaryNegExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(637);
        match(TQLParser::MINUS);
        setState(638);
        expr(11);
        break;
      }

      case TQLParser::NOT: {
        _localctx = _tracker.createInstance<NotExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(639);
        match(TQLParser::NOT);
        setState(640);
        expr(10);
        break;
      }

      case TQLParser::GEN_UUID:
      case TQLParser::NOW:
      case TQLParser::MATCH_FN:
      case TQLParser::EMBED:
      case TQLParser::PROMPT:
      case TQLParser::COUNT:
      case TQLParser::SUM:
      case TQLParser::AVG:
      case TQLParser::MIN_FN:
      case TQLParser::MAX_FN: {
        _localctx = _tracker.createInstance<FuncCallExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(641);
        functionCall();
        break;
      }

      case TQLParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<NameExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(642);
        qualifiedName();
        break;
      }

      case TQLParser::NULL_:
      case TQLParser::TRUE:
      case TQLParser::FALSE:
      case TQLParser::FLOAT_LIT:
      case TQLParser::INTEGER_LIT:
      case TQLParser::STRING_LIT:
      case TQLParser::SINGLE_STRING_LIT: {
        _localctx = _tracker.createInstance<LiteralExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(643);
        literal();
        break;
      }

      case TQLParser::LBRACKET: {
        _localctx = _tracker.createInstance<ArrayLiteralExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(644);
        arrayLiteral();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(664);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(662);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MulDivExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(647);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(648);
          _la = _input->LA(1);
          if (!(_la == TQLParser::STAR

          || _la == TQLParser::SLASH)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(649);
          expr(10);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddSubExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(650);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(651);
          _la = _input->LA(1);
          if (!(_la == TQLParser::PLUS

          || _la == TQLParser::MINUS)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(652);
          expr(9);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ComparisonExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(653);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(654);
          _la = _input->LA(1);
          if (!(((((_la - 74) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 74)) & 111) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(655);
          expr(8);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<AndExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(656);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(657);
          match(TQLParser::AND);
          setState(658);
          expr(7);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<OrExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(659);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(660);
          match(TQLParser::OR);
          setState(661);
          expr(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(666);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

TQLParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t TQLParser::FunctionCallContext::getRuleIndex() const {
  return TQLParser::RuleFunctionCall;
}

void TQLParser::FunctionCallContext::copyFrom(FunctionCallContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- NowCallContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::NowCallContext::NOW() {
  return getToken(TQLParser::NOW, 0);
}

tree::TerminalNode* TQLParser::NowCallContext::LPAREN() {
  return getToken(TQLParser::LPAREN, 0);
}

tree::TerminalNode* TQLParser::NowCallContext::RPAREN() {
  return getToken(TQLParser::RPAREN, 0);
}

TQLParser::NowCallContext::NowCallContext(FunctionCallContext *ctx) { copyFrom(ctx); }


std::any TQLParser::NowCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitNowCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MatchCallContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::MatchCallContext::MATCH_FN() {
  return getToken(TQLParser::MATCH_FN, 0);
}

tree::TerminalNode* TQLParser::MatchCallContext::LPAREN() {
  return getToken(TQLParser::LPAREN, 0);
}

TQLParser::ExprContext* TQLParser::MatchCallContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}

tree::TerminalNode* TQLParser::MatchCallContext::COMMA() {
  return getToken(TQLParser::COMMA, 0);
}

tree::TerminalNode* TQLParser::MatchCallContext::STRING_LIT() {
  return getToken(TQLParser::STRING_LIT, 0);
}

tree::TerminalNode* TQLParser::MatchCallContext::RPAREN() {
  return getToken(TQLParser::RPAREN, 0);
}

TQLParser::MatchCallContext::MatchCallContext(FunctionCallContext *ctx) { copyFrom(ctx); }


std::any TQLParser::MatchCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitMatchCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MinCallContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::MinCallContext::MIN_FN() {
  return getToken(TQLParser::MIN_FN, 0);
}

tree::TerminalNode* TQLParser::MinCallContext::LPAREN() {
  return getToken(TQLParser::LPAREN, 0);
}

TQLParser::ExprContext* TQLParser::MinCallContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}

tree::TerminalNode* TQLParser::MinCallContext::RPAREN() {
  return getToken(TQLParser::RPAREN, 0);
}

TQLParser::MinCallContext::MinCallContext(FunctionCallContext *ctx) { copyFrom(ctx); }


std::any TQLParser::MinCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitMinCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AvgCallContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::AvgCallContext::AVG() {
  return getToken(TQLParser::AVG, 0);
}

tree::TerminalNode* TQLParser::AvgCallContext::LPAREN() {
  return getToken(TQLParser::LPAREN, 0);
}

TQLParser::ExprContext* TQLParser::AvgCallContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}

tree::TerminalNode* TQLParser::AvgCallContext::RPAREN() {
  return getToken(TQLParser::RPAREN, 0);
}

TQLParser::AvgCallContext::AvgCallContext(FunctionCallContext *ctx) { copyFrom(ctx); }


std::any TQLParser::AvgCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitAvgCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PromptCallContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::PromptCallContext::PROMPT() {
  return getToken(TQLParser::PROMPT, 0);
}

tree::TerminalNode* TQLParser::PromptCallContext::LPAREN() {
  return getToken(TQLParser::LPAREN, 0);
}

TQLParser::ExprContext* TQLParser::PromptCallContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}

std::vector<tree::TerminalNode *> TQLParser::PromptCallContext::COMMA() {
  return getTokens(TQLParser::COMMA);
}

tree::TerminalNode* TQLParser::PromptCallContext::COMMA(size_t i) {
  return getToken(TQLParser::COMMA, i);
}

tree::TerminalNode* TQLParser::PromptCallContext::STRING_LIT() {
  return getToken(TQLParser::STRING_LIT, 0);
}

TQLParser::QualifiedNameContext* TQLParser::PromptCallContext::qualifiedName() {
  return getRuleContext<TQLParser::QualifiedNameContext>(0);
}

tree::TerminalNode* TQLParser::PromptCallContext::RPAREN() {
  return getToken(TQLParser::RPAREN, 0);
}

TQLParser::PromptCallContext::PromptCallContext(FunctionCallContext *ctx) { copyFrom(ctx); }


std::any TQLParser::PromptCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitPromptCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CountCallContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::CountCallContext::COUNT() {
  return getToken(TQLParser::COUNT, 0);
}

tree::TerminalNode* TQLParser::CountCallContext::LPAREN() {
  return getToken(TQLParser::LPAREN, 0);
}

tree::TerminalNode* TQLParser::CountCallContext::RPAREN() {
  return getToken(TQLParser::RPAREN, 0);
}

tree::TerminalNode* TQLParser::CountCallContext::STAR() {
  return getToken(TQLParser::STAR, 0);
}

TQLParser::ExprContext* TQLParser::CountCallContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}

TQLParser::CountCallContext::CountCallContext(FunctionCallContext *ctx) { copyFrom(ctx); }


std::any TQLParser::CountCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitCountCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- GenUuidCallContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::GenUuidCallContext::GEN_UUID() {
  return getToken(TQLParser::GEN_UUID, 0);
}

tree::TerminalNode* TQLParser::GenUuidCallContext::LPAREN() {
  return getToken(TQLParser::LPAREN, 0);
}

tree::TerminalNode* TQLParser::GenUuidCallContext::RPAREN() {
  return getToken(TQLParser::RPAREN, 0);
}

TQLParser::GenUuidCallContext::GenUuidCallContext(FunctionCallContext *ctx) { copyFrom(ctx); }


std::any TQLParser::GenUuidCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitGenUuidCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EmbedCallContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::EmbedCallContext::EMBED() {
  return getToken(TQLParser::EMBED, 0);
}

tree::TerminalNode* TQLParser::EmbedCallContext::LPAREN() {
  return getToken(TQLParser::LPAREN, 0);
}

tree::TerminalNode* TQLParser::EmbedCallContext::STRING_LIT() {
  return getToken(TQLParser::STRING_LIT, 0);
}

tree::TerminalNode* TQLParser::EmbedCallContext::RPAREN() {
  return getToken(TQLParser::RPAREN, 0);
}

tree::TerminalNode* TQLParser::EmbedCallContext::COMMA() {
  return getToken(TQLParser::COMMA, 0);
}

TQLParser::QualifiedNameContext* TQLParser::EmbedCallContext::qualifiedName() {
  return getRuleContext<TQLParser::QualifiedNameContext>(0);
}

TQLParser::EmbedCallContext::EmbedCallContext(FunctionCallContext *ctx) { copyFrom(ctx); }


std::any TQLParser::EmbedCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitEmbedCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SumCallContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::SumCallContext::SUM() {
  return getToken(TQLParser::SUM, 0);
}

tree::TerminalNode* TQLParser::SumCallContext::LPAREN() {
  return getToken(TQLParser::LPAREN, 0);
}

TQLParser::ExprContext* TQLParser::SumCallContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}

tree::TerminalNode* TQLParser::SumCallContext::RPAREN() {
  return getToken(TQLParser::RPAREN, 0);
}

TQLParser::SumCallContext::SumCallContext(FunctionCallContext *ctx) { copyFrom(ctx); }


std::any TQLParser::SumCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitSumCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MaxCallContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::MaxCallContext::MAX_FN() {
  return getToken(TQLParser::MAX_FN, 0);
}

tree::TerminalNode* TQLParser::MaxCallContext::LPAREN() {
  return getToken(TQLParser::LPAREN, 0);
}

TQLParser::ExprContext* TQLParser::MaxCallContext::expr() {
  return getRuleContext<TQLParser::ExprContext>(0);
}

tree::TerminalNode* TQLParser::MaxCallContext::RPAREN() {
  return getToken(TQLParser::RPAREN, 0);
}

TQLParser::MaxCallContext::MaxCallContext(FunctionCallContext *ctx) { copyFrom(ctx); }


std::any TQLParser::MaxCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitMaxCall(this);
  else
    return visitor->visitChildren(this);
}
TQLParser::FunctionCallContext* TQLParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 104, TQLParser::RuleFunctionCall);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(724);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TQLParser::GEN_UUID: {
        _localctx = _tracker.createInstance<TQLParser::GenUuidCallContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(667);
        match(TQLParser::GEN_UUID);
        setState(668);
        match(TQLParser::LPAREN);
        setState(669);
        match(TQLParser::RPAREN);
        break;
      }

      case TQLParser::NOW: {
        _localctx = _tracker.createInstance<TQLParser::NowCallContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(670);
        match(TQLParser::NOW);
        setState(671);
        match(TQLParser::LPAREN);
        setState(672);
        match(TQLParser::RPAREN);
        break;
      }

      case TQLParser::MATCH_FN: {
        _localctx = _tracker.createInstance<TQLParser::MatchCallContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(673);
        match(TQLParser::MATCH_FN);
        setState(674);
        match(TQLParser::LPAREN);
        setState(675);
        expr(0);
        setState(676);
        match(TQLParser::COMMA);
        setState(677);
        match(TQLParser::STRING_LIT);
        setState(678);
        match(TQLParser::RPAREN);
        break;
      }

      case TQLParser::EMBED: {
        _localctx = _tracker.createInstance<TQLParser::EmbedCallContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(680);
        match(TQLParser::EMBED);
        setState(681);
        match(TQLParser::LPAREN);
        setState(682);
        match(TQLParser::STRING_LIT);
        setState(685);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == TQLParser::COMMA) {
          setState(683);
          match(TQLParser::COMMA);
          setState(684);
          qualifiedName();
        }
        setState(687);
        match(TQLParser::RPAREN);
        break;
      }

      case TQLParser::PROMPT: {
        _localctx = _tracker.createInstance<TQLParser::PromptCallContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(688);
        match(TQLParser::PROMPT);
        setState(689);
        match(TQLParser::LPAREN);
        setState(690);
        expr(0);
        setState(691);
        match(TQLParser::COMMA);
        setState(692);
        match(TQLParser::STRING_LIT);
        setState(693);
        match(TQLParser::COMMA);
        setState(694);
        qualifiedName();
        setState(695);
        match(TQLParser::RPAREN);
        break;
      }

      case TQLParser::COUNT: {
        _localctx = _tracker.createInstance<TQLParser::CountCallContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(697);
        match(TQLParser::COUNT);
        setState(698);
        match(TQLParser::LPAREN);
        setState(701);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case TQLParser::STAR: {
            setState(699);
            match(TQLParser::STAR);
            break;
          }

          case TQLParser::NULL_:
          case TQLParser::TRUE:
          case TQLParser::FALSE:
          case TQLParser::NOT:
          case TQLParser::GEN_UUID:
          case TQLParser::NOW:
          case TQLParser::MATCH_FN:
          case TQLParser::EMBED:
          case TQLParser::PROMPT:
          case TQLParser::COUNT:
          case TQLParser::SUM:
          case TQLParser::AVG:
          case TQLParser::MIN_FN:
          case TQLParser::MAX_FN:
          case TQLParser::MINUS:
          case TQLParser::LPAREN:
          case TQLParser::LBRACKET:
          case TQLParser::FLOAT_LIT:
          case TQLParser::INTEGER_LIT:
          case TQLParser::STRING_LIT:
          case TQLParser::SINGLE_STRING_LIT:
          case TQLParser::IDENTIFIER: {
            setState(700);
            expr(0);
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        setState(703);
        match(TQLParser::RPAREN);
        break;
      }

      case TQLParser::SUM: {
        _localctx = _tracker.createInstance<TQLParser::SumCallContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(704);
        match(TQLParser::SUM);
        setState(705);
        match(TQLParser::LPAREN);
        setState(706);
        expr(0);
        setState(707);
        match(TQLParser::RPAREN);
        break;
      }

      case TQLParser::AVG: {
        _localctx = _tracker.createInstance<TQLParser::AvgCallContext>(_localctx);
        enterOuterAlt(_localctx, 8);
        setState(709);
        match(TQLParser::AVG);
        setState(710);
        match(TQLParser::LPAREN);
        setState(711);
        expr(0);
        setState(712);
        match(TQLParser::RPAREN);
        break;
      }

      case TQLParser::MIN_FN: {
        _localctx = _tracker.createInstance<TQLParser::MinCallContext>(_localctx);
        enterOuterAlt(_localctx, 9);
        setState(714);
        match(TQLParser::MIN_FN);
        setState(715);
        match(TQLParser::LPAREN);
        setState(716);
        expr(0);
        setState(717);
        match(TQLParser::RPAREN);
        break;
      }

      case TQLParser::MAX_FN: {
        _localctx = _tracker.createInstance<TQLParser::MaxCallContext>(_localctx);
        enterOuterAlt(_localctx, 10);
        setState(719);
        match(TQLParser::MAX_FN);
        setState(720);
        match(TQLParser::LPAREN);
        setState(721);
        expr(0);
        setState(722);
        match(TQLParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

TQLParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t TQLParser::LiteralContext::getRuleIndex() const {
  return TQLParser::RuleLiteral;
}

void TQLParser::LiteralContext::copyFrom(LiteralContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- StringLitContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::StringLitContext::STRING_LIT() {
  return getToken(TQLParser::STRING_LIT, 0);
}

TQLParser::StringLitContext::StringLitContext(LiteralContext *ctx) { copyFrom(ctx); }


std::any TQLParser::StringLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitStringLit(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TrueLitContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::TrueLitContext::TRUE() {
  return getToken(TQLParser::TRUE, 0);
}

TQLParser::TrueLitContext::TrueLitContext(LiteralContext *ctx) { copyFrom(ctx); }


std::any TQLParser::TrueLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitTrueLit(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FloatLitContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::FloatLitContext::FLOAT_LIT() {
  return getToken(TQLParser::FLOAT_LIT, 0);
}

TQLParser::FloatLitContext::FloatLitContext(LiteralContext *ctx) { copyFrom(ctx); }


std::any TQLParser::FloatLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitFloatLit(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FalseLitContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::FalseLitContext::FALSE() {
  return getToken(TQLParser::FALSE, 0);
}

TQLParser::FalseLitContext::FalseLitContext(LiteralContext *ctx) { copyFrom(ctx); }


std::any TQLParser::FalseLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitFalseLit(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntLitContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::IntLitContext::INTEGER_LIT() {
  return getToken(TQLParser::INTEGER_LIT, 0);
}

TQLParser::IntLitContext::IntLitContext(LiteralContext *ctx) { copyFrom(ctx); }


std::any TQLParser::IntLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitIntLit(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NullLitContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::NullLitContext::NULL_() {
  return getToken(TQLParser::NULL_, 0);
}

TQLParser::NullLitContext::NullLitContext(LiteralContext *ctx) { copyFrom(ctx); }


std::any TQLParser::NullLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitNullLit(this);
  else
    return visitor->visitChildren(this);
}
//----------------- JsonValueLitContext ------------------------------------------------------------------

tree::TerminalNode* TQLParser::JsonValueLitContext::SINGLE_STRING_LIT() {
  return getToken(TQLParser::SINGLE_STRING_LIT, 0);
}

TQLParser::JsonValueLitContext::JsonValueLitContext(LiteralContext *ctx) { copyFrom(ctx); }


std::any TQLParser::JsonValueLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitJsonValueLit(this);
  else
    return visitor->visitChildren(this);
}
TQLParser::LiteralContext* TQLParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 106, TQLParser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(733);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TQLParser::STRING_LIT: {
        _localctx = _tracker.createInstance<TQLParser::StringLitContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(726);
        match(TQLParser::STRING_LIT);
        break;
      }

      case TQLParser::SINGLE_STRING_LIT: {
        _localctx = _tracker.createInstance<TQLParser::JsonValueLitContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(727);
        match(TQLParser::SINGLE_STRING_LIT);
        break;
      }

      case TQLParser::FLOAT_LIT: {
        _localctx = _tracker.createInstance<TQLParser::FloatLitContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(728);
        match(TQLParser::FLOAT_LIT);
        break;
      }

      case TQLParser::INTEGER_LIT: {
        _localctx = _tracker.createInstance<TQLParser::IntLitContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(729);
        match(TQLParser::INTEGER_LIT);
        break;
      }

      case TQLParser::TRUE: {
        _localctx = _tracker.createInstance<TQLParser::TrueLitContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(730);
        match(TQLParser::TRUE);
        break;
      }

      case TQLParser::FALSE: {
        _localctx = _tracker.createInstance<TQLParser::FalseLitContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(731);
        match(TQLParser::FALSE);
        break;
      }

      case TQLParser::NULL_: {
        _localctx = _tracker.createInstance<TQLParser::NullLitContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(732);
        match(TQLParser::NULL_);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayLiteralContext ------------------------------------------------------------------

TQLParser::ArrayLiteralContext::ArrayLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TQLParser::ArrayLiteralContext::LBRACKET() {
  return getToken(TQLParser::LBRACKET, 0);
}

tree::TerminalNode* TQLParser::ArrayLiteralContext::RBRACKET() {
  return getToken(TQLParser::RBRACKET, 0);
}

std::vector<TQLParser::ExprContext *> TQLParser::ArrayLiteralContext::expr() {
  return getRuleContexts<TQLParser::ExprContext>();
}

TQLParser::ExprContext* TQLParser::ArrayLiteralContext::expr(size_t i) {
  return getRuleContext<TQLParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> TQLParser::ArrayLiteralContext::COMMA() {
  return getTokens(TQLParser::COMMA);
}

tree::TerminalNode* TQLParser::ArrayLiteralContext::COMMA(size_t i) {
  return getToken(TQLParser::COMMA, i);
}


size_t TQLParser::ArrayLiteralContext::getRuleIndex() const {
  return TQLParser::RuleArrayLiteral;
}


std::any TQLParser::ArrayLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TQLParserVisitor*>(visitor))
    return parserVisitor->visitArrayLiteral(this);
  else
    return visitor->visitChildren(this);
}

TQLParser::ArrayLiteralContext* TQLParser::arrayLiteral() {
  ArrayLiteralContext *_localctx = _tracker.createInstance<ArrayLiteralContext>(_ctx, getState());
  enterRule(_localctx, 108, TQLParser::RuleArrayLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(735);
    match(TQLParser::LBRACKET);
    setState(747);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 56) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 56)) & 34094255767527) != 0)) {
      setState(736);
      expr(0);
      setState(741);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(737);
          match(TQLParser::COMMA);
          setState(738);
          expr(0); 
        }
        setState(743);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx);
      }
      setState(745);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == TQLParser::COMMA) {
        setState(744);
        match(TQLParser::COMMA);
      }
    }
    setState(749);
    match(TQLParser::RBRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool TQLParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 51: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool TQLParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 9);
    case 1: return precpred(_ctx, 8);
    case 2: return precpred(_ctx, 7);
    case 3: return precpred(_ctx, 6);
    case 4: return precpred(_ctx, 5);

  default:
    break;
  }
  return true;
}

void TQLParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  tqlparserParserInitialize();
#else
  ::antlr4::internal::call_once(tqlparserParserOnceFlag, tqlparserParserInitialize);
#endif
}
