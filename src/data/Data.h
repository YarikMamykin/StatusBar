#pragma once
#include <variant>

namespace ymwm::data {

  struct Time {};
  struct Cpu {};
  struct Ram {};
  struct Drive {};
  struct Battery {};

  using Data = std::variant<std::monostate, Time, Cpu, Ram, Drive, Battery>;

} // namespace ymwm::data
