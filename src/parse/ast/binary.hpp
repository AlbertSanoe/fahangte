#pragma once

#include "../visitor/base_visitor.hpp"
#include "base.hpp"
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

class BinaryArithOp final : public BinaryOperator<OperatorType> {
public:
  using BinaryOperator<OperatorType>::BinaryOperator;
  void accept(Parse::AstVisitorBase &visitor) override {
    return visitor.visit(*this);
  }
};

} // namespace Ast
