#pragma once
#include <tuple>
typedef long long LL;

using namespace std;

inline tuple<LL, LL, LL> extended_gcd(const LL a, const LL b) {
    if (a == 0)
        return {b, 0, 1};

    auto [g, x1, y1] = extended_gcd(b % a, a);
    return {g, y1 - (b / a) * x1, x1};
}
