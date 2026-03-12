
// Generated from DBParser.g4 by ANTLR 4.13.2


#include "DBParserVisitor.h"

#include "DBParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct DBParserStaticData final {
  DBParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  DBParserStaticData(const DBParserStaticData&) = delete;
  DBParserStaticData(DBParserStaticData&&) = delete;
  DBParserStaticData& operator=(const DBParserStaticData&) = delete;
  DBParserStaticData& operator=(DBParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag dbparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<DBParserStaticData> dbparserParserStaticData = nullptr;

void dbparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (dbparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(dbparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<DBParserStaticData>(
    std::vector<std::string>{
      "script", "statement", "importStmt", "packageDecl", "typeDecl", "fieldDecl", 
      "typeRef", "typeArg", "primitiveType", "qualifiedName", "createTableStmt", 
      "createRoleStmt", "createApiKeyStmt", "grantStmt", "iamRule", "iamPermList", 
      "iamPerm", "iamPermOrStar", "queryStmt", "fromClause", "joinClause", 
      "whereClause", "groupByClause", "havingClause", "selectClause", "projectionBlock", 
      "projectionEntry", "orderByClause", "orderItem", "limitClause", "letBinding", 
      "insertStmt", "literalInsertBody", "pipelineInsertBody", "valueBlock", 
      "valueEntry", "updateStmt", "setClause", "setEntry", "deleteStmt", 
      "truncateStmt", "upsertStmt", "returningClause", "expr", "primary", 
      "functionCall", "argList", "aggregateCall", "aggregateFn", "literal", 
      "arrayLiteral", "exprList"
    },
    std::vector<std::string>{
      "", "'import'", "'from'", "'as'", "'where'", "'let'", "'select'", 
      "'order'", "'by'", "'limit'", "'group'", "'having'", "'join'", "'left'", 
      "'on'", "'asc'", "'desc'", "'contains'", "'insert'", "'into'", "'update'", 
      "'set'", "'delete'", "'upsert'", "'conflict'", "'returning'", "'truncate'", 
      "'create'", "'table'", "'package'", "'type'", "'role'", "'grant'", 
      "'to'", "'allow'", "'deny'", "'read'", "'write'", "'api_key'", "'for'", 
      "'expires'", "'in'", "'int32'", "'int64'", "'float32'", "'float64'", 
      "'decimal'", "'bool'", "'text'", "'uuid'", "'timestamp'", "'json'", 
      "'array'", "'vector'", "'map'", "'true'", "'false'", "'null'", "'and'", 
      "'or'", "'not'", "'<->'", "'=='", "'!='", "'<='", "'>='", "'<'", "'>'", 
      "'+'", "'-'", "'*'", "'/'", "'='", "'.'", "','", "':'", "'\\u003F'", 
      "'('", "')'", "'{'", "'}'", "'['", "']'"
    },
    std::vector<std::string>{
      "", "IMPORT", "FROM", "AS", "WHERE", "LET", "SELECT", "ORDER", "BY", 
      "LIMIT", "GROUP", "HAVING", "JOIN", "LEFT", "ON", "ASC", "DESC", "CONTAINS", 
      "INSERT", "INTO", "UPDATE", "SET", "DELETE", "UPSERT", "CONFLICT", 
      "RETURNING", "TRUNCATE", "CREATE", "TABLE", "PACKAGE", "TYPE", "ROLE", 
      "GRANT", "TO", "ALLOW", "DENY", "READ", "WRITE", "API_KEY", "FOR", 
      "EXPIRES", "IN", "K_INT32", "K_INT64", "K_FLOAT32", "K_FLOAT64", "K_DECIMAL", 
      "K_BOOL", "K_TEXT", "K_UUID", "K_TIMESTAMP", "K_JSON", "K_ARRAY", 
      "K_VECTOR", "K_MAP", "TRUE", "FALSE", "NULL", "AND", "OR", "NOT", 
      "DISTANCE", "EQ", "NEQ", "LEQ", "GEQ", "LT", "GT", "PLUS", "MINUS", 
      "STAR", "SLASH", "ASSIGN", "DOT", "COMMA", "COLON", "QUESTION", "LPAREN", 
      "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "INTEGER_LIT", 
      "DECIMAL_LIT", "STRING_LIT", "SINGLE_STRING_LIT", "DURATION_LIT", 
      "IDENTIFIER", "LINE_COMMENT", "BLOCK_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,91,623,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,1,0,5,0,106,8,0,10,0,12,0,109,9,0,1,0,1,0,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,126,8,1,1,2,1,2,1,
  	2,1,3,1,3,1,3,1,4,1,4,1,4,1,4,5,4,138,8,4,10,4,12,4,141,9,4,1,4,1,4,1,
  	5,1,5,1,5,1,5,1,6,1,6,3,6,151,8,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,3,6,160,
  	8,6,1,6,1,6,1,6,1,6,1,6,3,6,167,8,6,1,6,3,6,170,8,6,1,6,1,6,1,6,1,6,1,
  	6,3,6,177,8,6,1,6,1,6,1,6,1,6,1,6,3,6,184,8,6,1,6,1,6,1,6,1,6,1,6,1,6,
  	3,6,192,8,6,3,6,194,8,6,1,7,1,7,1,8,1,8,1,9,1,9,1,9,5,9,203,8,9,10,9,
  	12,9,206,9,9,1,10,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,12,1,
  	12,1,12,1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,5,13,231,8,
  	13,10,13,12,13,234,9,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,3,14,248,8,14,1,15,1,15,1,15,5,15,253,8,15,10,15,12,15,
  	256,9,15,1,16,1,16,1,17,1,17,1,17,5,17,263,8,17,10,17,12,17,266,9,17,
  	1,17,3,17,269,8,17,1,18,5,18,272,8,18,10,18,12,18,275,9,18,1,18,1,18,
  	5,18,279,8,18,10,18,12,18,282,9,18,1,18,3,18,285,8,18,1,18,3,18,288,8,
  	18,1,18,5,18,291,8,18,10,18,12,18,294,9,18,1,18,3,18,297,8,18,1,18,1,
  	18,3,18,301,8,18,1,18,3,18,304,8,18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,20,3,20,314,8,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,21,
  	1,21,1,21,1,22,1,22,1,22,1,22,1,23,1,23,1,23,1,24,1,24,1,24,1,25,1,25,
  	1,25,1,25,5,25,342,8,25,10,25,12,25,345,9,25,1,25,3,25,348,8,25,1,25,
  	1,25,1,26,1,26,1,26,1,26,1,26,1,26,1,26,3,26,359,8,26,1,27,1,27,1,27,
  	1,27,1,27,5,27,366,8,27,10,27,12,27,369,9,27,1,28,1,28,3,28,373,8,28,
  	1,29,1,29,1,29,1,30,1,30,1,30,1,30,3,30,382,8,30,1,30,1,30,1,30,1,31,
  	1,31,1,31,1,31,1,31,1,31,1,31,3,31,394,8,31,1,31,3,31,397,8,31,1,32,1,
  	32,1,32,5,32,402,8,32,10,32,12,32,405,9,32,1,33,1,33,5,33,409,8,33,10,
  	33,12,33,412,9,33,1,33,3,33,415,8,33,1,33,5,33,418,8,33,10,33,12,33,421,
  	9,33,1,33,1,33,1,34,1,34,1,34,1,34,5,34,429,8,34,10,34,12,34,432,9,34,
  	1,34,3,34,435,8,34,1,34,1,34,1,35,1,35,1,35,1,35,1,36,1,36,1,36,1,36,
  	1,36,1,36,1,36,3,36,450,8,36,1,36,5,36,453,8,36,10,36,12,36,456,9,36,
  	1,36,1,36,3,36,460,8,36,1,37,1,37,1,37,1,37,1,37,5,37,467,8,37,10,37,
  	12,37,470,9,37,1,37,3,37,473,8,37,1,37,1,37,1,38,1,38,1,38,1,38,1,39,
  	1,39,1,39,1,39,1,39,1,39,1,39,1,39,3,39,489,8,39,1,39,3,39,492,8,39,1,
  	40,1,40,1,40,1,41,1,41,1,41,1,41,1,41,1,41,1,41,1,41,1,41,1,41,1,41,1,
  	41,1,41,1,41,3,41,511,8,41,1,42,1,42,1,42,1,43,1,43,1,43,1,43,1,43,1,
  	43,3,43,522,8,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,
  	43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,5,43,545,8,43,10,
  	43,12,43,548,9,43,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,3,44,558,8,
  	44,1,45,1,45,1,45,3,45,563,8,45,1,45,1,45,1,46,1,46,1,46,5,46,570,8,46,
  	10,46,12,46,573,9,46,1,47,1,47,1,47,1,47,1,47,1,47,1,47,1,47,1,47,1,47,
  	3,47,585,8,47,1,48,1,48,1,49,1,49,1,49,1,49,1,49,1,49,1,49,1,49,3,49,
  	597,8,49,1,50,1,50,1,50,1,50,5,50,603,8,50,10,50,12,50,606,9,50,1,50,
  	3,50,609,8,50,3,50,611,8,50,1,50,1,50,1,51,1,51,1,51,5,51,618,8,51,10,
  	51,12,51,621,9,51,1,51,0,1,86,52,0,2,4,6,8,10,12,14,16,18,20,22,24,26,
  	28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,
  	74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,0,6,2,0,42,45,47,50,1,
  	0,36,37,1,0,15,16,1,0,62,67,1,0,68,69,1,0,70,71,661,0,107,1,0,0,0,2,125,
  	1,0,0,0,4,127,1,0,0,0,6,130,1,0,0,0,8,133,1,0,0,0,10,144,1,0,0,0,12,193,
  	1,0,0,0,14,195,1,0,0,0,16,197,1,0,0,0,18,199,1,0,0,0,20,207,1,0,0,0,22,
  	213,1,0,0,0,24,217,1,0,0,0,26,225,1,0,0,0,28,247,1,0,0,0,30,249,1,0,0,
  	0,32,257,1,0,0,0,34,268,1,0,0,0,36,273,1,0,0,0,38,305,1,0,0,0,40,313,
  	1,0,0,0,42,324,1,0,0,0,44,327,1,0,0,0,46,331,1,0,0,0,48,334,1,0,0,0,50,
  	337,1,0,0,0,52,358,1,0,0,0,54,360,1,0,0,0,56,370,1,0,0,0,58,374,1,0,0,
  	0,60,377,1,0,0,0,62,386,1,0,0,0,64,398,1,0,0,0,66,406,1,0,0,0,68,424,
  	1,0,0,0,70,438,1,0,0,0,72,442,1,0,0,0,74,461,1,0,0,0,76,476,1,0,0,0,78,
  	480,1,0,0,0,80,493,1,0,0,0,82,496,1,0,0,0,84,512,1,0,0,0,86,521,1,0,0,
  	0,88,557,1,0,0,0,90,559,1,0,0,0,92,566,1,0,0,0,94,584,1,0,0,0,96,586,
  	1,0,0,0,98,596,1,0,0,0,100,598,1,0,0,0,102,614,1,0,0,0,104,106,3,2,1,
  	0,105,104,1,0,0,0,106,109,1,0,0,0,107,105,1,0,0,0,107,108,1,0,0,0,108,
  	110,1,0,0,0,109,107,1,0,0,0,110,111,5,0,0,1,111,1,1,0,0,0,112,126,3,4,
  	2,0,113,126,3,6,3,0,114,126,3,8,4,0,115,126,3,20,10,0,116,126,3,22,11,
  	0,117,126,3,26,13,0,118,126,3,24,12,0,119,126,3,36,18,0,120,126,3,62,
  	31,0,121,126,3,72,36,0,122,126,3,78,39,0,123,126,3,82,41,0,124,126,3,
  	80,40,0,125,112,1,0,0,0,125,113,1,0,0,0,125,114,1,0,0,0,125,115,1,0,0,
  	0,125,116,1,0,0,0,125,117,1,0,0,0,125,118,1,0,0,0,125,119,1,0,0,0,125,
  	120,1,0,0,0,125,121,1,0,0,0,125,122,1,0,0,0,125,123,1,0,0,0,125,124,1,
  	0,0,0,126,3,1,0,0,0,127,128,5,1,0,0,128,129,5,85,0,0,129,5,1,0,0,0,130,
  	131,5,29,0,0,131,132,5,88,0,0,132,7,1,0,0,0,133,134,5,30,0,0,134,135,
  	5,88,0,0,135,139,5,79,0,0,136,138,3,10,5,0,137,136,1,0,0,0,138,141,1,
  	0,0,0,139,137,1,0,0,0,139,140,1,0,0,0,140,142,1,0,0,0,141,139,1,0,0,0,
  	142,143,5,80,0,0,143,9,1,0,0,0,144,145,5,88,0,0,145,146,5,75,0,0,146,
  	147,3,12,6,0,147,11,1,0,0,0,148,150,3,16,8,0,149,151,5,76,0,0,150,149,
  	1,0,0,0,150,151,1,0,0,0,151,194,1,0,0,0,152,153,5,46,0,0,153,154,5,77,
  	0,0,154,155,5,83,0,0,155,156,5,74,0,0,156,157,5,83,0,0,157,159,5,78,0,
  	0,158,160,5,76,0,0,159,158,1,0,0,0,159,160,1,0,0,0,160,194,1,0,0,0,161,
  	166,5,51,0,0,162,163,5,66,0,0,163,164,3,14,7,0,164,165,5,67,0,0,165,167,
  	1,0,0,0,166,162,1,0,0,0,166,167,1,0,0,0,167,169,1,0,0,0,168,170,5,76,
  	0,0,169,168,1,0,0,0,169,170,1,0,0,0,170,194,1,0,0,0,171,172,5,52,0,0,
  	172,173,5,66,0,0,173,174,3,12,6,0,174,176,5,67,0,0,175,177,5,76,0,0,176,
  	175,1,0,0,0,176,177,1,0,0,0,177,194,1,0,0,0,178,179,5,53,0,0,179,180,
  	5,77,0,0,180,181,5,83,0,0,181,183,5,78,0,0,182,184,5,76,0,0,183,182,1,
  	0,0,0,183,184,1,0,0,0,184,194,1,0,0,0,185,186,5,54,0,0,186,187,5,81,0,
  	0,187,188,3,12,6,0,188,189,5,82,0,0,189,191,3,12,6,0,190,192,5,76,0,0,
  	191,190,1,0,0,0,191,192,1,0,0,0,192,194,1,0,0,0,193,148,1,0,0,0,193,152,
  	1,0,0,0,193,161,1,0,0,0,193,171,1,0,0,0,193,178,1,0,0,0,193,185,1,0,0,
  	0,194,13,1,0,0,0,195,196,3,12,6,0,196,15,1,0,0,0,197,198,7,0,0,0,198,
  	17,1,0,0,0,199,204,5,88,0,0,200,201,5,73,0,0,201,203,5,88,0,0,202,200,
  	1,0,0,0,203,206,1,0,0,0,204,202,1,0,0,0,204,205,1,0,0,0,205,19,1,0,0,
  	0,206,204,1,0,0,0,207,208,5,27,0,0,208,209,5,28,0,0,209,210,5,85,0,0,
  	210,211,5,3,0,0,211,212,3,18,9,0,212,21,1,0,0,0,213,214,5,27,0,0,214,
  	215,5,31,0,0,215,216,5,88,0,0,216,23,1,0,0,0,217,218,5,27,0,0,218,219,
  	5,38,0,0,219,220,5,39,0,0,220,221,5,88,0,0,221,222,5,40,0,0,222,223,5,
  	41,0,0,223,224,5,87,0,0,224,25,1,0,0,0,225,226,5,32,0,0,226,227,5,33,
  	0,0,227,228,5,88,0,0,228,232,5,79,0,0,229,231,3,28,14,0,230,229,1,0,0,
  	0,231,234,1,0,0,0,232,230,1,0,0,0,232,233,1,0,0,0,233,235,1,0,0,0,234,
  	232,1,0,0,0,235,236,5,80,0,0,236,27,1,0,0,0,237,238,5,34,0,0,238,239,
  	3,30,15,0,239,240,5,14,0,0,240,241,5,85,0,0,241,248,1,0,0,0,242,243,5,
  	35,0,0,243,244,3,34,17,0,244,245,5,14,0,0,245,246,5,85,0,0,246,248,1,
  	0,0,0,247,237,1,0,0,0,247,242,1,0,0,0,248,29,1,0,0,0,249,254,3,32,16,
  	0,250,251,5,74,0,0,251,253,3,32,16,0,252,250,1,0,0,0,253,256,1,0,0,0,
  	254,252,1,0,0,0,254,255,1,0,0,0,255,31,1,0,0,0,256,254,1,0,0,0,257,258,
  	7,1,0,0,258,33,1,0,0,0,259,264,3,32,16,0,260,261,5,74,0,0,261,263,3,32,
  	16,0,262,260,1,0,0,0,263,266,1,0,0,0,264,262,1,0,0,0,264,265,1,0,0,0,
  	265,269,1,0,0,0,266,264,1,0,0,0,267,269,5,70,0,0,268,259,1,0,0,0,268,
  	267,1,0,0,0,269,35,1,0,0,0,270,272,3,60,30,0,271,270,1,0,0,0,272,275,
  	1,0,0,0,273,271,1,0,0,0,273,274,1,0,0,0,274,276,1,0,0,0,275,273,1,0,0,
  	0,276,280,3,38,19,0,277,279,3,40,20,0,278,277,1,0,0,0,279,282,1,0,0,0,
  	280,278,1,0,0,0,280,281,1,0,0,0,281,284,1,0,0,0,282,280,1,0,0,0,283,285,
  	3,42,21,0,284,283,1,0,0,0,284,285,1,0,0,0,285,287,1,0,0,0,286,288,3,44,
  	22,0,287,286,1,0,0,0,287,288,1,0,0,0,288,292,1,0,0,0,289,291,3,60,30,
  	0,290,289,1,0,0,0,291,294,1,0,0,0,292,290,1,0,0,0,292,293,1,0,0,0,293,
  	296,1,0,0,0,294,292,1,0,0,0,295,297,3,46,23,0,296,295,1,0,0,0,296,297,
  	1,0,0,0,297,298,1,0,0,0,298,300,3,48,24,0,299,301,3,54,27,0,300,299,1,
  	0,0,0,300,301,1,0,0,0,301,303,1,0,0,0,302,304,3,58,29,0,303,302,1,0,0,
  	0,303,304,1,0,0,0,304,37,1,0,0,0,305,306,5,2,0,0,306,307,5,85,0,0,307,
  	308,5,3,0,0,308,309,5,88,0,0,309,310,5,75,0,0,310,311,3,18,9,0,311,39,
  	1,0,0,0,312,314,5,13,0,0,313,312,1,0,0,0,313,314,1,0,0,0,314,315,1,0,
  	0,0,315,316,5,12,0,0,316,317,5,85,0,0,317,318,5,3,0,0,318,319,5,88,0,
  	0,319,320,5,75,0,0,320,321,3,18,9,0,321,322,5,14,0,0,322,323,3,86,43,
  	0,323,41,1,0,0,0,324,325,5,4,0,0,325,326,3,86,43,0,326,43,1,0,0,0,327,
  	328,5,10,0,0,328,329,5,8,0,0,329,330,3,102,51,0,330,45,1,0,0,0,331,332,
  	5,11,0,0,332,333,3,86,43,0,333,47,1,0,0,0,334,335,5,6,0,0,335,336,3,50,
  	25,0,336,49,1,0,0,0,337,338,5,79,0,0,338,343,3,52,26,0,339,340,5,74,0,
  	0,340,342,3,52,26,0,341,339,1,0,0,0,342,345,1,0,0,0,343,341,1,0,0,0,343,
  	344,1,0,0,0,344,347,1,0,0,0,345,343,1,0,0,0,346,348,5,74,0,0,347,346,
  	1,0,0,0,347,348,1,0,0,0,348,349,1,0,0,0,349,350,5,80,0,0,350,51,1,0,0,
  	0,351,352,5,88,0,0,352,353,5,75,0,0,353,359,3,86,43,0,354,359,5,88,0,
  	0,355,356,5,88,0,0,356,357,5,75,0,0,357,359,3,50,25,0,358,351,1,0,0,0,
  	358,354,1,0,0,0,358,355,1,0,0,0,359,53,1,0,0,0,360,361,5,7,0,0,361,362,
  	5,8,0,0,362,367,3,56,28,0,363,364,5,74,0,0,364,366,3,56,28,0,365,363,
  	1,0,0,0,366,369,1,0,0,0,367,365,1,0,0,0,367,368,1,0,0,0,368,55,1,0,0,
  	0,369,367,1,0,0,0,370,372,3,86,43,0,371,373,7,2,0,0,372,371,1,0,0,0,372,
  	373,1,0,0,0,373,57,1,0,0,0,374,375,5,9,0,0,375,376,5,83,0,0,376,59,1,
  	0,0,0,377,378,5,5,0,0,378,381,5,88,0,0,379,380,5,75,0,0,380,382,3,12,
  	6,0,381,379,1,0,0,0,381,382,1,0,0,0,382,383,1,0,0,0,383,384,5,72,0,0,
  	384,385,3,86,43,0,385,61,1,0,0,0,386,387,5,18,0,0,387,388,5,19,0,0,388,
  	389,5,85,0,0,389,390,5,3,0,0,390,393,3,18,9,0,391,394,3,64,32,0,392,394,
  	3,66,33,0,393,391,1,0,0,0,393,392,1,0,0,0,394,396,1,0,0,0,395,397,3,84,
  	42,0,396,395,1,0,0,0,396,397,1,0,0,0,397,63,1,0,0,0,398,403,3,68,34,0,
  	399,400,5,74,0,0,400,402,3,68,34,0,401,399,1,0,0,0,402,405,1,0,0,0,403,
  	401,1,0,0,0,403,404,1,0,0,0,404,65,1,0,0,0,405,403,1,0,0,0,406,410,3,
  	38,19,0,407,409,3,40,20,0,408,407,1,0,0,0,409,412,1,0,0,0,410,408,1,0,
  	0,0,410,411,1,0,0,0,411,414,1,0,0,0,412,410,1,0,0,0,413,415,3,42,21,0,
  	414,413,1,0,0,0,414,415,1,0,0,0,415,419,1,0,0,0,416,418,3,60,30,0,417,
  	416,1,0,0,0,418,421,1,0,0,0,419,417,1,0,0,0,419,420,1,0,0,0,420,422,1,
  	0,0,0,421,419,1,0,0,0,422,423,3,48,24,0,423,67,1,0,0,0,424,425,5,79,0,
  	0,425,430,3,70,35,0,426,427,5,74,0,0,427,429,3,70,35,0,428,426,1,0,0,
  	0,429,432,1,0,0,0,430,428,1,0,0,0,430,431,1,0,0,0,431,434,1,0,0,0,432,
  	430,1,0,0,0,433,435,5,74,0,0,434,433,1,0,0,0,434,435,1,0,0,0,435,436,
  	1,0,0,0,436,437,5,80,0,0,437,69,1,0,0,0,438,439,5,88,0,0,439,440,5,75,
  	0,0,440,441,3,86,43,0,441,71,1,0,0,0,442,443,5,20,0,0,443,444,5,85,0,
  	0,444,445,5,3,0,0,445,446,5,88,0,0,446,447,5,75,0,0,447,449,3,18,9,0,
  	448,450,3,42,21,0,449,448,1,0,0,0,449,450,1,0,0,0,450,454,1,0,0,0,451,
  	453,3,60,30,0,452,451,1,0,0,0,453,456,1,0,0,0,454,452,1,0,0,0,454,455,
  	1,0,0,0,455,457,1,0,0,0,456,454,1,0,0,0,457,459,3,74,37,0,458,460,3,84,
  	42,0,459,458,1,0,0,0,459,460,1,0,0,0,460,73,1,0,0,0,461,462,5,21,0,0,
  	462,463,5,79,0,0,463,468,3,76,38,0,464,465,5,74,0,0,465,467,3,76,38,0,
  	466,464,1,0,0,0,467,470,1,0,0,0,468,466,1,0,0,0,468,469,1,0,0,0,469,472,
  	1,0,0,0,470,468,1,0,0,0,471,473,5,74,0,0,472,471,1,0,0,0,472,473,1,0,
  	0,0,473,474,1,0,0,0,474,475,5,80,0,0,475,75,1,0,0,0,476,477,5,88,0,0,
  	477,478,5,75,0,0,478,479,3,86,43,0,479,77,1,0,0,0,480,481,5,22,0,0,481,
  	482,5,2,0,0,482,483,5,85,0,0,483,484,5,3,0,0,484,485,5,88,0,0,485,486,
  	5,75,0,0,486,488,3,18,9,0,487,489,3,42,21,0,488,487,1,0,0,0,488,489,1,
  	0,0,0,489,491,1,0,0,0,490,492,3,84,42,0,491,490,1,0,0,0,491,492,1,0,0,
  	0,492,79,1,0,0,0,493,494,5,26,0,0,494,495,5,85,0,0,495,81,1,0,0,0,496,
  	497,5,23,0,0,497,498,5,19,0,0,498,499,5,85,0,0,499,500,5,3,0,0,500,501,
  	3,18,9,0,501,502,5,24,0,0,502,503,5,14,0,0,503,504,5,88,0,0,504,505,3,
  	68,34,0,505,506,5,14,0,0,506,507,5,24,0,0,507,508,5,21,0,0,508,510,3,
  	74,37,0,509,511,3,84,42,0,510,509,1,0,0,0,510,511,1,0,0,0,511,83,1,0,
  	0,0,512,513,5,25,0,0,513,514,3,50,25,0,514,85,1,0,0,0,515,516,6,43,-1,
  	0,516,517,5,60,0,0,517,522,3,86,43,8,518,519,5,69,0,0,519,522,3,86,43,
  	2,520,522,3,88,44,0,521,515,1,0,0,0,521,518,1,0,0,0,521,520,1,0,0,0,522,
  	546,1,0,0,0,523,524,10,10,0,0,524,525,5,59,0,0,525,545,3,86,43,11,526,
  	527,10,9,0,0,527,528,5,58,0,0,528,545,3,86,43,10,529,530,10,7,0,0,530,
  	531,5,17,0,0,531,545,3,86,43,8,532,533,10,6,0,0,533,534,7,3,0,0,534,545,
  	3,86,43,7,535,536,10,5,0,0,536,537,5,61,0,0,537,545,3,86,43,6,538,539,
  	10,4,0,0,539,540,7,4,0,0,540,545,3,86,43,5,541,542,10,3,0,0,542,543,7,
  	5,0,0,543,545,3,86,43,4,544,523,1,0,0,0,544,526,1,0,0,0,544,529,1,0,0,
  	0,544,532,1,0,0,0,544,535,1,0,0,0,544,538,1,0,0,0,544,541,1,0,0,0,545,
  	548,1,0,0,0,546,544,1,0,0,0,546,547,1,0,0,0,547,87,1,0,0,0,548,546,1,
  	0,0,0,549,558,3,98,49,0,550,558,3,90,45,0,551,558,3,94,47,0,552,558,3,
  	18,9,0,553,554,5,77,0,0,554,555,3,86,43,0,555,556,5,78,0,0,556,558,1,
  	0,0,0,557,549,1,0,0,0,557,550,1,0,0,0,557,551,1,0,0,0,557,552,1,0,0,0,
  	557,553,1,0,0,0,558,89,1,0,0,0,559,560,5,88,0,0,560,562,5,77,0,0,561,
  	563,3,92,46,0,562,561,1,0,0,0,562,563,1,0,0,0,563,564,1,0,0,0,564,565,
  	5,78,0,0,565,91,1,0,0,0,566,571,3,86,43,0,567,568,5,74,0,0,568,570,3,
  	86,43,0,569,567,1,0,0,0,570,573,1,0,0,0,571,569,1,0,0,0,571,572,1,0,0,
  	0,572,93,1,0,0,0,573,571,1,0,0,0,574,575,3,96,48,0,575,576,5,77,0,0,576,
  	577,5,70,0,0,577,578,5,78,0,0,578,585,1,0,0,0,579,580,3,96,48,0,580,581,
  	5,77,0,0,581,582,3,86,43,0,582,583,5,78,0,0,583,585,1,0,0,0,584,574,1,
  	0,0,0,584,579,1,0,0,0,585,95,1,0,0,0,586,587,5,88,0,0,587,97,1,0,0,0,
  	588,597,5,83,0,0,589,597,5,84,0,0,590,597,5,85,0,0,591,597,5,86,0,0,592,
  	597,5,55,0,0,593,597,5,56,0,0,594,597,5,57,0,0,595,597,3,100,50,0,596,
  	588,1,0,0,0,596,589,1,0,0,0,596,590,1,0,0,0,596,591,1,0,0,0,596,592,1,
  	0,0,0,596,593,1,0,0,0,596,594,1,0,0,0,596,595,1,0,0,0,597,99,1,0,0,0,
  	598,610,5,81,0,0,599,604,3,86,43,0,600,601,5,74,0,0,601,603,3,86,43,0,
  	602,600,1,0,0,0,603,606,1,0,0,0,604,602,1,0,0,0,604,605,1,0,0,0,605,608,
  	1,0,0,0,606,604,1,0,0,0,607,609,5,74,0,0,608,607,1,0,0,0,608,609,1,0,
  	0,0,609,611,1,0,0,0,610,599,1,0,0,0,610,611,1,0,0,0,611,612,1,0,0,0,612,
  	613,5,82,0,0,613,101,1,0,0,0,614,619,3,86,43,0,615,616,5,74,0,0,616,618,
  	3,86,43,0,617,615,1,0,0,0,618,621,1,0,0,0,619,617,1,0,0,0,619,620,1,0,
  	0,0,620,103,1,0,0,0,621,619,1,0,0,0,60,107,125,139,150,159,166,169,176,
  	183,191,193,204,232,247,254,264,268,273,280,284,287,292,296,300,303,313,
  	343,347,358,367,372,381,393,396,403,410,414,419,430,434,449,454,459,468,
  	472,488,491,510,521,544,546,557,562,571,584,596,604,608,610,619
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  dbparserParserStaticData = std::move(staticData);
}

}

DBParser::DBParser(TokenStream *input) : DBParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

DBParser::DBParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  DBParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *dbparserParserStaticData->atn, dbparserParserStaticData->decisionToDFA, dbparserParserStaticData->sharedContextCache, options);
}

DBParser::~DBParser() {
  delete _interpreter;
}

const atn::ATN& DBParser::getATN() const {
  return *dbparserParserStaticData->atn;
}

std::string DBParser::getGrammarFileName() const {
  return "DBParser.g4";
}

const std::vector<std::string>& DBParser::getRuleNames() const {
  return dbparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& DBParser::getVocabulary() const {
  return dbparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView DBParser::getSerializedATN() const {
  return dbparserParserStaticData->serializedATN;
}


//----------------- ScriptContext ------------------------------------------------------------------

DBParser::ScriptContext::ScriptContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::ScriptContext::EOF() {
  return getToken(DBParser::EOF, 0);
}

std::vector<DBParser::StatementContext *> DBParser::ScriptContext::statement() {
  return getRuleContexts<DBParser::StatementContext>();
}

DBParser::StatementContext* DBParser::ScriptContext::statement(size_t i) {
  return getRuleContext<DBParser::StatementContext>(i);
}


size_t DBParser::ScriptContext::getRuleIndex() const {
  return DBParser::RuleScript;
}


std::any DBParser::ScriptContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitScript(this);
  else
    return visitor->visitChildren(this);
}

DBParser::ScriptContext* DBParser::script() {
  ScriptContext *_localctx = _tracker.createInstance<ScriptContext>(_ctx, getState());
  enterRule(_localctx, 0, DBParser::RuleScript);
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
    setState(107);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 6120800294) != 0)) {
      setState(104);
      statement();
      setState(109);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(110);
    match(DBParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

DBParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DBParser::ImportStmtContext* DBParser::StatementContext::importStmt() {
  return getRuleContext<DBParser::ImportStmtContext>(0);
}

DBParser::PackageDeclContext* DBParser::StatementContext::packageDecl() {
  return getRuleContext<DBParser::PackageDeclContext>(0);
}

DBParser::TypeDeclContext* DBParser::StatementContext::typeDecl() {
  return getRuleContext<DBParser::TypeDeclContext>(0);
}

DBParser::CreateTableStmtContext* DBParser::StatementContext::createTableStmt() {
  return getRuleContext<DBParser::CreateTableStmtContext>(0);
}

DBParser::CreateRoleStmtContext* DBParser::StatementContext::createRoleStmt() {
  return getRuleContext<DBParser::CreateRoleStmtContext>(0);
}

DBParser::GrantStmtContext* DBParser::StatementContext::grantStmt() {
  return getRuleContext<DBParser::GrantStmtContext>(0);
}

DBParser::CreateApiKeyStmtContext* DBParser::StatementContext::createApiKeyStmt() {
  return getRuleContext<DBParser::CreateApiKeyStmtContext>(0);
}

DBParser::QueryStmtContext* DBParser::StatementContext::queryStmt() {
  return getRuleContext<DBParser::QueryStmtContext>(0);
}

DBParser::InsertStmtContext* DBParser::StatementContext::insertStmt() {
  return getRuleContext<DBParser::InsertStmtContext>(0);
}

DBParser::UpdateStmtContext* DBParser::StatementContext::updateStmt() {
  return getRuleContext<DBParser::UpdateStmtContext>(0);
}

DBParser::DeleteStmtContext* DBParser::StatementContext::deleteStmt() {
  return getRuleContext<DBParser::DeleteStmtContext>(0);
}

DBParser::UpsertStmtContext* DBParser::StatementContext::upsertStmt() {
  return getRuleContext<DBParser::UpsertStmtContext>(0);
}

DBParser::TruncateStmtContext* DBParser::StatementContext::truncateStmt() {
  return getRuleContext<DBParser::TruncateStmtContext>(0);
}


size_t DBParser::StatementContext::getRuleIndex() const {
  return DBParser::RuleStatement;
}


std::any DBParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

DBParser::StatementContext* DBParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, DBParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(125);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(112);
      importStmt();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(113);
      packageDecl();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(114);
      typeDecl();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(115);
      createTableStmt();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(116);
      createRoleStmt();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(117);
      grantStmt();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(118);
      createApiKeyStmt();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(119);
      queryStmt();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(120);
      insertStmt();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(121);
      updateStmt();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(122);
      deleteStmt();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(123);
      upsertStmt();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(124);
      truncateStmt();
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

//----------------- ImportStmtContext ------------------------------------------------------------------

DBParser::ImportStmtContext::ImportStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::ImportStmtContext::IMPORT() {
  return getToken(DBParser::IMPORT, 0);
}

tree::TerminalNode* DBParser::ImportStmtContext::STRING_LIT() {
  return getToken(DBParser::STRING_LIT, 0);
}


size_t DBParser::ImportStmtContext::getRuleIndex() const {
  return DBParser::RuleImportStmt;
}


std::any DBParser::ImportStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitImportStmt(this);
  else
    return visitor->visitChildren(this);
}

DBParser::ImportStmtContext* DBParser::importStmt() {
  ImportStmtContext *_localctx = _tracker.createInstance<ImportStmtContext>(_ctx, getState());
  enterRule(_localctx, 4, DBParser::RuleImportStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(127);
    match(DBParser::IMPORT);
    setState(128);
    match(DBParser::STRING_LIT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PackageDeclContext ------------------------------------------------------------------

DBParser::PackageDeclContext::PackageDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::PackageDeclContext::PACKAGE() {
  return getToken(DBParser::PACKAGE, 0);
}

tree::TerminalNode* DBParser::PackageDeclContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}


size_t DBParser::PackageDeclContext::getRuleIndex() const {
  return DBParser::RulePackageDecl;
}


std::any DBParser::PackageDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitPackageDecl(this);
  else
    return visitor->visitChildren(this);
}

DBParser::PackageDeclContext* DBParser::packageDecl() {
  PackageDeclContext *_localctx = _tracker.createInstance<PackageDeclContext>(_ctx, getState());
  enterRule(_localctx, 6, DBParser::RulePackageDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(130);
    match(DBParser::PACKAGE);
    setState(131);
    match(DBParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeDeclContext ------------------------------------------------------------------

DBParser::TypeDeclContext::TypeDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::TypeDeclContext::TYPE() {
  return getToken(DBParser::TYPE, 0);
}

tree::TerminalNode* DBParser::TypeDeclContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}

tree::TerminalNode* DBParser::TypeDeclContext::LBRACE() {
  return getToken(DBParser::LBRACE, 0);
}

tree::TerminalNode* DBParser::TypeDeclContext::RBRACE() {
  return getToken(DBParser::RBRACE, 0);
}

std::vector<DBParser::FieldDeclContext *> DBParser::TypeDeclContext::fieldDecl() {
  return getRuleContexts<DBParser::FieldDeclContext>();
}

DBParser::FieldDeclContext* DBParser::TypeDeclContext::fieldDecl(size_t i) {
  return getRuleContext<DBParser::FieldDeclContext>(i);
}


size_t DBParser::TypeDeclContext::getRuleIndex() const {
  return DBParser::RuleTypeDecl;
}


std::any DBParser::TypeDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitTypeDecl(this);
  else
    return visitor->visitChildren(this);
}

DBParser::TypeDeclContext* DBParser::typeDecl() {
  TypeDeclContext *_localctx = _tracker.createInstance<TypeDeclContext>(_ctx, getState());
  enterRule(_localctx, 8, DBParser::RuleTypeDecl);
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
    setState(133);
    match(DBParser::TYPE);
    setState(134);
    match(DBParser::IDENTIFIER);
    setState(135);
    match(DBParser::LBRACE);
    setState(139);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == DBParser::IDENTIFIER) {
      setState(136);
      fieldDecl();
      setState(141);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(142);
    match(DBParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FieldDeclContext ------------------------------------------------------------------

DBParser::FieldDeclContext::FieldDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::FieldDeclContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}

tree::TerminalNode* DBParser::FieldDeclContext::COLON() {
  return getToken(DBParser::COLON, 0);
}

DBParser::TypeRefContext* DBParser::FieldDeclContext::typeRef() {
  return getRuleContext<DBParser::TypeRefContext>(0);
}


size_t DBParser::FieldDeclContext::getRuleIndex() const {
  return DBParser::RuleFieldDecl;
}


std::any DBParser::FieldDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitFieldDecl(this);
  else
    return visitor->visitChildren(this);
}

DBParser::FieldDeclContext* DBParser::fieldDecl() {
  FieldDeclContext *_localctx = _tracker.createInstance<FieldDeclContext>(_ctx, getState());
  enterRule(_localctx, 10, DBParser::RuleFieldDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(144);
    match(DBParser::IDENTIFIER);
    setState(145);
    match(DBParser::COLON);
    setState(146);
    typeRef();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeRefContext ------------------------------------------------------------------

DBParser::TypeRefContext::TypeRefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t DBParser::TypeRefContext::getRuleIndex() const {
  return DBParser::RuleTypeRef;
}

void DBParser::TypeRefContext::copyFrom(TypeRefContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DecimalTypeContext ------------------------------------------------------------------

tree::TerminalNode* DBParser::DecimalTypeContext::K_DECIMAL() {
  return getToken(DBParser::K_DECIMAL, 0);
}

tree::TerminalNode* DBParser::DecimalTypeContext::LPAREN() {
  return getToken(DBParser::LPAREN, 0);
}

std::vector<tree::TerminalNode *> DBParser::DecimalTypeContext::INTEGER_LIT() {
  return getTokens(DBParser::INTEGER_LIT);
}

tree::TerminalNode* DBParser::DecimalTypeContext::INTEGER_LIT(size_t i) {
  return getToken(DBParser::INTEGER_LIT, i);
}

tree::TerminalNode* DBParser::DecimalTypeContext::COMMA() {
  return getToken(DBParser::COMMA, 0);
}

tree::TerminalNode* DBParser::DecimalTypeContext::RPAREN() {
  return getToken(DBParser::RPAREN, 0);
}

tree::TerminalNode* DBParser::DecimalTypeContext::QUESTION() {
  return getToken(DBParser::QUESTION, 0);
}

DBParser::DecimalTypeContext::DecimalTypeContext(TypeRefContext *ctx) { copyFrom(ctx); }


std::any DBParser::DecimalTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitDecimalType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayTypeContext ------------------------------------------------------------------

tree::TerminalNode* DBParser::ArrayTypeContext::K_ARRAY() {
  return getToken(DBParser::K_ARRAY, 0);
}

tree::TerminalNode* DBParser::ArrayTypeContext::LT() {
  return getToken(DBParser::LT, 0);
}

DBParser::TypeRefContext* DBParser::ArrayTypeContext::typeRef() {
  return getRuleContext<DBParser::TypeRefContext>(0);
}

tree::TerminalNode* DBParser::ArrayTypeContext::GT() {
  return getToken(DBParser::GT, 0);
}

tree::TerminalNode* DBParser::ArrayTypeContext::QUESTION() {
  return getToken(DBParser::QUESTION, 0);
}

DBParser::ArrayTypeContext::ArrayTypeContext(TypeRefContext *ctx) { copyFrom(ctx); }


std::any DBParser::ArrayTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitArrayType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VectorTypeContext ------------------------------------------------------------------

tree::TerminalNode* DBParser::VectorTypeContext::K_VECTOR() {
  return getToken(DBParser::K_VECTOR, 0);
}

tree::TerminalNode* DBParser::VectorTypeContext::LPAREN() {
  return getToken(DBParser::LPAREN, 0);
}

tree::TerminalNode* DBParser::VectorTypeContext::INTEGER_LIT() {
  return getToken(DBParser::INTEGER_LIT, 0);
}

tree::TerminalNode* DBParser::VectorTypeContext::RPAREN() {
  return getToken(DBParser::RPAREN, 0);
}

tree::TerminalNode* DBParser::VectorTypeContext::QUESTION() {
  return getToken(DBParser::QUESTION, 0);
}

DBParser::VectorTypeContext::VectorTypeContext(TypeRefContext *ctx) { copyFrom(ctx); }


std::any DBParser::VectorTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitVectorType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MapTypeContext ------------------------------------------------------------------

tree::TerminalNode* DBParser::MapTypeContext::K_MAP() {
  return getToken(DBParser::K_MAP, 0);
}

tree::TerminalNode* DBParser::MapTypeContext::LBRACKET() {
  return getToken(DBParser::LBRACKET, 0);
}

std::vector<DBParser::TypeRefContext *> DBParser::MapTypeContext::typeRef() {
  return getRuleContexts<DBParser::TypeRefContext>();
}

DBParser::TypeRefContext* DBParser::MapTypeContext::typeRef(size_t i) {
  return getRuleContext<DBParser::TypeRefContext>(i);
}

tree::TerminalNode* DBParser::MapTypeContext::RBRACKET() {
  return getToken(DBParser::RBRACKET, 0);
}

tree::TerminalNode* DBParser::MapTypeContext::QUESTION() {
  return getToken(DBParser::QUESTION, 0);
}

DBParser::MapTypeContext::MapTypeContext(TypeRefContext *ctx) { copyFrom(ctx); }


std::any DBParser::MapTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitMapType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- JsonTypeContext ------------------------------------------------------------------

tree::TerminalNode* DBParser::JsonTypeContext::K_JSON() {
  return getToken(DBParser::K_JSON, 0);
}

tree::TerminalNode* DBParser::JsonTypeContext::LT() {
  return getToken(DBParser::LT, 0);
}

DBParser::TypeArgContext* DBParser::JsonTypeContext::typeArg() {
  return getRuleContext<DBParser::TypeArgContext>(0);
}

tree::TerminalNode* DBParser::JsonTypeContext::GT() {
  return getToken(DBParser::GT, 0);
}

tree::TerminalNode* DBParser::JsonTypeContext::QUESTION() {
  return getToken(DBParser::QUESTION, 0);
}

DBParser::JsonTypeContext::JsonTypeContext(TypeRefContext *ctx) { copyFrom(ctx); }


std::any DBParser::JsonTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitJsonType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NullablePrimitiveContext ------------------------------------------------------------------

DBParser::PrimitiveTypeContext* DBParser::NullablePrimitiveContext::primitiveType() {
  return getRuleContext<DBParser::PrimitiveTypeContext>(0);
}

tree::TerminalNode* DBParser::NullablePrimitiveContext::QUESTION() {
  return getToken(DBParser::QUESTION, 0);
}

DBParser::NullablePrimitiveContext::NullablePrimitiveContext(TypeRefContext *ctx) { copyFrom(ctx); }


std::any DBParser::NullablePrimitiveContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitNullablePrimitive(this);
  else
    return visitor->visitChildren(this);
}
DBParser::TypeRefContext* DBParser::typeRef() {
  TypeRefContext *_localctx = _tracker.createInstance<TypeRefContext>(_ctx, getState());
  enterRule(_localctx, 12, DBParser::RuleTypeRef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(193);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DBParser::K_INT32:
      case DBParser::K_INT64:
      case DBParser::K_FLOAT32:
      case DBParser::K_FLOAT64:
      case DBParser::K_BOOL:
      case DBParser::K_TEXT:
      case DBParser::K_UUID:
      case DBParser::K_TIMESTAMP: {
        _localctx = _tracker.createInstance<DBParser::NullablePrimitiveContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(148);
        primitiveType();
        setState(150);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
        case 1: {
          setState(149);
          match(DBParser::QUESTION);
          break;
        }

        default:
          break;
        }
        break;
      }

      case DBParser::K_DECIMAL: {
        _localctx = _tracker.createInstance<DBParser::DecimalTypeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(152);
        match(DBParser::K_DECIMAL);
        setState(153);
        match(DBParser::LPAREN);
        setState(154);
        match(DBParser::INTEGER_LIT);
        setState(155);
        match(DBParser::COMMA);
        setState(156);
        match(DBParser::INTEGER_LIT);
        setState(157);
        match(DBParser::RPAREN);
        setState(159);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
        case 1: {
          setState(158);
          match(DBParser::QUESTION);
          break;
        }

        default:
          break;
        }
        break;
      }

      case DBParser::K_JSON: {
        _localctx = _tracker.createInstance<DBParser::JsonTypeContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(161);
        match(DBParser::K_JSON);
        setState(166);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == DBParser::LT) {
          setState(162);
          match(DBParser::LT);
          setState(163);
          typeArg();
          setState(164);
          match(DBParser::GT);
        }
        setState(169);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
        case 1: {
          setState(168);
          match(DBParser::QUESTION);
          break;
        }

        default:
          break;
        }
        break;
      }

      case DBParser::K_ARRAY: {
        _localctx = _tracker.createInstance<DBParser::ArrayTypeContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(171);
        match(DBParser::K_ARRAY);
        setState(172);
        match(DBParser::LT);
        setState(173);
        typeRef();
        setState(174);
        match(DBParser::GT);
        setState(176);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
        case 1: {
          setState(175);
          match(DBParser::QUESTION);
          break;
        }

        default:
          break;
        }
        break;
      }

      case DBParser::K_VECTOR: {
        _localctx = _tracker.createInstance<DBParser::VectorTypeContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(178);
        match(DBParser::K_VECTOR);
        setState(179);
        match(DBParser::LPAREN);
        setState(180);
        match(DBParser::INTEGER_LIT);
        setState(181);
        match(DBParser::RPAREN);
        setState(183);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
        case 1: {
          setState(182);
          match(DBParser::QUESTION);
          break;
        }

        default:
          break;
        }
        break;
      }

      case DBParser::K_MAP: {
        _localctx = _tracker.createInstance<DBParser::MapTypeContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(185);
        match(DBParser::K_MAP);
        setState(186);
        match(DBParser::LBRACKET);
        setState(187);
        typeRef();
        setState(188);
        match(DBParser::RBRACKET);
        setState(189);
        typeRef();
        setState(191);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
        case 1: {
          setState(190);
          match(DBParser::QUESTION);
          break;
        }

        default:
          break;
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

//----------------- TypeArgContext ------------------------------------------------------------------

DBParser::TypeArgContext::TypeArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DBParser::TypeRefContext* DBParser::TypeArgContext::typeRef() {
  return getRuleContext<DBParser::TypeRefContext>(0);
}


size_t DBParser::TypeArgContext::getRuleIndex() const {
  return DBParser::RuleTypeArg;
}


std::any DBParser::TypeArgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitTypeArg(this);
  else
    return visitor->visitChildren(this);
}

DBParser::TypeArgContext* DBParser::typeArg() {
  TypeArgContext *_localctx = _tracker.createInstance<TypeArgContext>(_ctx, getState());
  enterRule(_localctx, 14, DBParser::RuleTypeArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(195);
    typeRef();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimitiveTypeContext ------------------------------------------------------------------

DBParser::PrimitiveTypeContext::PrimitiveTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::PrimitiveTypeContext::K_INT32() {
  return getToken(DBParser::K_INT32, 0);
}

tree::TerminalNode* DBParser::PrimitiveTypeContext::K_INT64() {
  return getToken(DBParser::K_INT64, 0);
}

tree::TerminalNode* DBParser::PrimitiveTypeContext::K_FLOAT32() {
  return getToken(DBParser::K_FLOAT32, 0);
}

tree::TerminalNode* DBParser::PrimitiveTypeContext::K_FLOAT64() {
  return getToken(DBParser::K_FLOAT64, 0);
}

tree::TerminalNode* DBParser::PrimitiveTypeContext::K_BOOL() {
  return getToken(DBParser::K_BOOL, 0);
}

tree::TerminalNode* DBParser::PrimitiveTypeContext::K_TEXT() {
  return getToken(DBParser::K_TEXT, 0);
}

tree::TerminalNode* DBParser::PrimitiveTypeContext::K_UUID() {
  return getToken(DBParser::K_UUID, 0);
}

tree::TerminalNode* DBParser::PrimitiveTypeContext::K_TIMESTAMP() {
  return getToken(DBParser::K_TIMESTAMP, 0);
}


size_t DBParser::PrimitiveTypeContext::getRuleIndex() const {
  return DBParser::RulePrimitiveType;
}


std::any DBParser::PrimitiveTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitPrimitiveType(this);
  else
    return visitor->visitChildren(this);
}

DBParser::PrimitiveTypeContext* DBParser::primitiveType() {
  PrimitiveTypeContext *_localctx = _tracker.createInstance<PrimitiveTypeContext>(_ctx, getState());
  enterRule(_localctx, 16, DBParser::RulePrimitiveType);
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
    setState(197);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2177033022996480) != 0))) {
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

//----------------- QualifiedNameContext ------------------------------------------------------------------

DBParser::QualifiedNameContext::QualifiedNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> DBParser::QualifiedNameContext::IDENTIFIER() {
  return getTokens(DBParser::IDENTIFIER);
}

tree::TerminalNode* DBParser::QualifiedNameContext::IDENTIFIER(size_t i) {
  return getToken(DBParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> DBParser::QualifiedNameContext::DOT() {
  return getTokens(DBParser::DOT);
}

tree::TerminalNode* DBParser::QualifiedNameContext::DOT(size_t i) {
  return getToken(DBParser::DOT, i);
}


size_t DBParser::QualifiedNameContext::getRuleIndex() const {
  return DBParser::RuleQualifiedName;
}


std::any DBParser::QualifiedNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitQualifiedName(this);
  else
    return visitor->visitChildren(this);
}

DBParser::QualifiedNameContext* DBParser::qualifiedName() {
  QualifiedNameContext *_localctx = _tracker.createInstance<QualifiedNameContext>(_ctx, getState());
  enterRule(_localctx, 18, DBParser::RuleQualifiedName);

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
    setState(199);
    match(DBParser::IDENTIFIER);
    setState(204);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(200);
        match(DBParser::DOT);
        setState(201);
        match(DBParser::IDENTIFIER); 
      }
      setState(206);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateTableStmtContext ------------------------------------------------------------------

DBParser::CreateTableStmtContext::CreateTableStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::CreateTableStmtContext::CREATE() {
  return getToken(DBParser::CREATE, 0);
}

tree::TerminalNode* DBParser::CreateTableStmtContext::TABLE() {
  return getToken(DBParser::TABLE, 0);
}

tree::TerminalNode* DBParser::CreateTableStmtContext::STRING_LIT() {
  return getToken(DBParser::STRING_LIT, 0);
}

tree::TerminalNode* DBParser::CreateTableStmtContext::AS() {
  return getToken(DBParser::AS, 0);
}

DBParser::QualifiedNameContext* DBParser::CreateTableStmtContext::qualifiedName() {
  return getRuleContext<DBParser::QualifiedNameContext>(0);
}


size_t DBParser::CreateTableStmtContext::getRuleIndex() const {
  return DBParser::RuleCreateTableStmt;
}


std::any DBParser::CreateTableStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitCreateTableStmt(this);
  else
    return visitor->visitChildren(this);
}

DBParser::CreateTableStmtContext* DBParser::createTableStmt() {
  CreateTableStmtContext *_localctx = _tracker.createInstance<CreateTableStmtContext>(_ctx, getState());
  enterRule(_localctx, 20, DBParser::RuleCreateTableStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(207);
    match(DBParser::CREATE);
    setState(208);
    match(DBParser::TABLE);
    setState(209);
    match(DBParser::STRING_LIT);
    setState(210);
    match(DBParser::AS);
    setState(211);
    qualifiedName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateRoleStmtContext ------------------------------------------------------------------

DBParser::CreateRoleStmtContext::CreateRoleStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::CreateRoleStmtContext::CREATE() {
  return getToken(DBParser::CREATE, 0);
}

tree::TerminalNode* DBParser::CreateRoleStmtContext::ROLE() {
  return getToken(DBParser::ROLE, 0);
}

tree::TerminalNode* DBParser::CreateRoleStmtContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}


size_t DBParser::CreateRoleStmtContext::getRuleIndex() const {
  return DBParser::RuleCreateRoleStmt;
}


std::any DBParser::CreateRoleStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitCreateRoleStmt(this);
  else
    return visitor->visitChildren(this);
}

DBParser::CreateRoleStmtContext* DBParser::createRoleStmt() {
  CreateRoleStmtContext *_localctx = _tracker.createInstance<CreateRoleStmtContext>(_ctx, getState());
  enterRule(_localctx, 22, DBParser::RuleCreateRoleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(213);
    match(DBParser::CREATE);
    setState(214);
    match(DBParser::ROLE);
    setState(215);
    match(DBParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateApiKeyStmtContext ------------------------------------------------------------------

DBParser::CreateApiKeyStmtContext::CreateApiKeyStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::CreateApiKeyStmtContext::CREATE() {
  return getToken(DBParser::CREATE, 0);
}

tree::TerminalNode* DBParser::CreateApiKeyStmtContext::API_KEY() {
  return getToken(DBParser::API_KEY, 0);
}

tree::TerminalNode* DBParser::CreateApiKeyStmtContext::FOR() {
  return getToken(DBParser::FOR, 0);
}

tree::TerminalNode* DBParser::CreateApiKeyStmtContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}

tree::TerminalNode* DBParser::CreateApiKeyStmtContext::EXPIRES() {
  return getToken(DBParser::EXPIRES, 0);
}

tree::TerminalNode* DBParser::CreateApiKeyStmtContext::IN() {
  return getToken(DBParser::IN, 0);
}

tree::TerminalNode* DBParser::CreateApiKeyStmtContext::DURATION_LIT() {
  return getToken(DBParser::DURATION_LIT, 0);
}


size_t DBParser::CreateApiKeyStmtContext::getRuleIndex() const {
  return DBParser::RuleCreateApiKeyStmt;
}


std::any DBParser::CreateApiKeyStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitCreateApiKeyStmt(this);
  else
    return visitor->visitChildren(this);
}

DBParser::CreateApiKeyStmtContext* DBParser::createApiKeyStmt() {
  CreateApiKeyStmtContext *_localctx = _tracker.createInstance<CreateApiKeyStmtContext>(_ctx, getState());
  enterRule(_localctx, 24, DBParser::RuleCreateApiKeyStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(217);
    match(DBParser::CREATE);
    setState(218);
    match(DBParser::API_KEY);
    setState(219);
    match(DBParser::FOR);
    setState(220);
    match(DBParser::IDENTIFIER);
    setState(221);
    match(DBParser::EXPIRES);
    setState(222);
    match(DBParser::IN);
    setState(223);
    match(DBParser::DURATION_LIT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GrantStmtContext ------------------------------------------------------------------

DBParser::GrantStmtContext::GrantStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::GrantStmtContext::GRANT() {
  return getToken(DBParser::GRANT, 0);
}

tree::TerminalNode* DBParser::GrantStmtContext::TO() {
  return getToken(DBParser::TO, 0);
}

tree::TerminalNode* DBParser::GrantStmtContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}

tree::TerminalNode* DBParser::GrantStmtContext::LBRACE() {
  return getToken(DBParser::LBRACE, 0);
}

tree::TerminalNode* DBParser::GrantStmtContext::RBRACE() {
  return getToken(DBParser::RBRACE, 0);
}

std::vector<DBParser::IamRuleContext *> DBParser::GrantStmtContext::iamRule() {
  return getRuleContexts<DBParser::IamRuleContext>();
}

DBParser::IamRuleContext* DBParser::GrantStmtContext::iamRule(size_t i) {
  return getRuleContext<DBParser::IamRuleContext>(i);
}


size_t DBParser::GrantStmtContext::getRuleIndex() const {
  return DBParser::RuleGrantStmt;
}


std::any DBParser::GrantStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitGrantStmt(this);
  else
    return visitor->visitChildren(this);
}

DBParser::GrantStmtContext* DBParser::grantStmt() {
  GrantStmtContext *_localctx = _tracker.createInstance<GrantStmtContext>(_ctx, getState());
  enterRule(_localctx, 26, DBParser::RuleGrantStmt);
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
    setState(225);
    match(DBParser::GRANT);
    setState(226);
    match(DBParser::TO);
    setState(227);
    match(DBParser::IDENTIFIER);
    setState(228);
    match(DBParser::LBRACE);
    setState(232);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == DBParser::ALLOW

    || _la == DBParser::DENY) {
      setState(229);
      iamRule();
      setState(234);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(235);
    match(DBParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IamRuleContext ------------------------------------------------------------------

DBParser::IamRuleContext::IamRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t DBParser::IamRuleContext::getRuleIndex() const {
  return DBParser::RuleIamRule;
}

void DBParser::IamRuleContext::copyFrom(IamRuleContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DenyRuleContext ------------------------------------------------------------------

tree::TerminalNode* DBParser::DenyRuleContext::DENY() {
  return getToken(DBParser::DENY, 0);
}

DBParser::IamPermOrStarContext* DBParser::DenyRuleContext::iamPermOrStar() {
  return getRuleContext<DBParser::IamPermOrStarContext>(0);
}

tree::TerminalNode* DBParser::DenyRuleContext::ON() {
  return getToken(DBParser::ON, 0);
}

tree::TerminalNode* DBParser::DenyRuleContext::STRING_LIT() {
  return getToken(DBParser::STRING_LIT, 0);
}

DBParser::DenyRuleContext::DenyRuleContext(IamRuleContext *ctx) { copyFrom(ctx); }


std::any DBParser::DenyRuleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitDenyRule(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AllowRuleContext ------------------------------------------------------------------

tree::TerminalNode* DBParser::AllowRuleContext::ALLOW() {
  return getToken(DBParser::ALLOW, 0);
}

DBParser::IamPermListContext* DBParser::AllowRuleContext::iamPermList() {
  return getRuleContext<DBParser::IamPermListContext>(0);
}

tree::TerminalNode* DBParser::AllowRuleContext::ON() {
  return getToken(DBParser::ON, 0);
}

tree::TerminalNode* DBParser::AllowRuleContext::STRING_LIT() {
  return getToken(DBParser::STRING_LIT, 0);
}

DBParser::AllowRuleContext::AllowRuleContext(IamRuleContext *ctx) { copyFrom(ctx); }


std::any DBParser::AllowRuleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitAllowRule(this);
  else
    return visitor->visitChildren(this);
}
DBParser::IamRuleContext* DBParser::iamRule() {
  IamRuleContext *_localctx = _tracker.createInstance<IamRuleContext>(_ctx, getState());
  enterRule(_localctx, 28, DBParser::RuleIamRule);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(247);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DBParser::ALLOW: {
        _localctx = _tracker.createInstance<DBParser::AllowRuleContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(237);
        match(DBParser::ALLOW);
        setState(238);
        iamPermList();
        setState(239);
        match(DBParser::ON);
        setState(240);
        match(DBParser::STRING_LIT);
        break;
      }

      case DBParser::DENY: {
        _localctx = _tracker.createInstance<DBParser::DenyRuleContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(242);
        match(DBParser::DENY);
        setState(243);
        iamPermOrStar();
        setState(244);
        match(DBParser::ON);
        setState(245);
        match(DBParser::STRING_LIT);
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

//----------------- IamPermListContext ------------------------------------------------------------------

DBParser::IamPermListContext::IamPermListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<DBParser::IamPermContext *> DBParser::IamPermListContext::iamPerm() {
  return getRuleContexts<DBParser::IamPermContext>();
}

DBParser::IamPermContext* DBParser::IamPermListContext::iamPerm(size_t i) {
  return getRuleContext<DBParser::IamPermContext>(i);
}

std::vector<tree::TerminalNode *> DBParser::IamPermListContext::COMMA() {
  return getTokens(DBParser::COMMA);
}

tree::TerminalNode* DBParser::IamPermListContext::COMMA(size_t i) {
  return getToken(DBParser::COMMA, i);
}


size_t DBParser::IamPermListContext::getRuleIndex() const {
  return DBParser::RuleIamPermList;
}


std::any DBParser::IamPermListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitIamPermList(this);
  else
    return visitor->visitChildren(this);
}

DBParser::IamPermListContext* DBParser::iamPermList() {
  IamPermListContext *_localctx = _tracker.createInstance<IamPermListContext>(_ctx, getState());
  enterRule(_localctx, 30, DBParser::RuleIamPermList);
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
    setState(249);
    iamPerm();
    setState(254);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == DBParser::COMMA) {
      setState(250);
      match(DBParser::COMMA);
      setState(251);
      iamPerm();
      setState(256);
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

//----------------- IamPermContext ------------------------------------------------------------------

DBParser::IamPermContext::IamPermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::IamPermContext::READ() {
  return getToken(DBParser::READ, 0);
}

tree::TerminalNode* DBParser::IamPermContext::WRITE() {
  return getToken(DBParser::WRITE, 0);
}


size_t DBParser::IamPermContext::getRuleIndex() const {
  return DBParser::RuleIamPerm;
}


std::any DBParser::IamPermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitIamPerm(this);
  else
    return visitor->visitChildren(this);
}

DBParser::IamPermContext* DBParser::iamPerm() {
  IamPermContext *_localctx = _tracker.createInstance<IamPermContext>(_ctx, getState());
  enterRule(_localctx, 32, DBParser::RuleIamPerm);
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
    setState(257);
    _la = _input->LA(1);
    if (!(_la == DBParser::READ

    || _la == DBParser::WRITE)) {
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

//----------------- IamPermOrStarContext ------------------------------------------------------------------

DBParser::IamPermOrStarContext::IamPermOrStarContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<DBParser::IamPermContext *> DBParser::IamPermOrStarContext::iamPerm() {
  return getRuleContexts<DBParser::IamPermContext>();
}

DBParser::IamPermContext* DBParser::IamPermOrStarContext::iamPerm(size_t i) {
  return getRuleContext<DBParser::IamPermContext>(i);
}

std::vector<tree::TerminalNode *> DBParser::IamPermOrStarContext::COMMA() {
  return getTokens(DBParser::COMMA);
}

tree::TerminalNode* DBParser::IamPermOrStarContext::COMMA(size_t i) {
  return getToken(DBParser::COMMA, i);
}

tree::TerminalNode* DBParser::IamPermOrStarContext::STAR() {
  return getToken(DBParser::STAR, 0);
}


size_t DBParser::IamPermOrStarContext::getRuleIndex() const {
  return DBParser::RuleIamPermOrStar;
}


std::any DBParser::IamPermOrStarContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitIamPermOrStar(this);
  else
    return visitor->visitChildren(this);
}

DBParser::IamPermOrStarContext* DBParser::iamPermOrStar() {
  IamPermOrStarContext *_localctx = _tracker.createInstance<IamPermOrStarContext>(_ctx, getState());
  enterRule(_localctx, 34, DBParser::RuleIamPermOrStar);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(268);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DBParser::READ:
      case DBParser::WRITE: {
        enterOuterAlt(_localctx, 1);
        setState(259);
        iamPerm();
        setState(264);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == DBParser::COMMA) {
          setState(260);
          match(DBParser::COMMA);
          setState(261);
          iamPerm();
          setState(266);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

      case DBParser::STAR: {
        enterOuterAlt(_localctx, 2);
        setState(267);
        match(DBParser::STAR);
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

//----------------- QueryStmtContext ------------------------------------------------------------------

DBParser::QueryStmtContext::QueryStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DBParser::FromClauseContext* DBParser::QueryStmtContext::fromClause() {
  return getRuleContext<DBParser::FromClauseContext>(0);
}

DBParser::SelectClauseContext* DBParser::QueryStmtContext::selectClause() {
  return getRuleContext<DBParser::SelectClauseContext>(0);
}

std::vector<DBParser::LetBindingContext *> DBParser::QueryStmtContext::letBinding() {
  return getRuleContexts<DBParser::LetBindingContext>();
}

DBParser::LetBindingContext* DBParser::QueryStmtContext::letBinding(size_t i) {
  return getRuleContext<DBParser::LetBindingContext>(i);
}

std::vector<DBParser::JoinClauseContext *> DBParser::QueryStmtContext::joinClause() {
  return getRuleContexts<DBParser::JoinClauseContext>();
}

DBParser::JoinClauseContext* DBParser::QueryStmtContext::joinClause(size_t i) {
  return getRuleContext<DBParser::JoinClauseContext>(i);
}

DBParser::WhereClauseContext* DBParser::QueryStmtContext::whereClause() {
  return getRuleContext<DBParser::WhereClauseContext>(0);
}

DBParser::GroupByClauseContext* DBParser::QueryStmtContext::groupByClause() {
  return getRuleContext<DBParser::GroupByClauseContext>(0);
}

DBParser::HavingClauseContext* DBParser::QueryStmtContext::havingClause() {
  return getRuleContext<DBParser::HavingClauseContext>(0);
}

DBParser::OrderByClauseContext* DBParser::QueryStmtContext::orderByClause() {
  return getRuleContext<DBParser::OrderByClauseContext>(0);
}

DBParser::LimitClauseContext* DBParser::QueryStmtContext::limitClause() {
  return getRuleContext<DBParser::LimitClauseContext>(0);
}


size_t DBParser::QueryStmtContext::getRuleIndex() const {
  return DBParser::RuleQueryStmt;
}


std::any DBParser::QueryStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitQueryStmt(this);
  else
    return visitor->visitChildren(this);
}

DBParser::QueryStmtContext* DBParser::queryStmt() {
  QueryStmtContext *_localctx = _tracker.createInstance<QueryStmtContext>(_ctx, getState());
  enterRule(_localctx, 36, DBParser::RuleQueryStmt);
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
    setState(273);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == DBParser::LET) {
      setState(270);
      letBinding();
      setState(275);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(276);
    fromClause();
    setState(280);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == DBParser::JOIN

    || _la == DBParser::LEFT) {
      setState(277);
      joinClause();
      setState(282);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(284);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::WHERE) {
      setState(283);
      whereClause();
    }
    setState(287);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::GROUP) {
      setState(286);
      groupByClause();
    }
    setState(292);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == DBParser::LET) {
      setState(289);
      letBinding();
      setState(294);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(296);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::HAVING) {
      setState(295);
      havingClause();
    }
    setState(298);
    selectClause();
    setState(300);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::ORDER) {
      setState(299);
      orderByClause();
    }
    setState(303);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::LIMIT) {
      setState(302);
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

//----------------- FromClauseContext ------------------------------------------------------------------

DBParser::FromClauseContext::FromClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::FromClauseContext::FROM() {
  return getToken(DBParser::FROM, 0);
}

tree::TerminalNode* DBParser::FromClauseContext::STRING_LIT() {
  return getToken(DBParser::STRING_LIT, 0);
}

tree::TerminalNode* DBParser::FromClauseContext::AS() {
  return getToken(DBParser::AS, 0);
}

tree::TerminalNode* DBParser::FromClauseContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}

tree::TerminalNode* DBParser::FromClauseContext::COLON() {
  return getToken(DBParser::COLON, 0);
}

DBParser::QualifiedNameContext* DBParser::FromClauseContext::qualifiedName() {
  return getRuleContext<DBParser::QualifiedNameContext>(0);
}


size_t DBParser::FromClauseContext::getRuleIndex() const {
  return DBParser::RuleFromClause;
}


std::any DBParser::FromClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitFromClause(this);
  else
    return visitor->visitChildren(this);
}

DBParser::FromClauseContext* DBParser::fromClause() {
  FromClauseContext *_localctx = _tracker.createInstance<FromClauseContext>(_ctx, getState());
  enterRule(_localctx, 38, DBParser::RuleFromClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(305);
    match(DBParser::FROM);
    setState(306);
    match(DBParser::STRING_LIT);
    setState(307);
    match(DBParser::AS);
    setState(308);
    match(DBParser::IDENTIFIER);
    setState(309);
    match(DBParser::COLON);
    setState(310);
    qualifiedName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JoinClauseContext ------------------------------------------------------------------

DBParser::JoinClauseContext::JoinClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::JoinClauseContext::JOIN() {
  return getToken(DBParser::JOIN, 0);
}

tree::TerminalNode* DBParser::JoinClauseContext::STRING_LIT() {
  return getToken(DBParser::STRING_LIT, 0);
}

tree::TerminalNode* DBParser::JoinClauseContext::AS() {
  return getToken(DBParser::AS, 0);
}

tree::TerminalNode* DBParser::JoinClauseContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}

tree::TerminalNode* DBParser::JoinClauseContext::COLON() {
  return getToken(DBParser::COLON, 0);
}

DBParser::QualifiedNameContext* DBParser::JoinClauseContext::qualifiedName() {
  return getRuleContext<DBParser::QualifiedNameContext>(0);
}

tree::TerminalNode* DBParser::JoinClauseContext::ON() {
  return getToken(DBParser::ON, 0);
}

DBParser::ExprContext* DBParser::JoinClauseContext::expr() {
  return getRuleContext<DBParser::ExprContext>(0);
}

tree::TerminalNode* DBParser::JoinClauseContext::LEFT() {
  return getToken(DBParser::LEFT, 0);
}


size_t DBParser::JoinClauseContext::getRuleIndex() const {
  return DBParser::RuleJoinClause;
}


std::any DBParser::JoinClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitJoinClause(this);
  else
    return visitor->visitChildren(this);
}

DBParser::JoinClauseContext* DBParser::joinClause() {
  JoinClauseContext *_localctx = _tracker.createInstance<JoinClauseContext>(_ctx, getState());
  enterRule(_localctx, 40, DBParser::RuleJoinClause);
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
    setState(313);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::LEFT) {
      setState(312);
      match(DBParser::LEFT);
    }
    setState(315);
    match(DBParser::JOIN);
    setState(316);
    match(DBParser::STRING_LIT);
    setState(317);
    match(DBParser::AS);
    setState(318);
    match(DBParser::IDENTIFIER);
    setState(319);
    match(DBParser::COLON);
    setState(320);
    qualifiedName();
    setState(321);
    match(DBParser::ON);
    setState(322);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhereClauseContext ------------------------------------------------------------------

DBParser::WhereClauseContext::WhereClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::WhereClauseContext::WHERE() {
  return getToken(DBParser::WHERE, 0);
}

DBParser::ExprContext* DBParser::WhereClauseContext::expr() {
  return getRuleContext<DBParser::ExprContext>(0);
}


size_t DBParser::WhereClauseContext::getRuleIndex() const {
  return DBParser::RuleWhereClause;
}


std::any DBParser::WhereClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitWhereClause(this);
  else
    return visitor->visitChildren(this);
}

DBParser::WhereClauseContext* DBParser::whereClause() {
  WhereClauseContext *_localctx = _tracker.createInstance<WhereClauseContext>(_ctx, getState());
  enterRule(_localctx, 42, DBParser::RuleWhereClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(324);
    match(DBParser::WHERE);
    setState(325);
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

DBParser::GroupByClauseContext::GroupByClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::GroupByClauseContext::GROUP() {
  return getToken(DBParser::GROUP, 0);
}

tree::TerminalNode* DBParser::GroupByClauseContext::BY() {
  return getToken(DBParser::BY, 0);
}

DBParser::ExprListContext* DBParser::GroupByClauseContext::exprList() {
  return getRuleContext<DBParser::ExprListContext>(0);
}


size_t DBParser::GroupByClauseContext::getRuleIndex() const {
  return DBParser::RuleGroupByClause;
}


std::any DBParser::GroupByClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitGroupByClause(this);
  else
    return visitor->visitChildren(this);
}

DBParser::GroupByClauseContext* DBParser::groupByClause() {
  GroupByClauseContext *_localctx = _tracker.createInstance<GroupByClauseContext>(_ctx, getState());
  enterRule(_localctx, 44, DBParser::RuleGroupByClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(327);
    match(DBParser::GROUP);
    setState(328);
    match(DBParser::BY);
    setState(329);
    exprList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HavingClauseContext ------------------------------------------------------------------

DBParser::HavingClauseContext::HavingClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::HavingClauseContext::HAVING() {
  return getToken(DBParser::HAVING, 0);
}

DBParser::ExprContext* DBParser::HavingClauseContext::expr() {
  return getRuleContext<DBParser::ExprContext>(0);
}


size_t DBParser::HavingClauseContext::getRuleIndex() const {
  return DBParser::RuleHavingClause;
}


std::any DBParser::HavingClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitHavingClause(this);
  else
    return visitor->visitChildren(this);
}

DBParser::HavingClauseContext* DBParser::havingClause() {
  HavingClauseContext *_localctx = _tracker.createInstance<HavingClauseContext>(_ctx, getState());
  enterRule(_localctx, 46, DBParser::RuleHavingClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(331);
    match(DBParser::HAVING);
    setState(332);
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

DBParser::SelectClauseContext::SelectClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::SelectClauseContext::SELECT() {
  return getToken(DBParser::SELECT, 0);
}

DBParser::ProjectionBlockContext* DBParser::SelectClauseContext::projectionBlock() {
  return getRuleContext<DBParser::ProjectionBlockContext>(0);
}


size_t DBParser::SelectClauseContext::getRuleIndex() const {
  return DBParser::RuleSelectClause;
}


std::any DBParser::SelectClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitSelectClause(this);
  else
    return visitor->visitChildren(this);
}

DBParser::SelectClauseContext* DBParser::selectClause() {
  SelectClauseContext *_localctx = _tracker.createInstance<SelectClauseContext>(_ctx, getState());
  enterRule(_localctx, 48, DBParser::RuleSelectClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(334);
    match(DBParser::SELECT);
    setState(335);
    projectionBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProjectionBlockContext ------------------------------------------------------------------

DBParser::ProjectionBlockContext::ProjectionBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::ProjectionBlockContext::LBRACE() {
  return getToken(DBParser::LBRACE, 0);
}

std::vector<DBParser::ProjectionEntryContext *> DBParser::ProjectionBlockContext::projectionEntry() {
  return getRuleContexts<DBParser::ProjectionEntryContext>();
}

DBParser::ProjectionEntryContext* DBParser::ProjectionBlockContext::projectionEntry(size_t i) {
  return getRuleContext<DBParser::ProjectionEntryContext>(i);
}

tree::TerminalNode* DBParser::ProjectionBlockContext::RBRACE() {
  return getToken(DBParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> DBParser::ProjectionBlockContext::COMMA() {
  return getTokens(DBParser::COMMA);
}

tree::TerminalNode* DBParser::ProjectionBlockContext::COMMA(size_t i) {
  return getToken(DBParser::COMMA, i);
}


size_t DBParser::ProjectionBlockContext::getRuleIndex() const {
  return DBParser::RuleProjectionBlock;
}


std::any DBParser::ProjectionBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitProjectionBlock(this);
  else
    return visitor->visitChildren(this);
}

DBParser::ProjectionBlockContext* DBParser::projectionBlock() {
  ProjectionBlockContext *_localctx = _tracker.createInstance<ProjectionBlockContext>(_ctx, getState());
  enterRule(_localctx, 50, DBParser::RuleProjectionBlock);
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
    setState(337);
    match(DBParser::LBRACE);
    setState(338);
    projectionEntry();
    setState(343);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(339);
        match(DBParser::COMMA);
        setState(340);
        projectionEntry(); 
      }
      setState(345);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    }
    setState(347);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::COMMA) {
      setState(346);
      match(DBParser::COMMA);
    }
    setState(349);
    match(DBParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProjectionEntryContext ------------------------------------------------------------------

DBParser::ProjectionEntryContext::ProjectionEntryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t DBParser::ProjectionEntryContext::getRuleIndex() const {
  return DBParser::RuleProjectionEntry;
}

void DBParser::ProjectionEntryContext::copyFrom(ProjectionEntryContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LabeledProjectionContext ------------------------------------------------------------------

tree::TerminalNode* DBParser::LabeledProjectionContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}

tree::TerminalNode* DBParser::LabeledProjectionContext::COLON() {
  return getToken(DBParser::COLON, 0);
}

DBParser::ExprContext* DBParser::LabeledProjectionContext::expr() {
  return getRuleContext<DBParser::ExprContext>(0);
}

DBParser::LabeledProjectionContext::LabeledProjectionContext(ProjectionEntryContext *ctx) { copyFrom(ctx); }


std::any DBParser::LabeledProjectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitLabeledProjection(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NestedProjectionContext ------------------------------------------------------------------

tree::TerminalNode* DBParser::NestedProjectionContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}

tree::TerminalNode* DBParser::NestedProjectionContext::COLON() {
  return getToken(DBParser::COLON, 0);
}

DBParser::ProjectionBlockContext* DBParser::NestedProjectionContext::projectionBlock() {
  return getRuleContext<DBParser::ProjectionBlockContext>(0);
}

DBParser::NestedProjectionContext::NestedProjectionContext(ProjectionEntryContext *ctx) { copyFrom(ctx); }


std::any DBParser::NestedProjectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitNestedProjection(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ShorthandProjectionContext ------------------------------------------------------------------

tree::TerminalNode* DBParser::ShorthandProjectionContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}

DBParser::ShorthandProjectionContext::ShorthandProjectionContext(ProjectionEntryContext *ctx) { copyFrom(ctx); }


std::any DBParser::ShorthandProjectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitShorthandProjection(this);
  else
    return visitor->visitChildren(this);
}
DBParser::ProjectionEntryContext* DBParser::projectionEntry() {
  ProjectionEntryContext *_localctx = _tracker.createInstance<ProjectionEntryContext>(_ctx, getState());
  enterRule(_localctx, 52, DBParser::RuleProjectionEntry);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(358);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<DBParser::LabeledProjectionContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(351);
      match(DBParser::IDENTIFIER);
      setState(352);
      match(DBParser::COLON);
      setState(353);
      expr(0);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<DBParser::ShorthandProjectionContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(354);
      match(DBParser::IDENTIFIER);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<DBParser::NestedProjectionContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(355);
      match(DBParser::IDENTIFIER);
      setState(356);
      match(DBParser::COLON);
      setState(357);
      projectionBlock();
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

//----------------- OrderByClauseContext ------------------------------------------------------------------

DBParser::OrderByClauseContext::OrderByClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::OrderByClauseContext::ORDER() {
  return getToken(DBParser::ORDER, 0);
}

tree::TerminalNode* DBParser::OrderByClauseContext::BY() {
  return getToken(DBParser::BY, 0);
}

std::vector<DBParser::OrderItemContext *> DBParser::OrderByClauseContext::orderItem() {
  return getRuleContexts<DBParser::OrderItemContext>();
}

DBParser::OrderItemContext* DBParser::OrderByClauseContext::orderItem(size_t i) {
  return getRuleContext<DBParser::OrderItemContext>(i);
}

std::vector<tree::TerminalNode *> DBParser::OrderByClauseContext::COMMA() {
  return getTokens(DBParser::COMMA);
}

tree::TerminalNode* DBParser::OrderByClauseContext::COMMA(size_t i) {
  return getToken(DBParser::COMMA, i);
}


size_t DBParser::OrderByClauseContext::getRuleIndex() const {
  return DBParser::RuleOrderByClause;
}


std::any DBParser::OrderByClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitOrderByClause(this);
  else
    return visitor->visitChildren(this);
}

DBParser::OrderByClauseContext* DBParser::orderByClause() {
  OrderByClauseContext *_localctx = _tracker.createInstance<OrderByClauseContext>(_ctx, getState());
  enterRule(_localctx, 54, DBParser::RuleOrderByClause);
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
    setState(360);
    match(DBParser::ORDER);
    setState(361);
    match(DBParser::BY);
    setState(362);
    orderItem();
    setState(367);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == DBParser::COMMA) {
      setState(363);
      match(DBParser::COMMA);
      setState(364);
      orderItem();
      setState(369);
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

//----------------- OrderItemContext ------------------------------------------------------------------

DBParser::OrderItemContext::OrderItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DBParser::ExprContext* DBParser::OrderItemContext::expr() {
  return getRuleContext<DBParser::ExprContext>(0);
}

tree::TerminalNode* DBParser::OrderItemContext::ASC() {
  return getToken(DBParser::ASC, 0);
}

tree::TerminalNode* DBParser::OrderItemContext::DESC() {
  return getToken(DBParser::DESC, 0);
}


size_t DBParser::OrderItemContext::getRuleIndex() const {
  return DBParser::RuleOrderItem;
}


std::any DBParser::OrderItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitOrderItem(this);
  else
    return visitor->visitChildren(this);
}

DBParser::OrderItemContext* DBParser::orderItem() {
  OrderItemContext *_localctx = _tracker.createInstance<OrderItemContext>(_ctx, getState());
  enterRule(_localctx, 56, DBParser::RuleOrderItem);
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
    setState(370);
    expr(0);
    setState(372);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::ASC

    || _la == DBParser::DESC) {
      setState(371);
      _la = _input->LA(1);
      if (!(_la == DBParser::ASC

      || _la == DBParser::DESC)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
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

DBParser::LimitClauseContext::LimitClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::LimitClauseContext::LIMIT() {
  return getToken(DBParser::LIMIT, 0);
}

tree::TerminalNode* DBParser::LimitClauseContext::INTEGER_LIT() {
  return getToken(DBParser::INTEGER_LIT, 0);
}


size_t DBParser::LimitClauseContext::getRuleIndex() const {
  return DBParser::RuleLimitClause;
}


std::any DBParser::LimitClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitLimitClause(this);
  else
    return visitor->visitChildren(this);
}

DBParser::LimitClauseContext* DBParser::limitClause() {
  LimitClauseContext *_localctx = _tracker.createInstance<LimitClauseContext>(_ctx, getState());
  enterRule(_localctx, 58, DBParser::RuleLimitClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(374);
    match(DBParser::LIMIT);
    setState(375);
    match(DBParser::INTEGER_LIT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LetBindingContext ------------------------------------------------------------------

DBParser::LetBindingContext::LetBindingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::LetBindingContext::LET() {
  return getToken(DBParser::LET, 0);
}

tree::TerminalNode* DBParser::LetBindingContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}

tree::TerminalNode* DBParser::LetBindingContext::ASSIGN() {
  return getToken(DBParser::ASSIGN, 0);
}

DBParser::ExprContext* DBParser::LetBindingContext::expr() {
  return getRuleContext<DBParser::ExprContext>(0);
}

tree::TerminalNode* DBParser::LetBindingContext::COLON() {
  return getToken(DBParser::COLON, 0);
}

DBParser::TypeRefContext* DBParser::LetBindingContext::typeRef() {
  return getRuleContext<DBParser::TypeRefContext>(0);
}


size_t DBParser::LetBindingContext::getRuleIndex() const {
  return DBParser::RuleLetBinding;
}


std::any DBParser::LetBindingContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitLetBinding(this);
  else
    return visitor->visitChildren(this);
}

DBParser::LetBindingContext* DBParser::letBinding() {
  LetBindingContext *_localctx = _tracker.createInstance<LetBindingContext>(_ctx, getState());
  enterRule(_localctx, 60, DBParser::RuleLetBinding);
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
    setState(377);
    match(DBParser::LET);
    setState(378);
    match(DBParser::IDENTIFIER);
    setState(381);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::COLON) {
      setState(379);
      match(DBParser::COLON);
      setState(380);
      typeRef();
    }
    setState(383);
    match(DBParser::ASSIGN);
    setState(384);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertStmtContext ------------------------------------------------------------------

DBParser::InsertStmtContext::InsertStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::InsertStmtContext::INSERT() {
  return getToken(DBParser::INSERT, 0);
}

tree::TerminalNode* DBParser::InsertStmtContext::INTO() {
  return getToken(DBParser::INTO, 0);
}

tree::TerminalNode* DBParser::InsertStmtContext::STRING_LIT() {
  return getToken(DBParser::STRING_LIT, 0);
}

tree::TerminalNode* DBParser::InsertStmtContext::AS() {
  return getToken(DBParser::AS, 0);
}

DBParser::QualifiedNameContext* DBParser::InsertStmtContext::qualifiedName() {
  return getRuleContext<DBParser::QualifiedNameContext>(0);
}

DBParser::LiteralInsertBodyContext* DBParser::InsertStmtContext::literalInsertBody() {
  return getRuleContext<DBParser::LiteralInsertBodyContext>(0);
}

DBParser::PipelineInsertBodyContext* DBParser::InsertStmtContext::pipelineInsertBody() {
  return getRuleContext<DBParser::PipelineInsertBodyContext>(0);
}

DBParser::ReturningClauseContext* DBParser::InsertStmtContext::returningClause() {
  return getRuleContext<DBParser::ReturningClauseContext>(0);
}


size_t DBParser::InsertStmtContext::getRuleIndex() const {
  return DBParser::RuleInsertStmt;
}


std::any DBParser::InsertStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitInsertStmt(this);
  else
    return visitor->visitChildren(this);
}

DBParser::InsertStmtContext* DBParser::insertStmt() {
  InsertStmtContext *_localctx = _tracker.createInstance<InsertStmtContext>(_ctx, getState());
  enterRule(_localctx, 62, DBParser::RuleInsertStmt);
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
    setState(386);
    match(DBParser::INSERT);
    setState(387);
    match(DBParser::INTO);
    setState(388);
    match(DBParser::STRING_LIT);
    setState(389);
    match(DBParser::AS);
    setState(390);
    qualifiedName();
    setState(393);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DBParser::LBRACE: {
        setState(391);
        literalInsertBody();
        break;
      }

      case DBParser::FROM: {
        setState(392);
        pipelineInsertBody();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(396);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::RETURNING) {
      setState(395);
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

//----------------- LiteralInsertBodyContext ------------------------------------------------------------------

DBParser::LiteralInsertBodyContext::LiteralInsertBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<DBParser::ValueBlockContext *> DBParser::LiteralInsertBodyContext::valueBlock() {
  return getRuleContexts<DBParser::ValueBlockContext>();
}

DBParser::ValueBlockContext* DBParser::LiteralInsertBodyContext::valueBlock(size_t i) {
  return getRuleContext<DBParser::ValueBlockContext>(i);
}

std::vector<tree::TerminalNode *> DBParser::LiteralInsertBodyContext::COMMA() {
  return getTokens(DBParser::COMMA);
}

tree::TerminalNode* DBParser::LiteralInsertBodyContext::COMMA(size_t i) {
  return getToken(DBParser::COMMA, i);
}


size_t DBParser::LiteralInsertBodyContext::getRuleIndex() const {
  return DBParser::RuleLiteralInsertBody;
}


std::any DBParser::LiteralInsertBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitLiteralInsertBody(this);
  else
    return visitor->visitChildren(this);
}

DBParser::LiteralInsertBodyContext* DBParser::literalInsertBody() {
  LiteralInsertBodyContext *_localctx = _tracker.createInstance<LiteralInsertBodyContext>(_ctx, getState());
  enterRule(_localctx, 64, DBParser::RuleLiteralInsertBody);
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
    setState(398);
    valueBlock();
    setState(403);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == DBParser::COMMA) {
      setState(399);
      match(DBParser::COMMA);
      setState(400);
      valueBlock();
      setState(405);
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

//----------------- PipelineInsertBodyContext ------------------------------------------------------------------

DBParser::PipelineInsertBodyContext::PipelineInsertBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DBParser::FromClauseContext* DBParser::PipelineInsertBodyContext::fromClause() {
  return getRuleContext<DBParser::FromClauseContext>(0);
}

DBParser::SelectClauseContext* DBParser::PipelineInsertBodyContext::selectClause() {
  return getRuleContext<DBParser::SelectClauseContext>(0);
}

std::vector<DBParser::JoinClauseContext *> DBParser::PipelineInsertBodyContext::joinClause() {
  return getRuleContexts<DBParser::JoinClauseContext>();
}

DBParser::JoinClauseContext* DBParser::PipelineInsertBodyContext::joinClause(size_t i) {
  return getRuleContext<DBParser::JoinClauseContext>(i);
}

DBParser::WhereClauseContext* DBParser::PipelineInsertBodyContext::whereClause() {
  return getRuleContext<DBParser::WhereClauseContext>(0);
}

std::vector<DBParser::LetBindingContext *> DBParser::PipelineInsertBodyContext::letBinding() {
  return getRuleContexts<DBParser::LetBindingContext>();
}

DBParser::LetBindingContext* DBParser::PipelineInsertBodyContext::letBinding(size_t i) {
  return getRuleContext<DBParser::LetBindingContext>(i);
}


size_t DBParser::PipelineInsertBodyContext::getRuleIndex() const {
  return DBParser::RulePipelineInsertBody;
}


std::any DBParser::PipelineInsertBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitPipelineInsertBody(this);
  else
    return visitor->visitChildren(this);
}

DBParser::PipelineInsertBodyContext* DBParser::pipelineInsertBody() {
  PipelineInsertBodyContext *_localctx = _tracker.createInstance<PipelineInsertBodyContext>(_ctx, getState());
  enterRule(_localctx, 66, DBParser::RulePipelineInsertBody);
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
    fromClause();
    setState(410);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == DBParser::JOIN

    || _la == DBParser::LEFT) {
      setState(407);
      joinClause();
      setState(412);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(414);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::WHERE) {
      setState(413);
      whereClause();
    }
    setState(419);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == DBParser::LET) {
      setState(416);
      letBinding();
      setState(421);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(422);
    selectClause();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueBlockContext ------------------------------------------------------------------

DBParser::ValueBlockContext::ValueBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::ValueBlockContext::LBRACE() {
  return getToken(DBParser::LBRACE, 0);
}

std::vector<DBParser::ValueEntryContext *> DBParser::ValueBlockContext::valueEntry() {
  return getRuleContexts<DBParser::ValueEntryContext>();
}

DBParser::ValueEntryContext* DBParser::ValueBlockContext::valueEntry(size_t i) {
  return getRuleContext<DBParser::ValueEntryContext>(i);
}

tree::TerminalNode* DBParser::ValueBlockContext::RBRACE() {
  return getToken(DBParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> DBParser::ValueBlockContext::COMMA() {
  return getTokens(DBParser::COMMA);
}

tree::TerminalNode* DBParser::ValueBlockContext::COMMA(size_t i) {
  return getToken(DBParser::COMMA, i);
}


size_t DBParser::ValueBlockContext::getRuleIndex() const {
  return DBParser::RuleValueBlock;
}


std::any DBParser::ValueBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitValueBlock(this);
  else
    return visitor->visitChildren(this);
}

DBParser::ValueBlockContext* DBParser::valueBlock() {
  ValueBlockContext *_localctx = _tracker.createInstance<ValueBlockContext>(_ctx, getState());
  enterRule(_localctx, 68, DBParser::RuleValueBlock);
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
    setState(424);
    match(DBParser::LBRACE);
    setState(425);
    valueEntry();
    setState(430);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(426);
        match(DBParser::COMMA);
        setState(427);
        valueEntry(); 
      }
      setState(432);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    }
    setState(434);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::COMMA) {
      setState(433);
      match(DBParser::COMMA);
    }
    setState(436);
    match(DBParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueEntryContext ------------------------------------------------------------------

DBParser::ValueEntryContext::ValueEntryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::ValueEntryContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}

tree::TerminalNode* DBParser::ValueEntryContext::COLON() {
  return getToken(DBParser::COLON, 0);
}

DBParser::ExprContext* DBParser::ValueEntryContext::expr() {
  return getRuleContext<DBParser::ExprContext>(0);
}


size_t DBParser::ValueEntryContext::getRuleIndex() const {
  return DBParser::RuleValueEntry;
}


std::any DBParser::ValueEntryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitValueEntry(this);
  else
    return visitor->visitChildren(this);
}

DBParser::ValueEntryContext* DBParser::valueEntry() {
  ValueEntryContext *_localctx = _tracker.createInstance<ValueEntryContext>(_ctx, getState());
  enterRule(_localctx, 70, DBParser::RuleValueEntry);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(438);
    match(DBParser::IDENTIFIER);
    setState(439);
    match(DBParser::COLON);
    setState(440);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UpdateStmtContext ------------------------------------------------------------------

DBParser::UpdateStmtContext::UpdateStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::UpdateStmtContext::UPDATE() {
  return getToken(DBParser::UPDATE, 0);
}

tree::TerminalNode* DBParser::UpdateStmtContext::STRING_LIT() {
  return getToken(DBParser::STRING_LIT, 0);
}

tree::TerminalNode* DBParser::UpdateStmtContext::AS() {
  return getToken(DBParser::AS, 0);
}

tree::TerminalNode* DBParser::UpdateStmtContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}

tree::TerminalNode* DBParser::UpdateStmtContext::COLON() {
  return getToken(DBParser::COLON, 0);
}

DBParser::QualifiedNameContext* DBParser::UpdateStmtContext::qualifiedName() {
  return getRuleContext<DBParser::QualifiedNameContext>(0);
}

DBParser::SetClauseContext* DBParser::UpdateStmtContext::setClause() {
  return getRuleContext<DBParser::SetClauseContext>(0);
}

DBParser::WhereClauseContext* DBParser::UpdateStmtContext::whereClause() {
  return getRuleContext<DBParser::WhereClauseContext>(0);
}

std::vector<DBParser::LetBindingContext *> DBParser::UpdateStmtContext::letBinding() {
  return getRuleContexts<DBParser::LetBindingContext>();
}

DBParser::LetBindingContext* DBParser::UpdateStmtContext::letBinding(size_t i) {
  return getRuleContext<DBParser::LetBindingContext>(i);
}

DBParser::ReturningClauseContext* DBParser::UpdateStmtContext::returningClause() {
  return getRuleContext<DBParser::ReturningClauseContext>(0);
}


size_t DBParser::UpdateStmtContext::getRuleIndex() const {
  return DBParser::RuleUpdateStmt;
}


std::any DBParser::UpdateStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitUpdateStmt(this);
  else
    return visitor->visitChildren(this);
}

DBParser::UpdateStmtContext* DBParser::updateStmt() {
  UpdateStmtContext *_localctx = _tracker.createInstance<UpdateStmtContext>(_ctx, getState());
  enterRule(_localctx, 72, DBParser::RuleUpdateStmt);
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
    setState(442);
    match(DBParser::UPDATE);
    setState(443);
    match(DBParser::STRING_LIT);
    setState(444);
    match(DBParser::AS);
    setState(445);
    match(DBParser::IDENTIFIER);
    setState(446);
    match(DBParser::COLON);
    setState(447);
    qualifiedName();
    setState(449);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::WHERE) {
      setState(448);
      whereClause();
    }
    setState(454);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == DBParser::LET) {
      setState(451);
      letBinding();
      setState(456);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(457);
    setClause();
    setState(459);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::RETURNING) {
      setState(458);
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

DBParser::SetClauseContext::SetClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::SetClauseContext::SET() {
  return getToken(DBParser::SET, 0);
}

tree::TerminalNode* DBParser::SetClauseContext::LBRACE() {
  return getToken(DBParser::LBRACE, 0);
}

std::vector<DBParser::SetEntryContext *> DBParser::SetClauseContext::setEntry() {
  return getRuleContexts<DBParser::SetEntryContext>();
}

DBParser::SetEntryContext* DBParser::SetClauseContext::setEntry(size_t i) {
  return getRuleContext<DBParser::SetEntryContext>(i);
}

tree::TerminalNode* DBParser::SetClauseContext::RBRACE() {
  return getToken(DBParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> DBParser::SetClauseContext::COMMA() {
  return getTokens(DBParser::COMMA);
}

tree::TerminalNode* DBParser::SetClauseContext::COMMA(size_t i) {
  return getToken(DBParser::COMMA, i);
}


size_t DBParser::SetClauseContext::getRuleIndex() const {
  return DBParser::RuleSetClause;
}


std::any DBParser::SetClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitSetClause(this);
  else
    return visitor->visitChildren(this);
}

DBParser::SetClauseContext* DBParser::setClause() {
  SetClauseContext *_localctx = _tracker.createInstance<SetClauseContext>(_ctx, getState());
  enterRule(_localctx, 74, DBParser::RuleSetClause);
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
    setState(461);
    match(DBParser::SET);
    setState(462);
    match(DBParser::LBRACE);
    setState(463);
    setEntry();
    setState(468);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(464);
        match(DBParser::COMMA);
        setState(465);
        setEntry(); 
      }
      setState(470);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
    }
    setState(472);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::COMMA) {
      setState(471);
      match(DBParser::COMMA);
    }
    setState(474);
    match(DBParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SetEntryContext ------------------------------------------------------------------

DBParser::SetEntryContext::SetEntryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::SetEntryContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}

tree::TerminalNode* DBParser::SetEntryContext::COLON() {
  return getToken(DBParser::COLON, 0);
}

DBParser::ExprContext* DBParser::SetEntryContext::expr() {
  return getRuleContext<DBParser::ExprContext>(0);
}


size_t DBParser::SetEntryContext::getRuleIndex() const {
  return DBParser::RuleSetEntry;
}


std::any DBParser::SetEntryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitSetEntry(this);
  else
    return visitor->visitChildren(this);
}

DBParser::SetEntryContext* DBParser::setEntry() {
  SetEntryContext *_localctx = _tracker.createInstance<SetEntryContext>(_ctx, getState());
  enterRule(_localctx, 76, DBParser::RuleSetEntry);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(476);
    match(DBParser::IDENTIFIER);
    setState(477);
    match(DBParser::COLON);
    setState(478);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeleteStmtContext ------------------------------------------------------------------

DBParser::DeleteStmtContext::DeleteStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::DeleteStmtContext::DELETE() {
  return getToken(DBParser::DELETE, 0);
}

tree::TerminalNode* DBParser::DeleteStmtContext::FROM() {
  return getToken(DBParser::FROM, 0);
}

tree::TerminalNode* DBParser::DeleteStmtContext::STRING_LIT() {
  return getToken(DBParser::STRING_LIT, 0);
}

tree::TerminalNode* DBParser::DeleteStmtContext::AS() {
  return getToken(DBParser::AS, 0);
}

tree::TerminalNode* DBParser::DeleteStmtContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}

tree::TerminalNode* DBParser::DeleteStmtContext::COLON() {
  return getToken(DBParser::COLON, 0);
}

DBParser::QualifiedNameContext* DBParser::DeleteStmtContext::qualifiedName() {
  return getRuleContext<DBParser::QualifiedNameContext>(0);
}

DBParser::WhereClauseContext* DBParser::DeleteStmtContext::whereClause() {
  return getRuleContext<DBParser::WhereClauseContext>(0);
}

DBParser::ReturningClauseContext* DBParser::DeleteStmtContext::returningClause() {
  return getRuleContext<DBParser::ReturningClauseContext>(0);
}


size_t DBParser::DeleteStmtContext::getRuleIndex() const {
  return DBParser::RuleDeleteStmt;
}


std::any DBParser::DeleteStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitDeleteStmt(this);
  else
    return visitor->visitChildren(this);
}

DBParser::DeleteStmtContext* DBParser::deleteStmt() {
  DeleteStmtContext *_localctx = _tracker.createInstance<DeleteStmtContext>(_ctx, getState());
  enterRule(_localctx, 78, DBParser::RuleDeleteStmt);
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
    setState(480);
    match(DBParser::DELETE);
    setState(481);
    match(DBParser::FROM);
    setState(482);
    match(DBParser::STRING_LIT);
    setState(483);
    match(DBParser::AS);
    setState(484);
    match(DBParser::IDENTIFIER);
    setState(485);
    match(DBParser::COLON);
    setState(486);
    qualifiedName();
    setState(488);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::WHERE) {
      setState(487);
      whereClause();
    }
    setState(491);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::RETURNING) {
      setState(490);
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

//----------------- TruncateStmtContext ------------------------------------------------------------------

DBParser::TruncateStmtContext::TruncateStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::TruncateStmtContext::TRUNCATE() {
  return getToken(DBParser::TRUNCATE, 0);
}

tree::TerminalNode* DBParser::TruncateStmtContext::STRING_LIT() {
  return getToken(DBParser::STRING_LIT, 0);
}


size_t DBParser::TruncateStmtContext::getRuleIndex() const {
  return DBParser::RuleTruncateStmt;
}


std::any DBParser::TruncateStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitTruncateStmt(this);
  else
    return visitor->visitChildren(this);
}

DBParser::TruncateStmtContext* DBParser::truncateStmt() {
  TruncateStmtContext *_localctx = _tracker.createInstance<TruncateStmtContext>(_ctx, getState());
  enterRule(_localctx, 80, DBParser::RuleTruncateStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(493);
    match(DBParser::TRUNCATE);
    setState(494);
    match(DBParser::STRING_LIT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UpsertStmtContext ------------------------------------------------------------------

DBParser::UpsertStmtContext::UpsertStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::UpsertStmtContext::UPSERT() {
  return getToken(DBParser::UPSERT, 0);
}

tree::TerminalNode* DBParser::UpsertStmtContext::INTO() {
  return getToken(DBParser::INTO, 0);
}

tree::TerminalNode* DBParser::UpsertStmtContext::STRING_LIT() {
  return getToken(DBParser::STRING_LIT, 0);
}

tree::TerminalNode* DBParser::UpsertStmtContext::AS() {
  return getToken(DBParser::AS, 0);
}

DBParser::QualifiedNameContext* DBParser::UpsertStmtContext::qualifiedName() {
  return getRuleContext<DBParser::QualifiedNameContext>(0);
}

std::vector<tree::TerminalNode *> DBParser::UpsertStmtContext::CONFLICT() {
  return getTokens(DBParser::CONFLICT);
}

tree::TerminalNode* DBParser::UpsertStmtContext::CONFLICT(size_t i) {
  return getToken(DBParser::CONFLICT, i);
}

std::vector<tree::TerminalNode *> DBParser::UpsertStmtContext::ON() {
  return getTokens(DBParser::ON);
}

tree::TerminalNode* DBParser::UpsertStmtContext::ON(size_t i) {
  return getToken(DBParser::ON, i);
}

tree::TerminalNode* DBParser::UpsertStmtContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}

DBParser::ValueBlockContext* DBParser::UpsertStmtContext::valueBlock() {
  return getRuleContext<DBParser::ValueBlockContext>(0);
}

tree::TerminalNode* DBParser::UpsertStmtContext::SET() {
  return getToken(DBParser::SET, 0);
}

DBParser::SetClauseContext* DBParser::UpsertStmtContext::setClause() {
  return getRuleContext<DBParser::SetClauseContext>(0);
}

DBParser::ReturningClauseContext* DBParser::UpsertStmtContext::returningClause() {
  return getRuleContext<DBParser::ReturningClauseContext>(0);
}


size_t DBParser::UpsertStmtContext::getRuleIndex() const {
  return DBParser::RuleUpsertStmt;
}


std::any DBParser::UpsertStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitUpsertStmt(this);
  else
    return visitor->visitChildren(this);
}

DBParser::UpsertStmtContext* DBParser::upsertStmt() {
  UpsertStmtContext *_localctx = _tracker.createInstance<UpsertStmtContext>(_ctx, getState());
  enterRule(_localctx, 82, DBParser::RuleUpsertStmt);
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
    setState(496);
    match(DBParser::UPSERT);
    setState(497);
    match(DBParser::INTO);
    setState(498);
    match(DBParser::STRING_LIT);
    setState(499);
    match(DBParser::AS);
    setState(500);
    qualifiedName();
    setState(501);
    match(DBParser::CONFLICT);
    setState(502);
    match(DBParser::ON);
    setState(503);
    match(DBParser::IDENTIFIER);
    setState(504);
    valueBlock();
    setState(505);
    match(DBParser::ON);
    setState(506);
    match(DBParser::CONFLICT);
    setState(507);
    match(DBParser::SET);
    setState(508);
    setClause();
    setState(510);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DBParser::RETURNING) {
      setState(509);
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

DBParser::ReturningClauseContext::ReturningClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::ReturningClauseContext::RETURNING() {
  return getToken(DBParser::RETURNING, 0);
}

DBParser::ProjectionBlockContext* DBParser::ReturningClauseContext::projectionBlock() {
  return getRuleContext<DBParser::ProjectionBlockContext>(0);
}


size_t DBParser::ReturningClauseContext::getRuleIndex() const {
  return DBParser::RuleReturningClause;
}


std::any DBParser::ReturningClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitReturningClause(this);
  else
    return visitor->visitChildren(this);
}

DBParser::ReturningClauseContext* DBParser::returningClause() {
  ReturningClauseContext *_localctx = _tracker.createInstance<ReturningClauseContext>(_ctx, getState());
  enterRule(_localctx, 84, DBParser::RuleReturningClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(512);
    match(DBParser::RETURNING);
    setState(513);
    projectionBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

DBParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t DBParser::ExprContext::getRuleIndex() const {
  return DBParser::RuleExpr;
}

void DBParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- NotExprContext ------------------------------------------------------------------

tree::TerminalNode* DBParser::NotExprContext::NOT() {
  return getToken(DBParser::NOT, 0);
}

DBParser::ExprContext* DBParser::NotExprContext::expr() {
  return getRuleContext<DBParser::ExprContext>(0);
}

DBParser::NotExprContext::NotExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any DBParser::NotExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitNotExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryMinusExprContext ------------------------------------------------------------------

tree::TerminalNode* DBParser::UnaryMinusExprContext::MINUS() {
  return getToken(DBParser::MINUS, 0);
}

DBParser::ExprContext* DBParser::UnaryMinusExprContext::expr() {
  return getRuleContext<DBParser::ExprContext>(0);
}

DBParser::UnaryMinusExprContext::UnaryMinusExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any DBParser::UnaryMinusExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitUnaryMinusExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrimaryExprContext ------------------------------------------------------------------

DBParser::PrimaryContext* DBParser::PrimaryExprContext::primary() {
  return getRuleContext<DBParser::PrimaryContext>(0);
}

DBParser::PrimaryExprContext::PrimaryExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any DBParser::PrimaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OrExprContext ------------------------------------------------------------------

std::vector<DBParser::ExprContext *> DBParser::OrExprContext::expr() {
  return getRuleContexts<DBParser::ExprContext>();
}

DBParser::ExprContext* DBParser::OrExprContext::expr(size_t i) {
  return getRuleContext<DBParser::ExprContext>(i);
}

tree::TerminalNode* DBParser::OrExprContext::OR() {
  return getToken(DBParser::OR, 0);
}

DBParser::OrExprContext::OrExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any DBParser::OrExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitOrExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ComparisonExprContext ------------------------------------------------------------------

std::vector<DBParser::ExprContext *> DBParser::ComparisonExprContext::expr() {
  return getRuleContexts<DBParser::ExprContext>();
}

DBParser::ExprContext* DBParser::ComparisonExprContext::expr(size_t i) {
  return getRuleContext<DBParser::ExprContext>(i);
}

tree::TerminalNode* DBParser::ComparisonExprContext::EQ() {
  return getToken(DBParser::EQ, 0);
}

tree::TerminalNode* DBParser::ComparisonExprContext::NEQ() {
  return getToken(DBParser::NEQ, 0);
}

tree::TerminalNode* DBParser::ComparisonExprContext::LT() {
  return getToken(DBParser::LT, 0);
}

tree::TerminalNode* DBParser::ComparisonExprContext::GT() {
  return getToken(DBParser::GT, 0);
}

tree::TerminalNode* DBParser::ComparisonExprContext::LEQ() {
  return getToken(DBParser::LEQ, 0);
}

tree::TerminalNode* DBParser::ComparisonExprContext::GEQ() {
  return getToken(DBParser::GEQ, 0);
}

DBParser::ComparisonExprContext::ComparisonExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any DBParser::ComparisonExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitComparisonExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DistanceExprContext ------------------------------------------------------------------

std::vector<DBParser::ExprContext *> DBParser::DistanceExprContext::expr() {
  return getRuleContexts<DBParser::ExprContext>();
}

DBParser::ExprContext* DBParser::DistanceExprContext::expr(size_t i) {
  return getRuleContext<DBParser::ExprContext>(i);
}

tree::TerminalNode* DBParser::DistanceExprContext::DISTANCE() {
  return getToken(DBParser::DISTANCE, 0);
}

DBParser::DistanceExprContext::DistanceExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any DBParser::DistanceExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitDistanceExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AdditiveExprContext ------------------------------------------------------------------

std::vector<DBParser::ExprContext *> DBParser::AdditiveExprContext::expr() {
  return getRuleContexts<DBParser::ExprContext>();
}

DBParser::ExprContext* DBParser::AdditiveExprContext::expr(size_t i) {
  return getRuleContext<DBParser::ExprContext>(i);
}

tree::TerminalNode* DBParser::AdditiveExprContext::PLUS() {
  return getToken(DBParser::PLUS, 0);
}

tree::TerminalNode* DBParser::AdditiveExprContext::MINUS() {
  return getToken(DBParser::MINUS, 0);
}

DBParser::AdditiveExprContext::AdditiveExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any DBParser::AdditiveExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitAdditiveExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ContainsExprContext ------------------------------------------------------------------

std::vector<DBParser::ExprContext *> DBParser::ContainsExprContext::expr() {
  return getRuleContexts<DBParser::ExprContext>();
}

DBParser::ExprContext* DBParser::ContainsExprContext::expr(size_t i) {
  return getRuleContext<DBParser::ExprContext>(i);
}

tree::TerminalNode* DBParser::ContainsExprContext::CONTAINS() {
  return getToken(DBParser::CONTAINS, 0);
}

DBParser::ContainsExprContext::ContainsExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any DBParser::ContainsExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitContainsExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MultiplicativeExprContext ------------------------------------------------------------------

std::vector<DBParser::ExprContext *> DBParser::MultiplicativeExprContext::expr() {
  return getRuleContexts<DBParser::ExprContext>();
}

DBParser::ExprContext* DBParser::MultiplicativeExprContext::expr(size_t i) {
  return getRuleContext<DBParser::ExprContext>(i);
}

tree::TerminalNode* DBParser::MultiplicativeExprContext::STAR() {
  return getToken(DBParser::STAR, 0);
}

tree::TerminalNode* DBParser::MultiplicativeExprContext::SLASH() {
  return getToken(DBParser::SLASH, 0);
}

DBParser::MultiplicativeExprContext::MultiplicativeExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any DBParser::MultiplicativeExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitMultiplicativeExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AndExprContext ------------------------------------------------------------------

std::vector<DBParser::ExprContext *> DBParser::AndExprContext::expr() {
  return getRuleContexts<DBParser::ExprContext>();
}

DBParser::ExprContext* DBParser::AndExprContext::expr(size_t i) {
  return getRuleContext<DBParser::ExprContext>(i);
}

tree::TerminalNode* DBParser::AndExprContext::AND() {
  return getToken(DBParser::AND, 0);
}

DBParser::AndExprContext::AndExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any DBParser::AndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitAndExpr(this);
  else
    return visitor->visitChildren(this);
}

DBParser::ExprContext* DBParser::expr() {
   return expr(0);
}

DBParser::ExprContext* DBParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  DBParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  DBParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 86;
  enterRecursionRule(_localctx, 86, DBParser::RuleExpr, precedence);

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
    setState(521);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DBParser::NOT: {
        _localctx = _tracker.createInstance<NotExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(516);
        match(DBParser::NOT);
        setState(517);
        expr(8);
        break;
      }

      case DBParser::MINUS: {
        _localctx = _tracker.createInstance<UnaryMinusExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(518);
        match(DBParser::MINUS);
        setState(519);
        expr(2);
        break;
      }

      case DBParser::TRUE:
      case DBParser::FALSE:
      case DBParser::NULL_:
      case DBParser::LPAREN:
      case DBParser::LBRACKET:
      case DBParser::INTEGER_LIT:
      case DBParser::DECIMAL_LIT:
      case DBParser::STRING_LIT:
      case DBParser::SINGLE_STRING_LIT:
      case DBParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<PrimaryExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(520);
        primary();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(546);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(544);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<OrExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(523);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(524);
          match(DBParser::OR);
          setState(525);
          expr(11);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AndExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(526);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(527);
          match(DBParser::AND);
          setState(528);
          expr(10);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ContainsExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(529);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(530);
          match(DBParser::CONTAINS);
          setState(531);
          expr(8);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<ComparisonExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(532);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(533);
          _la = _input->LA(1);
          if (!(((((_la - 62) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 62)) & 63) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(534);
          expr(7);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<DistanceExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(535);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(536);
          match(DBParser::DISTANCE);
          setState(537);
          expr(6);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<AdditiveExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(538);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(539);
          _la = _input->LA(1);
          if (!(_la == DBParser::PLUS

          || _la == DBParser::MINUS)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(540);
          expr(5);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<MultiplicativeExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(541);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(542);
          _la = _input->LA(1);
          if (!(_la == DBParser::STAR

          || _la == DBParser::SLASH)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(543);
          expr(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(548);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PrimaryContext ------------------------------------------------------------------

DBParser::PrimaryContext::PrimaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t DBParser::PrimaryContext::getRuleIndex() const {
  return DBParser::RulePrimary;
}

void DBParser::PrimaryContext::copyFrom(PrimaryContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ParenPrimaryContext ------------------------------------------------------------------

tree::TerminalNode* DBParser::ParenPrimaryContext::LPAREN() {
  return getToken(DBParser::LPAREN, 0);
}

DBParser::ExprContext* DBParser::ParenPrimaryContext::expr() {
  return getRuleContext<DBParser::ExprContext>(0);
}

tree::TerminalNode* DBParser::ParenPrimaryContext::RPAREN() {
  return getToken(DBParser::RPAREN, 0);
}

DBParser::ParenPrimaryContext::ParenPrimaryContext(PrimaryContext *ctx) { copyFrom(ctx); }


std::any DBParser::ParenPrimaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitParenPrimary(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LiteralPrimaryContext ------------------------------------------------------------------

DBParser::LiteralContext* DBParser::LiteralPrimaryContext::literal() {
  return getRuleContext<DBParser::LiteralContext>(0);
}

DBParser::LiteralPrimaryContext::LiteralPrimaryContext(PrimaryContext *ctx) { copyFrom(ctx); }


std::any DBParser::LiteralPrimaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitLiteralPrimary(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionCallPrimaryContext ------------------------------------------------------------------

DBParser::FunctionCallContext* DBParser::FunctionCallPrimaryContext::functionCall() {
  return getRuleContext<DBParser::FunctionCallContext>(0);
}

DBParser::FunctionCallPrimaryContext::FunctionCallPrimaryContext(PrimaryContext *ctx) { copyFrom(ctx); }


std::any DBParser::FunctionCallPrimaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitFunctionCallPrimary(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AggregateCallPrimaryContext ------------------------------------------------------------------

DBParser::AggregateCallContext* DBParser::AggregateCallPrimaryContext::aggregateCall() {
  return getRuleContext<DBParser::AggregateCallContext>(0);
}

DBParser::AggregateCallPrimaryContext::AggregateCallPrimaryContext(PrimaryContext *ctx) { copyFrom(ctx); }


std::any DBParser::AggregateCallPrimaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitAggregateCallPrimary(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NamePrimaryContext ------------------------------------------------------------------

DBParser::QualifiedNameContext* DBParser::NamePrimaryContext::qualifiedName() {
  return getRuleContext<DBParser::QualifiedNameContext>(0);
}

DBParser::NamePrimaryContext::NamePrimaryContext(PrimaryContext *ctx) { copyFrom(ctx); }


std::any DBParser::NamePrimaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitNamePrimary(this);
  else
    return visitor->visitChildren(this);
}
DBParser::PrimaryContext* DBParser::primary() {
  PrimaryContext *_localctx = _tracker.createInstance<PrimaryContext>(_ctx, getState());
  enterRule(_localctx, 88, DBParser::RulePrimary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(557);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<DBParser::LiteralPrimaryContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(549);
      literal();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<DBParser::FunctionCallPrimaryContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(550);
      functionCall();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<DBParser::AggregateCallPrimaryContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(551);
      aggregateCall();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<DBParser::NamePrimaryContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(552);
      qualifiedName();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<DBParser::ParenPrimaryContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(553);
      match(DBParser::LPAREN);
      setState(554);
      expr(0);
      setState(555);
      match(DBParser::RPAREN);
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

//----------------- FunctionCallContext ------------------------------------------------------------------

DBParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::FunctionCallContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}

tree::TerminalNode* DBParser::FunctionCallContext::LPAREN() {
  return getToken(DBParser::LPAREN, 0);
}

tree::TerminalNode* DBParser::FunctionCallContext::RPAREN() {
  return getToken(DBParser::RPAREN, 0);
}

DBParser::ArgListContext* DBParser::FunctionCallContext::argList() {
  return getRuleContext<DBParser::ArgListContext>(0);
}


size_t DBParser::FunctionCallContext::getRuleIndex() const {
  return DBParser::RuleFunctionCall;
}


std::any DBParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}

DBParser::FunctionCallContext* DBParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 90, DBParser::RuleFunctionCall);
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
    setState(559);
    match(DBParser::IDENTIFIER);
    setState(560);
    match(DBParser::LPAREN);
    setState(562);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 55) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 55)) & 12687786023) != 0)) {
      setState(561);
      argList();
    }
    setState(564);
    match(DBParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgListContext ------------------------------------------------------------------

DBParser::ArgListContext::ArgListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<DBParser::ExprContext *> DBParser::ArgListContext::expr() {
  return getRuleContexts<DBParser::ExprContext>();
}

DBParser::ExprContext* DBParser::ArgListContext::expr(size_t i) {
  return getRuleContext<DBParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> DBParser::ArgListContext::COMMA() {
  return getTokens(DBParser::COMMA);
}

tree::TerminalNode* DBParser::ArgListContext::COMMA(size_t i) {
  return getToken(DBParser::COMMA, i);
}


size_t DBParser::ArgListContext::getRuleIndex() const {
  return DBParser::RuleArgList;
}


std::any DBParser::ArgListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitArgList(this);
  else
    return visitor->visitChildren(this);
}

DBParser::ArgListContext* DBParser::argList() {
  ArgListContext *_localctx = _tracker.createInstance<ArgListContext>(_ctx, getState());
  enterRule(_localctx, 92, DBParser::RuleArgList);
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
    setState(566);
    expr(0);
    setState(571);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == DBParser::COMMA) {
      setState(567);
      match(DBParser::COMMA);
      setState(568);
      expr(0);
      setState(573);
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

//----------------- AggregateCallContext ------------------------------------------------------------------

DBParser::AggregateCallContext::AggregateCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t DBParser::AggregateCallContext::getRuleIndex() const {
  return DBParser::RuleAggregateCall;
}

void DBParser::AggregateCallContext::copyFrom(AggregateCallContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AggregateFnCallContext ------------------------------------------------------------------

DBParser::AggregateFnContext* DBParser::AggregateFnCallContext::aggregateFn() {
  return getRuleContext<DBParser::AggregateFnContext>(0);
}

tree::TerminalNode* DBParser::AggregateFnCallContext::LPAREN() {
  return getToken(DBParser::LPAREN, 0);
}

DBParser::ExprContext* DBParser::AggregateFnCallContext::expr() {
  return getRuleContext<DBParser::ExprContext>(0);
}

tree::TerminalNode* DBParser::AggregateFnCallContext::RPAREN() {
  return getToken(DBParser::RPAREN, 0);
}

DBParser::AggregateFnCallContext::AggregateFnCallContext(AggregateCallContext *ctx) { copyFrom(ctx); }


std::any DBParser::AggregateFnCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitAggregateFnCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CountStarCallContext ------------------------------------------------------------------

DBParser::AggregateFnContext* DBParser::CountStarCallContext::aggregateFn() {
  return getRuleContext<DBParser::AggregateFnContext>(0);
}

tree::TerminalNode* DBParser::CountStarCallContext::LPAREN() {
  return getToken(DBParser::LPAREN, 0);
}

tree::TerminalNode* DBParser::CountStarCallContext::STAR() {
  return getToken(DBParser::STAR, 0);
}

tree::TerminalNode* DBParser::CountStarCallContext::RPAREN() {
  return getToken(DBParser::RPAREN, 0);
}

DBParser::CountStarCallContext::CountStarCallContext(AggregateCallContext *ctx) { copyFrom(ctx); }


std::any DBParser::CountStarCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitCountStarCall(this);
  else
    return visitor->visitChildren(this);
}
DBParser::AggregateCallContext* DBParser::aggregateCall() {
  AggregateCallContext *_localctx = _tracker.createInstance<AggregateCallContext>(_ctx, getState());
  enterRule(_localctx, 94, DBParser::RuleAggregateCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(584);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<DBParser::CountStarCallContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(574);
      aggregateFn();
      setState(575);
      match(DBParser::LPAREN);
      setState(576);
      match(DBParser::STAR);
      setState(577);
      match(DBParser::RPAREN);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<DBParser::AggregateFnCallContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(579);
      aggregateFn();
      setState(580);
      match(DBParser::LPAREN);
      setState(581);
      expr(0);
      setState(582);
      match(DBParser::RPAREN);
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

//----------------- AggregateFnContext ------------------------------------------------------------------

DBParser::AggregateFnContext::AggregateFnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::AggregateFnContext::IDENTIFIER() {
  return getToken(DBParser::IDENTIFIER, 0);
}


size_t DBParser::AggregateFnContext::getRuleIndex() const {
  return DBParser::RuleAggregateFn;
}


std::any DBParser::AggregateFnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitAggregateFn(this);
  else
    return visitor->visitChildren(this);
}

DBParser::AggregateFnContext* DBParser::aggregateFn() {
  AggregateFnContext *_localctx = _tracker.createInstance<AggregateFnContext>(_ctx, getState());
  enterRule(_localctx, 96, DBParser::RuleAggregateFn);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(586);
    match(DBParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

DBParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::LiteralContext::INTEGER_LIT() {
  return getToken(DBParser::INTEGER_LIT, 0);
}

tree::TerminalNode* DBParser::LiteralContext::DECIMAL_LIT() {
  return getToken(DBParser::DECIMAL_LIT, 0);
}

tree::TerminalNode* DBParser::LiteralContext::STRING_LIT() {
  return getToken(DBParser::STRING_LIT, 0);
}

tree::TerminalNode* DBParser::LiteralContext::SINGLE_STRING_LIT() {
  return getToken(DBParser::SINGLE_STRING_LIT, 0);
}

tree::TerminalNode* DBParser::LiteralContext::TRUE() {
  return getToken(DBParser::TRUE, 0);
}

tree::TerminalNode* DBParser::LiteralContext::FALSE() {
  return getToken(DBParser::FALSE, 0);
}

tree::TerminalNode* DBParser::LiteralContext::NULL_() {
  return getToken(DBParser::NULL_, 0);
}

DBParser::ArrayLiteralContext* DBParser::LiteralContext::arrayLiteral() {
  return getRuleContext<DBParser::ArrayLiteralContext>(0);
}


size_t DBParser::LiteralContext::getRuleIndex() const {
  return DBParser::RuleLiteral;
}


std::any DBParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

DBParser::LiteralContext* DBParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 98, DBParser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(596);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DBParser::INTEGER_LIT: {
        enterOuterAlt(_localctx, 1);
        setState(588);
        match(DBParser::INTEGER_LIT);
        break;
      }

      case DBParser::DECIMAL_LIT: {
        enterOuterAlt(_localctx, 2);
        setState(589);
        match(DBParser::DECIMAL_LIT);
        break;
      }

      case DBParser::STRING_LIT: {
        enterOuterAlt(_localctx, 3);
        setState(590);
        match(DBParser::STRING_LIT);
        break;
      }

      case DBParser::SINGLE_STRING_LIT: {
        enterOuterAlt(_localctx, 4);
        setState(591);
        match(DBParser::SINGLE_STRING_LIT);
        break;
      }

      case DBParser::TRUE: {
        enterOuterAlt(_localctx, 5);
        setState(592);
        match(DBParser::TRUE);
        break;
      }

      case DBParser::FALSE: {
        enterOuterAlt(_localctx, 6);
        setState(593);
        match(DBParser::FALSE);
        break;
      }

      case DBParser::NULL_: {
        enterOuterAlt(_localctx, 7);
        setState(594);
        match(DBParser::NULL_);
        break;
      }

      case DBParser::LBRACKET: {
        enterOuterAlt(_localctx, 8);
        setState(595);
        arrayLiteral();
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

DBParser::ArrayLiteralContext::ArrayLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DBParser::ArrayLiteralContext::LBRACKET() {
  return getToken(DBParser::LBRACKET, 0);
}

tree::TerminalNode* DBParser::ArrayLiteralContext::RBRACKET() {
  return getToken(DBParser::RBRACKET, 0);
}

std::vector<DBParser::ExprContext *> DBParser::ArrayLiteralContext::expr() {
  return getRuleContexts<DBParser::ExprContext>();
}

DBParser::ExprContext* DBParser::ArrayLiteralContext::expr(size_t i) {
  return getRuleContext<DBParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> DBParser::ArrayLiteralContext::COMMA() {
  return getTokens(DBParser::COMMA);
}

tree::TerminalNode* DBParser::ArrayLiteralContext::COMMA(size_t i) {
  return getToken(DBParser::COMMA, i);
}


size_t DBParser::ArrayLiteralContext::getRuleIndex() const {
  return DBParser::RuleArrayLiteral;
}


std::any DBParser::ArrayLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitArrayLiteral(this);
  else
    return visitor->visitChildren(this);
}

DBParser::ArrayLiteralContext* DBParser::arrayLiteral() {
  ArrayLiteralContext *_localctx = _tracker.createInstance<ArrayLiteralContext>(_ctx, getState());
  enterRule(_localctx, 100, DBParser::RuleArrayLiteral);
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
    setState(598);
    match(DBParser::LBRACKET);
    setState(610);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 55) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 55)) & 12687786023) != 0)) {
      setState(599);
      expr(0);
      setState(604);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(600);
          match(DBParser::COMMA);
          setState(601);
          expr(0); 
        }
        setState(606);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
      }
      setState(608);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == DBParser::COMMA) {
        setState(607);
        match(DBParser::COMMA);
      }
    }
    setState(612);
    match(DBParser::RBRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprListContext ------------------------------------------------------------------

DBParser::ExprListContext::ExprListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<DBParser::ExprContext *> DBParser::ExprListContext::expr() {
  return getRuleContexts<DBParser::ExprContext>();
}

DBParser::ExprContext* DBParser::ExprListContext::expr(size_t i) {
  return getRuleContext<DBParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> DBParser::ExprListContext::COMMA() {
  return getTokens(DBParser::COMMA);
}

tree::TerminalNode* DBParser::ExprListContext::COMMA(size_t i) {
  return getToken(DBParser::COMMA, i);
}


size_t DBParser::ExprListContext::getRuleIndex() const {
  return DBParser::RuleExprList;
}


std::any DBParser::ExprListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DBParserVisitor*>(visitor))
    return parserVisitor->visitExprList(this);
  else
    return visitor->visitChildren(this);
}

DBParser::ExprListContext* DBParser::exprList() {
  ExprListContext *_localctx = _tracker.createInstance<ExprListContext>(_ctx, getState());
  enterRule(_localctx, 102, DBParser::RuleExprList);
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
    setState(614);
    expr(0);
    setState(619);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == DBParser::COMMA) {
      setState(615);
      match(DBParser::COMMA);
      setState(616);
      expr(0);
      setState(621);
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

bool DBParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 43: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool DBParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 10);
    case 1: return precpred(_ctx, 9);
    case 2: return precpred(_ctx, 7);
    case 3: return precpred(_ctx, 6);
    case 4: return precpred(_ctx, 5);
    case 5: return precpred(_ctx, 4);
    case 6: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void DBParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  dbparserParserInitialize();
#else
  ::antlr4::internal::call_once(dbparserParserOnceFlag, dbparserParserInitialize);
#endif
}
