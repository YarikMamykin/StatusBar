#include "ColorProvider.h"

namespace ymwm::ui {
  ColorProvider::ColorProvider()
      : m_background{ 0x0c, 0x0c, 0x0c, 255 }
      , m_regular{ 200, 200, 200, 255 }
      , m_alert{ 200, 0, 0, 255 }
      , m_warning{ 0, 200, 200, 255 }
      , m_charging{ 255, 0, 255, 255 }
      , m_charged{ 255, 255, 255, 255 }
      , m_delimiter{ 0, 0, 255, 255 } {}

  const Color& ColorProvider::color(Colors c) const noexcept {
    switch (c) {
    case Colors::Background:
      return m_background;
    case Colors::Regular:
      return m_regular;
    case Colors::Alert:
      return m_alert;
    case Colors::Warning:
      return m_warning;
    case Colors::Charging:
      return m_charging;
    case Colors::Charged:
      return m_charged;
    case Colors::Delimiter:
      return m_delimiter;
    }
  }

  ColorProvider::~ColorProvider() = default;
} // namespace ymwm::ui
