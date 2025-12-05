#ifndef KRYPTO_POINT_H
#define KRYPTO_POINT_H
#include <functional>
#include "Int.h"
#include "EC.h"

struct Point {
    Int x;
    Int y;
    bool inf;
    const EC& curve;

    Point(const EC& curve);
    Point(Int x, Int y, bool inf, const EC& curve);
    Point(const string& xy, const EC& curve);

    Point& operator=(const Point& rhs);
    Point operator-() const;
    Point operator+(const Point& rhs);
    void operator+=(const Point& rhs);
    bool operator==(const Point& rhs) const;
    bool operator!=(const Point& rhs) const;

    operator string() const;
};

Point operator*(const LL& scalar, const Point& point);
Point find_generator(const EC &curve, const array<LL, 2>& order);

template<> struct std::hash<Point> {
    size_t operator()(const Point& p) const noexcept {
        if (p.inf) return std::hash<bool>{}(true);

        const size_t hash_x = std::hash<LL>{}(LL(p.x));
        const size_t hash_y = std::hash<LL>{}(LL(p.y));

        size_t seed = 0;
        seed ^= hash_x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= hash_y + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

#endif //KRYPTO_POINT_H
