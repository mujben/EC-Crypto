#include <gtest/gtest.h>
#include <vector>
#include "SubgroupGenerator.h"
#include "Point.h"

TEST(finding_square_root, test0) {
    Int::set_mod(13);
    // 4*4 = 3 (mod13) and 9*9 = 3 (mod13)
    Int root = find_root_mod(3);
    EXPECT_TRUE(root == Int(4) || root == Int(9));
}

class CurveMod7Test : public testing::Test {
protected:
    EC curve;
    std::vector<Point> points;

    void SetUp() override {
        Int::set_mod(7);
        curve.a = 1;
        curve.b = 0;
        points.emplace_back(Int(0), Int(0), true, curve);
        points.emplace_back(Int(0), Int(0), false, curve);
        points.emplace_back(Int(1), Int(3), false, curve);
        points.emplace_back(Int(1), Int(4), false, curve);
        points.emplace_back(Int(3), Int(3), false, curve);
        points.emplace_back(Int(3), Int(4), false, curve);
        points.emplace_back(Int(5), Int(2), false, curve);
        points.emplace_back(Int(5), Int(5), false, curve);
    }
};

TEST_F(CurveMod7Test, random_point_is_valid) {

    for (int i = 0; i < 100; i++) {
        Point A = pick_random_point(curve);
        bool found = (std::find(points.begin(), points.end(), A) != points.end());
        EXPECT_TRUE(found)
            << "pick_random_point() returned false: " << "x = " << LL(A.x) << ", y = " << LL(A.y);
    }
}