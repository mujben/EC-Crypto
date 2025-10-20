#include <random>
#include "Int.h"
#include "EC.h"

EC::EC(const LL modulo) {
    Int::set_mod(modulo);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 255);
    Int delta = 0;
    do {
        a = dis(gen);
        b = dis(gen);
        delta = Int(4) * a * a * a + Int(27) * b * b;
    } while (delta == Int(0));
}

EC::EC() : EC(65537) {};