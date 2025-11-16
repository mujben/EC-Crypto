#include <gtest/gtest.h>
#include "ECDSA.h"
#include "EC.h"
#include "Point.h"
#include "Int.h"
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

TEST_F(ECDSATest, sign_and_verify_happy_path) {
    ECDSA alice(*curve, *g, n);
    Point QA = alice.get_public_key();

    std::string message = "To jest moja testowa wiadomosc";
    Signature sig = alice.sign(message);

    bool is_valid = ECDSA::verify(message, sig, QA, *curve, *g, n);

    ASSERT_TRUE(is_valid);
}

TEST_F(ECDSATest, verify_fails_on_tampered_message) {
    ECDSA alice(*curve, *g, n);
    Point QA = alice.get_public_key();
    std::string message = "Oryginalna wiadomosc";
    std::string tampered_message = "SFAŁSZOWANA wiadomosc";

    Signature sig = alice.sign(message);

    bool is_valid = ECDSA::verify(tampered_message, sig, QA, *curve, *g, n);

    ASSERT_FALSE(is_valid);
}

TEST_F(ECDSATest, verify_fails_on_tampered_signature) {
    ECDSA alice(*curve, *g, n);
    Point QA = alice.get_public_key();
    std::string message = "Wiadomosc";

    Signature sig = alice.sign(message);

    sig.s = sig.s + Int(1, n);

    bool is_valid = ECDSA::verify(message, sig, QA, *curve, *g, n);

    ASSERT_FALSE(is_valid);
}

TEST_F(ECDSATest, signature_to_string_conversion) {
    Int r(123, n);
    Int s(456, n);
    Signature sig{r, s};

    ASSERT_EQ((std::string)sig, "123 456");
}