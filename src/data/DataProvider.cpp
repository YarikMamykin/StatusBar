#include "DataProvider.h"

#include "Data.h"
#include "DataType.h"

namespace ymwm::data {
  DataProvider::DataProvider() = default;

  Data DataProvider::provide(DataType dt) const noexcept {
    switch (dt) {
    case data::DataType::Battery:
      return Battery{};
    case data::DataType::Cpu:
      return Cpu{};
    case data::DataType::Ram:
      return Ram{};
    case data::DataType::Time:
      return Time{};
    case data::DataType::Drive:
      return Drive{};
    }
    return {};
  }

  DataProvider::~DataProvider() = default;
} // namespace ymwm::data
