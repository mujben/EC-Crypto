#ifndef KRYPTO_MATHHELPER_H
#define KRYPTO_MATHHELPER_H
#include <tuple>
#include "Int.h"
typedef long long LL;

std::tuple<LL, LL, LL> extended_gcd(LL a, LL b);

bool is_prime(LL n, int iterations = 10);

std::array<LL, 2> factor(LL);

LL random_LL(LL min, LL max);

#endif //KRYPTO_MATHHELPER_H