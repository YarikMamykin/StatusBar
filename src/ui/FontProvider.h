#pragma once
#include "FontType.h"
#include "RaylibFont.h"

namespace ymwm::ui {
  struct FontProvider {
    FontProvider();

    const RaylibFont& font(FontType font_type) const noexcept;

    inline float spacing() const noexcept { return m_font_spacing; }

    ~FontProvider();

  private:
    RaylibFont m_font_regular;
    RaylibFont m_font_big;
    const float m_font_spacing;
  };
} // namespace ymwm::ui
