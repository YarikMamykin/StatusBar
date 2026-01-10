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
      , m_rendering_visitor(m_renderer)
      , m_measuring_visitor(m_renderer) {}

  void StatusBarWindow::render() noexcept {
    prv::DrawingContext ctx;
    // SetTextLineSpacing(10);
    int window_width = GetRenderWidth();
    int window_height = GetRenderHeight();

    int window_center_x = window_width / 2;
    int window_center_y = window_height / 2;

    m_renderer.render_background(Colors::Background);

    auto [time_width, time_height] = std::visit(
        m_measuring_visitor, m_data_provider.provide(data::DataType::Time));
    auto [cpu_width, cpu_height] = std::visit(
        m_measuring_visitor, m_data_provider.provide(data::DataType::Cpu));
    auto [ram_width, ram_height] = std::visit(
        m_measuring_visitor, m_data_provider.provide(data::DataType::Ram));
    auto [drive_width, drive_height] = std::visit(
        m_measuring_visitor, m_data_provider.provide(data::DataType::Drive));
    auto [bat_width, bat_height] = std::visit(
        m_measuring_visitor, m_data_provider.provide(data::DataType::Battery));

    const int margin_between_icons = 15;
    int full_width = time_width + 60 + cpu_width;
    int full_height = std::max(time_height,
                               cpu_height + ram_height + drive_height +
                                   bat_height + margin_between_icons * 3);

    const std::tuple initial_offset = { window_center_x - (full_width / 2),
                                        window_center_y - (full_height / 2) };
    std::tuple icons_offset = { std::get<0>(initial_offset) + time_width + 60,
                                std::get<1>(initial_offset) };

    m_rendering_visitor.set_offset(initial_offset);
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Time));

    m_renderer.render_line(
        RenderLineOptions{ .xs = std::get<0>(initial_offset) + time_width + 30,
                           .ys = std::get<1>(initial_offset),
                           .xe = std::get<0>(initial_offset) + time_width + 30,
                           .ye = std::get<1>(initial_offset) + full_height,
                           .width = 10,
                           .color = Colors::Delimiter });

    m_rendering_visitor.set_offset(icons_offset);
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Cpu));

    std::get<1>(icons_offset) += cpu_height + margin_between_icons;

    m_rendering_visitor.set_offset(icons_offset);
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Ram));

    std::get<1>(icons_offset) += ram_height + margin_between_icons;

    m_rendering_visitor.set_offset(icons_offset);
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Drive));

    std::get<1>(icons_offset) += drive_height + margin_between_icons;

    m_rendering_visitor.set_offset(icons_offset);
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Battery));
  }

  bool StatusBarWindow::closed() const noexcept { return WindowShouldClose(); }

  StatusBarWindow::~StatusBarWindow() = default;
} // namespace ymwm::ui
