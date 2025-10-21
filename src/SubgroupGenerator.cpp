#include <random>
#include "MathHelper.h"
#include "Int.h"
#include "Point.h"
#include "EC.h"

Int find_root_mod(const Int value) {
    const LL mod = Int::get_mod();
    if (value == Int(0)) return 0;
    if (value.pow(LL(mod - 1) / 2) != Int(1)) return -1;
    // finding non-residue z
    Int z;
    do {
        z = random_LL(1, mod - 1);
    }while (z.pow(LL(mod - 1) / 2) != Int(mod - 1) /*|| z.pow(LL((mod - 1) / 2)) != Int(-1)*/);
    // p - 1 = Q2^S
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
    while (t != Int(1)) {
        LL i = 1;
        Int t_temp = t;
        while (i <= M) {
            t_temp = t_temp * t_temp;
            if (i == M) return -1;
            if (t_temp == Int(1)) break;
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

Point pick_random_point(const EC &curve) {
    const LL mod = Int::get_mod();
    int value = mod % 4; // possible values: 1, 3 <- we want this
    while (true) {
        Int x(random_LL(0, mod - 1));
        Int y_sq = x.pow(3) + curve.a * x + curve.b;
        Int euler_cryterium = y_sq.pow(LL((mod - 1) / 2));
        if (euler_cryterium == Int(1)) {
            if (value == 3) {
                Int y = y_sq.pow(LL((mod + 1) / 4));
                return {x, y, false, curve};
            }
            if (value == 1) {
                Int y = find_root_mod(y_sq);
                return {x, y, false, curve};
            }
        }
        else if (euler_cryterium == Int(0)) {
            return {x, 0, false, curve};
        }
    }
}