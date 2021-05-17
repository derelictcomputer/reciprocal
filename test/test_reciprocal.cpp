#include <gtest/gtest.h>
#include "../api/reciprocal.h"

TEST(Hi, There) {
    const auto c = rc_test(2, 3);
    ASSERT_EQ(c, 6);
}
