#include <limits>
#include <gtest/gtest.h>
#include "dagnabbit/Param.h"

using namespace dc;

TEST(Param, SetGetBool) {
  BoolParam p{false};
  ASSERT_EQ(p.min, false);
  ASSERT_EQ(p.max, true);
  ASSERT_EQ(p.step, true);
  ASSERT_EQ(p.def, false);
  ASSERT_EQ(p.get(), false);
  p.set(true);
  ASSERT_EQ(p.get(), true);
}

using TestTypes = ::testing::Types<uint8_t, float, double, int64_t>;

template <class T>
class ParamTest : public ::testing::Test {};

TYPED_TEST_SUITE(ParamTest, TestTypes, );

TYPED_TEST(ParamTest, SetGetContinuous) {
  const auto min = std::numeric_limits<TypeParam>::lowest() + 1;
  const auto max = std::numeric_limits<TypeParam>::max() - 1;
  const auto def = min + 1;
  const TypeParam step = 0;

  // check initialization
  Param<TypeParam> p{min, max, def, step};
  ASSERT_EQ(p.min, min);
  ASSERT_EQ(p.max, max);
  ASSERT_EQ(p.def, def);
  ASSERT_EQ(p.step, step);
  ASSERT_EQ(p.get(), def);

  // set in range
  const auto inRange = max / 2;
  p.set(inRange);
  ASSERT_EQ(p.get(), inRange);

  // set below the range, expect min
  p.set(min - 1);
  ASSERT_EQ(p.get(), min);

  // set above the range, expect max
  p.set(max + 1);
  ASSERT_EQ(p.get(), max);
}

TYPED_TEST(ParamTest, SetGetStepped) {
  const TypeParam min = 2;
  const TypeParam max = 123;
  const auto def = min + 2;
  const TypeParam step = 3;

  // check initialization
  Param<TypeParam> p{min, max, def, step};
  ASSERT_EQ(p.min, min);
  ASSERT_EQ(p.max, max);
  ASSERT_EQ(p.def, def);
  ASSERT_EQ(p.step, step);
  ASSERT_EQ(p.get(), def);

  // go from min to max and expect the value to snap to step
  auto current = min;
  while (current < max) {
    p.set(current);
    const auto expected = min + step * std::floor((current - min) / step + TypeParam(0.5));
    ASSERT_EQ(p.get(), expected);
    current += 1;
  }
}
