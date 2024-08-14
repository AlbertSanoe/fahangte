#pragma once

/* to link the type of token and ast */
namespace Parse {
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

enum class ExprRetType {
  Unevaluated,
  Error,
  Integer,
};

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

} // namespace Parse