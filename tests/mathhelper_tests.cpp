#include <gtest/gtest.h>
#include "../src/MathHelper.cpp"

TEST(extended_gcd_tests, base_case) {
    auto [g, x, y] = extended_gcd(0, 6);
    ASSERT_EQ(g, 6);
    ASSERT_EQ(x, 0);
    ASSERT_EQ(y, 1);
}

TEST(extended_gcd_tests, base_case_swapped) {
    auto [g, x, y] = extended_gcd(6, 0);
    ASSERT_EQ(g, 6);
    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, 0);
}

TEST(extended_gcd_tests, coprime_case) {
    auto [g, x, y] = extended_gcd(13, 3);
    ASSERT_EQ(g, 1);
    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, -4);
}

TEST(extended_gcd_tests, standard_case) {
    auto [g, x, y] = extended_gcd(35, 15);
    ASSERT_EQ(g, 5);
    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, -2);
}