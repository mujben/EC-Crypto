#include <gtest/gtest.h>
#include "../src/MathHelper.h"

TEST(extended_gcd_tests, base_case) {
    auto [g, x, y] = extended_gcd(0, 6);
    ASSERT_EQ(g, 6);
    ASSERT_EQ(x, 0);
    ASSERT_EQ(y, 1);
}