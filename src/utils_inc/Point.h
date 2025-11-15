#ifndef KRYPTO_POINT_H
#define KRYPTO_POINT_H
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
    bool operator==(const Point& rhs);
    bool operator!=(const Point& rhs);

    operator string() const;
};

Point operator*(const LL& scalar, const Point& point);
Point find_generator(const EC &curve, const array<LL, 2>& order);

#endif //KRYPTO_POINT_H
