#pragma once

#include "../ast/base.hpp"
#include "../ast/binary.hpp"
#include "../ast/constant.hpp"
namespace Parse {
using namespace Ast;
class AstVisitorBase {
public:
  virtual void visit(BinaryArithOp &) = 0;
  virtual void visit(IntegerConstant &) = 0;
};
} // namespace Parse