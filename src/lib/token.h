#include <string>

enum TokenType {
  NUMBER,
  OPERATOR,
  PARENTHESIS  
};

class Token {
  int line;
  int column;
  string token;
  TokenType type;

  // add functions if need be for lexer
  
};
