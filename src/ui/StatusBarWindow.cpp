#include "StatusBarWindow.h"

#include "Colors.h"
#include "DataRenderingVisitor.h"
#include "Offset.h"
#include "RenderLineOptions.h"
#include "Renderer.h"
#include "data/DataProvider.h"
#include "data/DataType.h"
#include "ui/FontType.h"

#include <raylib.h>

namespace ymwm::ui::prv {
  struct DrawingContext {
    DrawingContext() { BeginDrawing(); }
    ~DrawingContext() { EndDrawing(); }
  };

  inline constinit int margin_between_icons{ 15 };
  inline constinit int delimiter_margin{ 20 };
  inline constinit int delimiter_width{ 10 };
  inline constinit int date_top_margin{ 20 };
} // namespace ymwm::ui::prv

namespace ymwm::ui {
  StatusBarWindow::StatusBarWindow(const data::DataProvider& data_provider)
      : m_data_provider(data_provider)
      , m_rendering_visitor(m_renderer)
      , m_measuring_visitor(m_renderer) {}

  void StatusBarWindow::render() noexcept {
    prv::DrawingContext ctx;

    m_renderer.render_background(Colors::Background);

    int window_width = GetRenderWidth();
    int window_height = GetRenderHeight();

    int window_center_x = window_width / 2;
    int window_center_y = window_height / 2;

    const int regular_font_size = m_renderer.font_size(FontType::Regular);
    const int big_font_size = m_renderer.font_size(FontType::Big);
    const int total_margin_between_icons = prv::margin_between_icons * 3;

    auto date = m_data_provider.provide(data::DataType::Date);
    auto time = m_data_provider.provide(data::DataType::Time);
    auto cpu = m_data_provider.provide(data::DataType::Cpu);
    auto ram = m_data_provider.provide(data::DataType::Ram);
    auto drive = m_data_provider.provide(data::DataType::Drive);
    auto battery = m_data_provider.provide(data::DataType::Battery);

    auto [date_width, date_height] = std::visit(m_measuring_visitor, date);
    auto [time_width, time_height] = std::visit(m_measuring_visitor, time);
    auto [cpu_width, cpu_height] = std::visit(m_measuring_visitor, cpu);
    auto [ram_width, ram_height] = std::visit(m_measuring_visitor, ram);
    auto [drive_width, drive_height] = std::visit(m_measuring_visitor, drive);
    auto [bat_width, bat_height] = std::visit(m_measuring_visitor, battery);

    // time is only component using big font that is why full_width defined by
    // time width
    int full_width = time_width + prv::delimiter_margin + prv::delimiter_width +
                     prv::delimiter_margin + cpu_width;
    int full_height = std::max(date_height + time_height,
                               cpu_height + ram_height + drive_height +
                                   bat_height + total_margin_between_icons);

    const Offset initial_offset{ window_center_x - (full_width / 2),
                                 window_center_y - (full_height / 2) };

    int date_and_icons_sum_width = date_width + prv::delimiter_margin +
                                   prv::delimiter_width +
                                   prv::delimiter_margin + cpu_width;
    m_rendering_visitor.set_offset(
        { window_center_x - (date_and_icons_sum_width / 2),
          initial_offset.y + prv::date_top_margin });
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Date));

    m_rendering_visitor.set_offset(
        { initial_offset.x,
          initial_offset.y + prv::date_top_margin + regular_font_size });
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Time));

    int line_x = initial_offset.x + time_width + prv::delimiter_margin;
    m_renderer.render_line(
        RenderLineOptions{ .xs = line_x,
                           .ys = initial_offset.y,
                           .xe = line_x,
                           .ye = initial_offset.y + full_height,
                           .width = prv::delimiter_width,
                           .color = Colors::Delimiter });

    Offset icons_offset = { initial_offset.x + time_width +
                                prv::delimiter_margin + prv::delimiter_width +
                                prv::delimiter_margin,
                            initial_offset.y };

    m_rendering_visitor.set_offset({ icons_offset.x, icons_offset.y });
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Cpu));

    icons_offset.y += cpu_height + prv::margin_between_icons;

    m_rendering_visitor.set_offset({ icons_offset.x, icons_offset.y });
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Ram));

    icons_offset.y += ram_height + prv::margin_between_icons;

    m_rendering_visitor.set_offset({ icons_offset.x, icons_offset.y });
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Drive));

    icons_offset.y += drive_height + prv::margin_between_icons;

    m_rendering_visitor.set_offset({ icons_offset.x, icons_offset.y });
    std::visit(m_rendering_visitor,
               m_data_provider.provide(data::DataType::Battery));
  }

  bool StatusBarWindow::closed() const noexcept { return WindowShouldClose(); }

  StatusBarWindow::~StatusBarWindow() = default;
} // namespace ymwm::ui
