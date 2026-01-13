#pragma once

#include <cstddef>
#include <raylib.h>

namespace ymwm::ui {

  struct RaylibIcon {
    RaylibIcon(const unsigned char* const raw_data,
               std::size_t icon_size,
               Color color);

    inline operator const Texture2D&() const noexcept { return m_texture; }

    RaylibIcon() = delete;
    RaylibIcon(const RaylibIcon&) = delete;
    RaylibIcon& operator=(const RaylibIcon&) = delete;

    ~RaylibIcon();

  private:
    Texture2D m_texture;
  };

} // namespace ymwm::ui
