#include <gtest/gtest.h>
#include "../MathHelpers.h"

using namespace dc;

using NextPowerOfTwoTestTypes = ::testing::Types<uint8_t, uint16_t, uint32_t, size_t>;
template <class T>
class NextPowerOfTwoTest : public ::testing::Test {};
TYPED_TEST_SUITE(NextPowerOfTwoTest, NextPowerOfTwoTestTypes, );

TYPED_TEST(NextPowerOfTwoTest, Sanity) {
  const auto widthBits = sizeof(TypeParam) * 8;
  // test powers of two
  for (size_t shift = 0; shift < widthBits; ++shift) {
    const TypeParam testVal = TypeParam(1) << shift;
    ASSERT_EQ(testVal, nextPowerOfTwo(testVal));
  }
  // test in between
  for (size_t shift = 2; shift < widthBits; ++shift) {
    const TypeParam expectedVal = TypeParam(1) << shift;
    const TypeParam inputVal = expectedVal - 1;
    ASSERT_EQ(expectedVal, nextPowerOfTwo(inputVal));
  }
}
