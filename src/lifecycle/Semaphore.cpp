#include "Semaphore.h"

#include <cerrno>
#include <fcntl.h>
#include <semaphore.h>

namespace ymwm::lifecycle {
  Semaphore::Semaphore()
      : m_name{ "/ymwm-sb-semaphore" }
      , m_created{ false }
      , m_opened{ false }
      , m_semaphore{ nullptr } {

    m_semaphore = sem_open(m_name.data(), O_CREAT | O_EXCL, 0666, 0);

    if (errno == EEXIST) {
      m_opened = true;
      m_created = false;
      return;
    }

    if (m_semaphore != SEM_FAILED) {
      m_created = true;
    }
  }

  void Semaphore::post() noexcept {
    m_semaphore = sem_open(m_name.data(), 0);
    if (m_semaphore != SEM_FAILED) {
      sem_post(m_semaphore);
      sem_close(m_semaphore);
    }
  }

  bool Semaphore::created() const noexcept { return m_created; }

  bool Semaphore::opened() const noexcept { return m_opened; }

  Semaphore::~Semaphore() {
    if (m_opened and not m_created) {
      // don't destroy if not the first instance.
      return;
    }

    sem_unlink(m_name.data());
  }

} // namespace ymwm::lifecycle
