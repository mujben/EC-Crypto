#include <iostream>
#include <random>

struct Point {
    int x;
    int y;
    bool inf;
};

int extended_gcd(const int a, const int b, int &x, int &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    // Rekurencyjne wywołanie: obliczenie x1, y1 dla (b % a, a)
    int x1, y1;
    int g = extended_gcd(b % a, a, x1, y1);
    // Aktualizacja x i y na podstawie x1 i y1
    x = y1 - (b / a) * x1;
    y = x1;
    return g;
}

int mod_inverse(const int a, const int mod) {
    int x, y;
    int g = extended_gcd(a, mod, x, y);
    if (g != 1) return 0;
    return (x % mod + mod) % mod;
}

int mod_mult(int a, int b, const int mod) {
    int result = 0;
    a %= mod;
    while (b) {
        //b jest nieparzyste - ostatni bit wynosi 1
        if (b & 1) {
            result = (result + a) % mod;
        }
        b = b >> 1;
        a = (2 * a) % mod;
    }
    return result;
}

Point point_add(const Point a, const Point b, const int mod, const int curve_param_a) {
    //1. A == INF_POINT || B == INF_POINT
    if (a.inf == true) return b;
    if (b.inf == true) return a;
    //2. P + Q = INF_POINT
    if (a.x == b.x && (a.y + b.y) % mod == 0) {
        return {0, 0, true};
    }
    int alpha;
    //3. P == Q
    if (a.x == b.x && a.y == b.y) {
        alpha = ((3 * mod_mult(a.x, a.x, mod) % mod + curve_param_a) * mod_inverse(2*a.y, mod)) % mod;
    }
    //4. P != Q
    else {
        alpha = ((b.y - a.y + mod) * mod_inverse((b.x - a.x + mod), mod)) % mod;
    }
    Point c = {0, 0, false};
    c.x = (mod_mult(alpha, alpha, mod) - a.x + mod - b.x + mod) % mod;
    c.y = (mod_mult(alpha, (a.x - c.x + mod), mod) - a.y + mod) % mod;
    return c;
}

Point scalar_mult(const Point a, const int scalar, const int mod, const int curve_param_a) {
    if (a.inf == true) return {0, 0, true};
    Point result = {0, 0, true};
    Point current = a;
    //praca na kopii skalara dla bezpieczeństwa
    int k = scalar;
    //szybkie mnożenie metodą podwajania i dodawania
    while (k > 0) {
        if (k & 1) {
            result = point_add(result, current, mod, curve_param_a);
        }
        current = point_add(current, current, mod, curve_param_a);
        k = k >> 1;
    }
    return result;
}

//algorytm schoofa
// int schoofs(int prime, const int curve_param_a, const int curve_param_b) {
//
// }

int main() {
    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::uniform_int_distribution<int> dis(0, 255);
    // int p = 65537;
    // int a, b;
    // long delta = 0;
    // do {
    //     a = dis(gen);
    //     b = dis(gen);
    //     delta = 4 * pow(a, 3) + 27*pow(b, 2);
    // } while (delta % p != 0);
    // std::cout << "a: " << a << "\nb: " << b << std::endl;
}