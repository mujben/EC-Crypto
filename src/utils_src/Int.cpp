#include "MathHelper.h"
#include "Int.h"

LL Int::mod = 1;

Int Int::inverse() const {
    auto [g, x, y] = extended_gcd(this->value, mod);
    if (g != 1) return 0;
    return (x % mod + mod) % mod;
}

Int::Int() : value(0) {}
Int::Int(LL val) : value(val % mod) {}

Int::operator LL() const {
    return value;
}

Int Int::operator+(const Int& rhs) const {
    return (this->value + rhs.value) % mod;
}

Int Int::operator-(const Int& rhs) const {
    return (this->value - rhs.value + mod) % mod;
}

Int Int::operator*(const Int& rhs) const {
    return (this->value * rhs.value) % mod;
}

void Int::operator*=(const Int& rhs) {
    this->value = (*this * rhs).value;
}

Int Int::operator/(const Int& rhs) const {
    return this->value * rhs.inverse().value % mod;
}

bool Int::operator==(const Int& rhs) const {
    return this->value == rhs.value;
}

void Int::set_mod(const LL modulo) {
    mod = modulo;
}

LL Int::get_mod() {
    return mod;
}

Int Int::pow(LL exp) const {
    if (exp == 0) return Int(1);
    Int result = Int(1);
    Int base = *this;
    if (exp < 0) {
        base = base.inverse();
        exp = -exp;
    }
    while (exp > 0) {
        if (exp & 1) result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}
