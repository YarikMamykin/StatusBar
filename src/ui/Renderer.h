#pragma once

#include "Colors.h"
#include "Icons.h"

#include <array>
#include <raylib.h>
#include <string>

namespace ymwm::ui {

  enum class RenderFontType { Regular, Big };

  struct RenderTextOptions {
    int x{ 0 };
    int y{ 0 };
    int font_size{ 10 };
    Colors color{ Colors::Regular };
    RenderFontType font_type{ RenderFontType::Regular };
  };

  struct RenderIconOptions {
    int x{ 0 };
    int y{ 0 };
  };

  struct RenderLineOptions {
    int xs{ 0 };
    int ys{ 0 };
    int xe{ 0 };
    int ye{ 0 };
    int width{ 0 };
    Colors color{ Colors::Regular };
  };

  struct Renderer {
    Renderer();

    void render_background(Colors color) const noexcept;
    void render_text(std::string&& txt,
                     const RenderTextOptions& options) const noexcept;
    void render_icon(Icons icon,
                     const RenderIconOptions& options) const noexcept;
    void render_line(const RenderLineOptions& options) const noexcept;

    int rendered_text_width(const std::string& txt,
                            RenderFontType font_type) const noexcept;

    inline constexpr int default_font_size() const noexcept { return 48; }

    inline constexpr int icon_size() const noexcept {
      // Size of icon calculated by original size (64)  * scaling factor (0.75)
      return 64 * icon_scaling_factor() / 100;
    }

    ~Renderer();

  private:
    inline const Color& raylib_color(Colors color) const noexcept {
      return m_colors.at(static_cast<std::size_t>(color));
    }

    inline const Texture2D& raylib_icon(Icons icon) const noexcept {
      return m_icons.at(static_cast<std::size_t>(icon));
    }

    inline constexpr int icon_scaling_factor() const noexcept { return 75; }

    void load_icons() noexcept;

  private:
    std::array<Color, 7ul> m_colors;
    std::array<Texture2D, 14ul> m_icons;
    Font m_font_regular;
    Font m_font_bold;
    const float m_font_spacing;
  };
} // namespace ymwm::ui
