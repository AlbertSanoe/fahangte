#pragma once

#include <iostream>
namespace Lex {
enum class TokenType {
  Eof,
  Integer,
  Operator,
};

enum class OperatorType {
  Default,
  UnaryPlus,
  UnaryMinus,
  BinaryPlus,
  BinaryMinus,
  BinaryMultiply,
  BinaryDivide,
};

enum class OperatorBindingPower {
  Default = 0,
  BinaryPlusMinus = 10,
  BinaryMultiplyDivide = 20,
};

inline std::ostream &operator<<(std::ostream &os, TokenType type) {
  switch (type) {
  case TokenType::Eof:
    os << "EOF";
    break;
  case TokenType::Integer:
    os << "Integer";
    break;
  case TokenType::Operator:
    os << "Operator";
    break;
  default:
    os << "Unknown";
    break;
  }
  return os;
}

inline std::ostream &operator<<(std::ostream &os, OperatorType op) {
  switch (op) {
  case OperatorType::Default:
    os << "Default";
    break;
  case OperatorType::UnaryPlus:
    os << "UnaryPlus";
    break;
  case OperatorType::UnaryMinus:
    os << "UnaryMinus";
    break;
  case OperatorType::BinaryPlus:
    os << "BinaryPlus";
    break;
  case OperatorType::BinaryMinus:
    os << "BinaryMinus";
    break;
  case OperatorType::BinaryMultiply:
    os << "BinaryMultiply";
    break;
  case OperatorType::BinaryDivide:
    os << "BinaryDivide";
    break;
  default:
    os << "Unknown";
    break;
  }
  return os;
}

template <OperatorType type> struct OperatorTypeTransfer {};

template <> struct OperatorTypeTransfer<OperatorType::BinaryPlus> {
  static constexpr bool is_left_associativity = true;
  static constexpr auto power = OperatorBindingPower::BinaryPlusMinus;
};

template <> struct OperatorTypeTransfer<OperatorType::BinaryMinus> {
  static constexpr bool is_left_associativity = true;
  static constexpr auto power = OperatorBindingPower::BinaryPlusMinus;
};

template <> struct OperatorTypeTransfer<OperatorType::BinaryMultiply> {
  static constexpr bool is_left_associativity = true;
  static constexpr auto power = OperatorBindingPower::BinaryMultiplyDivide;
};

template <> struct OperatorTypeTransfer<OperatorType::BinaryDivide> {
  static constexpr bool is_left_associativity = true;
  static constexpr auto power = OperatorBindingPower::BinaryMultiplyDivide;
};
} // namespace Lex
