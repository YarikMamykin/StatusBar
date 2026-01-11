#pragma once

#include <filesystem>
#include <raylib.h>

namespace ymwm::ui {

  struct RaylibFont {
    RaylibFont(std::filesystem::path&& font_path, int font_size);

    inline const Font& handler() const noexcept { return m_font; }
    inline int size() const noexcept { return m_font_size; }

    ~RaylibFont();

  private:
    Font m_font;
    const int m_font_size;
  };

} // namespace ymwm::ui
