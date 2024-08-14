#pragma once
#include "lex/lexer.hpp"
#include "ast/base.hpp"
namespace Parse {



class Parser {
  using AstType = Ast::Expr;

public:
  AstType parse();

private:
  Lex::Lexer lexer;

private:
  Ast::Expr parseExpr(
      Lex::OperatorInfo info = std::move(Lex::OperatorInfo::createDefault()));
  Ast::Expr parseBinary(Ast::Expr left,Lex::OperatorInfo info);
  Ast::Expr parseIntegerConstant();

private:

};
} // namespace Parse