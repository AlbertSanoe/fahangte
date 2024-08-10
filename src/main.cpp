// #include <iostream>
// #include "test.hpp"
// #include <cstdint>
// #include "vm/vm.hpp"

// int main() {
//   VirtualMachine vm;

//   // Instruction x(Instruction::InstructionType::CMPMI);
//   // std::cout<<std::hex<<std::uppercase<<(unsigned int)x.unit<<std::endl;
//   // vm.test(x);

//   Instruction array[3];
//   array[0]=Instruction(Instruction::InstructionType::MOVRR);
//   array[1]=0;
//   array[2]=6;

//   vm.registers[6]=12580;
//   uint32_t *ptr=(uint32_t*)array;
//   vm.loadPC(ptr);
//   vm.exeMOVRR();
//   std::cout<<vm.registers[6]<<std::endl;

// }

#include "vm/code/base.hpp"
#include "vm/code/type2.hpp"
#include "vm/impl/vm_impl.hpp"
#include <iostream>

int main() {
  Impl::get_vm_impl()->registers[0] = 10;
  Impl::get_vm_impl()->registers[1] = 20;
  Code::BaseCode *addCode;
  auto code = Code::Type2<Impl::Param2::add, Impl::OperandLabel::Reg,
                          Impl::OperandLabel::Reg>(0, 1);
  addCode = &code;
  // 执行 add 指令
  addCode->handle();
  std::cout << sizeof(code) << std::endl;
  // 打印执行结果
  std::cout << "Result: ax = " << Impl::get_vm_impl()->registers[0]
            << std::endl;

  return 0;
}