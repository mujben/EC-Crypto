#include <gtest/gtest.h>
#include "Point.h"

TEST(point_add_tests, lhs_is_inf) {
    LL p = 97;
    EC curve(2, 3, p);
    Point A(Int(2, p), Int(3, p), false, curve);
    Point B(curve);
    Point res = A;
    ASSERT_TRUE(res == A + B);
}

TEST(point_add_tests, rhs_is_inf) {
    LL p = 97;
    EC curve(2, 3, p);
    Point A(curve);
    Point B(Int(2, p), Int(3, p), false, curve);
    Point res = B;
    ASSERT_TRUE(res == A + B);
}

TEST(point_add_tests, add_inverse) {
    LL p = 97;
    EC curve(2, 3, p);
    Point A(Int(3, p), Int(6, p), false, curve);
    Point B(Int(3, p), Int(91, p), false, curve);
    Point res(curve);
    ASSERT_TRUE(res == A + B);
}

TEST(point_add_tests, point_doubling) {
    LL p = 97;
    EC curve(2, 3, p);
    Point A(Int(3, p), Int(6, p), false, curve);
    Point B(Int(3, p), Int(6, p), false, curve);
    Point res(Int(80, p), Int(10, p), false, curve);
    ASSERT_TRUE(res == A + B);
}

TEST(point_add_tests, point_addition) {
    LL p = 97;
    EC curve(2, 3, p);
    Point A(Int(3, p), Int(6, p), false, curve);
    Point B(Int(80, p), Int(10, p), false, curve);
    Point res(Int(80, p), Int(87, p), false, curve);
    ASSERT_TRUE(res == A + B);
}

TEST(point_mult_tests, mult_by_zero) {
    LL p = 97;
    EC curve(2, 3, p);
    Point A(Int(3, p), Int(6, p), false, curve);
    Point res(curve);
    ASSERT_TRUE(res == (LL)0 * A);
}

TEST(point_mult_tests, mult_by_one) {
    LL p = 97;
    EC curve(2, 3, p);
    Point A(Int(3, p), Int(6, p), false, curve);
    Point res = A;
    ASSERT_TRUE(res == (LL)1 * A);
}

TEST(point_mult_tests, mult_by_two) {
    LL p = 97;
    EC curve(2, 3, p);
    Point A(Int(3, p), Int(6, p), false, curve);
    Point res(Int(80, p), Int(10, p), false, curve);
    ASSERT_TRUE(res == (LL)2 * A);
}

TEST(point_mult_tests, mult_by_three) {
    LL p = 97;
    EC curve(2, 3, p);
    Point A(Int(3, p), Int(6, p), false, curve);
    Point res(Int(80, p), Int(87, p), false, curve);
    ASSERT_TRUE(res == (LL)3 * A);
}

TEST(point_mult_tests, mult_inf_point) {
    LL p = 97;
    EC curve(2, 3, p);
    Point A(curve);
    Point res(curve);
    ASSERT_TRUE(res == (LL)3 * A);
}

TEST(point_ops_tests, equality_operator) {
    LL p = 97;
    EC curve(2, 3, p);
    Point A(Int(3, p), Int(6, p), false, curve);
    Point B(Int(80, p), Int(10, p), false, curve);
    Point A_copy(Int(3, p), Int(6, p), false, curve);

    ASSERT_TRUE(A == A_copy);
    ASSERT_FALSE(A == B);
}

TEST(point_ops_tests, operator_plus_equals) {
    LL p = 97;
    EC curve(2, 3, p);
    Point A(Int(3, p), Int(6, p), false, curve);
    Point B(Int(80, p), Int(10, p), false, curve);
    Point res(Int(80, p), Int(87, p), false, curve);
    A += B;
    ASSERT_TRUE(res == A);
}

TEST(point_ops_tests, curve_mismatch_exception) {
    LL p = 97;
    EC curve1(2, 3, p);
    Point A(Int(3, p), Int(6, p), false, curve1);

    EC curve2(5, 6, p);
    Point B(Int(1, p), Int(1, p), false, curve2);

    ASSERT_THROW(A + B, runtime_error);
}
