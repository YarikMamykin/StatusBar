#include "Renderer.h"

#include "Colors.h"
#include "Icons.h"

#include <algorithm>

namespace ymwm::ui::prv {
  inline constexpr std::tuple<unsigned char*, std::size_t>
  icon_raw_data(Icons icon) noexcept {
    switch (icon) {
    case Icons::FullBat:
      return { full_battery.data(), full_battery.size() };
    case Icons::NormalBat:
      return { battery.data(), battery.size() };
    case Icons::HalfBat:
      return { half_battery.data(), half_battery.size() };
    case Icons::LowBat:
      return { low_battery.data(), low_battery.size() };
    case Icons::ChargingBat:
      return { charging_battery.data(), charging_battery.size() };
    case Icons::Cpu:
      return { cpu.data(), cpu.size() };
    case Icons::Ram:
      return { ram.data(), ram.size() };
    case Icons::Drive:
      return { drive.data(), drive.size() };
    }

    return { nullptr, 0ul };
  }
} // namespace ymwm::ui::prv

namespace ymwm::ui {

  Renderer::Renderer() {
    m_colors.at(static_cast<std::size_t>(Colors::Regular)) =
        Color{ 20, 30, 48, 255 };
    m_colors.at(static_cast<std::size_t>(Colors::Text)) =
        Color{ 200, 0, 0, 255 };
    m_colors.at(static_cast<std::size_t>(Colors::Alert)) =
        Color{ 20, 30, 48, 255 };
    m_colors.at(static_cast<std::size_t>(Colors::Warning)) =
        Color{ 255, 255, 255, 255 };
    m_colors.at(static_cast<std::size_t>(Colors::Charging)) =
        Color{ 0x0c, 0x0c, 0x0c, 255 };
    m_colors.at(static_cast<std::size_t>(Colors::Background)) =
        Color{ 0x0c, 0x0c, 0x0c, 255 };

    load_icons();
  }

  void Renderer::render_background(Colors color) {
    ClearBackground(raylib_color(color));
  }

  void Renderer::render_text(std::string&& txt,
                             const RenderTextOptions& options) {
    DrawText(txt.c_str(),
             options.x,
             options.y,
             options.font_size,
             raylib_color(options.color));
  }

  void Renderer::render_icon(Icons icon, const RenderIconOptions& options) {
    DrawTexture(
        raylib_icon(icon), options.x, options.y, raylib_color(options.color));
  }

  int Renderer::rendered_text_width(const std::string& txt, int font_size) {
    return MeasureText(txt.c_str(), font_size);
  }

  Renderer::~Renderer() {
    std::for_each(m_icons.begin(), m_icons.end(), [](const Texture2D& texture) {
      UnloadTexture(texture);
    });
  }

  void Renderer::load_icons() noexcept {
    for (auto icon : { Icons::FullBat,
                       Icons::NormalBat,
                       Icons::HalfBat,
                       Icons::LowBat,
                       Icons::ChargingBat,
                       Icons::Cpu,
                       Icons::Ram,
                       Icons::Drive }) {
      auto [icon_data, icon_size] = prv::icon_raw_data(icon);
      const std::array<const char, 5ul> file_type{ ".png" };

      Image img = LoadImageFromMemory(file_type.data(), icon_data, icon_size);
      m_icons.at(static_cast<std::size_t>(icon)) = LoadTextureFromImage(img);
      UnloadImage(img);
    }
  }

} // namespace ymwm::ui
