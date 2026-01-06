#include "LifecycleHandler.h"

#include "data/DataProvider.h"
#include "ui/StatusBarWindow.h"

namespace ymwm::lifecycle {
  LifecycleHandler::LifecycleHandler()
      : m_exit_requested{ false } {
    if (not m_semaphor.opened() and not m_semaphor.created()) {
      return;
    }

    m_data_provider.reset(new ymwm::data::DataProvider());
    m_window.reset(new ymwm::ui::StatusBarWindow());
  }

  int LifecycleHandler::run() noexcept {
    if (not m_semaphor.opened() and not m_semaphor.created()) {
      return 1;
    }

    if (m_semaphor.opened()) {
      m_semaphor.post();
      return 0;
    }

    while (not m_exit_requested) {
      m_semaphor.wait();
    }

    return 0;
  }

  void LifecycleHandler::stop() noexcept {
    m_exit_requested = true;
    m_semaphor.post();
  }

  LifecycleHandler::~LifecycleHandler() = default;
} // namespace ymwm::lifecycle
