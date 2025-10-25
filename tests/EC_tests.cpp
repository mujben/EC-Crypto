#include <gtest/gtest.h>
#include "EC.h"


TEST(ec_equality_tests, are_equal) {
    Int::set_mod(101);
    EC curve1;
    curve1.a = 10;
    curve1.b = 20;

    EC curve2;
    curve2.a = 10;
    curve2.b = 20;

    ASSERT_TRUE(curve1 == curve2);
    ASSERT_FALSE(curve1 != curve2);
}

TEST(ec_equality_tests, are_not_equal_a) {
    Int::set_mod(101);
    EC curve1;
    curve1.a = 10;
    curve1.b = 20;

    EC curve2;
    curve2.a = 11;
    curve2.b = 20;

    ASSERT_FALSE(curve1 == curve2);
    ASSERT_TRUE(curve1 != curve2);
}

TEST(ec_equality_tests, are_not_equal_b) {
    Int::set_mod(101);
    EC curve1;
    curve1.a = 10;
    curve1.b = 20;

    EC curve2;
    curve2.a = 10;
    curve2.b = 21;

    ASSERT_FALSE(curve1 == curve2);
    ASSERT_TRUE(curve1 != curve2);
}

