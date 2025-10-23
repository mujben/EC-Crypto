#include <gtest/gtest.h>
#include "ECHelper.h"

class CurveMod137Test : public ::testing::Test {
protected:
    void SetUp() override {
        Int::set_mod(137);
        EC curve;
        curve.a = 54;
        curve.b = 85;
    }
    void TearDown() override {
        Int::set_mod(1);
    }
};

TEST_F(CurveMod137Test, brute_force_order) {
    EC curve;
    Int::set_mod(137);
    curve.a = 54;
    curve.b = 85;
    LL order = find_order(curve);
    ASSERT_EQ(order, LL(144));
}
