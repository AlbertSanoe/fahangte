#pragma once

#include "ast/binary.hpp"
#include "base_visitor.hpp"
#include <cassert>
#include <cstddef>
#include <iostream>
#include <utility>
namespace Parse {
using namespace Ast;
inline const char *OperatorName(BinaryArithOpKind op) {
  switch (op) {
  case BinaryArithOpKind::Plus:
    return "BinaryPlus";
  case BinaryArithOpKind::Minus:
    return "BinaryMinus";
  case BinaryArithOpKind::Multiply:
    return "BinaryMultiply";
  case BinaryArithOpKind::Divide:
    return "BinaryDivide";
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

  template <typename Operator, typename Child, std::size_t I>
  void dumpChild(Operator &node, const char *nodeName, Child child) {
    if constexpr (I > 0) {
      mOS << mContentBefore << "|-";
      mContentBefore += "| ";
    } else {
      mOS << mContentBefore << "`-";
      mContentBefore += "  ";
    }
    (node.*child)().accept(*this);
    mContentBefore.pop_back();
    mContentBefore.pop_back();
  }

  template <typename Operator, std::size_t... Is, typename... Children>
  void dumpChildrenImpl(Operator &node, const char *nodeName,
                        std::index_sequence<Is...> index_sequence,
                        Children... children) {
    (dumpChild<Operator, Children, sizeof...(Is) - Is - 1>(node, nodeName,
                                                           children),
     ...);
  }

  template <typename Operator, typename... Children>
  void dumpChildren(Operator &node, const char *nodeName,
                    Children... children) {
    dumpChildrenImpl(node, nodeName,
                     std::make_index_sequence<sizeof...(Children)>{},
                     children...);
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

  void visitBinaryArithOp(BinaryArithOp &b) {
    const char *nodeName = "BinaryArithOp";
    mOS << OperatorTitle<BinaryArithOp>{b, nodeName} << std::endl;
    dumpChildren(b, nodeName, &BinaryArithOp::getLHS, &BinaryArithOp::getRHS);
  }

public:
  explicit DumpVisitor(std::ostream &os) : mOS{os} {}

  void visit(Ast::IntegerConstant &i) override {
    mOS << "IntegerConstant " << i.getValue() << std::endl;
  }

  void visit(Ast::BinaryArithOp &b) override { visitBinaryArithOp(b); }
};

inline void dump(const Ast::Expr &expr, std::ostream &os = std::cout) {
  DumpVisitor visitor{os};
  expr.accept(visitor);
}
} // namespace Parse