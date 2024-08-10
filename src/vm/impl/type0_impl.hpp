#include "vm_impl.hpp"
#include <iostream>
namespace Impl {
inline void implHALT() { std::cout << "exeHALT" << std::endl; }

inline void implNOP() { std::cout << "exeNOP" << std::endl; }
} // namespace Impl