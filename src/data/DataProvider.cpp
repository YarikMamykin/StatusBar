#include "DataProvider.h"

#include "Data.h"
#include "DataType.h"

#include <iostream>
#include <string_view>
#include <sys/statfs.h>
#include <thread>

namespace ymwm::data::prv {
  inline constinit double mb{ 1024 * 1024 };
  inline constinit std::string_view cpuinfo_filepath{ "/proc/stat" };
  inline constinit std::string_view raminfo_filepath{ "/proc/meminfo" };
  inline constinit std::string_view batcap_filepath{
    "/sys/class/power_supply/BAT0/capacity"
  };
  inline constinit std::string_view batstatus_filepath{
    "/sys/class/power_supply/BAT0/status"
  };
} // namespace ymwm::data::prv

namespace ymwm::data {
  Date DataProvider::DateProvider::provide() const noexcept {
    return Date{
      .data = std::chrono::zoned_time{ std::chrono::current_zone(),
                                      std::chrono::floor<std::chrono::seconds>(
                                           std::chrono::system_clock::now()) }
    };
  }
} // namespace ymwm::data

namespace ymwm::data {
  Time DataProvider::TimeProvider::provide() const noexcept {
    return Time{
      .data = std::chrono::zoned_time{ std::chrono::current_zone(),
                                      std::chrono::floor<std::chrono::seconds>(
                                           std::chrono::system_clock::now()) }
    };
  }
} // namespace ymwm::data

namespace ymwm::data {
  DataProvider::CpuProvider::CpuProvider()
      /*
       * First goes average value for all cpus.
       * Thus we need number_of_cpus + 1 records.
       */
      : m_stats(std::thread::hardware_concurrency() + 1ul)
      , m_levels(std::thread::hardware_concurrency() + 1ul)
      , m_filestream(prv::cpuinfo_filepath.data()) {
    if (not m_filestream.is_open()) {
      std::cerr << "Failed to open " << prv::cpuinfo_filepath.data() << "\n";
      return;
    }
  }

  Cpu DataProvider::CpuProvider::provide() const noexcept {

    if (not m_filestream.is_open()) {
      std::cerr << "Failed to open " << prv::cpuinfo_filepath.data() << "\n";
      return Cpu{ .cores_load_lvl = {}, .load_lvl = 0 };
    }

    m_filestream.clear();
    m_filestream.seekg(0, std::ios::beg);

    for (std::size_t core = 0ul; core < m_stats.size(); ++core) {
      m_filestream >> m_ignore >> m_stats.at(core).curr.a >>
          m_stats.at(core).curr.b >> m_stats.at(core).curr.c >>
          m_stats.at(core).curr.idle >> m_ignore >> m_ignore >> m_ignore >>
          m_ignore >> m_ignore >> m_ignore;

      const auto& [curr_a, curr_b, curr_c, curr_idle] = m_stats.at(core).curr;
      const auto& [prev_a, prev_b, prev_c, prev_idle] = m_stats.at(core).prev;

      auto total_curr = curr_a + curr_b + curr_c + curr_idle;
      auto total_prev = prev_a + prev_b + prev_c + prev_idle;
      m_levels.at(core) =
          (total_curr - total_prev > 0)
              ? (100u * (total_curr - total_prev - curr_idle + prev_idle) /
                 (total_curr - total_prev))
              : 0;
      m_stats.at(core).prev = m_stats.at(core).curr;
    }
    return Cpu{ .cores_load_lvl = m_levels };
  }
} // namespace ymwm::data

namespace ymwm::data {
  DataProvider::RamProvider::RamProvider()
      : m_filestream(prv::raminfo_filepath.data()) {
    if (not m_filestream.is_open()) {
      std::cerr << "Failed to open " << prv::raminfo_filepath.data() << "\n";
    }
  }

  Ram DataProvider::RamProvider::provide() const noexcept {
    if (not m_filestream.is_open()) {
      return Ram{};
    }

    m_filestream.clear();
    m_filestream.seekg(0, std::ios::beg);

    unsigned long total_memory, available_memory;
    std::string _;
    m_filestream >> _ >> total_memory >> _ >> _ >> _ >> _ >> _ >>
        available_memory;

    unsigned long used_memory = total_memory - available_memory;

    return Ram{ .megabytes = static_cast<unsigned int>(used_memory / 1024ul),
                .level = static_cast<unsigned char>(100u * used_memory /
                                                    total_memory) };
  }
} // namespace ymwm::data

namespace ymwm::data {
  Drive DataProvider::DriveProvider::provide() const noexcept {
    struct statfs stat;

    if (statfs("/", &stat) != 0) {
      return Drive{ .bytes = 0, .level = 0 };
    }

    unsigned long long free_space = stat.f_bsize * stat.f_bavail;
    unsigned long long total_space = stat.f_bsize * stat.f_blocks;
    double free_space_mb = free_space / prv::mb;
    double total_space_mb = total_space / prv::mb;

    return Drive{ .bytes = free_space,
                  .level = static_cast<unsigned char>(
                      (total_space_mb - free_space_mb) / total_space_mb *
                      100) };
  }
} // namespace ymwm::data

namespace ymwm::data {
  DataProvider::BatteryProvider::BatteryProvider()
      : m_capacity_filestream(prv::batcap_filepath.data())
      , m_status_filestream(prv::batstatus_filepath.data()) {
    if (not m_capacity_filestream.is_open()) {
      std::cerr << "Failed to open " << prv::batcap_filepath.data() << "\n";
    }
    if (not m_status_filestream.is_open()) {
      std::cerr << "Failed to open " << prv::batstatus_filepath.data() << "\n";
    }
  }

  Battery DataProvider::BatteryProvider::provide() const noexcept {
    if (not m_capacity_filestream.is_open() or
        not m_status_filestream.is_open()) {
      return Battery{ 0, Battery::BatteryStatus::NO_BATTERY };
    }

    m_capacity_filestream.clear();
    m_capacity_filestream.seekg(0, std::ios::beg);
    m_status_filestream.clear();
    m_status_filestream.seekg(0, std::ios::beg);

    std::string battery_level_raw;
    m_capacity_filestream >> battery_level_raw;
    unsigned char battery_level = std::stoi(battery_level_raw);

    std::string battery_status_raw;
    m_status_filestream >> battery_status_raw;
    auto battery_status = battery_status_raw == "Discharging"
                              ? Battery::BatteryStatus::DISCHARGING
                          : battery_status_raw == "Charging"
                              ? Battery::BatteryStatus::CHARGING
                              : Battery::BatteryStatus::FULL;
    return Battery{ .level = battery_level, .status = battery_status };
  }
} // namespace ymwm::data

namespace ymwm::data {
  DataProvider::DataProvider() = default;

  Data DataProvider::provide(DataType dt) const noexcept {
    switch (dt) {
    case data::DataType::Battery:
      return m_battery_provider.provide();
    case data::DataType::Cpu:
      return m_cpu_provider.provide();
    case data::DataType::Ram:
      return m_ram_provider.provide();
    case data::DataType::Date:
      return m_date_provider.provide();
    case data::DataType::Time:
      return m_time_provider.provide();
    case data::DataType::Drive:
      return m_drive_provider.provide();
    }
    return {};
  }

  DataProvider::~DataProvider() = default;
} // namespace ymwm::data
