#include "parser.hpp"
#include "ast/base.hpp"

namespace Parse {
    using namespace Ast;
    Parser::AstType Parser::parse(){
        return parseExpr();
    }
// Expr -> Integer |
//         Binary           
    Expr Parser::parseExpr(int rbp){
        parseIntegerConstant();
        while (lexer.peek().getKind()==Lex::TokenType::Operator){
            parseBinary();
        }

    }
// Binary -> Expr BinaryArithOperator Expr
    Expr parseBinary(){

    }

    Expr Parser::parseIntegerConstant(){

    }

}