#include "fahangte/vm.hpp"
#include <cstddef>
#include <iostream>

static const unsigned reg_pace = 1;
static const unsigned mem_pace = 4;
static const unsigned imme_pace = 4;

template <> struct VirtualMachine::Pace<VirtualMachine::RegIndexType> {
  static constexpr std::size_t pace = 1;
};

template <> struct VirtualMachine::Pace<VirtualMachine::AddrIndexType> {
  static constexpr std::size_t pace = 2;
};

template <> struct VirtualMachine::Pace<VirtualMachine::ImmeType> {
  static constexpr std::size_t pace = 4;
};

/* Default: the converted data is an unsigned integer */
template <typename DataType>
void VirtualMachine::convert(DataType &val, std::size_t offset) {
  Instruction *ptr =
      (Instruction *)this->PC + VirtualMachine::Pace<DataType>::pace + offset;
  val = *(DataType *)ptr;
}

template <typename DataType1, typename DataType2>
void VirtualMachine::convert2(DataType1 &val1, DataType2 &val2) {
  this->convert<DataType1>(val1);
  this->convert<DataType2>(val2, VirtualMachine::Pace<DataType1>::pace);
}

template <typename... DataTypes> void VirtualMachine::movePC() {
  // static assert
  std::size_t totalPace = (Pace<DataTypes>::pace + ... + 1);
  this->PC += totalPace;
}

void VirtualMachine::exeHALT() { std::cout << "exeHALT" << std::endl; }
void VirtualMachine::exeNOP() { std::cout << "exeNOP" << std::endl; }

void VirtualMachine::exeSTDINR() {
  RegIndexType dest;
  this->convert(dest);
  std::cin >> this->registers[dest];
  this->movePC<RegIndexType>();
}

void VirtualMachine::exeSTDINM() { 
  AddrIndexType dest;
  this->convert(dest);
  std::cin >> this->memory[dest];
  this->movePC<AddrIndexType>();
 }
void VirtualMachine::exeSTDOUTR() { std::cout << "exeSTDOUTR" << std::endl; }
void VirtualMachine::exeSTDOUTM() { std::cout << "exeSTDOUTM" << std::endl; }
void VirtualMachine::exeSTDOUTI() { std::cout << "exeSTDOUTI" << std::endl; }
void VirtualMachine::exeJMPR() { std::cout << "exeJMPR" << std::endl; }
void VirtualMachine::exeJMPM() { std::cout << "exeJMPM" << std::endl; }
void VirtualMachine::exeJMPI() { std::cout << "exeJMPI" << std::endl; }
void VirtualMachine::exeJER() { std::cout << "exeJER" << std::endl; }
void VirtualMachine::exeJEM() { std::cout << "exeJEM" << std::endl; }
void VirtualMachine::exeJEI() { std::cout << "exeJEI" << std::endl; }
void VirtualMachine::exeJNER() { std::cout << "exeJNER" << std::endl; }
void VirtualMachine::exeJNEM() { std::cout << "exeJNEM" << std::endl; }
void VirtualMachine::exeJNEI() { std::cout << "exeJNEI" << std::endl; }
void VirtualMachine::exeJLTR() { std::cout << "exeJLTR" << std::endl; }
void VirtualMachine::exeJLTM() { std::cout << "exeJLTM" << std::endl; }
void VirtualMachine::exeJLTI() { std::cout << "exeJLTI" << std::endl; }
void VirtualMachine::exeJLER() { std::cout << "exeJLER" << std::endl; }
void VirtualMachine::exeJLEM() { std::cout << "exeJLEM" << std::endl; }
void VirtualMachine::exeJLEI() { std::cout << "exeJLEI" << std::endl; }
void VirtualMachine::exeJGTR() { std::cout << "exeJGTR" << std::endl; }
void VirtualMachine::exeJGTM() { std::cout << "exeJGTM" << std::endl; }
void VirtualMachine::exeJGTI() { std::cout << "exeJGTI" << std::endl; }
void VirtualMachine::exeJGER() { std::cout << "exeJGER" << std::endl; }
void VirtualMachine::exeJGEM() { std::cout << "exeJGEM" << std::endl; }
void VirtualMachine::exeJGEI() { std::cout << "exeJGEI" << std::endl; }

void VirtualMachine::exeMOVRR() {
  RegIndexType dest, src;
  this->convert2(dest, src);
  this->registers[dest] = this->registers[src];
  this->movePC<RegIndexType, RegIndexType>();
}

void VirtualMachine::exeMOVRM() {
  RegIndexType dest;
  AddrIndexType src;
  this->convert2(dest, src);
  this->registers[dest] = this->memory[src];
  this->movePC<RegIndexType, AddrIndexType>();
}

void VirtualMachine::exeMOVRI() {
  RegIndexType dest;
  ImmeType src;
  this->convert2(dest, src);
  this->registers[dest] = src;
  this->movePC<RegIndexType, ImmeType>();
}

void VirtualMachine::exeMOVMR() {
  AddrIndexType dest;
  RegIndexType src;
  this->convert2(dest, src);
  this->memory[dest] = this->registers[src];
  this->movePC<AddrIndexType, RegIndexType>();
}

void VirtualMachine::exeMOVMI() {
  AddrIndexType dest;
  ImmeType src;
  this->convert2(dest, src);
  this->registers[dest] = src;
  this->movePC<AddrIndexType, ImmeType>();
}

void VirtualMachine::exeADDRR() {
  RegIndexType dest, src;
  this->convert2(dest, src);
  this->registers[dest] += this->registers[src];
  this->movePC<RegIndexType, RegIndexType>();
}

void VirtualMachine::exeADDRM() {
  RegIndexType dest;
  AddrIndexType src;
  this->convert2(dest, src);
  this->registers[dest] += this->memory[src];
  this->movePC<RegIndexType, AddrIndexType>();
}

void VirtualMachine::exeADDRI() {
  RegIndexType dest;
  ImmeType src;
  this->convert2(dest, src);
  this->registers[dest] += src;
  this->movePC<RegIndexType, ImmeType>();
}

void VirtualMachine::exeADDMR() {
  AddrIndexType dest;
  RegIndexType src;
  this->convert2(dest, src);
  this->memory[dest] += this->registers[src];
  this->movePC<AddrIndexType, RegIndexType>();
}

void VirtualMachine::exeADDMI() {
  AddrIndexType dest;
  ImmeType src;
  this->convert2(dest, src);
  this->registers[dest] += src;
  this->movePC<AddrIndexType, ImmeType>();
}

void VirtualMachine::exeSUBRR() { std::cout << "exeSUBRR" << std::endl; }
void VirtualMachine::exeSUBRM() { std::cout << "exeSUBRM" << std::endl; }
void VirtualMachine::exeSUBRI() { std::cout << "exeSUBRI" << std::endl; }
void VirtualMachine::exeSUBMR() { std::cout << "exeSUBMR" << std::endl; }
void VirtualMachine::exeSUBMI() { std::cout << "exeSUBMI" << std::endl; }

void VirtualMachine::exeMULRR() { std::cout << "exeMULRR" << std::endl; }
void VirtualMachine::exeMULRM() { std::cout << "exeMULRM" << std::endl; }
void VirtualMachine::exeMULRI() { std::cout << "exeMULRI" << std::endl; }
void VirtualMachine::exeMULMR() { std::cout << "exeMULMR" << std::endl; }
void VirtualMachine::exeMULMI() { std::cout << "exeMULMI" << std::endl; }

void VirtualMachine::exeDIVRR() { std::cout << "exeDIVRR" << std::endl; }
void VirtualMachine::exeDIVRM() { std::cout << "exeDIVRM" << std::endl; }
void VirtualMachine::exeDIVRI() { std::cout << "exeDIVRI" << std::endl; }
void VirtualMachine::exeDIVMR() { std::cout << "exeDIVMR" << std::endl; }
void VirtualMachine::exeDIVMI() { std::cout << "exeDIVMI" << std::endl; }

void VirtualMachine::exeMODRR() { std::cout << "exeMODRR" << std::endl; }
void VirtualMachine::exeMODRM() { std::cout << "exeMODRM" << std::endl; }
void VirtualMachine::exeMODRI() { std::cout << "exeMODRI" << std::endl; }
void VirtualMachine::exeMODMR() { std::cout << "exeMODMR" << std::endl; }
void VirtualMachine::exeMODMI() { std::cout << "exeMODMI" << std::endl; }

void VirtualMachine::exeCMPRR() { std::cout << "exeCMPRR" << std::endl; }
void VirtualMachine::exeCMPRM() { std::cout << "exeCMPRM" << std::endl; }
void VirtualMachine::exeCMPRI() { std::cout << "exeCMPRI" << std::endl; }
void VirtualMachine::exeCMPMR() { std::cout << "exeCMPMR" << std::endl; }
void VirtualMachine::exeCMPMI() { std::cout << "exeCMPMI" << std::endl; }