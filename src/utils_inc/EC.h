#ifndef KRYPTO_EC_H
#define KRYPTO_EC_H
#include <iostream>
#include "Int.h"

struct EC {
    Int a;
    Int b;
    LL p;

    EC(LL a_val, LL b_val, LL modulo);

    EC(LL modulo);

    EC();

private:
    void init_random(LL modulo);
};

bool operator==(const EC& lhs, const EC& rhs);

bool operator!=(const EC& lhs, const EC& rhs);

std::ostream& operator<<(std::ostream& os, const EC& curve);
#endif //KRYPTO_EC_H

