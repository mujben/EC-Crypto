#include <gtest/gtest.h>
#include "MathHelper.h"

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

class is_residue_tests : public ::testing::Test {
    protected:
    void SetUp() override {
        Int::set_mod(13);
    }
    void TearDown() override {
        Int::set_mod(1);
    }
};

TEST_F(is_residue_tests, base_case) {
    Int n(0);
    int result_n = 0;
    ASSERT_EQ(is_residue(n), result_n);
}

TEST_F(is_residue_tests, true_case) {
    Int a(1);
    int result_a = 1;
    ASSERT_EQ(is_residue(a), result_a);
}

TEST_F(is_residue_tests, false_case) {
    Int b(2);
    int result_b = -1;
    ASSERT_EQ(is_residue(b), result_b);
}

TEST(factor_tests, input_is_big_prime) {
    LL ord = 1000000007;
    array<LL, 2> expected = {1, ord};
    ASSERT_EQ(factor(ord), expected);
}

TEST(factor_tests, input_is_small_composite) {
    // ord1 = 10 * 1000000007
    LL ord1 = 10000000070;
    array<LL, 2> expected1 = {10, 1000000007};
    // ord2 = 8 * 1000000007
    LL ord2 = 8000000056;
    array<LL, 2> expected2 = {8, 1000000007};
    ASSERT_EQ(factor(ord1), expected1);
    ASSERT_EQ(factor(ord2), expected2);
}

TEST(factor_tests, h_is_MAX_COFACTOR) {
    // ord = 1000000007 * 11 (default MAX_COFACTOR);
    LL ord = 11000000077;
    array<LL, 2> expected = {11, 1000000007};
    ASSERT_EQ(factor(ord), expected);
}

TEST(factor_tests, h_too_big) {
    // ord = 1000000007 * 16
    LL ord = 16000000112;
    array<LL, 2> expected = {0, 0};
    ASSERT_EQ(factor(ord), expected);
}