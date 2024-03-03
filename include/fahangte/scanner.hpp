#pragma once
#include "file.hpp"
#include <memory>
#include <variant>
namespace fahangte::lex {
// enum class TokenType : unsigned int {
//   TOKEN_INTEGER = 0,
//   TOKEN_PLUS,
//   TOKEN_MINUS,
//   TOKEN_ASTERISK,
//   TOKEN_SLASH,
//   TOKEN_DOUBLE,
//   TOKEN_EOF,
//   TOKEN_UNKNOWN
// };

struct Token {
  struct Integer {
    int value;
  };
  struct Plus {};
  struct Minus {};
  struct Asterisk {};
  struct Slash {};
  struct Double {
    double value;
  };
  struct Eof {};
  struct Unknown {};
  using Tag =
      std::variant<Integer, Double, Plus, Minus, Asterisk, Slash, Eof, Unknown>;
  Tag _tag;
  unsigned int _length;
  unsigned int _line;
  unsigned int _column;
  Token() : _tag(Unknown{}) {}
  Token(Tag tag, unsigned int length, unsigned int line, unsigned int column)
      : _tag(tag), _length(length), _line(line), _column(column) {}
};


inline std::ostream &operator<<(std::ostream &out, const Token::Integer &tk) {
    return out << "Integer: " << tk.value;
}

inline std::ostream &operator<<(std::ostream &out, const Token::Double &tk) {
    return out << "Double: " << tk.value;
}

inline std::ostream &operator<<(std::ostream &out, const Token::Plus &) {
    return out << "Plus";
}

inline std::ostream &operator<<(std::ostream &out, const Token::Minus &) {
    return out << "Minus";
}

inline std::ostream &operator<<(std::ostream &out, const Token::Asterisk &) {
    return out << "Asterisk";
}

inline std::ostream &operator<<(std::ostream &out, const Token::Slash &) {
    return out << "Slash";
}

inline std::ostream &operator<<(std::ostream &out, const Token::Eof &) {
    return out << "EOF";
}

inline std::ostream &operator<<(std::ostream &out, const Token::Unknown &) {
    return out << "Unknown";
}

// 重载输出流操作符，用于Token
inline std::ostream &operator<<(std::ostream &out, const Token &tk) {
    std::visit([&out](auto &&arg) {
        out << arg; // 直接调用上面定义的重载
    }, tk._tag);
    return out << " (Line: " << tk._line << ", Column: " << tk._column << ")";
}

class Scanner {
public:
  explicit Scanner(fahangte::file::FileReader *file_reader)
      : _file_reader(file_reader) {}
  Token get_token();

private:
  bool is_alpha(char c);
  bool is_digit(char c);

  Token gen_number();
  Token gen_punctuation();
  Token gen_eof();
  void ignore_space();

private:
  fahangte::file::FileReader *_file_reader;
};
} // namespace fahangte::lex