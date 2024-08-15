#pragma once

#include "../ast/binary.hpp"
#include "../ast/constant.hpp"
#include <cassert>
#include <iostream>
namespace Parse {

// inline const char *OperatorName(OperatorType op) {
//   switch (op) {
//   case OperatorType::UnaryPlus:
//     return "+";
//   case OperatorType::UnaryMinus:
//     return "-";
//   case OperatorType::BinaryPlus:
//     return "+";
//   case OperatorType::BinaryMinus:
//     return "-";
//   case OperatorType::BinaryMultiply:
//     return "*";
//   case OperatorType::BinaryDivide:
//     return "/";
//   default:
//     assert(false && "not reachable");
//     return nullptr;
//   }
// }

inline const char *OperatorName(OperatorType op) {
  switch (op) {
  case OperatorType::UnaryPlus:
    return "UnaryPlus";
  case OperatorType::UnaryMinus:
    return "UnaryMinus";
  case OperatorType::BinaryPlus:
    return "BinaryPlus";
  case OperatorType::BinaryMinus:
    return "BinaryMinus";
  case OperatorType::BinaryMultiply:
    return "BinaryMultiply";
  case OperatorType::BinaryDivide:
    return "BinaryDivide";
  default:
    assert(false && "not reachable");
    return nullptr;
  }
}

inline const char *TypeName(ExprRetType type) {
  switch (type) {
  case ExprRetType::Unevaluated:
    return "Unevaluated";
  case ExprRetType::Integer:
    return "Integer";
  case ExprRetType::Error:
    return "Error";
  default:
    assert(false && "not reachable");
    return nullptr;
  }
}

class DumpVisitor : public AstVisitorBase {
  std::ostream &mOS;
  std::string mContentBefore;

  // FirstChild and RestChildren are pointer-to-member-functions.
  // e.g. If Operator = UnaryArithOp and firstChild = &UnaryArithOp::getOperand,
  // (node.*firstChild)() is equivalent to node.getOperand().
  template <typename Operator, typename FirstChild, typename... RestChildren>
  void dumpChildren(Operator &node, const char *nodeName, FirstChild firstChild,
                    RestChildren... restChildren) {
    if constexpr (sizeof...(RestChildren) > 0) {
      mOS << mContentBefore << "|-";
      mContentBefore += "| ";
    } else {
      mOS << mContentBefore << "`-";
      mContentBefore += "  ";
    }

    // Calls 'accept' on the corresponding child, to traverse the tree
    // recursively.
    (node.*firstChild)().accept(*this);
    mContentBefore.pop_back();
    mContentBefore.pop_back();
    if constexpr (sizeof...(RestChildren) > 0)
      dumpChildren(node, nodeName, restChildren...);
  }

  template <typename Operator> struct OperatorTitle {
    Operator &node;
    const char *nodeName;

    OperatorTitle(Operator &node, const char *name)
        : node{node}, nodeName{name} {}

    friend std::ostream &operator<<(std::ostream &os, const OperatorTitle &ot) {
      return os << OperatorName(ot.node.getExprType()) << " -> "
                << TypeName(ot.node.getRetType());
    }
  };

  void visitBinaryArithOp(Ast::BinaryArithOp &b, const char *nodeName) {
    mOS << OperatorTitle{b, nodeName} << '\n';
    dumpChildren(b, nodeName, &Ast::BinaryArithOp::getLHS,
                 &Ast::BinaryArithOp::getRHS);
  }

public:
  explicit DumpVisitor(std::ostream &os) : mOS{os} {}

  void visit(Ast::IntegerConstant &i) override {
    mOS << "IntegerConstant " << i.getValue() << '\n';
  }

  void visit(Ast::BinaryArithOp &b) override {
    visitBinaryArithOp(b, "BinaryArithOp");
  }
};

inline void dump(const Ast::Expr &expr, std::ostream &os = std::cout) {
  DumpVisitor visitor{os};
  expr.accept(visitor);
}
} // namespace Parse