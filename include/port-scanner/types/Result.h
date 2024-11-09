// Copyright (c) 2024 Alexandru Constantin

#ifndef INCLUDE_PORT_SCANNER_TYPES_RESULT_H_
#define INCLUDE_PORT_SCANNER_TYPES_RESULT_H_

#include <optional>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

namespace ac_scanner {
template <typename T>
class Result {
 public:
  explicit Result(T value, std::optional<std::string> error = std::nullopt)
      : _value(value), _error(error) {}

  T getValue() const { return this->_value; }

  std::optional<std::string> getError() const { return this->_error; }

  template <std::size_t Index>
  std::tuple_element_t<Index, Result>& get() & {
    if constexpr (Index == 0)
      return _value;
    if constexpr (Index == 1)
      return _error;
  }

  template <std::size_t Index>
  std::tuple_element_t<Index, Result> const& get() const& {
    if constexpr (Index == 0)
      return _value;
    if constexpr (Index == 1)
      return _error;
  }

  template <std::size_t Index>
  std::tuple_element_t<Index, Result>&& get() && {
    if constexpr (Index == 0)
      return std::move(_value);
    if constexpr (Index == 1)
      return std::move(_error);
  }

 private:
  T _value;
  std::optional<std::string> _error;
};
}  // namespace ac_scanner

namespace std {
template <typename T>
struct tuple_size<::ac_scanner::Result<T>> : integral_constant<size_t, 2> {};

template <std::size_t Index, typename T>
struct tuple_element<Index, ::ac_scanner::Result<T>>
    : conditional<Index == 0, T, std::optional<std::string>> {
  static_assert(Index < 2,
                "Trying to access more fields than exist inside Result");
};

}  // namespace std

#endif  // INCLUDE_PORT_SCANNER_TYPES_RESULT_H_
