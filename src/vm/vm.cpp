// #include "vm.hpp"
// #include <cstddef>
// #include <iostream>

// template <> struct VirtualMachine::Pace<VirtualMachine::RegIndexType> {
//   static constexpr std::size_t pace = 1;
// };

// template <> struct VirtualMachine::Pace<VirtualMachine::AddrIndexType> {
//   static constexpr std::size_t pace = 2;
// };

// template <> struct VirtualMachine::Pace<VirtualMachine::ImmeType> {
//   static constexpr std::size_t pace = 4;
// };

// /* Default: the converted data is an unsigned integer */
// template <typename DataType>
// void VirtualMachine::convert(DataType &val, std::size_t offset) {
//   Instruction *ptr =
//       (Instruction *)this->PC + VirtualMachine::Pace<DataType>::pace + offset;
//   val = *(DataType *)ptr;
// }

// template <typename DataType1, typename DataType2>
// void VirtualMachine::convert2(DataType1 &val1, DataType2 &val2) {
//   this->convert<DataType1>(val1);
//   this->convert<DataType2>(val2, VirtualMachine::Pace<DataType1>::pace);
// }

// template <typename... DataTypes> void VirtualMachine::incPC() {
//   // static assert
//   std::size_t totalPace = (Pace<DataTypes>::pace + ... + 1);
//   *this->PC += totalPace;
// }

// void VirtualMachine::movePC(std::size_t addr) {
//   // static assert
//   *this->PC = addr;
// }

// void VirtualMachine::exeHALT() { std::cout << "exeHALT" << std::endl; }
// void VirtualMachine::exeNOP() { std::cout << "exeNOP" << std::endl; }

// void VirtualMachine::exeSTDINR() {
//   RegIndexType input;
//   this->convert(input);
//   std::cin >> this->registers[input];
//   this->incPC<RegIndexType>();
// }

// void VirtualMachine::exeSTDINM() {
//   AddrIndexType input;
//   this->convert(input);
//   std::cin >> this->memory[input];
//   this->incPC<AddrIndexType>();
// }

// void VirtualMachine::exeSTDOUTR() {
//   RegIndexType output;
//   this->convert(output);
//   std::cout << this->registers[output] << std::endl;
//   this->incPC<RegIndexType>();
// }

// void VirtualMachine::exeSTDOUTM() {
//   AddrIndexType output;
//   this->convert(output);
//   std::cout << this->memory[output] << std::endl;
//   this->incPC<AddrIndexType>();
// }

// void VirtualMachine::exeSTDOUTI() {
//   ImmeType output;
//   this->convert(output);
//   std::cout << output << std::endl;
//   this->incPC<ImmeType>();
// }

// void VirtualMachine::exeJMPR() {
//   RegIndexType index;
//   this->convert(index);
//   this->movePC(this->registers[index]);
// }
// void VirtualMachine::exeJMPM() {
//   AddrIndexType mem_addr;
//   this->convert(mem_addr); // check
//   this->movePC(this->memory[mem_addr]);
// }

// void VirtualMachine::exeJMPI() {
//   ImmeType abs_addr;
//   this->convert(abs_addr);
//   this->movePC(abs_addr);
// }

// void VirtualMachine::exeJER() {
//   if (*this->ex == 0) {
//     RegIndexType index;
//     this->convert(index);
//     this->movePC(this->registers[index]);
//   } else {
//     this->incPC<RegIndexType>();
//   }
// }

// void VirtualMachine::exeJEM() {
//   if (*this->ex == 0) {
//     AddrIndexType mem_addr;
//     this->convert(mem_addr); // check
//     this->movePC(this->memory[mem_addr]);
//   } else {
//     this->incPC<AddrIndexType>();
//   }
// }

// void VirtualMachine::exeJEI() {
//   if (*this->ex == 0) {
//     ImmeType abs_addr;
//     this->convert(abs_addr);
//     this->movePC(abs_addr);
//   } else {
//     this->incPC<ImmeType>();
//   }
// }

// void VirtualMachine::exeJNER() {
//   if (*this->ex != 0) {
//     RegIndexType index;
//     this->convert(index);
//     this->movePC(this->registers[index]);
//   } else {
//     this->incPC<RegIndexType>();
//   }
// }

// void VirtualMachine::exeJNEM() {
//   if (*this->ex != 0) {
//     AddrIndexType mem_addr;
//     this->convert(mem_addr); // check
//     this->movePC(this->memory[mem_addr]);
//   } else {
//     this->incPC<AddrIndexType>();
//   }
// }

// void VirtualMachine::exeJNEI() {
//   if (*this->ex != 0) {
//     ImmeType abs_addr;
//     this->convert(abs_addr);
//     this->movePC(abs_addr);
//   } else {
//     this->incPC<ImmeType>();
//   }
// }

// void VirtualMachine::exeJLTR() {
//   if (*this->ex < 0) {
//     RegIndexType index;
//     this->convert(index);
//     this->movePC(this->registers[index]);
//   } else {
//     this->incPC<RegIndexType>();
//   }
// }

// void VirtualMachine::exeJLTM() {
//   if (*this->ex < 0) {
//     AddrIndexType mem_addr;
//     this->convert(mem_addr); // check
//     this->movePC(this->memory[mem_addr]);
//   } else {
//     this->incPC<AddrIndexType>();
//   }
// }

// void VirtualMachine::exeJLTI() {
//   if (*this->ex < 0) {
//     ImmeType abs_addr;
//     this->convert(abs_addr);
//     this->movePC(abs_addr);
//   } else {
//     this->incPC<ImmeType>();
//   }
// }

// void VirtualMachine::exeJLER() {
//   if (*this->ex <= 0) {
//     RegIndexType index;
//     this->convert(index);
//     this->movePC(this->registers[index]);
//   } else {
//     this->incPC<RegIndexType>();
//   }
// }

// void VirtualMachine::exeJLEM() {
//   if (*this->ex <= 0) {
//     AddrIndexType mem_addr;
//     this->convert(mem_addr); // check
//     this->movePC(this->memory[mem_addr]);
//   } else {
//     this->incPC<AddrIndexType>();
//   }
// }

// void VirtualMachine::exeJLEI() {
//   if (*this->ex <= 0) {
//     ImmeType abs_addr;
//     this->convert(abs_addr);
//     this->movePC(abs_addr);
//   } else {
//     this->incPC<ImmeType>();
//   }
// }

// void VirtualMachine::exeJGTR() {
//   if (*this->ex > 0) {
//     RegIndexType index;
//     this->convert(index);
//     this->movePC(this->registers[index]);
//   } else {
//     this->incPC<RegIndexType>();
//   }
// }

// void VirtualMachine::exeJGTM() {
//   if (*this->ex > 0) {
//     AddrIndexType mem_addr;
//     this->convert(mem_addr); // check
//     this->movePC(this->memory[mem_addr]);
//   } else {
//     this->incPC<AddrIndexType>();
//   }
// }

// void VirtualMachine::exeJGTI() {
//   if (*this->ex > 0) {
//     ImmeType abs_addr;
//     this->convert(abs_addr);
//     this->movePC(abs_addr);
//   } else {
//     this->incPC<ImmeType>();
//   }
// }

// void VirtualMachine::exeJGER() {
//   if (*this->ex >= 0) {
//     RegIndexType index;
//     this->convert(index);
//     this->movePC(this->registers[index]);
//   } else {
//     this->incPC<RegIndexType>();
//   }
// }

// void VirtualMachine::exeJGEM() {
//   if (*this->ex >= 0) {
//     AddrIndexType mem_addr;
//     this->convert(mem_addr); // check
//     this->movePC(this->memory[mem_addr]);
//   } else {
//     this->incPC<AddrIndexType>();
//   }
// }

// void VirtualMachine::exeJGEI() {
//   if (*this->ex >= 0) {
//     ImmeType abs_addr;
//     this->convert(abs_addr);
//     this->movePC(abs_addr);
//   } else {
//     this->incPC<ImmeType>();
//   }
// }

// void VirtualMachine::exeMOVRR() {
//   RegIndexType dest, src;
//   this->convert2(dest, src);
//   this->registers[dest] = this->registers[src];
//   this->incPC<RegIndexType, RegIndexType>();
// }

// void VirtualMachine::exeMOVRM() {
//   RegIndexType dest;
//   AddrIndexType src;
//   this->convert2(dest, src);
//   this->registers[dest] = this->memory[src];
//   this->incPC<RegIndexType, AddrIndexType>();
// }

// void VirtualMachine::exeMOVRI() {
//   RegIndexType dest;
//   ImmeType src;
//   this->convert2(dest, src);
//   this->registers[dest] = src;
//   this->incPC<RegIndexType, ImmeType>();
// }

// void VirtualMachine::exeMOVMR() {
//   AddrIndexType dest;
//   RegIndexType src;
//   this->convert2(dest, src);
//   this->memory[dest] = this->registers[src];
//   this->incPC<AddrIndexType, RegIndexType>();
// }

// void VirtualMachine::exeMOVMI() {
//   AddrIndexType dest;
//   ImmeType src;
//   this->convert2(dest, src);
//   this->registers[dest] = src;
//   this->incPC<AddrIndexType, ImmeType>();
// }

// void VirtualMachine::exeADDRR() {
//   RegIndexType dest, src;
//   this->convert2(dest, src);
//   this->registers[dest] += this->registers[src];
//   this->incPC<RegIndexType, RegIndexType>();
// }

// void VirtualMachine::exeADDRM() {
//   RegIndexType dest;
//   AddrIndexType src;
//   this->convert2(dest, src);
//   this->registers[dest] += this->memory[src];
//   this->incPC<RegIndexType, AddrIndexType>();
// }

// void VirtualMachine::exeADDRI() {
//   RegIndexType dest;
//   ImmeType src;
//   this->convert2(dest, src);
//   this->registers[dest] += src;
//   this->incPC<RegIndexType, ImmeType>();
// }

// void VirtualMachine::exeADDMR() {
//   AddrIndexType dest;
//   RegIndexType src;
//   this->convert2(dest, src);
//   this->memory[dest] += this->registers[src];
//   this->incPC<AddrIndexType, RegIndexType>();
// }

// void VirtualMachine::exeADDMI() {
//   AddrIndexType dest;
//   ImmeType src;
//   this->convert2(dest, src);
//   this->registers[dest] += src;
//   this->incPC<AddrIndexType, ImmeType>();
// }

// void VirtualMachine::exeSUBRR() {
//   RegIndexType dest, src;
//   this->convert2(dest, src);
//   this->registers[dest] -= this->registers[src];
//   this->incPC<RegIndexType, RegIndexType>();
// }

// void VirtualMachine::exeSUBRM() {
//   RegIndexType dest;
//   AddrIndexType src;
//   this->convert2(dest, src);
//   this->registers[dest] -= this->memory[src];
//   this->incPC<RegIndexType, AddrIndexType>();
// }

// void VirtualMachine::exeSUBRI() {
//   RegIndexType dest;
//   ImmeType src;
//   this->convert2(dest, src);
//   this->registers[dest] -= src;
//   this->incPC<RegIndexType, ImmeType>();
// }

// void VirtualMachine::exeSUBMR() {
//   AddrIndexType dest;
//   RegIndexType src;
//   this->convert2(dest, src);
//   this->memory[dest] -= this->registers[src];
//   this->incPC<AddrIndexType, RegIndexType>();
// }

// void VirtualMachine::exeSUBMI() {
//   AddrIndexType dest;
//   ImmeType src;
//   this->convert2(dest, src);
//   this->registers[dest] -= src;
//   this->incPC<AddrIndexType, ImmeType>();
// }

// void VirtualMachine::exeMULRR() {
//   RegIndexType dest, src;
//   this->convert2(dest, src);
//   this->registers[dest] *= this->registers[src];
//   this->incPC<RegIndexType, RegIndexType>();
// }

// void VirtualMachine::exeMULRM() {
//   RegIndexType dest;
//   AddrIndexType src;
//   this->convert2(dest, src);
//   this->registers[dest] *= this->memory[src];
//   this->incPC<RegIndexType, AddrIndexType>();
// }

// void VirtualMachine::exeMULRI() {
//   RegIndexType dest;
//   ImmeType src;
//   this->convert2(dest, src);
//   this->registers[dest] *= src;
//   this->incPC<RegIndexType, ImmeType>();
// }

// void VirtualMachine::exeMULMR() {
//   AddrIndexType dest;
//   RegIndexType src;
//   this->convert2(dest, src);
//   this->memory[dest] *= this->registers[src];
//   this->incPC<AddrIndexType, RegIndexType>();
// }

// void VirtualMachine::exeMULMI() {
//   AddrIndexType dest;
//   ImmeType src;
//   this->convert2(dest, src);
//   this->registers[dest] *= src;
//   this->incPC<AddrIndexType, ImmeType>();
// }

// // divide zero !
// void VirtualMachine::exeDIVRR() {
//   RegIndexType dest, src;
//   this->convert2(dest, src);
//   this->registers[dest] /= this->registers[src];
//   this->incPC<RegIndexType, RegIndexType>();
// }

// void VirtualMachine::exeDIVRM() {
//   RegIndexType dest;
//   AddrIndexType src;
//   this->convert2(dest, src);
//   this->registers[dest] /= this->memory[src];
//   this->incPC<RegIndexType, AddrIndexType>();
// }

// void VirtualMachine::exeDIVRI() {
//   RegIndexType dest;
//   ImmeType src;
//   this->convert2(dest, src);
//   this->registers[dest] /= src;
//   this->incPC<RegIndexType, ImmeType>();
// }

// void VirtualMachine::exeDIVMR() {
//   AddrIndexType dest;
//   RegIndexType src;
//   this->convert2(dest, src);
//   this->memory[dest] /= this->registers[src];
//   this->incPC<AddrIndexType, RegIndexType>();
// }

// void VirtualMachine::exeDIVMI() {
//   AddrIndexType dest;
//   ImmeType src;
//   this->convert2(dest, src);
//   this->registers[dest] /= src;
//   this->incPC<AddrIndexType, ImmeType>();
// }

// void VirtualMachine::exeMODRR() {
//   RegIndexType dest, src;
//   this->convert2(dest, src);
//   this->registers[dest] %= this->registers[src];
//   this->incPC<RegIndexType, RegIndexType>();
// }

// void VirtualMachine::exeMODRM() {
//   RegIndexType dest;
//   AddrIndexType src;
//   this->convert2(dest, src);
//   this->registers[dest] %= this->memory[src];
//   this->incPC<RegIndexType, AddrIndexType>();
// }

// void VirtualMachine::exeMODRI() {
//   RegIndexType dest;
//   ImmeType src;
//   this->convert2(dest, src);
//   this->registers[dest] %= src;
//   this->incPC<RegIndexType, ImmeType>();
// }

// void VirtualMachine::exeMODMR() {
//   AddrIndexType dest;
//   RegIndexType src;
//   this->convert2(dest, src);
//   this->memory[dest] %= this->registers[src];
//   this->incPC<AddrIndexType, RegIndexType>();
// }

// void VirtualMachine::exeMODMI() {
//   AddrIndexType dest;
//   ImmeType src;
//   this->convert2(dest, src);
//   this->registers[dest] %= src;
//   this->incPC<AddrIndexType, ImmeType>();
// }

// // some may not work
// void VirtualMachine::exeCMPRR() {
//   RegIndexType dest, src;
//   this->convert2(dest, src);
//   *this->ex = this->registers[dest] - this->registers[src];
//   this->incPC<RegIndexType, RegIndexType>();
// }

// void VirtualMachine::exeCMPRM() {
//   RegIndexType dest;
//   AddrIndexType src;
//   this->convert2(dest, src);
//   *this->ex = this->registers[dest] - this->memory[src];
//   this->incPC<RegIndexType, AddrIndexType>();
// }

// void VirtualMachine::exeCMPRI() {
//   RegIndexType dest;
//   ImmeType src;
//   this->convert2(dest, src);
//   *this->ex = this->registers[dest] - src;
//   this->incPC<RegIndexType, ImmeType>();
// }

// void VirtualMachine::exeCMPMR() {
//   AddrIndexType dest;
//   RegIndexType src;
//   this->convert2(dest, src);
//   *this->ex = this->memory[dest] - this->registers[src];
//   this->incPC<AddrIndexType, RegIndexType>();
// }

// void VirtualMachine::exeCMPMI() {
//   AddrIndexType dest;
//   ImmeType src;
//   this->convert2(dest, src);
//   *this->ex = this->registers[dest] - src;
//   this->incPC<AddrIndexType, ImmeType>();
// }