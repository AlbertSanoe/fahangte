#pragma once
#include "ast/base.hpp"
#include "lexer.hpp"
namespace Parse {

class Parser {
  using AstType = Ast::Expr;

public:
  Parser(Lex::Lexer lexer) : _lexer{std::move(lexer)} {}
  AstType parse();

private:
  Lex::Lexer _lexer;

private:
  Ast::Expr parseExpr(
      Lex::OperatorInfo info = std::move(Lex::OperatorInfo::createDefault()));
  Ast::Expr parseBinary(Ast::Expr left, Lex::OperatorInfo info);
  Ast::Expr parseIntegerConstant();

private:
};
} // namespace Parse