#pragma once
#include "token.hpp"
#include <queue>
namespace Lex {
class Lexer {
private:
  std::queue<Token> _queue;

public:
  Lexer(std::queue<Token> queue);
  Token peek();
  Token consume();
};
} // namespace Lex