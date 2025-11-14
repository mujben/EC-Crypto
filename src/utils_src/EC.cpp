#include <random>
#include "Int.h"
#include "EC.h"

EC::EC(LL a_val, LL b_val, LL modulo)
    : a(a_val, modulo), b(b_val, modulo), p(modulo)
{
    Int delta = Int(4, p) * a * a * a + Int(27, p) * b * b;
    if (delta == (0, p)) {
        throw std::runtime_error("Invalid curve (delta is zero)");
    }
}

void EC::init_random(LL modulo) {
    this->p = modulo;
    this->a = Int(0, modulo); //
    this->b = Int(0, modulo); //

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 255);

    Int delta(0, p);
    do {
        a = Int(dis(gen), p);
        b = Int(dis(gen), p);
        delta = Int(4, p) * a * a * a + Int(27, p) * b * b;
    } while (delta == 0); //
}

EC::EC(const LL modulo) {
    init_random(modulo);
}

EC::EC() {
    init_random(65537);
}

bool operator==(const EC& lhs, const EC& rhs) {
    return lhs.a == rhs.a && lhs.b == rhs.b;
}

bool operator!=(const EC& lhs, const EC& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const EC& curve) {
    os << "----- Curve -----\n";
    os << "a: " << curve.a << ", b: " << curve.b << "\n";
    return os;
}
