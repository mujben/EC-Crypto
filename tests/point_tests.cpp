#include <gtest/gtest.h>
#include "Point.h"

TEST(point_add_tests, lhs_is_inf) {
    EC curve;
    Int::set_mod(97);
    Point A(2, 3, false, curve);
    Point B(0, 0, true, curve);
    Point res = A;
    ASSERT_EQ(res, A + B);
}

TEST(point_add_tests, rhs_is_inf) {
    EC curve;
    Int::set_mod(97);
    Point A(0, 0, true, curve);
    Point B(2, 3, false, curve);
    Point res = B;
    ASSERT_EQ(res, A + B);
}

TEST(point_add_tests, add_inverse) {
    EC curve;
    Int::set_mod(97);
    curve.a = 2;
    curve.b = 3;
    Point A = {Int(3), Int(6), false, curve};
    Point B = {Int(3), Int(91), false, curve};
    Point res = {Int(0), Int(0), true, curve};
    ASSERT_EQ(res, A + B);
}

TEST(point_add_tests, point_doubling) {
    EC curve;
    Int::set_mod(97);
    curve.a = 2;
    curve.b = 3;
    Point A = {Int(3), Int(6), false, curve};
    Point B = {Int(3), Int(6), false, curve};
    Point res = {Int(80), Int(10), false, curve};
    ASSERT_EQ(res, A + B);
}

TEST(point_add_tests, point_addition) {
    EC curve;
    Int::set_mod(97);
    curve.a = 2;
    curve.b = 3;
    Point A = {Int(3), Int(6), false, curve};
    Point B = {Int(80), Int(10), false, curve};
    Point res = {Int(80), Int(87), false, curve};
    ASSERT_EQ(res, A + B);
}

TEST(point_mult_tests, mult_by_zero) {
    EC curve;
    Int::set_mod(97);
    curve.a = 2;
    curve.b = 3;
    Point A = {Int(3), Int(6), false, curve};
    Point res = {Int(0), Int(0), true, curve};
    ASSERT_EQ(res, Int(0) * A);
}

TEST(point_mult_tests, mult_by_one) {
    EC curve;
    Int::set_mod(97);
    curve.a = 2;
    curve.b = 3;
    Point A = {Int(3), Int(6), false, curve};
    Point res = A;
    ASSERT_EQ(res, Int(1) * A);
}

TEST(point_mult_tests, mult_by_two) {
    EC curve;
    Int::set_mod(97);
    curve.a = 2;
    curve.b = 3;
    Point A = {Int(3), Int(6), false, curve};
    Point res = {Int(80), Int(10), false, curve};
    ASSERT_EQ(res, Int(2) * A);
}

TEST(point_mult_tests, mult_by_three) {
    EC curve;
    Int::set_mod(97);
    curve.a = 2;
    curve.b = 3;
    Point A = {Int(3), Int(6), false, curve};
    Point res = {Int(80), Int(87), false, curve};
    ASSERT_EQ(res, Int(3) * A);
}

TEST(point_mult_tests, mult_inf_point) {
    EC curve;
    Int::set_mod(97);
    curve.a = 2;
    curve.b = 3;
    Point A = {Int(0), Int(0), true, curve};
    Point res = {Int(0), Int(0), true, curve};
    ASSERT_EQ(res, Int(3) * A);
}

TEST(point_ops_tests, equality_operator) {
    EC curve;
    Int::set_mod(97);
    curve.a = 2;
    curve.b = 3;
    Point A = {Int(3), Int(6), false, curve};
    Point B = {Int(80), Int(10), false, curve};
    Point A_copy = {Int(3), Int(6), false, curve};

    ASSERT_TRUE(A == A_copy);
    ASSERT_FALSE(A == B);
}

TEST(point_ops_tests, operator_plus_equals) {
    EC curve;
    Int::set_mod(97);
    curve.a = 2;
    curve.b = 3;
    Point A = {Int(3), Int(6), false, curve};
    Point B = {Int(80), Int(10), false, curve};
    Point res = {Int(80), Int(87), false, curve};
    A += B;
    ASSERT_EQ(res, A);
}

TEST(point_ops_tests, curve_mismatch_exception) {
    EC curve1;
    curve1.a = 2;
    curve1.b = 3;
    Point A = {Int(3), Int(6), false, curve1};
    EC curve2;
    Int::set_mod(97);
    curve2.a = 5;
    curve2.b = 6;
    Point B = {Int(1), Int(1), false, curve2};
    ASSERT_ANY_THROW(A + B);
}