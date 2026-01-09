#include "DataRenderingVisitor.h"

#include "data/Data.h"
#include "ui/Colors.h"
#include "ui/Icons.h"
#include "ui/Renderer.h"

namespace ymwm::ui {
  DataRenderingVisitor::DataRenderingVisitor(const Renderer& renderer)
      : m_renderer(renderer) {}

  int DataRenderingVisitor::operator()(const data::Time& d) const noexcept {
    const std::string mock_date{ "Fri Jan  2 EET 2026" };
    const std::string mock_time{ "05:26:14 PM" };

    m_renderer.render_text(mock_date.c_str(),
                           { .x = 100,
                             .y = 100,
                             .font_size = m_renderer.default_font_size(),
                             .color = Colors::Regular });
    m_renderer.render_text(mock_time.c_str(),
                           { .x = 100,
                             .y = 200,
                             .font_size = m_renderer.default_font_size() * 2,
                             .color = Colors::Regular });

    return m_renderer.rendered_text_width(mock_time,
                                          m_renderer.default_font_size() * 2);
  }

  int DataRenderingVisitor::operator()(const data::Cpu& d) const noexcept {
    const std::string mock_cpudata{ "75%" };
    m_renderer.render_text(mock_cpudata.c_str(),
                           { .x = 500,
                             .y = 100,
                             .font_size = m_renderer.default_font_size(),
                             .color = Colors::Regular });
    m_renderer.render_icon(
        Icons::Cpu,
        {
            .x = 500 + m_renderer.rendered_text_width(
                           mock_cpudata, m_renderer.default_font_size()),
            .y = 100,
        });
    return m_renderer.rendered_text_width(mock_cpudata,
                                          m_renderer.default_font_size());
  }

  int DataRenderingVisitor::operator()(const data::Ram& d) const noexcept {
    const std::string mock_ramdata{ "25%" };
    m_renderer.render_text(mock_ramdata.c_str(),
                           { .x = 500,
                             .y = 100 + m_renderer.default_font_size(),
                             .font_size = m_renderer.default_font_size(),
                             .color = Colors::Regular });
    return m_renderer.rendered_text_width(mock_ramdata,
                                          m_renderer.default_font_size());
  }

  int DataRenderingVisitor::operator()(const data::Drive& d) const noexcept {
    const std::string mock_drivedata{ "34%" };
    m_renderer.render_text(mock_drivedata.c_str(),
                           { .x = 500,
                             .y = 100 + m_renderer.default_font_size() * 2,
                             .font_size = m_renderer.default_font_size(),
                             .color = Colors::Regular });
    return m_renderer.rendered_text_width(mock_drivedata,
                                          m_renderer.default_font_size());
  }

  int DataRenderingVisitor::operator()(const data::Battery& d) const noexcept {
    return 0;
  }

  int DataRenderingVisitor::operator()(const std::monostate&) const noexcept {
    return -1;
  }

  DataRenderingVisitor::~DataRenderingVisitor() = default;
} // namespace ymwm::ui
