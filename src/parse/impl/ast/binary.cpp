#include "ast/binary.hpp"
#include "visitor/base_visitor.hpp"

namespace Parse {
namespace Ast {
void BinaryArithOp::accept(Parse::AstVisitorBase &visitor) {
  return visitor.visit(*this);
}
} // namespace Ast
} // namespace Parse