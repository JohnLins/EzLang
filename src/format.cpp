#include <vector>
#include <iostream>
#include <string>
#include "lib/infix.cpp"
#include "lib/lexer.cpp"

void format(std::vector<Token>& tokens, std::string indent) {
  size_t ifCounter = 0;

  for (size_t i = 0; i < tokens.size(); ++i) {
    if (tokens[i].type == END) break;
    std::cout << indent;

    // expression and print case
    if (tokens[i].type != COMMAND || tokens[i].token == "print") {
      if (tokens[i].token == "print") {
        std::cout << "print ";
	++i;
      }

      size_t line = tokens[i].line;
      std::vector<Token> tempTokens = {tokens[i]};

      while (tokens[i + 1].line == line && tokens[i + 1].type != END) {
	tempTokens.push_back(tokens[i + 1]);
        ++i;
      }
      tempTokens.push_back(Token{0, 0, "END", END});
/*
      for (Token token : tempTokens) {
        std::cout << token.token << " " << token.type << " " << token.line << " " << token.column << std::endl;
      }
*/
      InfixParser parser = InfixParser(tempTokens);
      std::cout << parser.toString() << std::endl;
    }

    // while and if case
    else if (tokens[i].token != "else") {
      if (tokens[i].token == "if") {
        if (ifCounter != 0) {
	  //TODO
	}
	
        std::cout << "if ";
        ++ifCounter;
      }	

      else std::cout << "while ";

      ++i;
      std::vector<Token> condition;

      while (tokens[i].token != "{") {
        condition.push_back(tokens[i]);
	++i;
      }
      condition.push_back(Token{0, 0, "END", END});

      /*
      for (Token token : condition) {
        std::cout << token.token << " " << token.type << std::endl;
      }
      */

      ++i;
      InfixParser parser = InfixParser(condition);
      std::cout << parser.toString() << " {" << std::endl;

      size_t numCurly = 1;
      std::vector<Token> body;

      while (true) {
	if (tokens[i].token == "{") ++numCurly;
	else if (tokens[i].token == "}") --numCurly;

        if (numCurly == 0) break;
        body.push_back(tokens[i]);
	++i;
      }

      format(body, indent + "    ");
      std::cout << indent << "}" << std::endl;
    }

    // else case
    else if (tokens[i].token == "else") {
      if (ifCounter == 0) {
        //TODO
      }

      --ifCounter;
      ++i;
      std::cout << "else {" << std::endl;

      size_t numCurly = 1;
      std::vector<Token> body;
      bool endingCurly = false;

      if (tokens[i].token == "if") {
        body.push_back(tokens[i]);
	body.push_back(tokens[i + 1]);
	++i;
	endingCurly = true;
      }

      ++i;

      while (true) {
        if (tokens[i].token == "{") ++numCurly;
        else if (tokens[i].token == "}") --numCurly;

        if (numCurly == 0) break;
        body.push_back(tokens[i]);
        ++i;
      }

      if (endingCurly) body.push_back(tokens[i]);

      format(body, indent + "    ");
      std::cout << indent << "}" << std::endl;
    }

    else {
      std::cout << "this formatting error should never happen" << std::endl;
      exit(1);
    }
  }
}

int main() {
    Lexer lexer = Lexer();

    std::vector<Token> tokens = lexer.lexer();
    for (Token token : tokens) {
      std::cout << token.token << " " << token.type << " " << token.line << " " << token.column << std::endl;
    }

    format(tokens, "");

    return 0;
}
