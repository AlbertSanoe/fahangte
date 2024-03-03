#include "fahangte/file.hpp"
#include "fahangte/log.hpp"
#include <string>
#define TEST_ACTIVE
// #undef TEST_ACTIVE

void test1(const std::string &file) {
  DEBUG(file);
  using namespace fahangte::file;
  FileReader fr;

  // 测试加载文件
  if (!fr.load_file(file)) {
    std::cerr << "Failed to load file.\n";
  }

  // 测试获取当前位置
  unsigned int line, col;
  fr.get_pos(line, col);
  DEBUG("Initial position: Line ", line, ", Column ", col);

  // 测试读取当前字符和向前查看
  char current = fr.get_current();
  char lookahead;
  bool is_eof=fr.get_lookahead(lookahead);
  DEBUG("Current char: ", current, ", Lookahead char: ", lookahead);

  // 测试向前移动并获取新位置
  if (!fr.is_eof()) {
    INFO("next");
    fr.next();
    current = fr.get_current();
    DEBUG("the new ch", current);
    fr.get_pos(line, col);
    DEBUG("After moving: Line ", line, ", Column ", col);
  } else {
    DEBUG("Reached EOF or encountered an error.");
  }

  // 继续测试到文件末尾
  do {
    if (fr.next(); fr.is_eof()) {
      break;
    }
    current = fr.get_current();
    if (current == '\n')
      DEBUG("blank");
    else {
      DEBUG(current);
    }
  } while (1);
  DEBUG("Reached EOF.");
}

#ifdef TEST_ACTIVE
int main(int argc, char **argv)
#else
void test_filereader()
#endif
{
  if (argc != 2) {
    std::cerr << "the argument is not valid\n";
    return 1;
  }

  std::string file_name(argv[1]);
  test1(file_name);
}
