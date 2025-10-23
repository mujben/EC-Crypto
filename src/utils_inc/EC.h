#ifndef KRYPTO_EC_H
#define KRYPTO_EC_H
#include <iostream>
#include "Int.h"

struct EC {
    Int a;
    Int b;
    EC();

    EC(LL modulo);
};

bool operator==(const EC& lhs, const EC& rhs);

bool operator!=(const EC& lhs, const EC& rhs);

std::ostream& operator<<(std::ostream& os, const EC& curve);
#endif //KRYPTO_EC_H
