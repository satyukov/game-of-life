#include "time.h"

#include <chrono>

static std::chrono::time_point<std::chrono::steady_clock> start;
static std::chrono::time_point<std::chrono::steady_clock> end;

void StartClock() {
  start = std::chrono::steady_clock::now();
}

int StopClock() {
  end = std::chrono::steady_clock::now();

  const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  return elapsed.count();
}
