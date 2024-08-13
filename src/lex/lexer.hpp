#pragma once
#include "token.hpp"
namespace Lex {
class Lexer {
public:
  Token peek();
  Token consume();
};
} // namespace lex