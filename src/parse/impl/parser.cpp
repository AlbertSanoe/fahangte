#include "parser.hpp"
#include "ast/binary.hpp"
#include "ast/constant.hpp"
#include "log.hpp"
#include <cstdlib>
namespace Parse {
using namespace Ast;

static BinaryArithOpKind toBinaryArithOpKind(Lex::OperatorType type) {
  switch (type) {
  case Lex::OperatorType::BinaryPlus:
    return BinaryArithOpKind::Plus;
  case Lex::OperatorType::BinaryMinus:
    return BinaryArithOpKind::Minus;
  case Lex::OperatorType::BinaryMultiply:
    return BinaryArithOpKind::Multiply;
  case Lex::OperatorType::BinaryDivide:
    return BinaryArithOpKind::Divide;
  default:
    assert(false && "not reachable");
  }
}

Parser::AstType Parser::parse() { return parseExpr(); }
// Expr -> Integer |
//         Binary
Expr Parser::parseExpr(Lex::OperatorInfo info) {
  auto expr = parseIntegerConstant();
  while (true) {
    auto next_token = _lexer.peek();
    if (next_token.getKind() == Lex::TokenType::Operator &&
        Lex::OperatorInfo::greaterBindingPower(next_token.getOperatorInfo(),
                                               info)) {
      expr =
          parseBinary(std::move(expr), std::move(next_token.getOperatorInfo()));
    } else {
      break;
    }
  }
  return expr;
}
// Binary -> Expr BinaryArithOperator Expr
Expr Parser::parseBinary(Expr lhs, Lex::OperatorInfo info) {
  auto operator_token = _lexer.consume();
  return Expr::create<BinaryArithOp>(
      toBinaryArithOpKind(operator_token.getOperatorInfo().getOperatorType()),
      std::move(lhs), parseExpr(std::move(info)));
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