#pragma once
#include "Data.h"
#include "DataType.h"

namespace ymwm::data {
  struct DataProvider {
    DataProvider();

    Data provide(DataType dt) const noexcept;

    ~DataProvider();
  };
} // namespace ymwm::data
