#pragma once
#include <variant>

namespace ymwm::data {

  struct Date {};
  struct Time {};
  struct Cpu {};
  struct Ram {};
  struct Drive {};
  struct Battery {};

  using Data =
      std::variant<std::monostate, Date, Time, Cpu, Ram, Drive, Battery>;

} // namespace ymwm::data
