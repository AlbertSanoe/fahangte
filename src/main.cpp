#include <iostream>
#include "fahangte/test.hpp"

#include "fahangte/vm.hpp"

int main() {
  VirtualMachine vm;

  Instruction x(Instruction::InstructionType::ADDMI);
  vm.test(x);

}