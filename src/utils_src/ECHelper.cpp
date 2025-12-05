#include <unordered_map>
#include <cmath>
#include "ECHelper.h"
#include "MathHelper.h"

LL find_order(const EC &curve) {
    //brute-force algorithm
    //O(p)
    LL order = 1;
    const LL p = curve.p;
    for (LL x = 0; x < p; x++) {
        Int x_int(x, p);
        Int res_y = x_int.pow(3) + curve.a * x_int + curve.b;
        int status = is_residue(res_y);
        if (status == 1) order += 2;
        else if (status == 0) order += 1;
    }
    return order;
}

LL find_order_bsgs(const EC &curve) {
    //baby steps giant steps algorithm
    //O(p^1/4)
    const LL p = curve.p;
    const LL s = ceil(std::pow(p, 1/4));

    LL i, j = 0;
    bool found = false;

    do{
        const Point P = pick_random_point(curve);
        const auto ZERO = Point(curve);

        std::unordered_map<Point, LL> points_hashmap;
        Point P_current = P;

        //baby steps: calculate hash map of points 0, +-P, +-2P, ..., +-sP
        points_hashmap[ZERO] = 0;
        for (i = 1; i <= s; i++) {
            points_hashmap[P_current] = i;
            points_hashmap[-P_current] = -i;
            P_current += P;
        }

        //giant steps: repeatedly add and subtract the point Q to compute R, R +- Q, ..., R +- tQ
        Point Q = (2 * s + 1) * P;
        Point R = (p + 1) * P;
        const LL t = static_cast<LL> (2 * ceil(std::sqrt(p)) / (2 * s + 1));

        for (i = 0; i <= t; i++) {
            Point res_pos = R + i * Q;
            if (points_hashmap.contains(res_pos)) {
                j = points_hashmap.at(res_pos);
                found = true;
                break;
            }
            Point res_neg = R + (-i * Q);
            if (points_hashmap.contains(res_neg)) {
                j = points_hashmap.at(res_neg);
                i = -i;
                found = true;
                break;
            }
        }
    }while (!found);

    const LL m = p + 1 + (2 * s + 1) * i - j;
    return m;
}

Point pick_random_point(const EC &curve) {
    const LL mod = curve.p;
    LL value = mod % 4;
    while (true) {
        Int x(random_LL(0, mod - 1), mod);
        Int y_sq = x.pow(3) + curve.a * x + curve.b;
        Int euler_criterion = y_sq.pow(LL((mod - 1) / 2));
        if (euler_criterion == 1) {
            if (value == 3) {
                Int y = y_sq.pow(LL((mod + 1) / 4));
                return {x, y, false, curve};
            }
            if (value == 1) {
                Int y = find_root_mod(y_sq);
                return {x, y, false, curve};
            }
        }
        else if (euler_criterion == 0) {
            return {x, Int(0, mod), false, curve};
        }
    }
}

Int find_root_mod(const Int value) {
    const LL mod = value.get_mod();
    if (value == 0) return Int(0, mod);
    if (value.pow(LL(mod - 1) / 2) != 1) return Int(-1, mod);

    Int z(0, mod);
    do {
        z = Int(random_LL(1, mod - 1), mod);
    } while (z.pow(LL(mod - 1) / 2) != (mod - 1));

    LL Q = mod - 1;
    LL s = 0;
    while ((Q & 1) == 0) {
        Q >>= 1;
        s++;
    }

    LL M = s;
    Int c = z.pow(Q);
    Int t = value.pow(Q);
    Int R = value.pow(LL(Q + 1) / 2);
    while (t != 1) {
        LL i = 1;
        Int t_temp = t;
        while (i <= M) {
            t_temp = t_temp * t_temp;
            if (i == M) return Int(-1, mod);
            if (t_temp == 1) break;
            i++;
        }
        Int b = c;
        LL exp = M - i - 1;
        while (exp > 0) {
            b = b * b;
            exp--;
        }
        M = i;
        c = b * b;
        t = t * c;
        R = R * b;
    }
    return R;
}
