#pragma once
#include <array>
#include <semaphore.h>

namespace ymwm::lifecycle {

  enum class SemaphoreLockedStatus { Locked, Free };

  struct Semaphore {
    Semaphore();
    ~Semaphore();

    void post() noexcept;
    SemaphoreLockedStatus locked() noexcept;

    bool created() const noexcept;
    bool opened() const noexcept;

  private:
    const std::array<const char, 19ul> m_name;
    bool m_created;
    bool m_opened;
    sem_t* m_semaphore;
  };
} // namespace ymwm::lifecycle
