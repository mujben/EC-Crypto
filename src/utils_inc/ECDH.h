#ifndef KRYPTO_ECDH_H
#define KRYPTO_ECDH_H
#include "EC.h"
#include "Point.h"
#include "Int.h"

class ECDH {
private:
    LL private_key;
    Point public_key;
    const EC& curve;
    const Point& G;
    LL n;

public:
    ECDH(const EC& curve, const Point& G, LL n);

    Point get_public_key() const;
    Point calculate_shared_secret(const Point& other_public_key) const;
};

#endif //KRYPTO_ECDH_H
