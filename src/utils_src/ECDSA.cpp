#include "ECDSA.h"
#include "MathHelper.h"
#include <functional>

ECDSA::ECDSA(const EC& curve, const Point& G, LL n)
    : p(curve.p), n(n), curve(curve), G(G), public_key(curve) {
    this->private_key = random_LL(1, n-1);
    this->public_key = this->private_key * this->G;
}

Point ECDSA::get_public_key() const {
    return this->public_key;
}

Signature ECDSA::sign(const string& message) const {
    hash<string> hash_fn;
    LL z_val = hash_fn(message);

    Int z(z_val, this->n);

    Int d(this->private_key, this->n);

    Int r(0, this->n);
    Int s(0, this->n);

    do {
        LL k_val = random_LL(1, n - 1);
        Int k(k_val, this->n);

        Point R = k_val * this->G;
        Int r_mod_p = R.x;

        r = Int(r_mod_p, this->n);
        if (r == 0) continue;

        s = k.inverse() * (z + r * d);
    } while (r == 0 || s == 0);
    return Signature{r, s};
}

bool ECDSA::verify(const string& message, const Signature& sig, const Point& public_key, const EC& curve, const Point& G, LL n) {
    hash<string> hash_fn;
    LL z_val = hash_fn(message);
    Int z(z_val, n);

    Int r = sig.r;
    Int s = sig.s;

    if (r == 0 || r >= n || s == 0 || s >= n) {
        return false;
    }
    Int u1 = z * s.inverse();
    Int u2 = r * s.inverse();

    Point P1 = u1 * G;
    Point P2 = u2 * public_key;
    Point P = P1 + P2;

    if (P.inf) return false;

    Int r_check(P.x, n);

    return r_check == r;
}
