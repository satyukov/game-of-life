#include "game_of_life/game_of_life.h"

void TestCheck() {
  CHECK(true);
  CHECK_NE(1, 2);
  CHECK_EQ(1, 1);
  CHECK_LE(1, 1);
  CHECK_LE(1, 2);
  CHECK_LT(1, 2);
  CHECK_GE(2, 1);
  CHECK_GE(2, 2);
  CHECK_GT(2, 1);
}

int main() {
  std::cout << "OK Common\n";
  return 0;
}
