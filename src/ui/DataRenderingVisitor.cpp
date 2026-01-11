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
    const std::string mock_date{ "Fri Jan  2 EET 2026" };
    const auto& [x, y] = m_offset;

    m_renderer.render_text(mock_date.c_str(),
                           RenderTextOptions{ .x = x,
                                              .y = y,
                                              .font_type = FontType::Regular,
                                              .color = Colors::Regular });
  }

  void DataRenderingVisitor::operator()(const data::Time& d) const noexcept {
    const std::string mock_time{ "05:26:14 PM" };
    const auto& [x, y] = m_offset;

    m_renderer.render_text(mock_time.c_str(),
                           RenderTextOptions{
                               .x = x,
                               .y = y + 15,
                               .font_type = FontType::Big,
                               .color = Colors::Regular,
                           });
  }

  void DataRenderingVisitor::operator()(const data::Cpu& d) const noexcept {
    const std::string mock_cpudata{ "75%" };
    const auto& [x, y] = m_offset;
    m_renderer.render_text(mock_cpudata.c_str(),
                           RenderTextOptions{ .x = x,
                                              .y = y,
                                              .font_type = FontType::Regular,
                                              .color = Colors::Regular });
    m_renderer.render_icon(Icons::Cpu,
                           RenderIconOptions{
                               .x = x + m_icon_offset +
                                    m_renderer.rendered_text_width(
                                        mock_cpudata, FontType::Regular),
                               .y = y,
                           });
  }

  void DataRenderingVisitor::operator()(const data::Ram& d) const noexcept {
    const std::string mock_ramdata{ "25%" };
    const auto& [x, y] = m_offset;
    m_renderer.render_text(mock_ramdata.c_str(),
                           RenderTextOptions{ .x = x,
                                              .y = y,
                                              .font_type = FontType::Regular,
                                              .color = Colors::Regular });
    m_renderer.render_icon(Icons::Ram,
                           RenderIconOptions{
                               .x = x + m_icon_offset +
                                    m_renderer.rendered_text_width(
                                        mock_ramdata, FontType::Regular),
                               .y = y,
                           });
  }

  void DataRenderingVisitor::operator()(const data::Drive& d) const noexcept {
    const std::string mock_drivedata{ "34%" };
    const auto& [x, y] = m_offset;
    m_renderer.render_text(mock_drivedata.c_str(),
                           RenderTextOptions{ .x = x,
                                              .y = y,
                                              .font_type = FontType::Regular,
                                              .color = Colors::Regular });
    m_renderer.render_icon(Icons::Drive,
                           RenderIconOptions{
                               .x = x + m_icon_offset +
                                    m_renderer.rendered_text_width(
                                        mock_drivedata, FontType::Regular),
                               .y = y,
                           });
  }

  void DataRenderingVisitor::operator()(const data::Battery& d) const noexcept {
    const std::string mock_batdata{ "34%" };
    const auto& [x, y] = m_offset;
    m_renderer.render_text(mock_batdata.c_str(),
                           RenderTextOptions{ .x = x,
                                              .y = y,
                                              .font_type = FontType::Regular,
                                              .color = Colors::Regular });
    m_renderer.render_icon(Icons::FullBat,
                           RenderIconOptions{
                               .x = x + m_icon_offset +
                                    m_renderer.rendered_text_width(
                                        mock_batdata, FontType::Regular),
                               .y = y,
                           });
  }

  void DataRenderingVisitor::operator()(const std::monostate&) const noexcept {}

  DataRenderingVisitor::~DataRenderingVisitor() = default;
} // namespace ymwm::ui
