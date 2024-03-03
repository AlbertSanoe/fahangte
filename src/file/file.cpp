#include "fahangte/file.hpp"
#include "fahangte/log.hpp"
#define LOG_FILE
#undef LOG_FILE
namespace fahangte::file {
bool FileReader::load_file(std::string const &file_path) {
  _file_path = file_path;
  _file_ptr.open(_file_path, std::ifstream::in);
  if (!_file_ptr.is_open()) {
    return false;
  }
  _current_line = 1;
  _current_col = 1;
  _eof_sign = false;
  _cur_pos = _file_ptr.tellg();
#ifdef LOG_FILE
  DEBUG(_cur_pos);
#endif
  _cur_ch = _file_ptr.get();
  return true;
}

void FileReader::get_pos(unsigned int &line, unsigned int &col) {
  line = _current_line;
  col = _current_col;
} // no safe guarantee
char FileReader::get_current() { return _cur_ch; } // no safe guarantee
bool FileReader::get_lookahead(char &ch) {
  return (ch = static_cast<char>(_file_ptr.peek()), ch != EOF) ? true : false;
} // tell whether it reaches EOF

void FileReader::next() {
  if (_eof_sign) {
    return;
  }
  if (_cur_ch == '\n') {
    _current_line += 1;
    _current_col = 1;
  } else {
    _current_col += 1;
  }
#ifdef LOG_FILE
  DEBUG(_current_line, _current_col);
#endif
  _cur_ch = _file_ptr.get();
  _cur_pos = _file_ptr.tellg();
  _eof_sign = _file_ptr.eof();
  // check if reaches end of file
#ifdef LOG_FILE
  DEBUG("cur:", _cur_ch, "cpos:", _cur_pos,
        "sign:", _eof_sign);
#endif
}
bool FileReader::is_eof() { return _eof_sign; }

} // namespace fahangte::file