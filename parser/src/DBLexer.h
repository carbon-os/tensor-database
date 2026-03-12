
// Generated from DBLexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  DBLexer : public antlr4::Lexer {
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

  explicit DBLexer(antlr4::CharStream *input);

  ~DBLexer() override;


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

