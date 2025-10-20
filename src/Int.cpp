#include "MathHelper.h"
#include "Int.h"
typedef long long LL;

LL Int::mod = 13;

Int Int::inverse() const {
    auto [g, x, y] = extended_gcd(this->value, mod);
    if (g != 1) return 0;
    return x % mod;
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
    if (exp < 0) {
        Int positive_exp = this -> pow(-exp);
        return positive_exp.pow(mod - 2);   //TODO naprawić!
    }
    Int result = Int(1);
    Int base = *this;
    while (exp > 0) {
        if (exp % 2 == 1) result = result * base;
        base = base * base;
        exp >>= 1;
    }
    return result;
}