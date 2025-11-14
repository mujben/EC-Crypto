#include <gtest/gtest.h>
#include "ECDH.h"
#include "EC.h"
#include "Point.h"
#include "Int.h"
#include "ECHelper.h"
#include "MathHelper.h"

class ECDHTest : public ::testing::Test {
protected:
    LL p;
    EC* curve;
    Point* g;
    LL n;

    void SetUp() override {
        p = 65537;

        std::array<LL, 2> factored = {0, 0};
        LL curve_order;

        curve = new EC(p);

        while (factored[0] == 0) {
            delete curve;
            curve = new EC(p);
            curve_order = find_order(*curve);
            factored = factor(curve_order, 11);
        }
        n = factored[1];
        g = new Point(find_generator(*curve, factored));
    }
    void TearDown() override {
        delete g;
        delete curve;
    }
};

TEST_F(ECDHTest, shared_secrets_match_and_not_inf) {
    ECDH alice(*curve, *g, n); //
    ECDH bob(*curve, *g, n);

    Point QA = alice.get_public_key(); //
    Point QB = bob.get_public_key();

    Point shared_A = alice.calculate_shared_secret(QB); //
    Point shared_B = bob.calculate_shared_secret(QA);

    ASSERT_EQ(shared_A, shared_B);

    ASSERT_FALSE(shared_A.inf);
    ASSERT_FALSE(shared_B.inf);
}

TEST_F(ECDHTest, public_keys_diff) {
    ECDH alice(*curve, *g, n);
    ECDH bob(*curve, *g, n);

    Point QA = alice.get_public_key();
    Point QB = bob.get_public_key();

    ASSERT_NE(QA, QB);
}

TEST_F(ECDHTest, throw_on_curve_mismatch) {
    ECDH alice(*curve, *g, n);
    EC other_curve(p);
    while (other_curve == *curve) {
        other_curve = EC(p);
    }

    Point other_public_key = pick_random_point(other_curve);
    ASSERT_THROW({
        alice.calculate_shared_secret(other_public_key);
    }, std::runtime_error);

    try {
        alice.calculate_shared_secret(other_public_key);
    } catch (const std::exception& e) {
        ASSERT_STREQ("Curve mismatch in ECDH secret calculation", e.what());
    }
}