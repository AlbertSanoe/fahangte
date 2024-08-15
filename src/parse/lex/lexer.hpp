#pragma once
#include "token.hpp"
#include <queue>
namespace Lex {
class Lexer {
private:
  std::queue<Token> _queue;

public:
  Lexer(std::queue<Token> queue) : _queue{std::move(queue)} {}
  Token peek() { return _queue.empty() ? Token::createEOF() : _queue.front(); }
  Token consume() {
    if (!_queue.empty()) {
      Token next = _queue.front();
      _queue.pop();
      return next;
    } else {
      return Token::createEOF();
    }
  }
};
} // namespace Lex