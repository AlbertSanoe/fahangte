#pragma once

#include <string_view>
#include <variant>
namespace Lex {
enum class TokenType {
  Eof,
  Integer,
  Operator,
};

class Token {
public:
  static Token createInteger(std::string_view lexeme, int value) {
    return {lexeme, value};
  }

  static Token createOperator(std::string_view lexeme) {
    return {lexeme, OperatorTag{}};
  }

public:
  TokenType getKind() const { return static_cast<TokenType>(_info.index()); }

private:
  struct OperatorTag {};
  std::variant<std::monostate, int, OperatorTag> _info;
  std::string_view _lexeme;

  template <typename Tag>
  Token(std::string_view lexeme, Tag value) : _info{value}, _lexeme{lexeme} {}
};
} // namespace Lex