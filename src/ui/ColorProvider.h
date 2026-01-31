#pragma once
#include "Colors.h"

#include <raylib.h>

namespace ymwm::ui {

  struct ColorProvider {
    ColorProvider();

    const Color& color(Colors c) const noexcept;

    ~ColorProvider();

  private:
    Color m_background;
    Color m_regular;
    Color m_regular_bat;
    Color m_alert;
    Color m_warning;
    Color m_charging;
    Color m_charged;
    Color m_delimiter;
  };
} // namespace ymwm::ui
