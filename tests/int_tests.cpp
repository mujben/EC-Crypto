#include <gtest/gtest.h>
#include "Int.h"

TEST(int_add_test, equal_mod) {
    LL p = 13;
    ASSERT_EQ(int(Int(7, p) + Int(6, p)), 0);
}

TEST(int_constructor_test, modulo_applied) {
    LL p = 13;
    ASSERT_EQ((LL)Int(15, p), 2);
    ASSERT_EQ((LL)Int(-1, p), 12);
}

TEST(int_cast_test, cast_to_ll) {
    LL p = 13;
    Int a(15, p);
    LL val = a;
    ASSERT_EQ(val, 2);
}


TEST(int_add_test, simple_add) {
    LL p = 13;
    ASSERT_EQ(int(Int(3, p) + Int(4, p)), 7);
}

TEST(int_sub_test, simple_sub) {
    LL p = 13;
    ASSERT_EQ(int(Int(10, p) - Int(3, p)), 7);
}

TEST(int_sub_test, wrap_around_sub) {
    LL p = 13;
    ASSERT_EQ(int(Int(3, p) - Int(5, p)), 11);
}

TEST(int_mul_test, simple_mul) {
    LL p = 13;
    ASSERT_EQ(int(Int(3, p) * Int(4, p)), 12);
}

TEST(int_mul_test, wrap_around_mul) {
    LL p = 13;
    ASSERT_EQ(int(Int(5, p) * Int(6, p)), 4);
}

TEST(int_div_test, simple_div) {
    LL p = 13;
    ASSERT_EQ(int(Int(10, p) / Int(2, p)), 5);
}

TEST(int_div_test, inverse_div) {
    LL p = 13;
    ASSERT_EQ(int(Int(7, p) / Int(3, p)), 11);
}

TEST(int_div_test, throws_on_non_invertible) {
    LL p = 12;
    Int a(5, p);
    Int b(3, p);
    ASSERT_THROW(a / b, runtime_error);
}

TEST(int_equality_test, are_equal) {
    LL p = 13;
    ASSERT_TRUE(Int(15, p) == Int(2, p)); // 15 % 13 == 2
    ASSERT_TRUE(Int(2, p) == Int(2, p));
}

TEST(int_equality_test, are_not_equal) {
    LL p = 13;
    ASSERT_FALSE(Int(15, p) == Int(3, p));
}

TEST(int_exponentiation_test, are_equal) {
    LL p = 13;
    Int a = Int(4, p);
    LL exp = -2;
    ASSERT_EQ(LL(a.pow(exp)), 9);
}
