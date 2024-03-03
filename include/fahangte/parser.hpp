#pragma once
#include "ast.hpp"
#include "fahangte/ast.h"
#include "fahangte/ast.hpp"
#include "scanner.hpp"
#include <memory>
#include <type_traits>
namespace fahangte::parse {

// using AstInteger = AstLiteral<int>;

// template <typename ParseType, typename AstType> class ParseBase {
// public:
//   AstType generate() { impl().generate(); }

// private:
//   ParseType &impl() { return *static_cast<ParseType *>(this); }
// };

// template <typename AstBinaryOperator, typename AstLeftOperand,
//           typename AstRightOperand>
// class ParseBinary final
//     : public ParseBase<
//           ParseBinary<AstBinaryOperator, AstLeftOperand, AstRightOperand>,
//           AstBinaryOperator> {
// public:
//   static AstBinaryOperator generate(std::unique_ptr<AstLeftOperand> lvalue,
//                                     std::unique_ptr<AstRightOperand> rvalue) {
//     return AstBinaryOperator(std::move(lvalue), std::move(rvalue));
//   }
// };
// class ParseInteger final : public ParseBase<ParseInteger, AstInteger> {
// public:
//   static AstInteger generate(int value) { return AstInteger(value); }
// };



class Parser {

private:
  enum class Precedence {
    PowerNone,
    PowerTerm,
    PowerFactor,
  };

  template <typename T> struct TokenToParse;

  template <> struct TokenToParse<lex::Token::Integer> {
    using prefix_ast =ast::AstLiteral<typename Literal, typename Inner>;
    static constexpr Precedence power = Precedence::PowerNone;
  };

  template <> struct TokenToParse<lex::Token::Plus> {
    using infix_type = ParseBinary<AstBinaryAdd<AstInteger, AstInteger>,
                                   AstInteger, AstInteger>;
    static constexpr Precedence power = Precedence::PowerTerm;
  };

  template <> struct TokenToParse<lex::Token::Minus> {
    using infix_type = ParseBinary<AstBinarySubtract<AstInteger, AstInteger>,
                                   AstInteger, AstInteger>;
    static constexpr Precedence power = Precedence::PowerTerm;
  };

  template <> struct TokenToParse<lex::Token::Asterisk> {
    using infix_type = ParseBinary<AstBinaryMultiply<AstInteger, AstInteger>,
                                   AstInteger, AstInteger>;
    static constexpr Precedence power = Precedence::PowerFactor;
  };

  template <> struct TokenToParse<lex::Token::Slash> {
    using infix_type = ParseBinary<AstBinaryDivide<AstInteger, AstInteger>,
                                   AstInteger, AstInteger>;
    static constexpr Precedence power = Precedence::PowerFactor;
  };

  // Return Type Infer
  template <typename Parse> struct ReturnType;

  template <typename AstType, typename ParseType, typename... Args>
  struct ReturnType<AstType (ParseType::*)(Args...)> {
    using type = AstType;
  };

  template <typename AstType, typename ParseType, typename... Args>
  struct ReturnType<AstType (ParseType::*)(Args...) const> {
    using ast_type = AstType;
  };

private:
  template <typename TokenType, typename... Args>
  static auto prefix(Args... args) {
    using ParseType = typename TokenToParse<TokenType>::prefix_type;
    using AstType =
        typename ReturnType<decltype(&ParseType::generate)>::ast_type;
    return ParseType::generate(std::forward<Args>(args)...);
  }

  template <typename TokenType, typename... Args>
  static auto infix(Args... args) {
    using ParseType = typename TokenToParse<TokenType>::infix_type;
    using AstType =
        typename ReturnType<decltype(&ParseType::generate)>::ast_type;
    return ParseType::generate(std::forward<Args>(args)...);
  }
private:
  lex::Scanner*_scaner;
  lex::Token _previous;
  lex::Token _current;
  void advance(){
    _previous=_current;
    _current=_scaner->get_token();
  }
  // lex::Token consume();
  // lex::Token peek();
  public:
  explicit Parser(lex::Scanner*scanner):_scaner(scanner){}
  
  void parse(){
    advance();
    auto x=_current;

    auto judge_eof = [](const lex::Token::Tag &tag) -> bool {
      return std::visit(
          [](auto &&arg) -> bool {
            using T = std::decay_t<decltype(arg)>;
            return std::is_same_v<T, lex::Token::Eof>;
          },
          tag);
    };

    
    //this->prefix<x>();
  }
};
} // namespace fahangte::parse
