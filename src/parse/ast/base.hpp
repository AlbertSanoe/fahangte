#pragma once
#include "../type.hpp"
#include <memory>
#include <type_traits>
namespace Parse {
class AstVisitorBase;
}

namespace Ast {
using namespace Parse;

class ExprNode {
public:
  ExprNode() : _type{ExprRetType::Unevaluated} {}
  explicit ExprNode(ExprRetType type) : _type{type} {}
  inline ExprRetType getRetType() const { return _type; }
  inline void setRetType(ExprRetType type) { _type = type; }
  virtual void accept(Parse::AstVisitorBase &visitor) = 0;
  virtual ~ExprNode() = default;

private:
  ExprRetType _type;
};

class Expr {
public:
  template <
      typename ConcreteType, typename... Args,
      typename = std::enable_if_t<std::is_base_of_v<ExprNode, ConcreteType>>>
  static Expr create(Args &&...args) {
    return {std::make_shared<ConcreteType>(std::forward<Args>(args)...)};
  }

  ExprRetType getRetType() const { return _node->getRetType(); }
  void accept(Parse::AstVisitorBase &visitor) const { _node->accept(visitor); }

private:
  std::shared_ptr<ExprNode> _node;
  Expr(std::shared_ptr<ExprNode> node) : _node{std::move(node)} {}
};

class BinaryArithOp;
class IntegerConstant;
} // namespace Ast
