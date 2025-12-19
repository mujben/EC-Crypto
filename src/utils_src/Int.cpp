#include "MathHelper.h"
#include "Int.h"
#include <tuple>

#define MOD_CHECK(op) if (this->mod != rhs.mod) \
{ throw std::runtime_error("Modulus mismatch in Int::operator" #op); }

tuple<LL, LL, LL> extended_gcd(const LL a, const LL b) {
    if (a == 0)
        return {b, 0, 1};
    auto [g, x1, y1] = extended_gcd(b % a, a);
    return {g, y1 - (b / a) * x1, x1};
}

Int::Int() : value(0), mod(1) {};

Int::Int(LL val, LL modulo) {
    if (modulo <= 0) {
        if (modulo == 0) throw runtime_error("Modulus cannot be 0");
        this->mod = modulo;
    } else {
        this->mod = modulo;
    }
    this->value = (val % mod + mod) % mod;
}

Int Int::inverse() const {
    if (mod == 1) return Int(0, 1);
    auto [g, x, y] = extended_gcd(this->value, this->mod);
    if (g != 1) {
        throw runtime_error("Modular inverse does not exist");
    }
    return Int((x % mod + mod) % mod, this->mod);
}

LL Int::get_mod() const {
    return mod;
}

Int Int::pow(LL exp) const {
    if (this->mod == 1) return Int(0, 1);
    Int result(1, this->mod);
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

Int::operator LL() const {
    return value;
}

Int Int::operator-() const {
    return Int(-this->value, this->mod);
}

Int Int::operator+(const Int& rhs) const {
    MOD_CHECK(+);
    return Int(this->value + rhs.value, this->mod);
}

Int Int::operator-(const Int& rhs) const {
    MOD_CHECK(-);
    return Int(this->value - rhs.value + mod, this->mod);
}

Int Int::operator*(const Int& rhs) const {
    MOD_CHECK(*);
    // return Int(this->value * rhs.value, this->mod);
    Int res(0, this->mod);
    LL b = rhs.value;
    LL a = this->value;
    while (b > 0) {
        if (b & 1) res.value = (res.value + a) % this->mod;
        a = (a << 1) % this->mod;
        b >>= 1;
    }
    return res;
}

Int Int::operator/(const Int& rhs) const {
    MOD_CHECK(/);
    return (*this) * rhs.inverse();
}

void Int::operator+=(const Int& rhs) {
    MOD_CHECK(+=);
    this->value = (*this + rhs).value;
}

void Int::operator-=(const Int& rhs) {
    MOD_CHECK(-=);
    this->value = (*this - rhs).value;
}

void Int::operator*=(const Int& rhs) {
    MOD_CHECK(*=);
    this->value = (*this * rhs).value;
}

void Int::operator/=(const Int& rhs) {
    MOD_CHECK(/=);
    this->value = (*this / rhs).value;
}

bool Int::operator==(const Int& rhs) const {
    return this->value == rhs.value && this->mod == rhs.mod;
}

bool Int::operator!=(const Int& rhs) const {
    return !(*this == rhs);
}
