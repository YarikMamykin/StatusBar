#pragma once

#include "Renderer.h"
#include "WindowHandler.h"
#include "ui/DataRenderingVisitor.h"

namespace ymwm::data {
  struct DataProvider;
}

namespace ymwm::ui {
  struct StatusBarWindow {
    StatusBarWindow(const data::DataProvider& data_provider);

    void render() noexcept;
    bool closed() const noexcept;

    ~StatusBarWindow();

  private:
    const data::DataProvider& m_data_provider;
    WindowHandler m_handler;
    Renderer m_renderer;
    DataRenderingVisitor m_rendering_visitor;
    RenderMeasuringVisitor m_measuring_visitor;
  };
} // namespace ymwm::ui
