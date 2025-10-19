#include <gtest/gtest.h>
#include "../src/Int.cpp"

TEST(int_add_test, equal_mod) {
    ASSERT_EQ(int(Int(7) + Int(6)), 0);
}