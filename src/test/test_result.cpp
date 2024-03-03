#include "fahangte/test.hpp"

#define TEST_ACTIVE
#undef TEST_ACTIVE

using namespace fahangte::util;

/**
 * @brief testing basic functions
 */
void T1() {
  std::string successMessage = "Operation successful";
  int errorCode = 500;
  auto result1 = Ok<std::string, int>("Everything is fine");
  auto result2 = Err<std::string, int>(334);
  auto result3 = Err<std::string, int>(errorCode);
  auto result4 = Ok<std::string, int>(std::move(successMessage));

  INFO("result1:");
  if (result1.is_ok()) {
    DEBUG("the value is: ", result1.ok().value());
  } else {
    DEBUG("the value is: ", result1.err().value());
  }
  DEBUG(result1);

  INFO("result2:");
  if (result2.is_err()) {
    DEBUG("the value is: ", result2.err().value());
  } else {
    DEBUG("the value is: ", result2.ok().value());
  }
  DEBUG(result2);

  INFO("Result 3:");
  if (result3.is_err()) {
    DEBUG("the value is: ", result3.err().value());
  } else {
    DEBUG("the value is: ", result3.ok().value());
  }
  DEBUG(result3);

  INFO("Result 4:");
  if (result3.is_ok()) {
    DEBUG("the value is: ", result3.ok().value());
  } else {
    DEBUG("the value is: ", result3.err().value());
  }
  DEBUG(result4);
}

/**
 * @brief testing copy constructers
 */
void T2() {
  // 常规拷贝构造函数测试
  Result<std::string, int> originalResult(Ok<std::string, int>("Original"));
  Result<std::string, int> copiedResult(originalResult);

  DEBUG("Original Result: ", originalResult);
  DEBUG("Copied Result: ", copiedResult);

  // 移动拷贝构造函数测试
  Result<std::string, int> movedResult = Ok<std::string, int>("To be moved");
  Result<std::string, int> resultAfterMove(std::move(movedResult));
  DEBUG("Original Result: ", movedResult);
  DEBUG("Moved Result: ", resultAfterMove);

  auto y = std::move(originalResult);
  DEBUG(y);
  auto x = y;
  DEBUG(x);
}

//  成功的函数，返回 Result<int, std::string>
Result<std::string, std::string> SuccessFunc(int x) {
  return Ok<std::string, std::string>(std::to_string(x));
}

// 失败的函数，返回 Result<int, std::string>
Result<int, std::string> FailFunc(int value) {
  return Err<int, std::string>("Error occurred");
}

// 转换函数，用于 map 方法
double TransformFunc(double value) { return value + 10; }
struct x {
  int operator()() { return 4; }
};

#include <functional>

void T3() {
  int x = 4;
  auto try_lam = [&x](int x1) noexcept -> Result<int, std::string> {
    return Ok<int, std::string>(x * 2 + x1);
  };

  // 测试 chain_and 方法
  auto result1 = try_lam(x);
  auto chain_and_result1 = result1.concat(try_lam(8));
  std::cout << "chain_and_result1: " << chain_and_result1 << std::endl;

  auto result2 = FailFunc(5);
  auto chain_and_result2 = result2.concat(SuccessFunc(10));
  std::cout << "chain_and_result2: " << chain_and_result2 << std::endl;

  // // 测试 chain_andthen 方法
  auto chain_andthen_result1 = result1.concat_then(SuccessFunc);
  std::cout << "chain_andthen_result1: " << chain_andthen_result1 << std::endl;

  auto chain_andthen_result2 = result2.concat_then(SuccessFunc);
  std::cout << "chain_andthen_result2: " << chain_andthen_result2 << std::endl;
  std::function xxx = try_lam;
  // 测试 map 方法
  auto map_result1 = result1.map(std::move(xxx));
  std::cout << "map_result1: " << map_result1 << std::endl;

  auto map_result2 = result2.map(try_lam);
  std::cout << "map_result2: " << map_result2 << std::endl;
}

#ifdef TEST_ACTIVE
int main()
#else
void test_result()
#endif
{
  T1();
}
