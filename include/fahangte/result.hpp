#pragma once
//#include "log.hpp"
#include <iostream>
#include <optional>
#include <type_traits>
#include <utility>
#include <variant>
// todo!
// is_ok_and
// is_err_and
// expect
// expect_err
// map_or

// refactor some functions using vistor
namespace fahangte::util {
template <typename T, typename F> class Result;
template <typename T, typename F> Result<T, F> Ok(T const &);
template <typename T, typename F> Result<T, F> Err(F const &);
template <typename T, typename F> Result<T, F> Ok(T &&);
template <typename T, typename F> Result<T, F> Err(F &&);

template <typename> struct OkType;
template <typename> struct ErrType;

template <typename T, typename F> struct OkType<Result<T, F>> {
  using type = T;
};

template <typename T, typename F> struct ErrType<Result<T, F>> {
  using type = F;
};

template <typename T, typename F> class Result {
public:
  friend Result<T, F> Ok<T, F>(T const &ok_lval);
  friend Result<T, F> Err<T, F>(F const &err_lval);
  friend Result<T, F> Ok<T, F>(T &&ok_rval);
  friend Result<T, F> Err<T, F>(F &&err_rval);

  bool is_ok() const;
  bool is_err() const;
  ::std::optional<T> ok() const;
  ::std::optional<F> err() const;

  template <typename U> Result<U, F> concat(Result<U, F> const &other);
  Result<T, F> choice(Result<T, F> const &other);
  template <typename Func>
  auto concat_then(Func &&func) -> Result<
      typename OkType<typename ::std::invoke_result<Func, T>::type>::type, F>;
  template <typename Func>
  auto choice_else(Func &&func) -> Result<
      T, typename ErrType<typename ::std::invoke_result<Func, T>::type>::type>;

  // is_ok_and
  // is_err_and
  // expect
  // expect_err
  // map_or

  template <typename Func>
  auto map(Func &&func) const
      -> Result<typename ::std::invoke_result<Func, T>::type, F>;

  // the copy constructor
  Result(Result const &result) : _value(result._value) {
    // INFO("copy!");
  }

  // the move constructor
  Result(Result &&result) noexcept : _value(::std::move(result._value)) {
    // INFO("MOVE");
  }

  friend ::std::ostream &operator<<(::std::ostream &out,
                                    Result<T, F> const &result) {
    if (result.is_ok()) {
      out << "OK: ";
      out << ::std::get<Result<T, F>::_ok_index>(result._value);
    } else {
      out << "Error: ";
      out << ::std::get<Result<T, F>::_err_index>(result._value);
    }
    return out;
  }

private:
  ::std::variant<T, F> _value;
  static int const _ok_index = 0;
  static int const _err_index = 1;
  struct _oktag {};
  struct _errtag {};
  Result(_oktag, T const &value)
      : _value(::std::in_place_index<Result::_ok_index>, value) {}
  Result(_errtag, F const &value)
      : _value(::std::in_place_index<Result::_err_index>, value) {}
  Result(_oktag, T &&value) noexcept
      : _value(::std::in_place_index<Result::_ok_index>, ::std::move(value)) {}
  Result(_errtag, F &&value) noexcept
      : _value(::std::in_place_index<Result::_err_index>, ::std::move(value)) {}
};

template <typename T, typename F> class ResultVistor {};

template <typename T, typename F> Result<T, F> Ok(T const &ok_lval) {
  return Result<T, F>(typename Result<T, F>::_oktag{}, ok_lval);
}

template <typename T, typename F> Result<T, F> Err(F const &err_lval) {
  return Result<T, F>(typename Result<T, F>::_errtag{}, err_lval);
}

template <typename T, typename F> Result<T, F> Ok(T &&ok_rval) {
  return Result<T, F>(typename Result<T, F>::_oktag{},
                      std::forward<T>(ok_rval));
}

template <typename T, typename F> Result<T, F> Err(F &&err_rval) {
  return Result<T, F>(typename Result<T, F>::_errtag{},
                      std::forward<F>(err_rval));
}

template <typename T, typename F> bool Result<T, F>::is_ok() const {
  return this->_value.index() == _ok_index;
}

template <typename T, typename F> bool Result<T, F>::is_err() const {
  return this->_value.index() == _err_index;
}

template <typename T, typename F>::std::optional<T> Result<T, F>::ok() const {
  auto visitor = [](auto &&arg) -> std::optional<T> {
    using Type = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<Type, T>) {
      return std::optional<T>{arg};
    } else {
      return std::nullopt;
    }
  };
  return std::visit(visitor, _value);
}

template <typename T, typename F>::std::optional<F> Result<T, F>::err() const {
  if (is_err()) {
    return ::std::get<Result::_err_index>(_value);
  } else {
    return ::std::nullopt;
  }
}

template <typename T, typename F>
template <typename Func>
auto Result<T, F>::map(Func &&func) const
    -> Result<typename ::std::invoke_result<Func, T>::type, F> {
  if (is_ok()) {
    return Ok<typename ::std::invoke_result<Func, T>::type, F>(
        func(ok().value()));
  } else {
    return Err<typename ::std::invoke_result<Func, T>::type, F>(err().value());
  }
}

template <typename T, typename F>
template <typename Func>
auto Result<T, F>::concat_then(Func &&func) -> Result<
    typename OkType<typename ::std::invoke_result<Func, T>::type>::type, F> {
  if (is_ok()) {
    return func(ok().value());
  } else {
    return Err<
        typename OkType<typename ::std::invoke_result<Func, T>::type>::type, F>(
        err().value());
  }
}

template <typename T, typename F>
template <typename Func>
auto Result<T, F>::choice_else(Func &&func) -> Result<
    T, typename ErrType<typename ::std::invoke_result<Func, T>::type>::type> {
  if (is_ok()) {
    return Ok<T, typename ErrType<
                     typename ::std::invoke_result<Func, T>::type>::type>(
        ok().value());
  } else {
    return func(err().value());
  }
}

template <typename T, typename F>
Result<T, F> Result<T, F>::choice(Result<T, F> const &other) {
  if (is_err()) {
    return other;
  } else {
    return *this;
  }
}

template <typename T, typename F>
template <typename U>
Result<U, F> Result<T, F>::concat(Result<U, F> const &other) {
  if (is_ok()) {
    return other;
  } else {
    return Err<U, F>(::std::move(err().value()));
  }
}
} // namespace fahangte::util
