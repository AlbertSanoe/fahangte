#include "fahangte/vm.hpp"
#include <iostream>

// void VirtualMachine::exeHALT() { *pc = 0; }

// void VirtualMachine::exeNOP() { (*pc)++; }

// void VirtualMachine::exeSTDIN(uint32_t *addr) {
//   if (addr != nullptr)
//     std::cin >> *addr;
// }

// void VirtualMachine::exeSTDOUT(uint32_t num) { std::cout << num; }

// void VirtualMachine::exeJMP(uint32_t next) { *pc = next; }

// void VirtualMachine::exeJE(uint32_t next) {
//   if (*this->ex == 0) {
//     *pc = next;
//   } else {
//     (*pc)++;
//   }
// }