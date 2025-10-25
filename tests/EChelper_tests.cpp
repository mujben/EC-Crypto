#include <gtest/gtest.h>
#include <vector>
#include "ECHelper.h"
#include "Point.h"
#include "EC.h"
#include "Int.h"

using namespace std;

TEST(finding_square_root, test0) {
    Int::set_mod(13);
    Int root = find_root_mod(3);
    EXPECT_TRUE(root == Int(4) || root == Int(9));
}

class curve_points_tests : public testing::Test {
protected:
    void SetUp() override {
        Int::set_mod(7);
        curve.a = 1;
        curve.b = 0;
        points = vector<Point>{
        {0, 0, true, curve},
        {0, 0, false, curve},
        {1, 3, false, curve},
        {1, 4, false, curve},
        {3, 3, false, curve},
        {3, 4, false, curve},
        {5, 2, false, curve},
        {5, 5, false, curve}
        };
    }

    EC curve;
    vector<Point> points;
};

TEST_F(curve_points_tests, random_point_is_valid) {
    for (int i = 0; i < 100; i++) {
        Point A = pick_random_point(curve);
        bool found = (find(points.begin(), points.end(), A) != points.end());
        EXPECT_TRUE(found);
    }
}

TEST_F(curve_points_tests, find_order_is_valid) {
    ASSERT_EQ(find_order(curve), points.size());
}