#include <gtest/gtest.h>
#include "../src/Point.cpp"

TEST(point_tests, lhs_is_inf) {
    EC curve;
    Point A(2, 3, false, curve);
    Point B(0, 0, true, curve);
    Point res = A;
    ASSERT_EQ(res, A + B);
}

