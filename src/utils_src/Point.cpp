#include <array>
#include <stdexcept>
#include "Int.h"
#include "EC.h"
#include "Point.h"
#include "ECHelper.h"

#define CURVE_CHECK(op) if (this->curve != rhs.curve) \
{ throw runtime_error("Curve mismatch in Point::operator" #op); }

Point::Point(const EC& curve) : x((0), curve.p), y((0), curve.p), inf(true), curve(curve) {};

Point::Point(Int x, Int y, bool inf, const EC& curve) : x(x), y(y), inf(inf), curve(curve) {};

Point& Point::operator=(const Point& rhs) {
    CURVE_CHECK(=);
    if (this == &rhs) return *this;
    this->x = rhs.x;
    this->y = rhs.y;
    this->inf = rhs.inf;
    return *this;
}

Point Point::operator-() const {
    return {this->x, -this->y, this->inf, this->curve};
}

Point Point::operator+(const Point& rhs) {
    CURVE_CHECK(+);

    if (this->inf == true) return rhs;
    if (rhs.inf == true) return *this;

    const LL p = this->curve.p;

    if (this->x == rhs.x && this->y + rhs.y == Int(0, p))
        return {this->curve};

    Int alpha;
    if (*this == rhs)
        alpha = (Int(3, p) * this->x * this->x + this->curve.a) / (Int(2, p) * this->y);
    else
        alpha = (rhs.y - this->y) / (rhs.x - this->x);

    Int res_x = alpha * alpha - this->x - rhs.x;
    return {res_x, alpha * (this->x - res_x) - this->y, false, this->curve};
}

void Point::operator+=(const Point& rhs) {
    CURVE_CHECK(+=);
    Point res = *this + rhs;
    this->x = res.x;
    this->y = res.y;
    this->inf = res.inf;
}

bool Point::operator==(const Point& rhs) {
    return (this->x == rhs.x && this->y == rhs.y && this->inf == rhs.inf && this->curve == rhs.curve);
}

bool Point::operator!=(const Point& rhs) {
    return !(*this == rhs);
}

Point operator*(const LL& scalar, const Point& point) {
    if (point.inf == true) {
        return {point.curve};
    }

    LL k = scalar;
    Point current = point;

    if (k < 0) {
        current = -current;
        k = -k;
    }

    Point res(point.curve);

    while (k > 0) {
        if (k & 1) { // if (k is odd)
            res += current; // add
        }
        current += current; // double
        k = k >> 1;         // k = k / 2
    }

    return res;
}

Point find_generator(const EC &curve, const array<LL, 2> &order) {
    const LL h = order[0];
    while (true){
        Point P = pick_random_point(curve);
        Point G = h * P;
        if (G.inf == false) return G;
    }
}
