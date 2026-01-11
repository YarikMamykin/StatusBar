#include "RaylibFont.h"

#include <raylib.h>

namespace ymwm::ui {

  RaylibFont::RaylibFont(std::filesystem::path&& font_path, int font_size)
      : m_font(LoadFontEx(font_path.c_str(), font_size, nullptr, 0))
      , m_font_size(font_size) {
    if (not IsFontValid(m_font)) {
      m_font = GetFontDefault();
    }
  }

  RaylibFont::~RaylibFont() { UnloadFont(m_font); }
} // namespace ymwm::ui
