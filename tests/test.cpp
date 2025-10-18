#include <gtest/gtest.h>

TEST(always_true, test0) {
    ASSERT_EQ(10, 2 * 5);
}

TEST(always_true, test1) {
    ASSERT_EQ(3, 5 - 2);
}
