#pragma once

#include "base.hpp"

namespace Parse {
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
  void accept(Parse::AstVisitorBase &visitor);
};

} // namespace Ast
} // namespace Parse
