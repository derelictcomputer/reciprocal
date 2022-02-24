#include <limits>
#include <gtest/gtest.h>
#include "dagnabbit/Param.h"

using namespace dc;

TEST(Param, SetGetBool) {
  const std::string name = "billy the boolean";
  BoolParam p{std::string(name), false};
  ASSERT_EQ(p.name, name);
  ASSERT_EQ(p.min, false);
  ASSERT_EQ(p.max, true);
  ASSERT_EQ(p.step, false);
  ASSERT_EQ(p.def, false);
  ASSERT_EQ(p.get(), false);
  p.set(true);
  ASSERT_EQ(p.get(), true);
  p.set(false);
  ASSERT_EQ(p.get(), false);
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
  Param<TypeParam> p{"", min, max, def, step};
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
  Param<TypeParam> p{"", min, max, def, step};
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

TYPED_TEST(ParamTest, SetGetNormalized) {
  const TypeParam min = 3;
  const TypeParam max = 42;
  const auto def = 4;
  const auto step = 0;

  // check initialization
  Param<TypeParam> p{"", min, max, def, step};
  ASSERT_EQ(p.min, min);
  ASSERT_EQ(p.max, max);
  ASSERT_EQ(p.def, def);
  ASSERT_EQ(p.step, step);
  ASSERT_EQ(p.get(), def);

  // set zero and expect min
  p.setNormalized(0.0);
  ASSERT_EQ(p.get(), min);
  ASSERT_EQ(p.getNormalized(), 0.0);

  // set 1.0 and expect max
  p.setNormalized(1.0);
  ASSERT_EQ(p.get(), max);
  ASSERT_EQ(p.getNormalized(), 1.0);

  // set somewhere in between and expect to get that value back
  const double norm = 0.5;
  p.setNormalized(norm);
  const auto expected = static_cast<TypeParam>(min + norm * (max - min));
  ASSERT_EQ(p.get(), expected);
  // some types/step sizes will cause the normalized value to snap
  const auto expectedNorm = static_cast<double>(expected - min) / (max - min);
  ASSERT_EQ(p.getNormalized(), expectedNorm);
}
