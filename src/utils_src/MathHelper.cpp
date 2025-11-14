#include <array>
#include <random>
#include "MathHelper.h"
#include "Int.h"

using namespace std;


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

    for (int i = 0; i < iterations; i++) {
        Int a(random_LL(1, n - 1), n);
        Int x = a.pow(d);
        if (x == 1 || x == (n - 1)) continue;
        bool composite = true;
        for (int r = 0; r < s - 1; r++) {
            x *= x;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) {
            return false;
        }
    }
    return true;
}

array<LL, 2> factor(const LL ord, int MAX_COFACTOR) {
    array<LL, 5> primes = {2, 3, 5, 7, 11};
    LL n = ord;
    LL h = 1;
    for (auto prime : primes) {
        while (n % prime == 0) {
            n /= prime;
            h *= prime;
        }
    }
    if (h > MAX_COFACTOR) return {0, 0};
    if (is_prime(n)) return {h, n};
    return {0, 0};
}

int is_residue(Int a) {
    if (a == 0) return 0;

    const LL modulo = a.get_mod();
    LL exponent = (modulo - 1) / 2;
    Int result = a.pow(exponent);
    if (result == 1) {
        return 1;
    }
    if (result == modulo - 1) {
        return -1;
    }
    return 0;
}