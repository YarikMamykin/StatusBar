#pragma once
#include <tuple>

namespace std {
  struct monostate;
}

namespace ymwm::data {
  struct Date;
  struct Time;
  struct Cpu;
  struct Ram;
  struct Drive;
  struct Battery;
} // namespace ymwm::data

namespace ymwm::ui {
  struct Renderer;

  struct RenderMeasuringVisitor {
    RenderMeasuringVisitor(const Renderer& renderer);

    std::tuple<int, int> operator()(const data::Date& d) const noexcept;
    std::tuple<int, int> operator()(const data::Time& d) const noexcept;
    std::tuple<int, int> operator()(const data::Cpu& d) const noexcept;
    std::tuple<int, int> operator()(const data::Ram& d) const noexcept;
    std::tuple<int, int> operator()(const data::Drive& d) const noexcept;
    std::tuple<int, int> operator()(const data::Battery& d) const noexcept;
    std::tuple<int, int> operator()(const std::monostate&) const noexcept;

    ~RenderMeasuringVisitor();

  private:
    const Renderer& m_renderer;
    const int m_icon_offset;
  };
} // namespace ymwm::ui
