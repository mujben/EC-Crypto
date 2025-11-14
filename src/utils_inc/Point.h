#ifndef KRYPTO_POINT_H
#define KRYPTO_POINT_H
#include "Int.h"
#include "EC.h"

struct Point {
    Int x;
    Int y;
    bool inf;

    const EC& curve;

    Point(const EC& curve) : x((0), curve.p), y((0), curve.p), inf(true), curve(curve) {};
    Point(Int x, Int y, bool inf, const EC& curve) : x(x), y(y), inf(inf), curve(curve) {};

    Point& operator=(const Point& rhs) {
        if (this == &rhs) return *this;
        if (this->curve != rhs.curve) throw std::runtime_error("Curve mismatch");
        this->x = rhs.x;
        this->y = rhs.y;
        this->inf = rhs.inf;
        return *this;
    }

    Point operator-() const;
};

bool operator==(const Point& lhs, const Point& rhs);

Point operator+(const Point& lhs, const Point& rhs);

void operator+=(Point& lhs, const Point& rhs);

Point operator*(const LL& scalar, const Point& point);

Point find_generator(const EC &curve, const std::array<LL, 2>& order);

#endif //KRYPTO_POINT_H