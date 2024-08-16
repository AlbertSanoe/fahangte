#include "lexer.hpp"
namespace Lex {
Lexer::Lexer(std::queue<Token> queue) : _queue{std::move(queue)} {}

Token Lexer::peek() {
  return _queue.empty() ? Token::createEOF() : _queue.front();
}

Token Lexer::consume() {
  if (!_queue.empty()) {
    Token next = _queue.front();
    _queue.pop();
    return next;
  } else {
    return Token::createEOF();
  }
}

} // namespace Lex