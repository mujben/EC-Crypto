#include <array>
#include <random>
#include "MathHelper.h"
#include "Int.h"

using namespace std;

tuple<LL, LL, LL> extended_gcd(const LL a, const LL b) {
    if (a == 0)
        return {b, 0, 1};

    auto [g, x1, y1] = extended_gcd(b % a, a);
    return {g, y1 - (b / a) * x1, x1};
}

LL random_LL(const LL min, const LL max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<LL> dis(min, max);
    return dis(gen);
}

bool is_prime(LL n, int iterations) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;

    LL s = 0;
    LL d = n - 1;
    while ((d & 1) == 0) {
        d = d >> 1;
        s++;
    }

    LL old_mod = Int::get_mod();

    for (int i = 0; i < iterations; i++) {
        Int::set_mod(n);
        Int a(random_LL(1, n - 1));
        Int x = a.pow(d);
        if (x == Int(1) || x == Int(n - 1)) continue;
        bool composite = true;
        for (int r = 0; r < s - 1; r++) {
            x *= x;
            if (x == Int(n - 1)) {
                composite = false;
                break;
            }
        }
        if (composite) {
            Int::set_mod(old_mod);
            return false;
        }
    }
    Int::set_mod(old_mod);
    return true;
}

array<LL, 2> factor(const LL ord) {
    array<LL, 5> primes = {2, 3, 5, 7, 11};
    LL n = ord;
    LL h = 1;
    for (auto prime : primes) {
        while (n % prime == 0) {
            n /= prime;
            h *= prime;
        }
    }
    if (h > 11) return {0, 0};
    if (is_prime(n)) return {h, n};
    return {0, 0};
}

