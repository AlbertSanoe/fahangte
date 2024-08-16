#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#define CURRENT_LINE __LINE__
#define CURRENT_FILE __FILE__

template <typename T>
void format_helper(std::ostringstream &oss, std::string_view &str,
                   const T &value) {
  std::size_t openBracket = str.find('{');
  if (openBracket == std::string::npos) {
    return;
  }
  std::size_t closeBracket = str.find('}', openBracket + 1);
  if (closeBracket == std::string::npos) {
    return;
  }
  oss << str.substr(0, openBracket) << value;
  str = str.substr(closeBracket + 1);
}

template <typename... Targs>
std::string format_impl(std::string_view format = "", Targs &&...args) {
  std::ostringstream oss;
  (format_helper(oss, format, std::forward<Targs>(args)), ...);
  oss << format;
  return oss.str();
}

template <typename... Targs>
void FORMAT(std::string_view format = "", Targs &&...args) {
  std::string str = format_impl(format, std::forward<Targs>(args)...);
  std::cout << str << std::endl;
}

constexpr const char *LOG_COLOR_BOLD_RED = "\033[1;31m";
constexpr const char *LOG_COLOR_RED = "\033[0;31m";

constexpr const char *LOG_COLOR_BOLD_BLUE = "\033[1;34m";
constexpr const char *LOG_COLOR_BLUE = "\033[0;34m";

constexpr const char *LOG_COLOR_BOLD_YELLOW = "\033[1;33m";
constexpr const char *LOG_COLOR_YELLOW = "\033[0;33m";

constexpr const char *LOG_COLOR_BOLD_GREEN = "\033[1;32m";
constexpr const char *LOG_COLOR_GREEN = "\033[0;32m";

constexpr const char *LOG_UNDERLINE = "\033[4m";
constexpr const char *LOG_RESET = "\033[0m";

#define DEBUG(...)                                                             \
  do {                                                                         \
    ::std::ostringstream oss;                                                  \
    oss << format_impl("{}[DEBUG]   {}({}, {}){}{}: ", LOG_COLOR_BOLD_BLUE,    \
                       LOG_UNDERLINE, CURRENT_FILE, CURRENT_LINE, LOG_RESET,   \
                       LOG_COLOR_BOLD_BLUE);                                   \
    oss << format_impl(__VA_ARGS__);                                           \
    oss << LOG_RESET;                                                          \
    ::std::cout << oss.str() << ::std::endl;                                   \
  } while (false)

#define INFO(...)                                                              \
  do {                                                                         \
    ::std::ostringstream oss;                                                  \
    oss << format_impl("{}[INFO]    {}({}, {}){}{}: ", LOG_COLOR_BOLD_GREEN,   \
                       LOG_UNDERLINE, CURRENT_FILE, CURRENT_LINE, LOG_RESET,   \
                       LOG_COLOR_BOLD_GREEN);                                  \
    oss << format_impl(__VA_ARGS__);                                           \
    oss << LOG_RESET;                                                          \
    ::std::cout << oss.str() << ::std::endl;                                   \
  } while (false)

#define WARNING(...)                                                           \
  do {                                                                         \
    ::std::ostringstream oss;                                                  \
    oss << format_impl("{}[WARNING] {}({}, {}){}{}: ", LOG_COLOR_BOLD_YELLOW,  \
                       LOG_UNDERLINE, CURRENT_FILE, CURRENT_LINE, LOG_RESET,   \
                       LOG_COLOR_BOLD_YELLOW);                                 \
    oss << format_impl(__VA_ARGS__);                                           \
    oss << LOG_RESET;                                                          \
    ::std::cout << oss.str() << ::std::endl;                                   \
  } while (false)

#define FATAL(...)                                                             \
  do {                                                                         \
    ::std::ostringstream oss;                                                  \
    oss << format_impl("{}[FATAL]   {}({}, {}){}{}: ", LOG_COLOR_BOLD_RED,     \
                       LOG_UNDERLINE, CURRENT_FILE, CURRENT_LINE, LOG_RESET,   \
                       LOG_COLOR_BOLD_RED);                                    \
    oss << format_impl(__VA_ARGS__);                                           \
    oss << LOG_RESET;                                                          \
    ::std::cout << oss.str() << ::std::endl;                                   \
  } while (false)
