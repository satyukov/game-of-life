#include "game_of_life/game_of_life.h"

void Test_Get_Manual1() {
  const auto field = MakeField2D({
    {true, false, false},
    {false, true, false},
  });
  CHECK_EQ(field.GetRows(), 2);
  CHECK_EQ(field.GetColumns(), 3);
  
  CHECK(field.Get(0, 0));
  CHECK(!field.Get(0, 1));
  CHECK(!field.Get(0, 2));

  CHECK(!field.Get(1, 0));
  CHECK(field.Get(1, 1));
  CHECK(!field.Get(1, 2));
}

void Test_Get_Manual2() {
  const auto field = MakeField2D(1, 2);
  CHECK_EQ(field.GetRows(), 1);
  CHECK_EQ(field.GetColumns(), 2);

  CHECK(!field.Get(0, 0));
  CHECK(!field.Get(0, 1));
}

void Test_Get() {
  Test_Get_Manual1();
  Test_Get_Manual2();
}

void Test_ParseField2D_1x1() {
  const auto field1 = ParseField2D(".");
  CHECK_EQ(field1.GetRows(), 1);
  CHECK_EQ(field1.GetColumns(), 1);
  CHECK(!field1.Get(0, 0));
  CHECK_EQ(".", SerializeField2D(field1));

  const auto field2 = ParseField2D("#");
  CHECK_EQ(field2.GetRows(), 1);
  CHECK_EQ(field2.GetColumns(), 1);
  CHECK(field2.Get(0, 0));
  CHECK_EQ("#", SerializeField2D(field2));

  const auto field3 = ParseField2D("0");
  CHECK_EQ(field3.GetRows(), 1);
  CHECK_EQ(field3.GetColumns(), 1);
  CHECK(!field3.Get(0, 0));
  CHECK_EQ(".", SerializeField2D(field3));

  const auto field4 = ParseField2D("1");
  CHECK_EQ(field4.GetRows(), 1);
  CHECK_EQ(field4.GetColumns(), 1);
  CHECK(field4.Get(0, 0));
  CHECK_EQ("#", SerializeField2D(field4));
}

void Test_ParseField2D_2x3() {
  const auto field = ParseField2D(".#.|#.#");
  CHECK_EQ(field.GetRows(), 2);
  CHECK_EQ(field.GetColumns(), 3);
  CHECK_EQ(".#.|#.#", SerializeField2D(field));

  CHECK(!field.Get(0, 0));
  CHECK(field.Get(0, 1));
  CHECK(!field.Get(0, 2));
  CHECK(field.Get(1, 0));
  CHECK(!field.Get(1, 1));
  CHECK(field.Get(1, 2));
}

void Test_ParseField2D_3x2() {
  const auto field = ParseField2D(".#|#.|##");
  CHECK_EQ(field.GetRows(), 3);
  CHECK_EQ(field.GetColumns(), 2);
  CHECK_EQ(".#|#.|##", SerializeField2D(field));

  CHECK(!field.Get(0, 0));
  CHECK(field.Get(0, 1));
  CHECK(field.Get(1, 0));
  CHECK(!field.Get(1, 1));
  CHECK(field.Get(2, 0));
  CHECK(field.Get(2, 1));
}

void Test_ParseField2D() {
  Test_ParseField2D_1x1();
  Test_ParseField2D_2x3();
  Test_ParseField2D_3x2();
}

void Test_Advance_1x1() {
  auto field = ParseField2D("#");
  CHECK_EQ(SerializeField2D(field), "#");

  CHECK(field.CanAdvance());
  field.Advance();
  CHECK_EQ(SerializeField2D(field), ".");

  CHECK(field.CanAdvance());
  field.Advance();
  CHECK_EQ(SerializeField2D(field), ".");
}

void CheckAdvance(const std::string& start, const int steps, const std::string& end) {
  auto field = ParseField2D(start);
  CHECK_EQ(SerializeField2D(field), start);

  for (int iteration = 0; iteration + 1 < steps; ++iteration) {
    CHECK(field.CanAdvance());
    field.Advance();
    CHECK_NE(SerializeField2D(field), end);
  }

  CHECK(field.CanAdvance());
  field.Advance();
  CHECK_EQ(SerializeField2D(field), end);
}

void CheckPeriodic(const std::string& text, const int expected_period) {
  CheckAdvance(text, expected_period, text);
}

void Test_Advance_StillLife() {
  // Block.
  CheckPeriodic("##|"
                "##", /*expected_period=*/1);

  // Bee-hive.
  CheckPeriodic(".##.|"
                "#..#|"
                ".##.", /*expected_period=*/1);

  // Loaf.
  CheckPeriodic(".##.|"
                "#..#|"
                ".#.#|"
                "..#.", /*expected_period=*/1);

  // Boat.
  CheckPeriodic("##.|"
                "#.#|"
                ".#.", /*expected_period=*/1);

  // Tub.
  CheckPeriodic(".#.|"
                "#.#|"
                ".#.", /*expected_period=*/1);
}

void Test_Advance_Oscillator() {
  // Blinker.
  CheckPeriodic("...|"
                "###|"
                "...", /*expected_period=*/2);

  // Toad.
  CheckPeriodic("....|"
                ".###|"
                "###.|"
                "....", /*expected_period=*/2);

  // Beacon.
  CheckPeriodic("##..|"
                "##..|"
                "..##|"
                "..##", /*expected_period=*/2);

  // Pulsar.
  CheckPeriodic("...............|"
                "...###...###...|"
                "...............|"
                ".#....#.#....#.|"
                ".#....#.#....#.|"
                ".#....#.#....#.|"
                "...###...###...|"
                "...............|"
                "...###...###...|"
                ".#....#.#....#.|"
                ".#....#.#....#.|"
                ".#....#.#....#.|"
                "...............|"
                "...###...###...|"
                "...............", /*expected_period=*/3);
}

void Test_Advance_Spaceship() {
  // Glider.
  CheckAdvance(".#..|"
               "..#.|"
               "###.|"
               "....",
               /*steps=*/4,
               "....|"
               "..#.|"
               "...#|"
               ".###");
}

void Test_Advance() {
  Test_Advance_1x1();
  Test_Advance_StillLife();
  Test_Advance_Oscillator();
  Test_Advance_Spaceship();
}

int main() {
  StartClock();

  Test_Get();
  Test_ParseField2D();
  Test_Advance();

  std::cout << "OK Field2D in " << StopClock() << "ms\n";
  return 0;
}
