#include "Renderer.h"

#include "Colors.h"
#include "Icons.h"
#include "ui/RaylibFont.h"

#include <raylib.h>

namespace ymwm::ui {

  Renderer::Renderer()
      : m_icon_provider(m_color_provider) {}

  void Renderer::render_background(Colors color) const noexcept {
    ClearBackground(m_color_provider.color(color));
  }

  void Renderer::render_text(std::string&& txt,
                             const RenderTextOptions& options) const noexcept {
    const RaylibFont& font = m_font_provider.font(options.font_type);
    DrawTextEx(font,
               txt.c_str(),
               { static_cast<float>(options.x), static_cast<float>(options.y) },
               font.size(),
               m_font_provider.spacing(),
               m_color_provider.color(options.color));
  }

  void Renderer::render_icon(Icons icon,
                             const RenderIconOptions& options) const noexcept {
    DrawTextureEx(
        m_icon_provider.icon(icon),
        { static_cast<float>(options.x), static_cast<float>(options.y) },
        0.0,
        icon_scaling_factor() / 100.0f,
        m_color_provider.color(Colors::Regular));
  }

  void Renderer::render_line(const RenderLineOptions& options) const noexcept {
    DrawLineEx(
        { static_cast<float>(options.xs), static_cast<float>(options.ys) },
        { static_cast<float>(options.xe), static_cast<float>(options.ye) },
        options.width,
        m_color_provider.color(options.color));
  }

  int Renderer::rendered_text_width(const std::string& txt,
                                    FontType font_type) const noexcept {
    const RaylibFont& font = m_font_provider.font(font_type);
    auto text_measures = MeasureTextEx(
        font, txt.c_str(), font.size(), m_font_provider.spacing());
    return text_measures.x;
  }

  Renderer::~Renderer() = default;

} // namespace ymwm::ui
