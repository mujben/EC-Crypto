#ifndef KRYPTO_INT_H
#define KRYPTO_INT_H
#include <stdexcept>
typedef long long LL;

std::tuple<LL, LL, LL> extended_gcd(LL a, LL b);

struct Int {
private:
    LL value;
    LL mod;

public:
    Int inverse() const;

    Int();
    Int(LL val, LL modulo);

    operator LL() const;

    LL get_mod() const;

    Int pow(LL exp) const;

    Int operator-() const;

    Int operator+(const Int& rhs) const;

    Int operator-(const Int& rhs) const;

    Int operator*(const Int& rhs) const;

    Int operator/(const Int& rhs) const;

    void operator+=(const Int& rhs);

    void operator*=(const Int& rhs);

    void operator-=(const Int& rhs);

    void operator/=(const Int& rhs);

    bool operator==(const Int& rhs) const;

    bool operator!=(const Int& rhs) const;

};
#endif //KRYPTO_INT_H