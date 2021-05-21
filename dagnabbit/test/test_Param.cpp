#include <gtest/gtest.h>
#include "../Param.h"

using namespace dc;

TEST(Param, Basics) {
  const float min = 1.1f;
  const float max = 3.5f;
  const float def = 2.9f;
  const float step = 0.4f;

  Param p({min, max, def, step});

  // check init values
  ASSERT_FLOAT_EQ(p.min, min);
  ASSERT_FLOAT_EQ(p.max, max);
  ASSERT_FLOAT_EQ(p.def, def);
  ASSERT_FLOAT_EQ(p.step, step);

  // check in-range param set/get
  for (float val = min; val < max; val += step) {
    ASSERT_EQ(p.set(val), Status::Ok);
    float v;
    ASSERT_EQ(p.get(v), Status::Ok);
    EXPECT_FLOAT_EQ(v, val);
  }

  // check out-of-range param set/get
  {
    ASSERT_EQ(p.set(min - 1), Status::Ok);
    float v;
    ASSERT_EQ(p.get(v), Status::Ok);
    EXPECT_FLOAT_EQ(v, min);
    ASSERT_EQ(p.set(max + 1), Status::Ok);
    ASSERT_EQ(p.get(v), Status::Ok);
    EXPECT_FLOAT_EQ(v, max);
  }

  // check step quantize
  {
    ASSERT_EQ(p.set(min + step * 0.4f), Status::Ok);
    float v;
    ASSERT_EQ(p.get(v), Status::Ok);
    EXPECT_FLOAT_EQ(v, min);
    ASSERT_EQ(p.set(min + step * 0.6f), Status::Ok);
    ASSERT_EQ(p.get(v), Status::Ok);
    EXPECT_FLOAT_EQ(v, min + step);
  }
}
