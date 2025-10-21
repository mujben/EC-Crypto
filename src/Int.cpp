#include "MathHelper.h"
#include "Int.h"

LL Int::mod = 13;

Int Int::inverse() const {
    auto [g, x, y] = extended_gcd(this->value, mod);
    if (g != 1) return 0;
    return (x % mod + mod) % mod;
}

void ::Int::set_mod(const LL modulo) {
    mod = modulo;
}

LL Int::get_mod() {
    return mod;
}

//needed for fast exponentiation modulo(mod)
Int Int::pow(LL exp) const {
    if (exp == 0) return Int(1);
    Int result = Int(1);
    Int base = *this;
    if (exp < 0) {
        base = base.inverse();
        exp = -exp;
    }
    while (exp > 0) {
        if (exp % 2 == 1) result = result * base;
        base = base * base;
        exp >>= 1;
    }
    return result;
}