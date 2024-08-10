#include "vm_impl.hpp"
#include <iostream>
namespace Impl {

inline void implSTDIN(ImmeType data) { std::cin >> data; }

inline void implSTDOUT(ImmeType data) { std::cout << data << std::endl; }

} // namespace Impl