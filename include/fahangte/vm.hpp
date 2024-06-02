#pragma once

#include <algorithm> /* fill */
#include <cstdint> /* UINT16_MAX */

class VirtualMachine;

class InsturctionUnit {
public:
  InsturctionUnit(uint8_t i) : unit(i) {}
  static const int non_operand_instruction_signal = 0;
  static const int one_operand_instruction_signal = 1;
  static const int two_operand_instruction_signal = 2;
  enum class NonOperand : uint8_t {
    NOP = 0,
    HALT = 1,
  };
  enum class OneOperand : uint8_t {
    STDIN = 0,
    STDOUT = 1,
    JMP = 2,
    JE = 3,
    JNE = 4,
    JLT = 5,
    JLE = 6,
    JGT = 7,
    JGE = 8,
  };
  enum class TwoOperand : uint8_t {
    MOV_RR = 0,
    MOV_RM = 1,
    MOV_RI = 2,
    MOV_MR = 3,
    MOV_MI = 4,

    ADD_RR = 5,
    ADD_RM = 6,
    ADD_RI = 7,
    ADD_MR = 8,
    ADD_MI = 9,

    SUB_RR = 10,
    SUB_RM = 11,
    SUB_RI = 12,
    SUB_MR = 13,
    SUB_MI = 14,

    MUL_RR = 15,
    MUL_RM = 16,
    MUL_RI = 17,
    MUL_MR = 18,
    MUL_MI = 19,

    DIV_RR = 20,
    DIV_RM = 21,
    DIV_RI = 22,
    DIV_MR = 23,
    DIV_MI = 24,

    TEST_RR = 25,
    TEST_RM = 26,
    TEST_RI = 27,
    TEST_MR = 28,
    TEST_MI = 29,
  };

  friend class VirtualMachine;

private:
  const uint8_t unit;
};

class VirtualMachine {
public:
  static const uint32_t instruction_addr_space = UINT16_MAX + 1;
  static const uint32_t memory_addr_space = UINT16_MAX + 1;
  static const int register_number = 8;

  VirtualMachine() {
    std::fill(memory, memory + memory_addr_space, 0);
    std::fill(text, text + instruction_addr_space, 0);
    std::fill(registers, registers + register_number, 0);
    ax = &registers[0];
    bx = &registers[1];
    cx = &registers[2];
    dx = &registers[3];
    ex = &registers[4];
    fx = &registers[5];
    gx = &registers[6];
    pc = &registers[7];
  }

  void non_operand_instruction();
  void one_operand_instruction();
  void two_operand_instruction();

private:
    void exeHALT();
    void exeNOP();
    void exeSTDIN(uint32_t*addr);
    void exeSTDOUT(uint32_t num);
    void exeJMP(uint32_t next);
    void exeJE(uint32_t next);
    void exeJNE();
    void exeJLT();
    void exeJLE();
    void exeJGT();
    void exeJGE();
    void exeMOVRR();
  static uint32_t memory[memory_addr_space];
  static InsturctionUnit text[instruction_addr_space];
  static uint32_t registers[register_number];
  uint32_t *ax, *bx, *cx, *dx, *ex, *fx, *gx, *pc;
  inline int which(InsturctionUnit i) { return (i.unit & (3 << 6)) >> 6; }
  
};