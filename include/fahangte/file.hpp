#pragma once
#include <fstream>
#include <string>

namespace fahangte::file {

class FileReader {
public:
  bool load_file(std::string const &file_path);
  void get_pos(unsigned int &line, unsigned int &col);
  char get_current();
  bool get_lookahead(char &lookahead);
  void next();
  bool is_eof();

private:
  bool _eof_sign; // true if reaches end of file
  char _cur_ch;
  std::string _file_path;
  unsigned int _current_line;
  unsigned int _current_col;
  std::ifstream _file_ptr;
  std::streampos _cur_pos;
};
} // namespace fahangte::file