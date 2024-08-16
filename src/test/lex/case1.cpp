#include "log.hpp"
#include <queue>
#include "lexer.hpp"
#include <iostream>

inline void testLexer() {
  using namespace Lex;
  std::queue<Token> tokenQueue;
  INFO("the input string is: {}", "5*3+2");
  // 创建表示 5*3+2 的 Token 序列
  tokenQueue.push(Token::createInteger("5", 5));
  tokenQueue.push(Token::createOperator<OperatorType::BinaryMultiply>("*"));
  tokenQueue.push(Token::createInteger("3", 3));
  tokenQueue.push(Token::createOperator<OperatorType::BinaryPlus>("+"));
  tokenQueue.push(Token::createInteger("2", 2));

  // 创建 Lexer 对象
  Lexer lexer(std::move(tokenQueue));

  // 使用 Lexer 对象处理 Token 序列
  while (true) {
    Token token = lexer.peek();
    if (token.getKind() == TokenType::Eof) {
      break;
    }

    token = lexer.consume();
    switch (token.getKind()) {
    case TokenType::Integer:
      INFO("{}: {}", token.getKind(), token.getIntValue());
      break;
    case TokenType::Operator:
      INFO("{}: {}", token.getKind(),
           token.getOperatorInfo().getOperatorType());
      break;
    default:
      break;
    }
  }
}