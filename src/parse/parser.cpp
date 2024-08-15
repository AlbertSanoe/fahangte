#include "parser.hpp"
#include "ast/binary.hpp"
#include "ast/constant.hpp"
#include "type.hpp"
#include <cstdlib>
namespace Parse {
using namespace Ast;
Parser::AstType Parser::parse() { return parseExpr(); }
// Expr -> Integer |
//         Binary
Expr Parser::parseExpr(Lex::OperatorInfo info) {
  auto expr = parseIntegerConstant();

  auto next_token = _lexer.peek();
  while (next_token.getKind() == Lex::TokenType::Operator &&
         Lex::OperatorInfo::greaterBindingPower(next_token.getOperatorInfo(),
                                                info)) {
    expr =
        parseBinary(std::move(expr), std::move(next_token.getOperatorInfo()));
    next_token = _lexer.peek();
  }
  return expr;
}
// Binary -> Expr BinaryArithOperator Expr
Expr Parser::parseBinary(Expr lhs, Lex::OperatorInfo info) {
  auto operator_token = _lexer.consume();
  auto type = operator_token.getOperatorInfo().getOperatorType();
  return Expr::create<BinaryArithOp>(type, std::move(lhs),
                                     parseExpr(std::move(info)));
}

Expr Parser::parseIntegerConstant() {
  auto next_token = _lexer.consume();
  if (next_token.getKind() == Lex::TokenType::Integer) {
    return Expr::create<IntegerConstant>(next_token.getIntValue());
  } else {
    exit(0);
    // error handling
  }
}

} // namespace Parse