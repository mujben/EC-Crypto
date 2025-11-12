#include <iostream>
#include <array>
#include <chrono>
#include "EC.h"
#include "ECHelper.h"
#include "Int.h"
#include "Point.h"
#include "MathHelper.h"
using namespace std;

int main() {
    const LL p = 65537;
    EC curve(p);
    LL curve_order = 0;
    array<LL, 2> factored{};

    int tries = 1;
    chrono::steady_clock::time_point curve_begin = chrono::steady_clock::now();
    while (factored[0] == 0) {
        curve = EC(p);
        curve_order = find_order(curve);
        factored = factor(curve_order);
        tries++;
    }
    chrono::steady_clock::time_point curve_end = chrono::steady_clock::now();

    chrono::steady_clock::time_point generator_begin = chrono::steady_clock::now();
    const Point g = find_generator(curve, factored);
    chrono::steady_clock::time_point generator_end = chrono::steady_clock::now();

    cout << curve << "\n";
    cout << "This curve has an order of: " << curve_order << " = h * n\n";
    cout << "h: " << factored[0] << "\nn: " << factored[1] << "\n";
    cout << "Time taken to choose a good curve: " << chrono::duration_cast<chrono::milliseconds>(curve_end - curve_begin).count() << " milliseconds " << "(in " << tries << " tries)\n";
    cout << "Generator point chosen: (" << g.x << ", " << g.y << ")\n";
    cout << "Time taken to choose generator: " << chrono::duration_cast<chrono::microseconds>(generator_end - generator_begin).count() << " microseconds\n";
    return 0;
}