#include "ECDSA.h"
#include "MathHelper.h"
#include <functional>

static Point calculate_public_key(LL p, LL private_key, const Point& G) {
    LL old_mod = Int::get_mod();
    Int::set_mod(p);
    Point Q = private_key * G;
    Int::set_mod(old_mod);
    return Q;
}

ECDSA::ECDSA(const EC& curve, const Point& G, LL n)
    : p(Int::get_mod()), curve(curve), G(G), n(n), public_key(curve)
{
    this->private_key = random_LL(1, n - 1);
    this->public_key = calculate_public_key(this->p, this->private_key, this->G);
}

Point ECDSA::get_public_key() const {
    return this->public_key;
}

Signature ECDSA::sign(const std::string& message) const {
    LL old_mod = Int::get_mod();
    std::hash<std::string> hash_fn;
    LL z_val = hash_fn(message);
    Int r, s;
    do {
        LL k_val = random_LL(1, n - 1);
        Int::set_mod(this->p);
        Point R = k_val * this->G;
        LL r_val = R.x;
        Int::set_mod(this->n);
        r = Int(r_val);
        if (r == Int(0)) continue;
        Int k(k_val);
        Int z(z_val);
        Int d(this->private_key);
        s = k.inverse() * (z + r * d);


    } while (r == Int(0) || s == Int(0));
    Int::set_mod(old_mod);
    return Signature{r, s};
}

bool ECDSA::verify(const std::string& message, const Signature& sig, const Point& public_key, const EC& curve, const Point& G, LL n, LL p) {
    LL old_mod = Int::get_mod();
    std::hash<std::string> hash_fn;
    LL z_val = hash_fn(message);

    Int::set_mod(n);
    Int r = sig.r;
    Int s = sig.s;
    if (r == Int(0) || r >= n || s >= n || s == Int(0)){
        Int::set_mod(old_mod);
        return false;
    }

    Int u1 = Int(z_val) * s.inverse();
    Int u2 = r * s.inverse();

    Int::set_mod(p);
    Point P = u1 * G + u2 * public_key;
    if (P.inf) {
        Int::set_mod(old_mod);
        return false;
    }
    LL P_x_val = P.x;
    Int::set_mod(n);
    Int r_check(P_x_val);
    bool result = (r_check == r);

    Int::set_mod(old_mod);
    return result;
}