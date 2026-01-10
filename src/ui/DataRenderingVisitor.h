#pragma once
#include <tuple>

namespace std {
  struct monostate;
}

namespace ymwm::data {
  struct Time;
  struct Cpu;
  struct Ram;
  struct Drive;
  struct Battery;
} // namespace ymwm::data

namespace ymwm::ui {
  struct Renderer;

  struct DataRenderingVisitor {
    DataRenderingVisitor(const Renderer& renderer);

    [[maybe_unused]] int operator()(const data::Time& d) const noexcept;
    [[maybe_unused]] int operator()(const data::Cpu& d) const noexcept;
    [[maybe_unused]] int operator()(const data::Ram& d) const noexcept;
    [[maybe_unused]] int operator()(const data::Drive& d) const noexcept;
    [[maybe_unused]] int operator()(const data::Battery& d) const noexcept;
    [[maybe_unused]] int operator()(const std::monostate&) const noexcept;

    inline void set_offset(std::tuple<int, int>&& offset) noexcept {
      m_offset = offset;
    }

    ~DataRenderingVisitor();

  private:
    const Renderer& m_renderer;
    std::tuple<int, int> m_offset;
  };
} // namespace ymwm::ui
