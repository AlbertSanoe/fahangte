#include "log.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "visitor/dump_visitor.hpp"
#include "visitor/type_check_visitor.hpp"
#include <iostream>

int main() { 
  using namespace Lex;
  std::queue<Token> tokenQueue;
  INFO("the input string is: {}", "5 * 3 + 2 / 7 - 6 * 5 / 8");
  
  // 创建表示 5 * 3 + 2/7-6*5/8 的 Token 序列
  tokenQueue.push(Token::createInteger("5", 5));
  tokenQueue.push(Token::createOperator<OperatorType::BinaryMultiply>("*"));
  tokenQueue.push(Token::createInteger("3", 3));
  tokenQueue.push(Token::createOperator<OperatorType::BinaryPlus>("+"));
  tokenQueue.push(Token::createInteger("2", 2));
  tokenQueue.push(Token::createOperator<OperatorType::BinaryDivide>("/"));
  tokenQueue.push(Token::createInteger("7", 7));
  tokenQueue.push(Token::createOperator<OperatorType::BinaryMinus>("-"));
  tokenQueue.push(Token::createInteger("6", 6));
  tokenQueue.push(Token::createOperator<OperatorType::BinaryMultiply>("*"));
  tokenQueue.push(Token::createInteger("5", 5));
  tokenQueue.push(Token::createOperator<OperatorType::BinaryDivide>("/"));
  tokenQueue.push(Token::createInteger("8", 8));

  // 创建 Lexer 对象
  Lexer lexer(std::move(tokenQueue));

  Parse::Parser parser(std::move(lexer));
  Parse::Ast::Expr ast = parser.parse();
  Parse::typeCheck(ast);
  Parse::dump(ast);
}
