#include "crypto++/rsa.h"
#include <iostream>
#include <random>
// #include <boost/multiprecision/cpp_int.hpp>

__uint128_t gcd(__uint128_t a, __uint128_t b) {
    __uint128_t t;
    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}
//fast modular multiplication for 128-bit numbers
__uint128_t mod_mult(__uint128_t a, __uint128_t b, const __uint128_t mod) {
    __uint128_t result = 0;
    a %= mod;
    while (b > 0) {
        if (b & 1) {
            result += a;
            if (result >= mod) result -= mod;
        }
        a = (a << 1);
        if (a >= mod) a -= mod;
        b >>= 1;
    }
    return result;
}

__uint128_t mod_pow(__uint128_t base, __uint128_t exp, __uint128_t mod) {
    __uint128_t result = 1;
    base %= mod;
    while (exp > 0) {
        //bit comparison
        if (exp & 1) result = mod_mult(result, base, mod);
        base = mod_mult(base, base, mod);
        exp >>= 1;
    }
    return result;
}

__uint128_t random_uint128(std::mt19937_64 &gen) {
    std::uniform_int_distribution<uint64_t> dis;
    __uint128_t low = dis(gen);
    __uint128_t high = dis(gen);
    return (high << 64) | low;
}

bool miller_rabin(__uint128_t n, int iterations = 10) {
    if (n < 4) return n == 2 || n == 3;
    if (n % 2 == 0) return false;
    __uint128_t d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    std::random_device rd;
    std::mt19937_64 gen(rd());
    for (int i = 0; i < iterations; i++) {
        __uint128_t a = 2 + (random_uint128(gen) % (n - 3));
        __uint128_t x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 0; r < s - 1; r++) {
            x = mod_mult(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

void print_uint128(__uint128_t x) {
    if (x == 0) std::cout << "0" << std::endl;
    std::string number;
    while (x > 0) {
        number.push_back('0' + (char)(x % 10));
        x /= 10;
    }
    std::reverse(number.begin(), number.end());
    std::cout << number << std::endl;
}

int main(int argc, char *argv[]) {
    //to start with basics - generation of two "large" prime numbers
    std::random_device rd;
    std::mt19937_64 gen(rd());
    const __uint128_t min = ((__uint128_t)1 << 128) - 1;
    const __uint128_t range = min;  //max - min = (2^128 - 1) - 2^127 = 2^127 - 1
    //generating 2 large prime numbers
    __uint128_t prime1 = 0;
    __uint128_t prime2 = 0;
    int prime_count = 0;
    std::cout << "Generating prime numbers, please wait..." << std::endl;
    while (prime_count < 2) {
        __uint128_t candidate = min + (random_uint128(gen) % range);
        //candidate has to be odd
        candidate = candidate | 1;
        if (miller_rabin(candidate)) {
            if (prime_count == 0) prime1 = candidate;
            else prime2 = candidate;
            prime_count++;
        }
    }
    // print_uint128(prime1);
    // std::cout << std::endl;
    // print_uint128(prime2);

    //generating number n = prime1 * prime2
    __uint128_t n = prime1 * prime2;
    __uint128_t phi = (prime1 - 1) * (prime2 - 1);
    __uint128_t p = 1;
    do {
        p = random_uint128(gen) % phi;
    } while (gcd(p, phi) != 1);

    return 0;
}