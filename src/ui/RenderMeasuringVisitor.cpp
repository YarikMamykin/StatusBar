#include "RenderMeasuringVisitor.h"

#include "Renderer.h"
#include "data/Data.h"

#include <string>

namespace ymwm::ui {
  RenderMeasuringVisitor::RenderMeasuringVisitor(const Renderer& renderer)
      : m_renderer(renderer)
      , m_icon_offset(10) // must be same as DataRenderingVisitor m_icon_offset
  {}

  std::tuple<int, int>
  RenderMeasuringVisitor::operator()(const data::Date& d) const noexcept {
    const std::string mock_date{ "Fri Jan  2 EET 2026" };
    int height = 48 + 15;
    int width =
        m_renderer.rendered_text_width(mock_date.c_str(), FontType::Regular);
    return { width, height };
  }

  std::tuple<int, int>
  RenderMeasuringVisitor::operator()(const data::Time& d) const noexcept {
    const std::string mock_time{ "05:26:14 PM" };

    int height = 48 * 2 + 15;
    int width =
        m_renderer.rendered_text_width(mock_time.c_str(), FontType::Big);
    return { width, height };
  }

  std::tuple<int, int>
  RenderMeasuringVisitor::operator()(const data::Cpu& d) const noexcept {
    const std::string mock_cpudata{ "75%" };
    int width =
        m_renderer.rendered_text_width(mock_cpudata.c_str(), FontType::Regular);
    width += m_icon_offset;
    int height = std::max(m_renderer.icon_size(), 48);
    return { width, height };
  }

  std::tuple<int, int>
  RenderMeasuringVisitor::operator()(const data::Ram& d) const noexcept {
    const std::string mock_ramdata{ "25%" };
    int width =
        m_renderer.rendered_text_width(mock_ramdata.c_str(), FontType::Regular);
    width += m_icon_offset;
    int height = std::max(m_renderer.icon_size(), 48);
    return { width, height };
  }

  std::tuple<int, int>
  RenderMeasuringVisitor::operator()(const data::Drive& d) const noexcept {
    const std::string mock_drivedata{ "34%" };
    int width = m_renderer.rendered_text_width(mock_drivedata.c_str(),
                                               FontType::Regular);
    width += m_icon_offset;
    int height = std::max(m_renderer.icon_size(), 48);
    return { width, height };
  }

  std::tuple<int, int>
  RenderMeasuringVisitor::operator()(const data::Battery& d) const noexcept {
    const std::string mock_batdata{ "34%" };
    int width =
        m_renderer.rendered_text_width(mock_batdata.c_str(), FontType::Regular);
    width += m_icon_offset;
    int height = std::max(m_renderer.icon_size(), 48);
    return { width, height };
  }

  std::tuple<int, int>
  RenderMeasuringVisitor::operator()(const std::monostate&) const noexcept {
    return { 0, 0 };
  }

  RenderMeasuringVisitor::~RenderMeasuringVisitor() = default;
} // namespace ymwm::ui
