#include <iostream>
#include "fahangte/test.hpp"
#include <cstdint>
#include "fahangte/vm.hpp"

int main() {
  VirtualMachine vm;
  
  // Instruction x(Instruction::InstructionType::CMPMI);
  // std::cout<<std::hex<<std::uppercase<<(unsigned int)x.unit<<std::endl;
  // vm.test(x);

  Instruction array[3];
  array[0]=Instruction(Instruction::InstructionType::MOVRR);
  array[1]=0;
  array[2]=6;

  vm.registers[6]=12580;
  uint32_t *ptr=(uint32_t*)array;
  vm.loadPC(ptr);
  vm.exeMOVRR();
  std::cout<<vm.registers[6]<<std::endl;

}