#pragma once
#include <iostream>
#include "MathHelper.cpp"
typedef long long LL;

struct Int {
private:
    LL value;
    static LL mod;

    Int inverse() const {
        auto [g, x, y] = extended_gcd(this->value, mod);
        if (g != 1) return 0;
        return Int((x % mod + mod) % mod);
    }

public:
    Int() {}
    Int(LL value) : value((value % mod + mod) % mod) {}
    operator LL() const {
        return value;
    }

    static void set_mod(const LL modulo) {
        mod = modulo;
    }

    Int operator+(const Int& rhs) const {
        return (this->value + rhs.value) % mod;
    }

    Int operator-(const Int& rhs) const {
        return (this->value - rhs.value + mod) % mod;
    }

    Int operator*(const Int& rhs) const {
        return (this->value * rhs.value) % mod;
    }

    Int operator/(const Int& rhs) const {
        LL res = this->value * rhs.inverse().value;
        return Int((res % mod + mod) % mod);
    }

    bool operator==(const Int& rhs) const {
        return this->value == rhs.value;
    }
};

inline long long Int::mod = 13;