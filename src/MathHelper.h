#ifndef KRYPTO_MATHHELPER_H
#define KRYPTO_MATHHELPER_H
#include <tuple>
typedef long long LL;

inline std::tuple<LL, LL, LL> extended_gcd(const LL a, const LL b) {
    if (a == 0)
        return {b, 0, 1};

    auto [g, x1, y1] = extended_gcd(b % a, a);
    return {g, y1 - (b / a) * x1, x1};
}
#endif //KRYPTO_MATHHELPER_H