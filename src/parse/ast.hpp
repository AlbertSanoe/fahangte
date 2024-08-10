#pragma once

namespace Parse {

enum class ExprRetType { Unevaluated, Integer };

class Node {
private:
  ExprRetType ret_type;
};
} // namespace Parse
