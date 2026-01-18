#pragma once
#include "Data.h"
#include "DataType.h"

#include <fstream>

namespace ymwm::data {
  struct DataProvider {
    DataProvider();

    Data provide(DataType dt) const noexcept;

    ~DataProvider();

  private:
    struct DateProvider {
      Date provide() const noexcept;
    } mutable m_date_provider;

    struct TimeProvider {
      Time provide() const noexcept;
    } mutable m_time_provider;

    struct CpuProvider {
      CpuProvider();
      Cpu provide() const noexcept;

    private:
      struct CoreData {
        long a{ 0l };
        long b{ 0l };
        long c{ 0l };
        long idle{ 0l };
      };
      struct CoreDataDiff {
        CoreData curr;
        CoreData prev;
      };
      mutable std::vector<CoreDataDiff> m_stats;
      mutable std::vector<unsigned char> m_levels;
      mutable std::ifstream m_filestream;
      mutable std::string m_ignore;

    } mutable m_cpu_provider;

    struct RamProvider {
      RamProvider();
      Ram provide() const noexcept;

    private:
      mutable std::ifstream m_filestream;
    } mutable m_ram_provider;

    struct DriveProvider {
      Drive provide() const noexcept;
    } m_drive_provider;

    struct BatteryProvider {
      BatteryProvider();
      Battery provide() const noexcept;

    private:
      mutable std::ifstream m_capacity_filestream;
      mutable std::ifstream m_status_filestream;
    } mutable m_battery_provider;
  };
} // namespace ymwm::data
