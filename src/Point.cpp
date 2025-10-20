#include "MathHelper.h"
#include "Int.h"
#include "EC.h"

struct Point {
    Int x;
    Int y;
    bool inf;

    EC& curve;
};

bool operator==(const Point& lhs, const Point& rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.inf == rhs.inf && lhs.curve == rhs.curve);
}

Point operator+(const Point& lhs, const Point& rhs) {
    if (lhs.curve != rhs.curve) throw;
    EC& curve = lhs.curve;

    if (lhs.inf == true) return rhs;
    if (rhs.inf == true) return lhs;

    if (lhs.x == rhs.x && lhs.y + rhs.y == Int(0))
        return {0, 0, true, curve};

    Int alpha;
    if (lhs == rhs)
        alpha = (rhs.y - lhs.y) / (rhs.x - lhs.x);
    else
        alpha = (Int(3) * lhs.x * lhs.x + curve.a) / (Int(2) * lhs.y);

    Int res_x = alpha * alpha - lhs.x - rhs.x;
    return {res_x, alpha * (lhs.x - res_x) - lhs.y, false, curve};
}

void operator+=(Point& lhs, const Point& rhs) {
    Point res = lhs + rhs;
    lhs.x = res.x;
    lhs.y = res.y;
    lhs.inf = res.inf;
}

Point operator*(const LL& scalar, const Point& point) {
    if (point.inf == true) return {0, 0, true, point.curve};

    Point res = {0, 0, true, point.curve}, current = point;
    LL k = scalar;

    while (k > 0) {
        if (k & 1)
            res += current;

        current += current;
        k = k >> 1;
    }

    return res;
}