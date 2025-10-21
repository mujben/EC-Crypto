#ifndef KRYPTO_SUBGROUPGENERATOR_H
#define KRYPTO_SUBGROUPGENERATOR_H
#include "Point.h"
#include "Int.h"
#include "EC.h"

Point pick_random_point(const EC &curve);

Int find_root_mod(Int value);

#endif //KRYPTO_SUBGROUPGENERATOR_H