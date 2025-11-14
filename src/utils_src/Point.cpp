#include <array>
#include <stdexcept>
#include "Int.h"
#include "EC.h"
#include "Point.h"
#include "ECHelper.h"

bool operator==(const Point& lhs, const Point& rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.inf == rhs.inf && lhs.curve == rhs.curve);
}

Point operator+(const Point& lhs, const Point& rhs) {
    if (lhs.curve != rhs.curve) throw std::runtime_error("Curve mismatch");
    const EC& curve = lhs.curve;

    if (lhs.inf == true) return rhs;
    if (rhs.inf == true) return lhs;

    const LL p = lhs.curve.p;

    if (lhs.x == rhs.x && lhs.y + rhs.y == Int(0, p))
        return {lhs.curve};

    Int alpha;
    if (lhs == rhs)
        alpha = (Int(3, p) * lhs.x * lhs.x + lhs.curve.a) / (Int(2, p) * lhs.y);
    else
        alpha = (rhs.y - lhs.y) / (rhs.x - lhs.x);

    Int res_x = alpha * alpha - lhs.x - rhs.x;
    return {res_x, alpha * (lhs.x - res_x) - lhs.y, false, lhs.curve};
}

void operator+=(Point& lhs, const Point& rhs) {
    Point res = lhs + rhs;
    lhs.x = res.x;
    lhs.y = res.y;
    lhs.inf = res.inf;
}
Point Point::operator-() const {
    return {this->x, -this->y, this->inf, this->curve};
}

Point operator*(const LL& scalar, const Point& point) {

    if (point.inf == true) {
        return Point(point.curve);
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

Point find_generator(const EC &curve, const std::array<LL, 2> &order) {
    const LL h = order[0];
    while (true){
        Point P = pick_random_point(curve);
        Point G = h * P;
        if (G.inf == false) return G;
    }
}