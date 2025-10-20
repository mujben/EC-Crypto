#ifndef KRYPTO_EC_H
#define KRYPTO_EC_H
#include <iostream>
#include "Int.h"

struct EC {
    Int a;
    Int b;
    EC();

    EC(const LL modulo);
};

inline bool operator==(const EC& lhs, const EC& rhs) {
    return lhs.a == rhs.a && lhs.b == rhs.b;
}

inline bool operator!=(const EC& lhs, const EC& rhs) {
    return !(lhs == rhs);
}

inline std::ostream& operator<<(std::ostream& os, const EC& curve) {
    os << "----- Curve -----\n";
    os << "a: " << curve.a << ", b: " << curve.b << "\n";
    return os;
}
#endif //KRYPTO_EC_H