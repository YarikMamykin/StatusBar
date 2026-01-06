#include "lifecycle/LifecycleHandler.h"

#include <csignal>
#include <cstdlib>

static ymwm::lifecycle::LifecycleHandler* phandler;

void sighandler(int signal) {
  if (signal == SIGINT or signal == SIGTERM) {
    phandler->stop();
    return;
  }

  std::exit(signal);
}

int main() {
  ymwm::lifecycle::LifecycleHandler handler;
  phandler = &handler;
  std::signal(SIGINT, sighandler);
  std::signal(SIGTERM, sighandler);
  return handler.run();
}
