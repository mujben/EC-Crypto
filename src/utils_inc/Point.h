#ifndef KRYPTO_POINT_H
#define KRYPTO_POINT_H
#include "Int.h"
#include "EC.h"

struct Point {
    Int x;
    Int y;
    bool inf;

    const EC& curve;
};

bool operator==(const Point& lhs, const Point& rhs);

Point operator+(const Point& lhs, const Point& rhs);

void operator+=(Point& lhs, const Point& rhs);

Point operator*(const LL& scalar, const Point& point);

#endif //KRYPTO_POINT_H
