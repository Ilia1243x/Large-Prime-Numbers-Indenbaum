#pragma once
#include "gcd.h"
#include <algorithm>
#include <vector>
#include <cmath>

namespace lp {
    template <class T>
    T PowMod(T a, T b, T mod) {  // a^b по mod
        if (a == T(0)) {
            return T(0);
        }
        assert(b >= T(0) && "We do not use negative degrees!");
        assert(mod >= T(1) && "We do not use mods smaller than one!");
        if (b == T(0)) {
            return T(1);
        } else if (b % T(2) == T(0)) {
            return PowMod<T>((a % mod * a % mod) % mod, b / T(2), mod) % mod;
        } else {
            return (PowMod<T>(a % mod, b - T(1), mod) % mod * a % mod) % mod;
        }
    }

    template <class T>
    T Pow(T a, T b) {
        assert(b >= T(0) && "We do not use negative degrees!");
        if (b == T(0)) {
            return T(1);
        } else if (b % T(2) == T(0)) {
            return Pow(a * a, b / T(2));
        } else {
            return Pow(a, b - T(1)) * a;
        }
    }
}  // namespace lp