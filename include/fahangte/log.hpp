#pragma once
#include <iomanip>
#include <iostream>
namespace fahangte::util {
#define CURRENT_LINE __LINE__
#define CURRENT_FILE __FILE__

#define LOG_ACTIVE

#ifdef LOG_ACTIVE
#define DEBUG(...)                                                             \
  do {                                                                         \
    ::std::ostringstream oss;                                                  \
    oss << "[DEBUG]"                                                           \
        << " "                                                                 \
        << "(" << CURRENT_FILE << "," << CURRENT_LINE << ")";                  \
    ::std::cout << ::std::left << ::std::setw(70) << ::std::setfill(' ')       \
                << oss.str();                                                  \
    fahangte::util::print_args(__VA_ARGS__);                                   \
  } while (false)
#else
#define DEBUG(...)
#endif

#ifdef LOG_ACTIVE
#define INFO(msg)                                                              \
  do {                                                                         \
    ::std::ostringstream oss;                                                  \
    oss << "|INFO|"                                                            \
        << " "                                                                 \
        << "(" << CURRENT_FILE << "," << CURRENT_LINE << ")";                  \
    ::std::cout << "======" << ::std::endl;                                    \
    ::std::cout << ::std::left << ::std::setw(70) << ::std::setfill(' ')       \
                << oss.str();                                                  \
    ::std::cout << msg << ::std::endl;                                         \
    ::std::cout << "======" << ::std::endl;                                    \
  } while (false)
#else 
#define INFO(msg)
#endif

template <typename... T> void print_args(T const &...args) {

  (::std::cout << ... << (::std::cout << args, " ")) << ::std::endl;
}
} // namespace fahangte::util
