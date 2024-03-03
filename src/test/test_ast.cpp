
#include "fahangte/ast.hpp"
#include "fahangte/parser.hpp"
#include "fahangte/scanner.hpp"
#include "fahangte/test.hpp"
#include <memory>
using namespace fahangte::parse;

// template<typename T, typename... Args>
// static std::unique_ptr<T> create(Args&&... args) {
//     return std::make_unique<T>(std::forward<Args>(args)...);
// }

int main() {
  auto x = std::make_unique<AstLiteral<int>>(2);
  auto y = std::make_unique<AstLiteral<int>>(3);
  auto x_val = x->code_gen();
  DEBUG(x_val);
  //   auto yy = std::make_unique<AstBinaryAdd<AstLiteral<int>,
  //   AstLiteral<int>>>(
  //       std::move(x), std::move(y));
  auto tree =
      ParseBinary<AstBinaryAdd<AstLiteral<int>, AstLiteral<int>>,
                  AstLiteral<int>, AstLiteral<int>>::generate(std::move(x),
                                                              std::move(y));
  tree.code_gen();
  // Parser x1;
}