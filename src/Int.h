#ifndef KRYPTO_INT_H
#define KRYPTO_INT_H
#include "MathHelper.h"
typedef long long LL;

struct Int {
private:
    LL value;
    static LL mod;
    Int inverse() const;
public:
    Int() : value(0) {};

    Int(LL val) : value(val % mod) {};

    operator LL() const {
        return value;
    };

    static void set_mod(const LL modulo);

    static LL get_mod();

    Int pow(LL exp) const;

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
        return this->value * rhs.inverse().value % mod;
    }

    bool operator==(const Int& rhs) const {
        return this->value == rhs.value;
    }
};
#endif //KRYPTO_INT_H