#include "FontProvider.h"

namespace ymwm::ui {
  FontProvider::FontProvider()
      : m_font_regular("/usr/share/fonts/TTF/RobotoMono-Regular.ttf", 48)
      , m_font_big("/usr/share/fonts/TTF/RobotoMono-Bold.ttf", 48 * 3)
      , m_font_spacing{ 2.0f } {}

  const RaylibFont& FontProvider::font(FontType font_type) const noexcept {
    switch (font_type) {
    case FontType::Regular:
      return m_font_regular;
    case FontType::Big:
      return m_font_big;
    }
  }

  FontProvider::~FontProvider() = default;
} // namespace ymwm::ui
