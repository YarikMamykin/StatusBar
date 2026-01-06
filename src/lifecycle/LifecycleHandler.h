#pragma once
#include "Semaphore.h"

#include <memory>

namespace ymwm::data {
  struct DataProvider;
}
namespace ymwm::ui {
  struct StatusBarWindow;
}

namespace ymwm::lifecycle {
  struct Semaphore;

  struct LifecycleHandler {

    LifecycleHandler();

    int run() noexcept;
    void stop() noexcept;

    ~LifecycleHandler();

  private:
    // Pointers for delayed initialization
    Semaphore m_semaphor;
    std::unique_ptr<ymwm::data::DataProvider> m_data_provider;
    std::unique_ptr<ymwm::ui::StatusBarWindow> m_window;
    bool m_exit_requested;
  };
} // namespace ymwm::lifecycle
