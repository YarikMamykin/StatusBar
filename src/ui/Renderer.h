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

    void render_background(Colors color);
    void render_text(std::string&& txt, const RenderTextOptions& options);
    void render_icon(Icons icon, const RenderIconOptions& options);

    int rendered_text_width(const std::string& txt, int font_size);

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
    std::array<Texture2D, 8ul> m_icons;
  };
} // namespace ymwm::ui
