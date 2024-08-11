#pragma once

#include "../visitor/base_visitor.hpp"
#include "base.hpp"
namespace Ast {

template <ExprRetType kind, typename RealType>
class Constant : public ExprNode {
public:
  Constant<kind, RealType>(RealType value) : ExprNode{kind}, _value{value} {}
  RealType getValue() const { return _value; }

private:
  RealType _value;
};

class IntegerConstant final : public Constant<ExprRetType::Integer, int> {
  using Constant<ExprRetType::Integer, int>::Constant;
  void accept(Parse::AstVisitorBase &visitor) override {
    return visitor.visit(*this);
  }
};

} // namespace Ast