#pragma once

#include "ast/base.hpp"
#include "ast/binary.hpp"
#include "ast/constant.hpp"
namespace Parse {
class AstVisitorBase {
public:
  virtual void visit(Ast::BinaryArithOp &) = 0;
  virtual void visit(Ast::IntegerConstant &) = 0;
};
} // namespace Parse