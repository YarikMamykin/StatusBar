#include "DataRenderingVisitor.h"

#include "Colors.h"
#include "Icons.h"
#include "RenderIconOptions.h"
#include "RenderTextOptions.h"
#include "Renderer.h"
#include "data/Data.h"

#include <raylib.h>

namespace ymwm::ui {
  DataRenderingVisitor::DataRenderingVisitor(const Renderer& renderer)
      : m_renderer(renderer)
      , m_offset({ 0, 0 })
      , m_icon_offset(10) {}

  void DataRenderingVisitor::operator()(const data::Date& d) const noexcept {
    std::string date = std::format("{:%a %b %e %Z %Y}", d.data);
    const auto& [x, y] = m_offset;

    m_renderer.render_text(date.c_str(),
                           RenderTextOptions{ .x = x,
                                              .y = y,
                                              .font_type = FontType::Regular,
                                              .color = Colors::Regular });
  }

  void DataRenderingVisitor::operator()(const data::Time& d) const noexcept {
    std::string time = std::format("{:%H:%M:%OS %p}", d.data);
    const auto& [x, y] = m_offset;

    m_renderer.render_text(time.c_str(),
                           RenderTextOptions{
                               .x = x,
                               .y = y + 15,
                               .font_type = FontType::Big,
                               .color = Colors::Regular,
                           });
  }

  void DataRenderingVisitor::operator()(const data::Cpu& d) const noexcept {
    std::string data =
        std::to_string(static_cast<unsigned int>(*d.cores_load_lvl.begin())) +
        "%";

    // should be configured externally
    bool warning = *d.cores_load_lvl.begin() >= 70;
    bool critical = *d.cores_load_lvl.begin() >= 90;

    const auto& [x, y] = m_offset;
    m_renderer.render_text(data.c_str(),
                           RenderTextOptions{ .x = x,
                                              .y = y,
                                              .font_type = FontType::Regular,
                                              .color = Colors::Regular });
    Icons icon{ Icons::Cpu };
    if (warning) {
      icon = Icons::WarningCpu;
    }
    if (critical) {
      icon = Icons::AlertCpu;
    }
    m_renderer.render_icon(
        icon,
        RenderIconOptions{
            .x = x + m_icon_offset +
                 m_renderer.rendered_text_width(data, FontType::Regular),
            .y = y,
        });
  }

  void DataRenderingVisitor::operator()(const data::Ram& d) const noexcept {
    std::string data = std::to_string(d.level) + "%";

    // should be configured externally
    bool warning = d.level >= 70;
    bool critical = d.level >= 90;

    const auto& [x, y] = m_offset;
    m_renderer.render_text(data.c_str(),
                           RenderTextOptions{ .x = x,
                                              .y = y,
                                              .font_type = FontType::Regular,
                                              .color = Colors::Regular });
    Icons icon{ Icons::Ram };
    if (warning) {
      icon = Icons::WarningRam;
    }
    if (critical) {
      icon = Icons::AlertRam;
    }
    m_renderer.render_icon(
        icon,
        RenderIconOptions{
            .x = x + m_icon_offset +
                 m_renderer.rendered_text_width(data, FontType::Regular),
            .y = y,
        });
  }

  void DataRenderingVisitor::operator()(const data::Drive& d) const noexcept {
    std::string data = std::to_string(d.level) + "%";

    // should be configured externally
    bool warning = d.level >= 70;
    bool critical = d.level >= 90;

    const auto& [x, y] = m_offset;
    m_renderer.render_text(data.c_str(),
                           RenderTextOptions{ .x = x,
                                              .y = y,
                                              .font_type = FontType::Regular,
                                              .color = Colors::Regular });
    Icons icon{ Icons::Drive };
    if (warning) {
      icon = Icons::WarningDrive;
    }
    if (critical) {
      icon = Icons::AlertDrive;
    }
    m_renderer.render_icon(
        icon,
        RenderIconOptions{
            .x = x + m_icon_offset +
                 m_renderer.rendered_text_width(data, FontType::Regular),
            .y = y,
        });
  }

  void DataRenderingVisitor::operator()(const data::Battery& d) const noexcept {
    if (d.status == data::Battery::BatteryStatus::NO_BATTERY) {
      return;
    }

    std::string data = std::to_string(d.level) + "%";

    bool normal = d.level < 100;
    bool half = d.level < 55;
    bool low = d.level < 25;
    bool charging = d.status == data::Battery::BatteryStatus::CHARGING;
    bool full = d.status == data::Battery::BatteryStatus::FULL;

    Colors color{ Colors::RegularBat };
    if (full) {
      color = Colors::Charged;
    }
    if (charging) {
      color = Colors::Charging;
    }
    if (low) {
      color = Colors::Alert;
    }

    const auto& [x, y] = m_offset;
    m_renderer.render_text(
        data.c_str(),
        RenderTextOptions{
            .x = x, .y = y, .font_type = FontType::Regular, .color = color });

    Icons icon{ Icons::NormalBat };
    if (charging) {
      icon = Icons::ChargingBat;
    } else if (full) {
      icon = Icons::FullBat;
    } else {
      if (half) {
        icon = Icons::HalfBat;
      }
      if (low) {
        icon = Icons::LowBat;
      }
    }
    m_renderer.render_icon(
        icon,
        RenderIconOptions{
            .x = x + m_icon_offset +
                 m_renderer.rendered_text_width(data, FontType::Regular),
            .y = y,
        });
  }

  void DataRenderingVisitor::operator()(const std::monostate&) const noexcept {}

  DataRenderingVisitor::~DataRenderingVisitor() = default;
} // namespace ymwm::ui
