#include <algorithm>
#include <iostream>
#include <random>

__uint128_t mod_mult(__uint128_t a, __uint128_t b, __uint128_t m) {
    __uint128_t res = 0;
    a %= m;
    while (b > 0) {
        if (b & 1) {
            res = (res + a) % m;
        }
        a = (2 * a) % m;
        b >>= 1;
    }
    return res;
}

__uint128_t mod_pow(__uint128_t base, __uint128_t exp, __uint128_t mod) {
    __uint128_t res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            res = mod_mult(res, base, mod);
        }
        base = mod_mult(base, base, mod);
        exp >>= 1;
    }
    return res;
}

__uint128_t gcd(__uint128_t a, __uint128_t b) {
    __uint128_t t;
    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}
__int128 extended_gcd(__uint128_t a, __uint128_t b, __int128 &x, __int128 &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    // Rekurencyjne wywołanie: Obliczamy x1, y1 dla (b % a, a)
    __int128 x1, y1;
    __uint128_t g = (__uint128_t)extended_gcd(b % a, a, x1, y1);
    // Aktualizacja x i y na podstawie x1 i y1
    x = y1 - (__int128)(b / a) * x1;
    y = x1;
    return g;
}

__uint128_t mod_inverse(__uint128_t a, __uint128_t mod) {
    __int128 x, y;
    __int128 g = extended_gcd(a, mod, x, y);
    if (g != 1) return 0;
    return (__uint128_t)(x % (__int128)mod + (__int128_t)mod) % (__int128)mod;
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

__uint128_t encrypt(__uint128_t message, __uint128_t key, __uint128_t modulo) {
    return mod_pow(message, key, modulo);
}

//vector with enough witnesses for numbers up to 62 bits
const std::vector<unsigned long long> witnesses = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
};

bool miller_rabin(uint64_t n) {
    if (n < 4) return n == 2 || n == 3;
    if (n % 2 == 0) return false;
    uint64_t d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    for (uint64_t a : witnesses) {
        if (a >= n) break;
        uint64_t x = (uint64_t)mod_pow(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }
        bool composite = true;
        for (int r = 0; r < s - 1; r++) {
            x = (uint64_t)mod_mult(x, x, n);

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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./" << argv[0] << " <message_to_encrypt>" << std::endl;
        return 1;
    }

    const unsigned long long MAX_VALUE = (1ull << 32) -1;
    const unsigned long long MIN_VALUE = (1ull << 31);
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(MIN_VALUE, MAX_VALUE);
    uint64_t prime1 = 0;
    uint64_t prime2 = 0;
    while (true) {
        prime1 = dis(gen);
        prime1 = prime1 | 1;
        if (miller_rabin(prime1)) break;
    }
    while (true) {
        prime2 = dis(gen);
        prime2 = prime2 | 1;
        if (miller_rabin(prime2) && prime2 != prime1) break;
    }
    __uint128_t mod = (__uint128_t)prime1 * (__uint128_t)prime2;
    __uint128_t totient = (__uint128_t)(prime1 - 1) * (__uint128_t)(prime2 - 1);
    //losowanie klucza publicznego
    __uint128_t e = 0;
    while (true) {
        e = dis(gen);
        if (e > 3 && gcd(e, totient) == 1) break;
    }
    __uint128_t d = mod_inverse(e, totient);
    if (d == 0) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    std::cout << "modulo: ";
    print_uint128(mod);
    std::cout << "klucz prywatny: ";
    print_uint128(e);
    std::cout << "klucz publiczny: ";
    print_uint128(d);
    uint64_t message = std::stoi(argv[1]);
    __uint128_t cryptogram = encrypt(message, d, mod);
    std::cout << "cryptogram: ";
    print_uint128(cryptogram);
    cryptogram = encrypt(cryptogram, e, mod);
    std::cout << "cryptogram after decryption: ";
    print_uint128(cryptogram);
    return 0;
}