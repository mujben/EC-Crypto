#include "ECHelper.h"
#include "MathHelper.h"

LL find_order(const EC &curve) {
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

Point pick_random_point(const EC &curve) {
    const LL mod = curve.p;
    LL value = mod % 4;
    while (true) {
        Int x(random_LL(0, mod - 1), mod);
        Int y_sq = x.pow(3) + curve.a * x + curve.b;
        Int euler_cryterium = y_sq.pow(LL((mod - 1) / 2));
        if (euler_cryterium == 1) {
            if (value == 3) {
                Int y = y_sq.pow(LL((mod + 1) / 4));
                return {x, y, false, curve};
            }
            if (value == 1) {
                Int y = find_root_mod(y_sq);
                return {x, y, false, curve};
            }
        }
        else if (euler_cryterium == 0) {
            return {x, Int(0, mod), false, curve};
        }
    }
}
