#include "WindowHandler.h"

#include <raylib.h>

namespace ymwm::ui {
  WindowHandler::WindowHandler() {
    InitWindow(100, 100, "YMWM-SB");
    SetTargetFPS(20);
  }

  WindowHandler::~WindowHandler() { CloseWindow(); }

} // namespace ymwm::ui
