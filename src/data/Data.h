#pragma once
#include <chrono>
#include <variant>
#include <vector>

namespace ymwm::data {

  struct Date {
    std::chrono::zoned_time<std::chrono::system_clock::duration> data;
  };

  struct Time {
    std::chrono::zoned_time<std::chrono::system_clock::duration> data;
  };

  struct Cpu {
    std::vector<unsigned char> cores_load_lvl;
    unsigned char load_lvl;
  };

  struct Ram {
    unsigned int megabytes;
    unsigned char level;
  };

  struct Drive {
    std::size_t bytes;
    unsigned char level;
  };

  struct Battery {
    unsigned char level;
    enum class BatteryStatus : unsigned char {
      NO_BATTERY,
      DISCHARGING,
      CHARGING,
      FULL
    } status;
  };

  using Data =
      std::variant<std::monostate, Date, Time, Cpu, Ram, Drive, Battery>;

} // namespace ymwm::data
