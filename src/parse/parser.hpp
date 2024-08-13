#pragma once
#include "../lex/lexer.hpp"
#include "ast/base.hpp"
namespace Parse {

using namespace Ast;

class Parser {
    using AstType= Expr;
public:
  AstType parse();

private:
    Lex::Lexer lexer;

private:
    Expr parseExpr(int rbp=0);
    Expr parseBinary();
    Expr parseIntegerConstant();
};
} // namespace Parse