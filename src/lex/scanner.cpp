#include "fahangte/scanner.hpp"
#include "fahangte/log.hpp"
#include <type_traits>
#include <variant>
#define LOG_SCANNER
namespace fahangte::lex {

#define CONVERT_NUMBER(c) static_cast<int>((c) - '0')
#define IS_ALPHA(c)                                                            \
  (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z') || (c) == '_')
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')

#define IS_SPACE(c) ((c) == ' ' || (c) == '\t' || (c) == '\n')

bool Scanner::is_alpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::is_digit(char c) { return c >= '0' && c <= '9'; }

// after current()
Token Scanner::gen_number() {
  int number = 0;
  unsigned int length = 0;
  unsigned int line, column;
  _file_reader->get_pos(line, column);
  char ch = _file_reader->get_current();
  do {
    number = (number << 3) + (number << 1) + CONVERT_NUMBER(ch);
    length += 1;
    _file_reader->next();
    ch = _file_reader->get_current();
  } while (IS_DIGIT(ch));

  return Token(Token::Integer{number}, length, line, column);
}

// after current()
Token Scanner::gen_punctuation() {
  char ch = _file_reader->get_current();
  unsigned int line, column;
  _file_reader->get_pos(line, column);
  _file_reader->next();
  //DEBUG(static_cast<int>(ch));
  switch (ch) {
  case '+':
    return Token(Token::Plus{}, 1, line, column);
  case '-':
    return Token(Token::Minus{}, 1, line, column);
  case '*':
    return Token(Token::Asterisk{}, 1, line, column);
  case '/':
    return Token(Token::Slash{}, 1, line, column);
  default:
    return Token(Token::Unknown{}, 1, line, column);
  }
}

void Scanner::ignore_space() {
  char ch;
  for (;;) {
    ch = _file_reader->get_current();
    if ((IS_SPACE(ch))) {
      //DEBUG("space", static_cast<int>(ch));
      _file_reader->next();
      continue;
    }
    break;
  }
}

Token Scanner::gen_eof() {
  unsigned int line, column;
  _file_reader->get_pos(line, column);
  return Token(Token::Eof{}, 1, line, column);
}

Token Scanner::get_token() {
  ignore_space();
  // skip space
  if (_file_reader->is_eof()) {
    return gen_eof();
  }
  char c = _file_reader->get_current();
  if (IS_DIGIT(c)) {
    return gen_number();
  }

  return gen_punctuation();
}

} // namespace fahangte::lex