#pragma once
#include "Offset.h"

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

  struct DataRenderingVisitor {
    DataRenderingVisitor(const Renderer& renderer);

    void operator()(const data::Date& d) const noexcept;
    void operator()(const data::Time& d) const noexcept;
    void operator()(const data::Cpu& d) const noexcept;
    void operator()(const data::Ram& d) const noexcept;
    void operator()(const data::Drive& d) const noexcept;
    void operator()(const data::Battery& d) const noexcept;
    void operator()(const std::monostate&) const noexcept;

    inline void set_offset(const Offset& offset) noexcept { m_offset = offset; }

    ~DataRenderingVisitor();

  private:
    const Renderer& m_renderer;
    Offset m_offset;
    const int m_icon_offset;
  };

} // namespace ymwm::ui
