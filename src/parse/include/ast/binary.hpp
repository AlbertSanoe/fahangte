#pragma once

#include "base.hpp"
namespace Parse {
namespace Ast {

template <typename OpKind> class BinaryOperator : public ExprNode {
public:
  BinaryOperator(OpKind op, Expr left, Expr right)
      : ExprNode{}, _op{op}, _left{std::move(left)}, _right{std::move(right)} {}

  const Expr &getLHS() const { return _left; }
  const Expr &getRHS() const { return _right; }

  OpKind getExprType() const { return _op; }

private:
  OpKind _op;
  Expr _left;
  Expr _right;
};

enum class BinaryArithOpKind {
  Plus,
  Minus,
  Multiply,
  Divide,
};

class BinaryArithOp final : public BinaryOperator<BinaryArithOpKind> {
public:
  using BinaryOperator<BinaryArithOpKind>::BinaryOperator;
  void accept(Parse::AstVisitorBase &visitor);
};

} // namespace Ast

} // namespace Parse
