#ifndef KRYPTO_EC_H
#define KRYPTO_EC_H
#include <iostream>
#include "Int.h"

using namespace std;

struct EC {
private:
    void init_random(LL modulo);

public:
    Int a;
    Int b;
    LL p;

    EC(LL a_val, LL b_val, LL modulo);
    EC(LL modulo);
    EC();

    bool operator==(const EC& rhs) const;
    bool operator!=(const EC& rhs) const;
};

ostream& operator<<(ostream& os, const EC& curve);

#endif //KRYPTO_EC_H

