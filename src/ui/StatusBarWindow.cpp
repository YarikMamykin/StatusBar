#include "StatusBarWindow.h"

#include "Colors.h"
#include "data/DataProvider.h"
#include "data/DataType.h"
#include "ui/DataRenderingVisitor.h"

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
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Time));
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Battery));
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Cpu));
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Ram));
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Drive));
  }

  bool StatusBarWindow::closed() const noexcept { return WindowShouldClose(); }

  StatusBarWindow::~StatusBarWindow() = default;
} // namespace ymwm::ui
