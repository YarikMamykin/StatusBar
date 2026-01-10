#include "DataRenderingVisitor.h"

#include "data/Data.h"
#include "ui/Colors.h"
#include "ui/Icons.h"
#include "ui/Renderer.h"

#include <algorithm>
#include <raylib.h>

namespace ymwm::ui {
  DataRenderingVisitor::DataRenderingVisitor(const Renderer& renderer)
      : m_renderer(renderer)
      , m_offset({ 0, 0 })
      , m_icon_offset(10) {}

  void DataRenderingVisitor::operator()(const data::Time& d) const noexcept {
    const std::string mock_date{ "Fri Jan  2 EET 2026" };
    const std::string mock_time{ "05:26:14 PM" };
    const auto& [x, y] = m_offset;

    m_renderer.render_text(mock_date.c_str(),
                           { .x = x,
                             .y = y,
                             .font_size = m_renderer.default_font_size(),
                             .color = Colors::Regular });
    m_renderer.render_text(mock_time.c_str(),
                           {
                               .x = x,
                               .y = y + m_renderer.default_font_size() + 15,
                               .color = Colors::Regular,
                               .font_type = RenderFontType::Big,
                           });
  }

  void DataRenderingVisitor::operator()(const data::Cpu& d) const noexcept {
    const std::string mock_cpudata{ "75%" };
    const auto& [x, y] = m_offset;
    m_renderer.render_text(mock_cpudata.c_str(),
                           { .x = x,
                             .y = y,
                             .font_size = m_renderer.default_font_size(),
                             .color = Colors::Regular });
    m_renderer.render_icon(Icons::Cpu,
                           {
                               .x = x + m_icon_offset +
                                    m_renderer.rendered_text_width(
                                        mock_cpudata, RenderFontType::Regular),
                               .y = y,
                           });
  }

  void DataRenderingVisitor::operator()(const data::Ram& d) const noexcept {
    const std::string mock_ramdata{ "25%" };
    const auto& [x, y] = m_offset;
    m_renderer.render_text(mock_ramdata.c_str(),
                           { .x = x,
                             .y = y,
                             .font_size = m_renderer.default_font_size(),
                             .color = Colors::Regular });
    m_renderer.render_icon(Icons::Ram,
                           {
                               .x = x + m_icon_offset +
                                    m_renderer.rendered_text_width(
                                        mock_ramdata, RenderFontType::Regular),
                               .y = y,
                           });
  }

  void DataRenderingVisitor::operator()(const data::Drive& d) const noexcept {
    const std::string mock_drivedata{ "34%" };
    const auto& [x, y] = m_offset;
    m_renderer.render_text(mock_drivedata.c_str(),
                           { .x = x,
                             .y = y,
                             .font_size = m_renderer.default_font_size(),
                             .color = Colors::Regular });
    m_renderer.render_icon(
        Icons::Drive,
        {
            .x = x + m_icon_offset +
                 m_renderer.rendered_text_width(mock_drivedata,
                                                RenderFontType::Regular),
            .y = y,
        });
  }

  void DataRenderingVisitor::operator()(const data::Battery& d) const noexcept {
    const std::string mock_batdata{ "34%" };
    const auto& [x, y] = m_offset;
    m_renderer.render_text(mock_batdata.c_str(),
                           { .x = x,
                             .y = y,
                             .font_size = m_renderer.default_font_size(),
                             .color = Colors::Regular });
    m_renderer.render_icon(Icons::FullBat,
                           {
                               .x = x + m_icon_offset +
                                    m_renderer.rendered_text_width(
                                        mock_batdata, RenderFontType::Regular),
                               .y = y,
                           });
  }

  void DataRenderingVisitor::operator()(const std::monostate&) const noexcept {}

  DataRenderingVisitor::~DataRenderingVisitor() = default;
} // namespace ymwm::ui

namespace ymwm::ui {
  RenderMeasuringVisitor::RenderMeasuringVisitor(const Renderer& renderer)
      : m_renderer(renderer)
      , m_icon_offset(10) // must be same as DataRenderingVisitor m_icon_offset
  {}

  std::tuple<int, int>
  RenderMeasuringVisitor::operator()(const data::Time& d) const noexcept {
    const std::string mock_date{ "Fri Jan  2 EET 2026" };
    const std::string mock_time{ "05:26:14 PM" };

    int height = m_renderer.default_font_size() * 3 + 15;
    int width =
        m_renderer.rendered_text_width(mock_time.c_str(), RenderFontType::Big);
    return { width, height };
  }

  std::tuple<int, int>
  RenderMeasuringVisitor::operator()(const data::Cpu& d) const noexcept {
    const std::string mock_cpudata{ "75%" };
    int width = m_renderer.rendered_text_width(mock_cpudata.c_str(),
                                               RenderFontType::Regular);
    width += m_icon_offset;
    int height =
        std::max(m_renderer.icon_size(), m_renderer.default_font_size());
    return { width, height };
  }

  std::tuple<int, int>
  RenderMeasuringVisitor::operator()(const data::Ram& d) const noexcept {
    const std::string mock_ramdata{ "25%" };
    int width = m_renderer.rendered_text_width(mock_ramdata.c_str(),
                                               RenderFontType::Regular);
    width += m_icon_offset;
    int height =
        std::max(m_renderer.icon_size(), m_renderer.default_font_size());
    return { width, height };
  }

  std::tuple<int, int>
  RenderMeasuringVisitor::operator()(const data::Drive& d) const noexcept {
    const std::string mock_drivedata{ "34%" };
    int width = m_renderer.rendered_text_width(mock_drivedata.c_str(),
                                               RenderFontType::Regular);
    width += m_icon_offset;
    int height =
        std::max(m_renderer.icon_size(), m_renderer.default_font_size());
    return { width, height };
  }

  std::tuple<int, int>
  RenderMeasuringVisitor::operator()(const data::Battery& d) const noexcept {
    const std::string mock_batdata{ "34%" };
    int width = m_renderer.rendered_text_width(mock_batdata.c_str(),
                                               RenderFontType::Regular);
    width += m_icon_offset;
    int height =
        std::max(m_renderer.icon_size(), m_renderer.default_font_size());
    return { width, height };
  }

  std::tuple<int, int>
  RenderMeasuringVisitor::operator()(const std::monostate&) const noexcept {
    return { 0, 0 };
  }

  RenderMeasuringVisitor::~RenderMeasuringVisitor() = default;
} // namespace ymwm::ui
