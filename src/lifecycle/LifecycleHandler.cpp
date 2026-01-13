#include "LifecycleHandler.h"

#include "data/DataProvider.h"
#include "lifecycle/Semaphore.h"
#include "ui/StatusBarWindow.h"

namespace ymwm::lifecycle {
  LifecycleHandler::LifecycleHandler()
      : m_exit_requested{ false } {
    if (not m_semaphor.opened() and not m_semaphor.created()) {
      return;
    }
  }

  int LifecycleHandler::run() noexcept {
    if (not m_semaphor.opened() and not m_semaphor.created()) {
      return 1;
    }

    if (m_semaphor.opened()) {
      return 0;
    }

    m_data_provider.reset(new ymwm::data::DataProvider());
    m_window.reset(new ymwm::ui::StatusBarWindow(*m_data_provider));

    while (not m_exit_requested) {
      if (m_window->closed()) {
        return 0;
      }
      m_window->render();
    }

    return 0;
  }

  void LifecycleHandler::stop() noexcept { m_exit_requested = true; }

  LifecycleHandler::~LifecycleHandler() = default;
} // namespace ymwm::lifecycle
