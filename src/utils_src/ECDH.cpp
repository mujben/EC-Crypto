#include "ECDH.h"
#include "MathHelper.h"
#include "Int.h"

ECDH::ECDH(const EC& curve, const Point& G, LL n)
    : curve(curve), G(G), n(n), public_key(curve) {
    this->private_key = random_LL(1, n - 1);
    this->public_key = this->private_key * this->G;
}

Point ECDH::get_public_key() const {
    return this->public_key;
}

Point ECDH::calculate_shared_secret(const Point& other_public_key) const {
    if (this->curve != other_public_key.curve) {
        throw std::runtime_error("Curve mismatch in ECDH secret calculation");
    }
    return this->private_key * other_public_key;
}
