#include <gtest/gtest.h>
#include "EC.h"


TEST(ec_equality_tests, are_equal) {
    LL p = 101;
    EC curve1(10, 20, p);
    EC curve2(10, 20, p);

    ASSERT_TRUE(curve1 == curve2);
    ASSERT_FALSE(curve1 != curve2);
}

TEST(ec_equality_tests, are_not_equal_a) {
    LL p = 101;
    EC curve1(10, 20, p);
    EC curve2(11, 20, p);

    ASSERT_FALSE(curve1 == curve2);
    ASSERT_TRUE(curve1 != curve2);
}

TEST(ec_equality_tests, are_not_equal_b) {
    LL p = 101;
    EC curve1(10, 20, p);
    EC curve2(10, 21, p);

    ASSERT_FALSE(curve1 == curve2);
    ASSERT_TRUE(curve1 != curve2);
}

