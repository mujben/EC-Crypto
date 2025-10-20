#include <gtest/gtest.h>
#include "../src/Int.cpp"

TEST(int_add_test, equal_mod) {
    ASSERT_EQ(int(Int(7) + Int(6)), 0);
}

class IntMod17Test : public ::testing::Test {
protected:
    void SetUp() override {
        Int::set_mod(17);
    }
    void TearDown() override {
        Int::set_mod(1);
    }
};

TEST_F(IntMod17Test, division_with_modular_inverse) {
    Int a = Int(7);
    Int b = Int(6);
    Int result = a / b;
    ASSERT_EQ(LL(result), 4);
}