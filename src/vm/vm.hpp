// #pragma once

// #include <algorithm> /* fill */
// #include <cstddef>
// #include <cstdint> /* UINT16_MAX */
// #include <unordered_map>

// class VirtualMachine;

// class Instruction {
// private:
//   static const uint8_t operand0 = 0;
//   static const uint8_t operand1 = 1;
//   static const uint8_t operand2 = 2;
//   static const uint8_t offsetOpType = 6;
//   static const uint8_t offset4bit = offsetOpType - 4;
//   static const uint8_t offset5bit = offsetOpType - 5;
// private:
//   enum class Type0 : uint8_t {
//     nop = 0,
//     halt = 1,
//   };

//   enum class Type1 : uint8_t {
//     stdin = 0,
//     stdout = 1,
//     jmp = 2,
//     je = 3,
//     jne = 4,
//     jlt = 5,
//     jle = 6,
//     jgt = 7,
//     jge = 8,
//   };
//   enum class Type1Param : uint8_t {
//     Reg = 0,
//     Mem = 1,
//     Imme = 2,
//   };
//   enum class Type2 : uint8_t {
//     movrr = 0,
//     movrm = 1,
//     movri = 2,
//     movmr = 3,
//     movmi = 4,

//     addrr = 5,
//     addrm = 6,
//     addri = 7,
//     addmr = 8,
//     addmi = 9,

//     subrr = 10,
//     subrm = 11,
//     subri = 12,
//     submr = 13,
//     submi = 14,

//     mulrr = 15,
//     mulrm = 16,
//     mulri = 17,
//     mulmr = 18,
//     mulmi = 19,

//     divrr = 20,
//     divrm = 21,
//     divri = 22,
//     divmr = 23,
//     divmi = 24,

//     cmprr = 25,
//     cmprm = 26,
//     cmpri = 27,
//     cmpmr = 28,
//     cmpmi = 29,
//   };

// public:
//   enum class InstructionType : uint8_t {
//     NOP = operand0 << offsetOpType | uint8_t(Type0::nop) << offset4bit,
//     HALT = operand0 << offsetOpType | uint8_t(Type0::halt) << offset4bit,

//     STDINR = operand1 << offsetOpType | uint8_t(Type1::stdin) << offset4bit |
//              uint8_t(Type1Param::Reg),
//     STDINM = operand1 << offsetOpType | uint8_t(Type1::stdin) << offset4bit |
//              uint8_t(Type1Param::Mem),

//     STDOUTR = operand1 << offsetOpType | uint8_t(Type1::stdout) << offset4bit |
//               uint8_t(Type1Param::Reg),
//     STDOUTM = operand1 << offsetOpType | uint8_t(Type1::stdout) << offset4bit |
//               uint8_t(Type1Param::Mem),
//     STDOUTI = operand1 << offsetOpType | uint8_t(Type1::stdout) << offset4bit |
//               uint8_t(Type1Param::Imme),

//     JMPR = operand1 << offsetOpType | uint8_t(Type1::jmp) << offset4bit |
//            uint8_t(Type1Param::Reg),
//     JMPM = operand1 << offsetOpType | uint8_t(Type1::jmp) << offset4bit |
//            uint8_t(Type1Param::Mem),
//     JMPI = operand1 << offsetOpType | uint8_t(Type1::jmp) << offset4bit |
//            uint8_t(Type1Param::Imme),

//     JER = operand1 << offsetOpType | uint8_t(Type1::je) << offset4bit |
//           uint8_t(Type1Param::Reg),
//     JEM = operand1 << offsetOpType | uint8_t(Type1::je) << offset4bit |
//           uint8_t(Type1Param::Mem),
//     JEI = operand1 << offsetOpType | uint8_t(Type1::je) << offset4bit |
//           uint8_t(Type1Param::Imme),

//     JNER = operand1 << offsetOpType | uint8_t(Type1::jne) << offset4bit |
//            uint8_t(Type1Param::Reg),
//     JNEM = operand1 << offsetOpType | uint8_t(Type1::jne) << offset4bit |
//            uint8_t(Type1Param::Mem),
//     JNEI = operand1 << offsetOpType | uint8_t(Type1::jne) << offset4bit |
//            uint8_t(Type1Param::Imme),

//     JLTR = operand1 << offsetOpType | uint8_t(Type1::jlt) << offset4bit |
//            uint8_t(Type1Param::Reg),
//     JLTM = operand1 << offsetOpType | uint8_t(Type1::jlt) << offset4bit |
//            uint8_t(Type1Param::Mem),
//     JLTI = operand1 << offsetOpType | uint8_t(Type1::jlt) << offset4bit |
//            uint8_t(Type1Param::Imme),

//     JLER = operand1 << offsetOpType | uint8_t(Type1::jle) << offset4bit |
//            uint8_t(Type1Param::Reg),
//     JLEM = operand1 << offsetOpType | uint8_t(Type1::jle) << offset4bit |
//            uint8_t(Type1Param::Mem),
//     JLEI = operand1 << offsetOpType | uint8_t(Type1::jle) << offset4bit |
//            uint8_t(Type1Param::Imme),

//     JGTR = operand1 << offsetOpType | uint8_t(Type1::jgt) << offset4bit |
//            uint8_t(Type1Param::Reg),
//     JGTM = operand1 << offsetOpType | uint8_t(Type1::jgt) << offset4bit |
//            uint8_t(Type1Param::Mem),
//     JGTI = operand1 << offsetOpType | uint8_t(Type1::jgt) << offset4bit |
//            uint8_t(Type1Param::Imme),

//     JGER = operand1 << offsetOpType | uint8_t(Type1::jge) << offset4bit |
//            uint8_t(Type1Param::Reg),
//     JGEM = operand1 << offsetOpType | uint8_t(Type1::jge) << offset4bit |
//            uint8_t(Type1Param::Mem),
//     JGEI = operand1 << offsetOpType | uint8_t(Type1::jge) << offset4bit |
//            uint8_t(Type1Param::Imme),

//     MOVRR = operand2 << offsetOpType | uint8_t(Type2::movrr) << offset5bit,
//     MOVRM = operand2 << offsetOpType | uint8_t(Type2::movrm) << offset5bit,
//     MOVRI = operand2 << offsetOpType | uint8_t(Type2::movri) << offset5bit,
//     MOVMR = operand2 << offsetOpType | uint8_t(Type2::movmr) << offset5bit,
//     MOVMI = operand2 << offsetOpType | uint8_t(Type2::movmi) << offset5bit,

//     ADDRR = operand2 << offsetOpType | uint8_t(Type2::addrr) << offset5bit,
//     ADDRM = operand2 << offsetOpType | uint8_t(Type2::addrm) << offset5bit,
//     ADDRI = operand2 << offsetOpType | uint8_t(Type2::addri) << offset5bit,
//     ADDMR = operand2 << offsetOpType | uint8_t(Type2::addmr) << offset5bit,
//     ADDMI = operand2 << offsetOpType | uint8_t(Type2::addmi) << offset5bit,

//     SUBRR = operand2 << offsetOpType | uint8_t(Type2::subrr) << offset5bit,
//     SUBRM = operand2 << offsetOpType | uint8_t(Type2::subrm) << offset5bit,
//     SUBRI = operand2 << offsetOpType | uint8_t(Type2::subri) << offset5bit,
//     SUBMR = operand2 << offsetOpType | uint8_t(Type2::submr) << offset5bit,
//     SUBMI = operand2 << offsetOpType | uint8_t(Type2::submi) << offset5bit,

//     MULRR = operand2 << offsetOpType | uint8_t(Type2::mulrr) << offset5bit,
//     MULRM = operand2 << offsetOpType | uint8_t(Type2::mulrm) << offset5bit,
//     MULRI = operand2 << offsetOpType | uint8_t(Type2::mulri) << offset5bit,
//     MULMR = operand2 << offsetOpType | uint8_t(Type2::mulmr) << offset5bit,
//     MULMI = operand2 << offsetOpType | uint8_t(Type2::mulmi) << offset5bit,

//     DIVRR = operand2 << offsetOpType | uint8_t(Type2::divrr) << offset5bit,
//     DIVRM = operand2 << offsetOpType | uint8_t(Type2::divrm) << offset5bit,
//     DIVRI = operand2 << offsetOpType | uint8_t(Type2::divri) << offset5bit,
//     DIVMR = operand2 << offsetOpType | uint8_t(Type2::divmr) << offset5bit,
//     DIVMI = operand2 << offsetOpType | uint8_t(Type2::divmi) << offset5bit,

//     MODRR = operand2 << offsetOpType | uint8_t(Type2::divrr) << offset5bit | 1,
//     MODRM = operand2 << offsetOpType | uint8_t(Type2::divrm) << offset5bit | 1,
//     MODRI = operand2 << offsetOpType | uint8_t(Type2::divri) << offset5bit | 1,
//     MODMR = operand2 << offsetOpType | uint8_t(Type2::divmr) << offset5bit | 1,
//     MODMI = operand2 << offsetOpType | uint8_t(Type2::divmi) << offset5bit | 1,

//     CMPRR = operand2 << offsetOpType | uint8_t(Type2::cmprr) << offset5bit,
//     CMPRM = operand2 << offsetOpType | uint8_t(Type2::cmprm) << offset5bit,
//     CMPRI = operand2 << offsetOpType | uint8_t(Type2::cmpri) << offset5bit,
//     CMPMR = operand2 << offsetOpType | uint8_t(Type2::cmpmr) << offset5bit,
//     CMPMI = operand2 << offsetOpType | uint8_t(Type2::cmpmi) << offset5bit,
//   };

//   friend class VirtualMachine;

//   // private:
// public:
//   uint8_t unit;
//   Instruction(InstructionType i) : unit(uint8_t(i)) {}
//   Instruction(uint8_t data) : unit(data) {}
//   Instruction() {}
// };

// class VirtualMachine {
// public:
//   using ImmeType = uint32_t;
//   using AddrIndexType = uint16_t;
//   using RegIndexType = uint8_t;
//   static const std::size_t instruction_addr_space = 1 << 16;
//   static const std::size_t memory_addr_space = 1 << 16;
//   static const RegIndexType register_number = 8;

//   // private:
// public:
//   // Assuming a 32-bit memory address space with a total of 2^16 addresses.
//   ImmeType memory[memory_addr_space];
//   // .section .text 32-bit address space with a total of 2^16 addresses
//   Instruction text[instruction_addr_space];

//   ImmeType registers[register_number];
//   ImmeType *ax, *bx, *cx, *dx, *ex, *fx, *gx, *PC;

// public:
//   VirtualMachine() {
//     std::fill(memory, memory + memory_addr_space, 0);
//     std::fill(text, text + instruction_addr_space, 0);
//     std::fill(registers, registers + register_number, 0);
//     ax = &registers[0];
//     bx = &registers[1];
//     cx = &registers[2];
//     dx = &registers[3];
//     ex = &registers[4];
//     fx = &registers[5];
//     gx = &registers[6];
//     PC = &registers[7];
//   }

//   void loadPC(uint32_t *ptr) { this->PC = ptr; }

//   void test(Instruction t) {

//     auto it = VirtualMachine::table.find((Instruction::InstructionType)t.unit);
//     if (it != table.end()) {
//       (this->*(it->second))();
//     } else {
//     }
//   }

//   void non_operand_instruction();
//   void one_operand_instruction();
//   void two_operand_instruction();

//   // private:
// public:
//   template <typename DataType>
//   void convert(DataType &val, std::size_t offset = 0);
//   template <typename DataType1, typename DataType2>
//   void convert2(DataType1 &val1, DataType2 &val2);

//   template <typename... DataTypes> void incPC();
//   void movePC(std::size_t addr);
//   // Template specialization for different types
//   template <typename ConvertType> struct Pace;

//   void exeHALT();
//   void exeNOP();
//   void exeSTDINR();
//   void exeSTDINM();
//   void exeSTDOUTR();
//   void exeSTDOUTM();
//   void exeSTDOUTI();
//   void exeJMPR();
//   void exeJMPM();
//   void exeJMPI();
//   void exeJER();
//   void exeJEM();
//   void exeJEI();
//   void exeJNER();
//   void exeJNEM();
//   void exeJNEI();
//   void exeJLTR();
//   void exeJLTM();
//   void exeJLTI();
//   void exeJLER();
//   void exeJLEM();
//   void exeJLEI();
//   void exeJGTR();
//   void exeJGTM();
//   void exeJGTI();
//   void exeJGER();
//   void exeJGEM();
//   void exeJGEI();

//   void exeMOVRR();
//   void exeMOVRM();
//   void exeMOVRI();
//   void exeMOVMR();
//   void exeMOVMI();

//   void exeADDRR();
//   void exeADDRM();
//   void exeADDRI();
//   void exeADDMR();
//   void exeADDMI();

//   void exeSUBRR();
//   void exeSUBRM();
//   void exeSUBRI();
//   void exeSUBMR();
//   void exeSUBMI();

//   void exeMULRR();
//   void exeMULRM();
//   void exeMULRI();
//   void exeMULMR();
//   void exeMULMI();

//   void exeDIVRR();
//   void exeDIVRM();
//   void exeDIVRI();
//   void exeDIVMR();
//   void exeDIVMI();

//   void exeMODRR();
//   void exeMODRM();
//   void exeMODRI();
//   void exeMODMR();
//   void exeMODMI();

//   void exeCMPRR();
//   void exeCMPRM();
//   void exeCMPRI();
//   void exeCMPMR();
//   void exeCMPMI();

//   static inline const std::unordered_map<Instruction::InstructionType,
//                                          void (VirtualMachine::*)()>
//       table = {
//           {Instruction::InstructionType::HALT, &VirtualMachine::exeHALT},
//           {Instruction::InstructionType::NOP, &VirtualMachine::exeNOP},

//           {Instruction::InstructionType::STDINR, &VirtualMachine::exeSTDINR},
//           {Instruction::InstructionType::STDINM, &VirtualMachine::exeSTDINM},

//           {Instruction::InstructionType::STDOUTR, &VirtualMachine::exeSTDOUTR},
//           {Instruction::InstructionType::STDOUTM, &VirtualMachine::exeSTDOUTM},
//           {Instruction::InstructionType::STDOUTI, &VirtualMachine::exeSTDOUTI},

//           {Instruction::InstructionType::JMPR, &VirtualMachine::exeJMPR},
//           {Instruction::InstructionType::JMPM, &VirtualMachine::exeJMPM},
//           {Instruction::InstructionType::JMPI, &VirtualMachine::exeJMPI},

//           {Instruction::InstructionType::JER, &VirtualMachine::exeJER},
//           {Instruction::InstructionType::JEM, &VirtualMachine::exeJEM},
//           {Instruction::InstructionType::JEI, &VirtualMachine::exeJEI},

//           {Instruction::InstructionType::JNER, &VirtualMachine::exeJNER},
//           {Instruction::InstructionType::JNEM, &VirtualMachine::exeJNEM},
//           {Instruction::InstructionType::JNEI, &VirtualMachine::exeJNEI},

//           {Instruction::InstructionType::JLTR, &VirtualMachine::exeJLTR},
//           {Instruction::InstructionType::JLTM, &VirtualMachine::exeJLTM},
//           {Instruction::InstructionType::JLTI, &VirtualMachine::exeJLTI},

//           {Instruction::InstructionType::JLER, &VirtualMachine::exeJLER},
//           {Instruction::InstructionType::JLEM, &VirtualMachine::exeJLEM},
//           {Instruction::InstructionType::JLEI, &VirtualMachine::exeJLEI},

//           {Instruction::InstructionType::JGTR, &VirtualMachine::exeJGTR},
//           {Instruction::InstructionType::JGTM, &VirtualMachine::exeJGTM},
//           {Instruction::InstructionType::JGTI, &VirtualMachine::exeJGTI},

//           {Instruction::InstructionType::JGER, &VirtualMachine::exeJGER},
//           {Instruction::InstructionType::JGEM, &VirtualMachine::exeJGEM},
//           {Instruction::InstructionType::JGEI, &VirtualMachine::exeJGEI},

//           {Instruction::InstructionType::MOVRR, &VirtualMachine::exeMOVRR},
//           {Instruction::InstructionType::MOVRM, &VirtualMachine::exeMOVRM},
//           {Instruction::InstructionType::MOVRI, &VirtualMachine::exeMOVRI},
//           {Instruction::InstructionType::MOVMR, &VirtualMachine::exeMOVMR},
//           {Instruction::InstructionType::MOVMI, &VirtualMachine::exeMOVMI},

//           {Instruction::InstructionType::ADDRR, &VirtualMachine::exeADDRR},
//           {Instruction::InstructionType::ADDRM, &VirtualMachine::exeADDRM},
//           {Instruction::InstructionType::ADDRI, &VirtualMachine::exeADDRI},
//           {Instruction::InstructionType::ADDMR, &VirtualMachine::exeADDMR},
//           {Instruction::InstructionType::ADDMI, &VirtualMachine::exeADDMI},

//           {Instruction::InstructionType::SUBRR, &VirtualMachine::exeSUBRR},
//           {Instruction::InstructionType::SUBRM, &VirtualMachine::exeSUBRM},
//           {Instruction::InstructionType::SUBRI, &VirtualMachine::exeSUBRI},
//           {Instruction::InstructionType::SUBMR, &VirtualMachine::exeSUBMR},
//           {Instruction::InstructionType::SUBMI, &VirtualMachine::exeSUBMI},

//           {Instruction::InstructionType::MULRR, &VirtualMachine::exeMULRR},
//           {Instruction::InstructionType::MULRM, &VirtualMachine::exeMULRM},
//           {Instruction::InstructionType::MULRI, &VirtualMachine::exeMULRI},
//           {Instruction::InstructionType::MULMR, &VirtualMachine::exeMULMR},
//           {Instruction::InstructionType::MULMI, &VirtualMachine::exeMULMI},

//           {Instruction::InstructionType::DIVRR, &VirtualMachine::exeDIVRR},
//           {Instruction::InstructionType::DIVRM, &VirtualMachine::exeDIVRM},
//           {Instruction::InstructionType::DIVRI, &VirtualMachine::exeDIVRI},
//           {Instruction::InstructionType::DIVMR, &VirtualMachine::exeDIVMR},
//           {Instruction::InstructionType::DIVMI, &VirtualMachine::exeDIVMI},

//           {Instruction::InstructionType::MODRR, &VirtualMachine::exeMODRR},
//           {Instruction::InstructionType::MODRM, &VirtualMachine::exeMODRM},
//           {Instruction::InstructionType::MODRI, &VirtualMachine::exeMODRI},
//           {Instruction::InstructionType::MODMR, &VirtualMachine::exeMODMR},
//           {Instruction::InstructionType::MODMI, &VirtualMachine::exeMODMI},

//           {Instruction::InstructionType::CMPRR, &VirtualMachine::exeCMPRR},
//           {Instruction::InstructionType::CMPRM, &VirtualMachine::exeCMPRM},
//           {Instruction::InstructionType::CMPRI, &VirtualMachine::exeCMPRI},
//           {Instruction::InstructionType::CMPMR, &VirtualMachine::exeCMPMR},
//           {Instruction::InstructionType::CMPMI, &VirtualMachine::exeCMPMI},
//   };
// };