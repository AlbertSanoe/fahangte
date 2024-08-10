#pragma once

#include "vm_impl.hpp"
namespace Impl {

template <OperandLabel Dest, OperandLabel Src>
inline void implADD(typename OperandType<Dest>::type dest_addr,
                    typename OperandType<Src>::type src_addr) {
  ImmeType *dest = OperandType<Dest>::get_ptr(dest_addr);
  ImmeType src = OperandType<Src>::get_val(src_addr);
  *dest += src;
}

// inline void implSUB(ImmeType *dest, ImmeType *src) { *dest -= *src; }

// inline void implMUL(ImmeType *dest, ImmeType *src) { *dest *= *src; }

// // divide zero !
// inline void implDIV(ImmeType *dest, ImmeType *src) { *dest /= *src; }

// inline void exeMODRR(ImmeType *dest, ImmeType *src) { *dest %= *src; }

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
} // namespace Impl