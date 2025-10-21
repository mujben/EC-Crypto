#ifndef KRYPTO_BRUTEFORCEORDER_H
#define KRYPTO_BRUTEFORCEORDER_H
#include "EC.h"

int is_residue(Int a);

LL find_order(const EC &curve);

#endif //KRYPTO_BRUTEFORCEORDER_H