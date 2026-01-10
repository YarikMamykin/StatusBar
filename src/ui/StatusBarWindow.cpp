#include "StatusBarWindow.h"

#include "Colors.h"
#include "data/DataProvider.h"
#include "data/DataType.h"
#include "ui/DataRenderingVisitor.h"
#include "ui/Renderer.h"

#include <raylib.h>

namespace ymwm::ui::prv {
  struct DrawingContext {
    DrawingContext() { BeginDrawing(); }
    ~DrawingContext() { EndDrawing(); }
  };
} // namespace ymwm::ui::prv

namespace ymwm::ui {
  StatusBarWindow::StatusBarWindow(const data::DataProvider& data_provider)
      : m_data_provider(data_provider)
      , m_rendering_visitor(m_renderer) {}

  void StatusBarWindow::render() noexcept {
    prv::DrawingContext ctx;
    m_renderer.render_background(Colors::Background);
    m_rendering_visitor.set_offset({ 0, 20 });
    auto time_width = std::visit(m_rendering_visitor,
                                 m_data_provider.provide(data::DataType::Time));
    m_rendering_visitor.set_offset({ time_width * 15 / 10, 20 });
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Battery));
    m_rendering_visitor.set_offset(
        { time_width * 15 / 10, 20 + m_renderer.default_font_size() * 2 });
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Cpu));
    m_rendering_visitor.set_offset(
        { time_width * 15 / 10, 20 + m_renderer.default_font_size() * 2 });
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Ram));
    m_rendering_visitor.set_offset(
        { time_width * 15 / 10, 20 + m_renderer.default_font_size() * 6 });
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Drive));

    m_renderer.render_line(RenderLineOptions{ .xs = time_width * 12 / 10,
                                              .ys = 20,
                                              .xe = time_width * 12 / 10,
                                              .ye = 300,
                                              .width = 10,
                                              .color = Colors::Delimiter });
  }

  bool StatusBarWindow::closed() const noexcept { return WindowShouldClose(); }

  StatusBarWindow::~StatusBarWindow() = default;
} // namespace ymwm::ui
