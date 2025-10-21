#include "Int.h"
#include "EC.h"

int is_residue(Int a) {
    if (a == Int(0)) return 0;

    const LL modulo = Int::get_mod();
    LL exponent = (modulo - 1) / 2;
    Int result = a.pow(exponent);
    if (result == Int(1)) {
        return 1;
    }
    if (result == Int(modulo - 1) || result == Int(-1)) {
        return -1;
    }
    return 0;
}

LL find_order(const EC &curve) {
    /*
        *---------------------------------------------------------------------------*
        *   This function is able to calculate order of an Elliptic curve group     *
        *   for modulo values up to 24 bits in under 10 sec.                        *
        *   For 26-bit modulo values it takes around 1 min to calculate an order.   *
        *---------------------------------------------------------------------------*
        *   ps. for square residue see the last page of WZMW lecture
    */
    LL order = 1;   //remember about the point in infinity
    const LL mod = Int::get_mod();
    for (LL x = 0; x < mod; x++) {
        Int res_y = Int(x).pow(3) + curve.a * Int(x) + curve.b;
        int status = is_residue(res_y);
        if (status == 1) order += 2;
        else if (status == 0) order += 1;
    }
    return order;
}