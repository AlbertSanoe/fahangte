#pragma once
#include "data_type.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>

namespace Impl {

static const std::size_t instruction_addr_space = 1 << 16;
static const std::size_t memory_addr_space = 1 << 16;
static const std::size_t register_number = 8;

template <
    OperandLabel label,
    typename = std::enable_if_t<std::disjunction_v<
        std::is_same<std::integral_constant<OperandLabel, label>,
                     std::integral_constant<OperandLabel, OperandLabel::Reg>>,
        std::is_same<std::integral_constant<OperandLabel, label>,
                     std::integral_constant<OperandLabel, OperandLabel::Mem>>,
        std::is_same<
            std::integral_constant<OperandLabel, label>,
            std::integral_constant<OperandLabel, OperandLabel::Imme>>>>>
struct OperandType {};

class VmImpl {
private:
public:
  // Assuming a 32-bit memory address space with a total of 2^16 addresses.
  ImmeType memory[memory_addr_space];
  // .section .text 32-bit address space with a total of 2^16 addresses
  ImmeType registers[register_number];

public:
  VmImpl() {
    std::fill(memory, memory + memory_addr_space, 0);
    std::fill(registers, registers + register_number, 0);
  }

private:
  friend OperandType<OperandLabel::Reg>;
  friend OperandType<OperandLabel::Mem>;
};

static thread_local std::unique_ptr<VmImpl> VM_IMPL = nullptr;

static VmImpl *get_vm_impl() {
  if (!VM_IMPL) {
    VM_IMPL = std::make_unique<VmImpl>();
  }
  return VM_IMPL.get();
}

template <> struct OperandType<OperandLabel::Reg> {
  using type = RegIndexType;
  inline static ImmeType *get_ptr(type val) {
    return &get_vm_impl()->registers[val];
  }
  inline static ImmeType get_val(type val) {
    return get_vm_impl()->registers[val];
  }
};

template <> struct OperandType<OperandLabel::Mem> {
  using type = AddrIndexType;
  inline static ImmeType *get_ptr(type val) {
    return &get_vm_impl()->memory[val];
  }
  inline static ImmeType get_val(type val) {
    return get_vm_impl()->memory[val];
  }
};

template <> struct OperandType<OperandLabel::Imme> {
  using type = ImmeType;
  inline static ImmeType *get_ptr(type val) { return nullptr; }
  inline static ImmeType get_val(type val) { return val; }
};

} // namespace Impl