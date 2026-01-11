#pragma once
#include "Colors.h"

namespace ymwm::ui {

  struct RenderLineOptions {
    int xs{ 0 };
    int ys{ 0 };
    int xe{ 0 };
    int ye{ 0 };
    int width{ 0 };
    Colors color{ Colors::Regular };
  };
} // namespace ymwm::ui
