#pragma once

#include "ColorProvider.h"
#include "Colors.h"
#include "FontProvider.h"
#include "FontType.h"
#include "IconProvider.h"

#include <raylib.h>
#include <string>

namespace ymwm::ui {

  struct RenderTextOptions {
    int x{ 0 };
    int y{ 0 };
    FontType font_type{ FontType::Regular };
    Colors color{ Colors::Regular };
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
                            FontType font_type) const noexcept;

    inline constexpr int icon_size() const noexcept {
      // Size of icon calculated by original size (64) * scaling factor (0.75)
      return 64 * icon_scaling_factor() / 100;
    }

    ~Renderer();

  private:
    inline constexpr int icon_scaling_factor() const noexcept { return 75; }

  private:
    ColorProvider m_color_provider;
    IconProvider m_icon_provider;
    FontProvider m_font_provider;
  };
} // namespace ymwm::ui
