#ifndef KRYPTO_MATHHELPER_H
#define KRYPTO_MATHHELPER_H
#include <tuple>
#include "Int.h"
typedef long long LL;
using namespace std;

LL random_LL(LL min, LL max);
bool is_prime(LL n, int iterations = 10);
array<LL, 2> factor(LL num, int MAX_COFACTOR = 11);
int is_residue(Int a);

#endif //KRYPTO_MATHHELPER_H
