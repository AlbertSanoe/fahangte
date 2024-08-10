#include "../impl/type2_impl.hpp"
#include "base.hpp"
#include <iostream>
namespace Code {
template <Impl::Param2 T2, Impl::OperandLabel Dest, Impl::OperandLabel Src>
struct Type2Handler {};

template <Impl::Param2 T2, Impl::OperandLabel Dest, Impl::OperandLabel Src>
class Type2 : public BaseCode {

public:
  void handle() override{
    Type2Handler<T2, Dest, Src>::handle(this);
  }
  Type2(typename Impl::OperandType<Dest>::type dest,
        typename Impl::OperandType<Src>::type src)
      : dest(dest), src(src) {}

private:
  friend Type2Handler<T2, Dest, Src>;
  typename Impl::OperandType<Dest>::type dest;
  typename Impl::OperandType<Src>::type src;
};

template <>
struct Type2Handler<Impl::Param2::add, Impl::OperandLabel::Reg,
                    Impl::OperandLabel::Reg> {
  static void handle(Type2<Impl::Param2::add, Impl::OperandLabel::Reg,
                           Impl::OperandLabel::Reg> *code) {
    Impl::implADD<Impl::OperandLabel::Reg, Impl::OperandLabel::Reg>(code->dest,
                                                                    code->src);
  }
};

} // namespace Code