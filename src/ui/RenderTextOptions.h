#pragma once
#include "Colors.h"
#include "FontType.h"

namespace ymwm::ui {

  struct RenderTextOptions {
    int x{ 0 };
    int y{ 0 };
    FontType font_type{ FontType::Regular };
    Colors color{ Colors::Regular };
  };

} // namespace ymwm::ui
