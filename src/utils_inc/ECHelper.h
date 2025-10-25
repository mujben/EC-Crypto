#ifndef KRYPTO_ECHELPER_H
#define KRYPTO_ECHELPER_H
#include "EC.h"
#include "Point.h"
#include "Int.h"

LL find_order(const EC &curve);

Point pick_random_point(const EC &curve);

Int find_root_mod(Int value);

#endif //KRYPTO_ECHELPER_H
