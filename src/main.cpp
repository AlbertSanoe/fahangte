// #include <iostream>
// #include "test.hpp"
// #include <cstdint>
// #include "vm/vm.hpp"

// int main() {
//   VirtualMachine vm;

//   // Instruction x(Instruction::InstructionType::CMPMI);
//   // std::cout<<std::hex<<std::uppercase<<(unsigned int)x.unit<<std::endl;
//   // vm.test(x);

//   Instruction array[3];
//   array[0]=Instruction(Instruction::InstructionType::MOVRR);
//   array[1]=0;
//   array[2]=6;

//   vm.registers[6]=12580;
//   uint32_t *ptr=(uint32_t*)array;
//   vm.loadPC(ptr);
//   vm.exeMOVRR();
//   std::cout<<vm.registers[6]<<std::endl;

// }

// #include "vm/code/base.hpp"
// #include "vm/code/type2.hpp"
// #include "vm/impl/vm_impl.hpp"
// #include <iostream>

// int main() {
//   Impl::get_vm_impl()->registers[0] = 10;
//   Impl::get_vm_impl()->registers[1] = 20;
//   Code::BaseCode *addCode;
//   auto code = Code::Type2<Impl::Param2::add, Impl::OperandLabel::Reg,
//                           Impl::OperandLabel::Reg>(0, 1);
//   addCode = &code;
//   // 执行 add 指令
//   addCode->handle();
//   std::cout << sizeof(code) << std::endl;
//   // 打印执行结果
//   std::cout << "Result: ax = " << Impl::get_vm_impl()->registers[0]
//             << std::endl;

//   return 0;
// }

#include "common/log.hpp"
#include "parse/lex/lexer.hpp"
#include "parse/parser.hpp"
#include "parse/type.hpp"
#include "parse/visitor/dump_visitor.hpp"
#include "parse/visitor/type_check_visitor.hpp"
#include <iostream>

void testLexer() {
  using namespace Lex;
  std::queue<Token> tokenQueue;
  INFO("the input string is: {}", "5*3+2");
  // 创建表示 5*3+2 的 Token 序列
  tokenQueue.push(Token::createInteger("5", 5));
  tokenQueue.push(Token::createOperator<OperatorType::BinaryMultiply>("*"));
  tokenQueue.push(Token::createInteger("3", 3));
  tokenQueue.push(Token::createOperator<OperatorType::BinaryPlus>("+"));
  tokenQueue.push(Token::createInteger("2", 2));

  // 创建 Lexer 对象
  Lexer lexer(std::move(tokenQueue));

  // 使用 Lexer 对象处理 Token 序列
  while (true) {
    Token token = lexer.peek();
    if (token.getKind() == TokenType::Eof) {
      break;
    }

    token = lexer.consume();
    switch (token.getKind()) {
    case TokenType::Integer:
      INFO("{}: {}", token.getKind(), token.getIntValue());
      break;
    case TokenType::Operator:
      INFO("{}: {}", token.getKind(),
           token.getOperatorInfo().getOperatorType());
      break;
    default:
      break;
    }
  }
}

int main() { 
  using namespace Lex;
  std::queue<Token> tokenQueue;
  INFO("the input string is: {}", "5 * 3 + 2 / 7 - 6 * 5 / 8");
  
  // 创建表示 5 * 3 + 2/7-6*5/8 的 Token 序列
  tokenQueue.push(Token::createInteger("5", 5));
  tokenQueue.push(Token::createOperator<OperatorType::BinaryMultiply>("*"));
  tokenQueue.push(Token::createInteger("3", 3));
  tokenQueue.push(Token::createOperator<OperatorType::BinaryPlus>("+"));
  tokenQueue.push(Token::createInteger("2", 2));
  tokenQueue.push(Token::createOperator<OperatorType::BinaryDivide>("/"));
  tokenQueue.push(Token::createInteger("7", 7));
  tokenQueue.push(Token::createOperator<OperatorType::BinaryMinus>("-"));
  tokenQueue.push(Token::createInteger("6", 6));
  tokenQueue.push(Token::createOperator<OperatorType::BinaryMultiply>("*"));
  tokenQueue.push(Token::createInteger("5", 5));
  tokenQueue.push(Token::createOperator<OperatorType::BinaryDivide>("/"));
  tokenQueue.push(Token::createInteger("8", 8));

  // 创建 Lexer 对象
  Lexer lexer(std::move(tokenQueue));

  Parser parser(std::move(lexer));
  Ast::Expr ast = parser.parse();
  typeCheck(ast);
  dump(ast);
}
