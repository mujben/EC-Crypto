#ifndef KRYPTO_BRUTEFORCEORDER_H
#define KRYPTO_BRUTEFORCEORDER_H
#include "EC.h"

int IsResidue(Int a);

LL FindOrder(const EC &curve);

#endif //KRYPTO_BRUTEFORCEORDER_H