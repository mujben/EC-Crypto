#ifndef KRYPTO_ECDSA_H
#define KRYPTO_ECDSA_H
#include "Int.h"
#include "Point.h"
#include "EC.h"

using namespace std;

struct Signature {
    Int r;
    Int s;

    operator string() const;
};

class ECDSA {
private:
    LL p;
    LL n;
    const EC& curve;
    const Point& G;
    LL private_key;
    Point public_key;

public:
    ECDSA(const EC& curve, const Point& G, LL n);

    Point get_public_key() const;
    Signature sign(const string& message) const;
    static bool verify(const string& message, const Signature& sig, const Point& public_key, const EC& curve, const Point& G, LL n);
};

#endif //KRYPTO_ECDSA_H
