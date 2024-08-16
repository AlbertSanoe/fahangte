#include "ast/constant.hpp"
#include "visitor/base_visitor.hpp"

namespace Parse {
namespace Ast {
void IntegerConstant::accept(Parse::AstVisitorBase &visitor) {
  return visitor.visit(*this);
}
} // namespace Ast
} // namespace Parse