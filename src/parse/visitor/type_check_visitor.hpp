#pragma once
#include "base_visitor.hpp"
#include <assert.h>
namespace Parse {
using namespace Ast;
class TypeCheckVisitor final : public AstVisitorBase {
public:
  void visit(BinaryArithOp &ba) override {
    ExprRetType lhs_type = visitExpr(ba.getLHS());
    ExprRetType rhs_type = visitExpr(ba.getRHS());
    ba.setRetType(InferType(lhs_type, rhs_type));
  }
  void visit(IntegerConstant &i) override {
    assert(i.getRetType() == ExprRetType::Integer);
  }

private:
  ExprRetType visitExpr(const Expr &expr) {
    expr.accept(*this);
    return expr.getRetType();
  }

  static ExprRetType InferType(ExprRetType lhs, ExprRetType rhs) {
    if (lhs == rhs) {
      return rhs;
    } else {
      return ExprRetType::Error;
    }
  }
};
} // namespace Parse