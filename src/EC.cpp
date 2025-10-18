#pragma once
#include <random>
#include <iostream>
#include "Int.cpp"

using namespace std;

struct EC {
    Int a;
    Int b;

    EC() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(1, 255);
        Int::set_mod(65537);
        Int delta = 0;
        do {
            a = dis(gen);
            b = dis(gen);
            delta = Int(4) * a * a * a + Int(27) * b * b;
        } while (delta != Int(0));
    }
};

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