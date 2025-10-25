#ifndef KRYPTO_INT_H
#define KRYPTO_INT_H
typedef long long LL;

struct Int {
private:
    LL value;
    static LL mod;
    Int inverse() const;

public:
    Int();
    Int(LL val);

    operator LL() const;

    static void set_mod(LL modulo);
    static LL get_mod();

    Int pow(LL exp) const;

    Int operator+(const Int& rhs) const;

    Int operator-(const Int& rhs) const;

    Int operator*(const Int& rhs) const;

    void operator*=(const Int& rhs);

    Int operator/(const Int& rhs) const;

    bool operator==(const Int& rhs) const;
};
#endif //KRYPTO_INT_H
