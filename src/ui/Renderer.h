#pragma once

#include "Colors.h"
#include "Icons.h"

#include <array>
#include <raylib.h>
#include <string>

namespace ymwm::ui {

  struct RenderTextOptions {
    int x{ 0 };
    int y{ 0 };
    int font_size{ 10 };
    Colors color{ Colors::Regular };
  };

  struct RenderIconOptions {
    int x{ 0 };
    int y{ 0 };
    Colors color{ Colors::Regular };
  };

  struct Renderer {
    Renderer();

    void render_background(Colors color) const noexcept;
    void render_text(std::string&& txt,
                     const RenderTextOptions& options) const noexcept;
    void render_icon(Icons icon,
                     const RenderIconOptions& options) const noexcept;

    int rendered_text_width(const std::string& txt,
                            int font_size) const noexcept;

    inline constexpr int default_font_size() const noexcept { return 32; }

    ~Renderer();

  private:
    inline const Color& raylib_color(Colors color) const noexcept {
      return m_colors.at(static_cast<std::size_t>(color));
    }

    inline const Texture2D& raylib_icon(Icons icon) const noexcept {
      return m_icons.at(static_cast<std::size_t>(icon));
    }

    void load_icons() noexcept;

  private:
    std::array<Color, 6ul> m_colors;
    std::array<Texture2D, 14ul> m_icons;
  };
} // namespace ymwm::ui
