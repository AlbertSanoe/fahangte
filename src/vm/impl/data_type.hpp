#pragma once
#include <cstdint>
namespace Impl {
using ImmeType = uint32_t;
using AddrIndexType = uint16_t;
using RegIndexType = uint8_t;

enum class Param0 : uint8_t {
  nop = 0,
  halt = 1,
};

enum class Param1 : uint8_t {
  stdin = 0,
  stdout = 1,
  jmp = 2,
  je = 3,
  jne = 4,
  jlt = 5,
  jle = 6,
  jgt = 7,
  jge = 8,
};

enum class Param2 : uint8_t {
  mov = 0,
  add = 1,
  sub = 2,
  mul = 3,
  div = 4,
  cmp = 5,
};

enum class OperandLabel {
  Reg = 0,
  Mem = 1,
  Imme = 2,
};

} // namespace Impl