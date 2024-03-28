#pragma once
#include "gcd.h"
#include <algorithm>
#include <vector>
#include <cmath>
#include "usings.h"

namespace lp {
template <class T>
OverflowType<T> PowMod(OverflowType<T> a, OverflowType<T> b, OverflowType<T> mod) {  // a^b по mod
    assert(b >= T(0) && "We do not use negative degrees!");
    assert(mod > T(1) && "We use mods bigger than one!");
    T result = T(1);
    while (b > T(0)) {
        if (b % T(2) == T(1)) {
            result = ((result % mod) * (a % mod)) % mod;
        }
        b = b / T(2);
        a = ((a % mod) * (a % mod)) % mod;
    }
    return result;
}

template <class T>
OverflowType<T> Pow(T  a, T  b) {
    assert(b >= OverflowType<T>(0) && "We do not use negative degrees!");
    OverflowType<T> result = OverflowType<T>(1);
    while (b > OverflowType<T>(0)) {
        if (b % OverflowType<T>(2) == OverflowType<T>(1)) {
            result = result * a;
        }
        b = b / OverflowType<T>(2);
        a = a * a;
    }
    return result;
}
}  // namespace lp
