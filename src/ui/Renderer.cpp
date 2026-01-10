#include "Renderer.h"

#include "Colors.h"
#include "Icons.h"

#include <algorithm>
#include <raylib.h>

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
    case Icons::WarningCpu:
    case Icons::AlertCpu:
      return { cpu.data(), cpu.size() };
    case Icons::Ram:
    case Icons::WarningRam:
    case Icons::AlertRam:
      return { ram.data(), ram.size() };
    case Icons::Drive:
    case Icons::WarningDrive:
    case Icons::AlertDrive:
      return { drive.data(), drive.size() };
    }

    return { nullptr, 0ul };
  }
} // namespace ymwm::ui::prv

namespace ymwm::ui {

  Renderer::Renderer()
      : m_font_spacing{ 2.0f } {
    m_colors.at(static_cast<std::size_t>(Colors::Background)) =
        Color{ 0x0c, 0x0c, 0x0c, 255 };
    m_colors.at(static_cast<std::size_t>(Colors::Regular)) =
        Color{ 200, 200, 200, 255 };
    m_colors.at(static_cast<std::size_t>(Colors::Alert)) =
        Color{ 200, 0, 0, 255 };
    m_colors.at(static_cast<std::size_t>(Colors::Warning)) =
        Color{ 0, 200, 200, 255 };
    m_colors.at(static_cast<std::size_t>(Colors::Charging)) =
        Color{ 255, 0, 255, 255 };
    m_colors.at(static_cast<std::size_t>(Colors::Charged)) =
        Color{ 255, 255, 255, 255 };
    m_colors.at(static_cast<std::size_t>(Colors::Delimiter)) =
        Color{ 0, 0, 255, 255 };

    load_icons();
    m_font_regular = LoadFontEx("/usr/share/fonts/TTF/RobotoMono-Regular.ttf",
                                default_font_size(),
                                nullptr,
                                0);

    m_font_bold =
        LoadFontEx("/usr/share/fonts/TTF/RobotoMono-Bold.ttf", 150, nullptr, 0);
  }

  void Renderer::render_background(Colors color) const noexcept {
    ClearBackground(raylib_color(color));
  }

  void Renderer::render_text(std::string&& txt,
                             const RenderTextOptions& options) const noexcept {
    DrawTextEx(options.font_type == RenderFontType::Regular ? m_font_regular
                                                            : m_font_bold,
               txt.c_str(),
               { static_cast<float>(options.x), static_cast<float>(options.y) },
               options.font_type == RenderFontType::Regular
                   ? default_font_size()
                   : 150,
               m_font_spacing,
               raylib_color(options.color));
  }

  void Renderer::render_icon(Icons icon,
                             const RenderIconOptions& options) const noexcept {
    DrawTextureEx(
        raylib_icon(icon),
        { static_cast<float>(options.x), static_cast<float>(options.y) },
        0.0,
        icon_scaling_factor() / 100.0f,
        raylib_color(Colors::Regular));
  }

  void Renderer::render_line(const RenderLineOptions& options) const noexcept {
    DrawLineEx(
        { static_cast<float>(options.xs), static_cast<float>(options.ys) },
        { static_cast<float>(options.xe), static_cast<float>(options.ye) },
        options.width,
        raylib_color(options.color));
  }

  int Renderer::rendered_text_width(const std::string& txt,
                                    RenderFontType font_type) const noexcept {
    return MeasureTextEx(
               font_type == RenderFontType::Regular ? m_font_regular
                                                    : m_font_bold,
               txt.c_str(),
               font_type == RenderFontType::Regular ? default_font_size() : 150,
               m_font_spacing)
        .x;
  }

  Renderer::~Renderer() {
    std::for_each(m_icons.begin(), m_icons.end(), [](const Texture2D& texture) {
      UnloadTexture(texture);
    });
    UnloadFont(m_font_regular);
    UnloadFont(m_font_bold);
  }

  void Renderer::load_icons() noexcept {
    static constinit std::string_view file_type{ ".png" };

    auto texture_from_raw_data = [](Color color,
                                    unsigned char* const icon_data,
                                    std::size_t icon_size) -> Texture2D {
      Image img = LoadImageFromMemory(file_type.data(), icon_data, icon_size);
      ImageColorReplace(&img, BLACK, color);
      Texture2D texture = LoadTextureFromImage(img);
      UnloadImage(img);
      return texture;
    };

    {
      auto [icon_data, icon_size] = prv::icon_raw_data(Icons::FullBat);

      m_icons.at(static_cast<std::size_t>(Icons::FullBat)) =
          texture_from_raw_data(
              raylib_color(Colors::Charged), icon_data, icon_size);
    }
    {
      auto [icon_data, icon_size] = prv::icon_raw_data(Icons::NormalBat);

      m_icons.at(static_cast<std::size_t>(Icons::NormalBat)) =
          texture_from_raw_data(
              raylib_color(Colors::Regular), icon_data, icon_size);
    }
    {
      auto [icon_data, icon_size] = prv::icon_raw_data(Icons::HalfBat);

      m_icons.at(static_cast<std::size_t>(Icons::HalfBat)) =
          texture_from_raw_data(
              raylib_color(Colors::Warning), icon_data, icon_size);
    }
    {
      auto [icon_data, icon_size] = prv::icon_raw_data(Icons::LowBat);

      m_icons.at(static_cast<std::size_t>(Icons::LowBat)) =
          texture_from_raw_data(
              raylib_color(Colors::Alert), icon_data, icon_size);
    }
    {
      auto [icon_data, icon_size] = prv::icon_raw_data(Icons::ChargingBat);

      m_icons.at(static_cast<std::size_t>(Icons::ChargingBat)) =
          texture_from_raw_data(
              raylib_color(Colors::Charging), icon_data, icon_size);
    }
    {
      auto [icon_data, icon_size] = prv::icon_raw_data(Icons::Cpu);

      m_icons.at(static_cast<std::size_t>(Icons::Cpu)) = texture_from_raw_data(
          raylib_color(Colors::Regular), icon_data, icon_size);
    }
    {
      auto [icon_data, icon_size] = prv::icon_raw_data(Icons::WarningCpu);

      m_icons.at(static_cast<std::size_t>(Icons::WarningCpu)) =
          texture_from_raw_data(
              raylib_color(Colors::Warning), icon_data, icon_size);
    }
    {
      auto [icon_data, icon_size] = prv::icon_raw_data(Icons::AlertCpu);

      m_icons.at(static_cast<std::size_t>(Icons::AlertCpu)) =
          texture_from_raw_data(
              raylib_color(Colors::Alert), icon_data, icon_size);
    }
    {
      auto [icon_data, icon_size] = prv::icon_raw_data(Icons::Ram);

      m_icons.at(static_cast<std::size_t>(Icons::Ram)) = texture_from_raw_data(
          raylib_color(Colors::Regular), icon_data, icon_size);
    }
    {
      auto [icon_data, icon_size] = prv::icon_raw_data(Icons::WarningRam);

      m_icons.at(static_cast<std::size_t>(Icons::WarningRam)) =
          texture_from_raw_data(
              raylib_color(Colors::Warning), icon_data, icon_size);
    }
    {
      auto [icon_data, icon_size] = prv::icon_raw_data(Icons::AlertRam);

      m_icons.at(static_cast<std::size_t>(Icons::AlertRam)) =
          texture_from_raw_data(
              raylib_color(Colors::Alert), icon_data, icon_size);
    }
    {
      auto [icon_data, icon_size] = prv::icon_raw_data(Icons::Drive);

      m_icons.at(static_cast<std::size_t>(Icons::Drive)) =
          texture_from_raw_data(
              raylib_color(Colors::Regular), icon_data, icon_size);
    }
    {
      auto [icon_data, icon_size] = prv::icon_raw_data(Icons::WarningDrive);

      m_icons.at(static_cast<std::size_t>(Icons::WarningDrive)) =
          texture_from_raw_data(
              raylib_color(Colors::Warning), icon_data, icon_size);
    }
    {
      auto [icon_data, icon_size] = prv::icon_raw_data(Icons::AlertDrive);

      m_icons.at(static_cast<std::size_t>(Icons::AlertDrive)) =
          texture_from_raw_data(
              raylib_color(Colors::Alert), icon_data, icon_size);
    }
  }

} // namespace ymwm::ui
