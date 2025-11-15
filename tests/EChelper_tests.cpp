#include <gtest/gtest.h>
#include <vector>
#include "ECHelper.h"
#include "Point.h"
#include "EC.h"
#include "Int.h"

using namespace std;

TEST(finding_square_root, test0) {
    LL p = 13;
    Int val(3, p);
    Int root = find_root_mod(val);
    EXPECT_TRUE(root == Int(4, p) || root == Int(9, p));
}

class curve_points_tests : public testing::Test {
protected:
    LL p;
    EC curve;
    vector<Point> points;
    void SetUp() override {
        p = 7;

        curve = EC(1, 0, p);

        points = vector<Point> {
            curve,
            {{0, p}, {0, p}, false, curve},
            {{1, p}, {3, p}, false, curve},
            {{1, p}, {4, p}, false, curve},
            {{3, p}, {3, p}, false, curve},
            {{3, p}, {4, p}, false, curve},
            {{5, p}, {2, p}, false, curve},
            {{5, p}, {5, p}, false, curve}
        };
    }
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