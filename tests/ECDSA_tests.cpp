#include <gtest/gtest.h>
#include "ECDSA.h"
#include "ECHelper.h"
#include "MathHelper.h"


class ECDSATest : public ::testing::Test {
protected:
    LL p;
    EC* curve;
    Point* g;
    LL n;

    void SetUp() override {
        p = 65537;
        Int::set_mod(p);

        std::array<LL, 2> factored = {0, 0};
        LL curve_order;

        curve = new EC(p); //

        while (factored[0] == 0) {
            delete curve;
            curve = new EC(p);
            curve_order = find_order(*curve); //
            factored = factor(curve_order, 11); //
        }
        n = factored[1];
        g = new Point(find_generator(*curve, factored)); //

        Int::set_mod(p);
    }

    void TearDown() override {
        delete g;
        delete curve;
        Int::set_mod(1);
    }
};


TEST_F(ECDSATest, SignAndVerifyHappyPath) {
    ASSERT_EQ(Int::get_mod(), p);
    ECDSA alice(*curve, *g, n);
    Point QA = alice.get_public_key();
    std::string message = "This is test message";
    Signature sig = alice.sign(message);

    ASSERT_EQ(Int::get_mod(), p);

    bool is_valid = ECDSA::verify(message, sig, QA, *curve, *g, n, p);

    ASSERT_TRUE(is_valid);
}

TEST_F(ECDSATest, VerifyFailsOnTamperedMessage) {
    ECDSA alice(*curve, *g, n);
    Point QA = alice.get_public_key();
    std::string message = "original message";
    std::string tampered_message = "tampered message";

    Signature sig = alice.sign(message);

    Int::set_mod(p);
    bool is_valid = ECDSA::verify(tampered_message, sig, QA, *curve, *g, n, p);

    ASSERT_FALSE(is_valid);
}

TEST_F(ECDSATest, VerifyFailsOnTamperedSignature) {
    ECDSA alice(*curve, *g, n);
    Point QA = alice.get_public_key();
    std::string message = "message";

    Signature sig = alice.sign(message);

    Int::set_mod(n);
    sig.s = sig.s + Int(1);

    Int::set_mod(p);
    bool is_valid = ECDSA::verify(message, sig, QA, *curve, *g, n, p);

    ASSERT_FALSE(is_valid);
}

TEST_F(ECDSATest, VerifyFailsOnZeroR) {
    ECDSA alice(*curve, *g, n);
    Point QA = alice.get_public_key();
    std::string message = "message";

    Signature sig = alice.sign(message);

    Int::set_mod(n);
    sig.r = Int(0);

    Int::set_mod(p);
    bool is_valid = ECDSA::verify(message, sig, QA, *curve, *g, n, p);

    ASSERT_FALSE(is_valid);
}