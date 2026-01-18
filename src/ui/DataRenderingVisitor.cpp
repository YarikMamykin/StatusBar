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
    const auto& [x, y] = m_offset;
    m_renderer.render_text(data.c_str(),
                           RenderTextOptions{ .x = x,
                                              .y = y,
                                              .font_type = FontType::Regular,
                                              .color = Colors::Regular });
    m_renderer.render_icon(
        Icons::Cpu,
        RenderIconOptions{
            .x = x + m_icon_offset +
                 m_renderer.rendered_text_width(data, FontType::Regular),
            .y = y,
        });
  }

  void DataRenderingVisitor::operator()(const data::Ram& d) const noexcept {
    std::string data = std::to_string(d.level) + "%";
    const auto& [x, y] = m_offset;
    m_renderer.render_text(data.c_str(),
                           RenderTextOptions{ .x = x,
                                              .y = y,
                                              .font_type = FontType::Regular,
                                              .color = Colors::Regular });
    m_renderer.render_icon(
        Icons::Ram,
        RenderIconOptions{
            .x = x + m_icon_offset +
                 m_renderer.rendered_text_width(data, FontType::Regular),
            .y = y,
        });
  }

  void DataRenderingVisitor::operator()(const data::Drive& d) const noexcept {
    std::string data = std::to_string(d.level) + "%";
    const auto& [x, y] = m_offset;
    m_renderer.render_text(data.c_str(),
                           RenderTextOptions{ .x = x,
                                              .y = y,
                                              .font_type = FontType::Regular,
                                              .color = Colors::Regular });
    m_renderer.render_icon(
        Icons::Drive,
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
    const auto& [x, y] = m_offset;
    m_renderer.render_text(data.c_str(),
                           RenderTextOptions{ .x = x,
                                              .y = y,
                                              .font_type = FontType::Regular,
                                              .color = Colors::Regular });
    m_renderer.render_icon(
        Icons::FullBat,
        RenderIconOptions{
            .x = x + m_icon_offset +
                 m_renderer.rendered_text_width(data, FontType::Regular),
            .y = y,
        });
  }

  void DataRenderingVisitor::operator()(const std::monostate&) const noexcept {}

  DataRenderingVisitor::~DataRenderingVisitor() = default;
} // namespace ymwm::ui
