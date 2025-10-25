#include <iostream>
#include "EC.h"
#include "ECHelper.h"
#include "Int.h"
using namespace std;

int main() {
    const EC curve(65537);
    cout << curve << "\n";
    LL curve_order = find_order(curve);
    cout << "This curve has an order of: " << curve_order << "\n";
}