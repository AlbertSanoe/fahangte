#pragma once

#include "../impl/vm_impl.hpp"

namespace Code {

class BaseCode {
public:
  virtual ~BaseCode() = default;
  virtual void handle() = 0;
};

} // namespace Code
