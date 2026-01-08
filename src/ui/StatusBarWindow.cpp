#include "StatusBarWindow.h"

#include "Colors.h"
#include "data/DataProvider.h"

#include <raylib.h>

namespace ymwm::ui::prv {
  struct DrawingContext {
    DrawingContext() { BeginDrawing(); }
    ~DrawingContext() { EndDrawing(); }
  };
} // namespace ymwm::ui::prv

namespace ymwm::ui {
  StatusBarWindow::StatusBarWindow(const data::DataProvider& data_provider)
      : m_data_provider(data_provider) {}

  void StatusBarWindow::render() noexcept {
    prv::DrawingContext ctx;
    m_renderer.render_background(Colors::Background);
    m_renderer.render_text(
        "KEK", { .x = 100, .y = 100, .font_size = 32, .color = Colors::Text });
  }

  bool StatusBarWindow::closed() const noexcept { return WindowShouldClose(); }

  StatusBarWindow::~StatusBarWindow() = default;
} // namespace ymwm::ui
