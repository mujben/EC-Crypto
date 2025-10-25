#include <gtest/gtest.h>
#include "Int.h"

TEST(int_add_test, equal_mod) {
    Int::set_mod(13);
    ASSERT_EQ(int(Int(7) + Int(6)), 0);
}

TEST(int_constructor_test, modulo_applied) {
    Int::set_mod(13);
    ASSERT_EQ(int(Int(15)), 2);
    ASSERT_EQ(int(Int(-1)), 12);
}

TEST(int_cast_test, cast_to_ll) {
    Int::set_mod(13);
    Int a(15);
    LL val = a;
    ASSERT_EQ(val, 2);
}

TEST(int_set_mod_test, mod_changes) {
    Int::set_mod(100);
    ASSERT_EQ(int(Int(50) + Int(60)), 10);

    Int::set_mod(13);
    ASSERT_EQ(int(Int(10) + Int(10)), 7);
}

TEST(int_add_test, simple_add) {
    Int::set_mod(13);
    ASSERT_EQ(int(Int(3) + Int(4)), 7);
}

TEST(int_sub_test, simple_sub) {
    Int::set_mod(13);
    ASSERT_EQ(int(Int(10) - Int(3)), 7);
}

TEST(int_sub_test, wrap_around_sub) {
    Int::set_mod(13);
    ASSERT_EQ(int(Int(3) - Int(5)), 11);
}

TEST(int_mul_test, simple_mul) {
    Int::set_mod(13);
    ASSERT_EQ(int(Int(3) * Int(4)), 12);
}

TEST(int_mul_test, wrap_around_mul) {
    Int::set_mod(13);
    ASSERT_EQ(int(Int(5) * Int(6)), 4);
}

TEST(int_div_test, simple_div) {
    Int::set_mod(13);
    ASSERT_EQ(int(Int(10) / Int(2)), 5);
}

TEST(int_div_test, inverse_div) {
    Int::set_mod(13);
    ASSERT_EQ(int(Int(7) / Int(3)), 11);
}

TEST(int_div_test, division_by_zero_inverse) {
    Int::set_mod(12);
    ASSERT_EQ(int(Int(5) / Int(3)), 0);
}

TEST(int_equality_test, are_equal) {
    Int::set_mod(13);
    ASSERT_TRUE(Int(15) == Int(2)); // 15 % 13 == 2
    ASSERT_TRUE(Int(2) == Int(2));
}

TEST(int_equality_test, are_not_equal) {
    Int::set_mod(13);
    ASSERT_FALSE(Int(15) == Int(3));
}