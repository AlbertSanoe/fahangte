#pragma once
#include "log.hpp"
#include <utility>
namespace fahangte::parse {



template <typename AstDerived> class AstBase {
public:
  void code_gen() { impl().code_gen(); }

private:
  AstDerived &impl() { return *static_cast<AstDerived *>(this); }
};

template <typename BinaryOperator, typename AstLeftOperand,
          typename AstRightOperand>
class AstBinary
    : public AstBase<
          AstBinary<BinaryOperator, AstLeftOperand, AstRightOperand>> {
public:
  void code_gen() { impl().code_gen(); }
  AstBinary(std::unique_ptr<AstLeftOperand> lvalue,
            std::unique_ptr<AstRightOperand> rvalue)
      : _lvalue(std::move(lvalue)),
        _rvalue(std::move(rvalue)) {}

protected:
  std::unique_ptr<AstLeftOperand> _lvalue;
  std::unique_ptr<AstRightOperand> _rvalue;

private:
  BinaryOperator &impl() { return *static_cast<BinaryOperator *>(this); }
};

template <typename AstLeftOperand, typename AstRightOperand>
class AstBinaryAdd
    : public AstBinary<AstBinaryAdd<AstLeftOperand, AstRightOperand>,
                       AstLeftOperand, AstRightOperand> {
public:
  AstBinaryAdd<AstLeftOperand, AstRightOperand>(
      std::unique_ptr<AstLeftOperand> lvalue,
      std::unique_ptr<AstRightOperand> rvalue)
      : AstBinary<AstBinaryAdd<AstLeftOperand, AstRightOperand>, AstLeftOperand,
                  AstRightOperand>(std::move(lvalue),
                                   std::move(rvalue)) {}
  void code_gen() { DEBUG("this is astbp"); }
};

template <typename AstLeftOperand, typename AstRightOperand>
class AstBinarySubtract
    : public AstBinary<AstBinarySubtract<AstLeftOperand, AstRightOperand>,
                       AstLeftOperand, AstRightOperand> {
public:
  AstBinarySubtract<AstLeftOperand, AstRightOperand>(
      std::unique_ptr<AstLeftOperand> lvalue,
      std::unique_ptr<AstRightOperand> rvalue)
      : AstBinary<AstBinarySubtract<AstLeftOperand, AstRightOperand>,
                  AstLeftOperand, AstRightOperand>(std::move(lvalue),
                                                   std::move(rvalue)) {}
  void code_gen() { DEBUG("this is astbp"); }
};

template <typename AstLeftOperand, typename AstRightOperand>
class AstBinaryMultiply
    : public AstBinary<AstBinaryMultiply<AstLeftOperand, AstRightOperand>,
                       AstLeftOperand, AstRightOperand> {
public:
  AstBinaryMultiply<AstLeftOperand, AstRightOperand>(
      std::unique_ptr<AstLeftOperand> lvalue,
      std::unique_ptr<AstRightOperand> rvalue)
      : AstBinary<AstBinaryMultiply<AstLeftOperand, AstRightOperand>,
                  AstLeftOperand, AstRightOperand>(std::move(lvalue),
                                                   std::move(rvalue)) {}
  void code_gen() { DEBUG("this is astbp"); }
};

template <typename AstLeftOperand, typename AstRightOperand>
class AstBinaryDivide
    : public AstBinary<AstBinaryDivide<AstLeftOperand, AstRightOperand>,
                       AstLeftOperand, AstRightOperand> {
public:
  AstBinaryDivide<AstLeftOperand, AstRightOperand>(
      std::unique_ptr<AstLeftOperand> lvalue,
      std::unique_ptr<AstRightOperand> rvalue)
      : AstBinary<AstBinaryDivide<AstLeftOperand, AstRightOperand>,
                  AstLeftOperand, AstRightOperand>(std::move(lvalue),
                                                   std::move(rvalue)) {}
  void code_gen() { DEBUG("this is astbp"); }
};

template <typename Literal,typename Inner> class AstLiteral : public AstBase<AstLiteral<Literal,Inner>> {
public:
  Inner code_gen() {
    DEBUG("the value is", 3);
    return _val;
  }
  AstLiteral(Inner value) : _val(value) {}

protected:
  Inner _val;

private:
};

class AstInteger final : public AstLiteral<AstInteger, int> {
public:
  AstInteger(int value) : AstLiteral<AstInteger, int>(value) {}
  void code_gen() { DEBUG("hello world!", this->_val); }

private:
};

template <typename Ast> void execute(Ast &ast) { ast->code_gen(); }
template <typename Ast> void execute1(Ast ast) { ast.code_gen(); }

} // namespace fahangte::parse