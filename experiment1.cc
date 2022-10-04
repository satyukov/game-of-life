#include "game_of_life/game_of_life.h"

int main() {
  auto field = MakeField2D(10, 20);
  CHECK(field.CanAdvance());
  field.Advance();

  std::cout << "Hello world!\n";
  return 0;
}
