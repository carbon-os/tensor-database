
// Generated from /home/user/tensor-database/parser/TQLLexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  TQLLexer : public antlr4::Lexer {
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

  explicit TQLLexer(antlr4::CharStream *input);

  ~TQLLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

