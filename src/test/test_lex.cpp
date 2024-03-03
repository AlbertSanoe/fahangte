
#include "fahangte/file.hpp"
#include "fahangte/scanner.hpp"
#include "fahangte/test.hpp"
#include <iostream>
#include <memory>

#define TEST_ACTIVE
// #undef TEST_ACTIVE

#ifdef TEST_ACTIVE
int main(int argc, char **argv)
#else
void test()
#endif
{
  using namespace fahangte::file;
  using namespace fahangte::lex;
  if (argc != 2) {
    std::cerr << "the argument is not valid\n";
    return 1;
  }
  FileReader reader_ptr;
  reader_ptr.load_file(argv[1]);
  Scanner s(&reader_ptr);
  for (int i = 0; i < 10; i++) {
    auto x = s.get_token();
    DEBUG(x);
    auto judge_eof = [](const Token::Tag &tag) -> bool {
      return std::visit(
          [](auto &&arg) -> bool {
            using T = std::decay_t<decltype(arg)>;
            return std::is_same_v<T, Token::Eof>;
          },
          tag);
    };
    if (judge_eof(x._tag)) {
      break;
    }
  }
}