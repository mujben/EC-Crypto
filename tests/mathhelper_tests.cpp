#include <gtest/gtest.h>
#include "MathHelper.h"

TEST(extended_gcd_tests, base_case) {
    auto [g, x, y] = extended_gcd(0, 6);
    ASSERT_EQ(g, 6);
    ASSERT_EQ(x, 0);
    ASSERT_EQ(y, 1);
}

TEST(is_prime_tests, is_true) {
    ASSERT_TRUE(is_prime(65537));
    ASSERT_TRUE(is_prime(1034302223));
    ASSERT_TRUE(!is_prime(1034302227));
}