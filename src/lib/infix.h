#include <string>
#include <vector>
#include <memory>
#include "token.h"
#include "parser.h"

class InfixParser {
  Node* root;
  int index = -1;
  size_t parenNum = 0;
  std::map<std::string, Node*> variableBuffer;

  Node* createTree(Node* leftHandSide, int minPrecedence, std::vector<Token> tokens);
  int precedence(std::string op);
  Token& peak(std::vector<Token> tokens);
  Node* nextNode(std::vector<Token> tokens);

public:
  InfixParser(std::vector<Token> tokens);
  ~InfixParser();

  std::string toString();
  double calculate();
};
