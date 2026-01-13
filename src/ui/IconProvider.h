#pragma once

#include "ui/Icons.h"
#include "ui/RaylibIcon.h"

namespace ymwm::ui {
  struct ColorProvider;

  struct IconProvider {
    IconProvider(const ColorProvider& color_provider);

    const RaylibIcon& icon(Icons i) const noexcept;

    ~IconProvider();

  private:
    RaylibIcon m_bat_full;
    RaylibIcon m_bat_normal;
    RaylibIcon m_bat_half;
    RaylibIcon m_bat_low;
    RaylibIcon m_bat_charging;
    RaylibIcon m_cpu;
    RaylibIcon m_cpu_warning;
    RaylibIcon m_cpu_alert;
    RaylibIcon m_ram;
    RaylibIcon m_ram_warning;
    RaylibIcon m_ram_alert;
    RaylibIcon m_drive;
    RaylibIcon m_drive_warning;
    RaylibIcon m_drive_alert;
  };
} // namespace ymwm::ui
