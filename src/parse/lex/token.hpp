#pragma once
#include "../type.hpp"
#include <assert.h>
#include <string_view>
#include <variant>
namespace Lex {
using namespace Parse;

class OperatorInfo {
public:
  constexpr OperatorInfo(OperatorType type, OperatorBindingPower power,
                         bool is_left_associativity)
      : _type{type}, _power{power}, _is_left_associativity{
                                        is_left_associativity} {}

  static constexpr OperatorInfo createDefault() {
    return {
        OperatorType::Default,
        OperatorBindingPower::Default,
        true,
    };
  }

  static constexpr bool greaterBindingPower(OperatorInfo lhs,
                                            OperatorInfo rhs) {
    return (lhs._power == rhs._power) ? lhs._power > rhs._power
           : (lhs._is_left_associativity && rhs._is_left_associativity) ? false
                                                                        : true;
  }
  constexpr OperatorType getOperatorType() const { return _type; }

private:
  OperatorType _type;
  OperatorBindingPower _power;
  bool _is_left_associativity;
};

class Token {
public:
  static Token createInteger(std::string_view lexeme, int value) {
    return {lexeme, value};
  }

  template <OperatorType op>
  static Token createOperator(std::string_view lexeme) {
    return {lexeme,
            OperatorInfo{op, OperatorTypeTransfer<op>::power,
                         OperatorTypeTransfer<op>::is_left_associativity}};
  }

public:
  TokenType getKind() const { return static_cast<TokenType>(_info.index()); }
  int getIntValue() const { return getValueImpl<int>(); }
  constexpr OperatorInfo getOperatorInfo() const {
    return getValueImpl<OperatorInfo>();
  }

private:
  std::variant<std::monostate, int, OperatorInfo> _info;
  std::string_view _lexeme;

  template <typename Tag>
  Token(std::string_view lexeme, Tag value) : _lexeme{lexeme}, _info{value} {}

  template <typename Type> Type getValueImpl() const {
    static_assert(std::is_same_v<Type, int> ||
                  std::is_same_v<Type, OperatorInfo>);
    return std::get<Type>(_info);
  }
};
} // namespace Lex