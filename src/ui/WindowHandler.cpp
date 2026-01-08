#include "WindowHandler.h"

#include <raylib.h>

namespace ymwm::ui {
  WindowHandler::WindowHandler() {
    InitWindow(100, 100, "YMWM-SB");
    SetTargetFPS(60);
  }

  WindowHandler::~WindowHandler() { CloseWindow(); }

} // namespace ymwm::ui
