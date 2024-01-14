#pragma once
#include <vector>
#include <cmath>
#include "powers.h"

namespace lp {
    template <class T>
    bool IsMersPrime(T n) {
        assert(n % T(2) == T(1) && n >= T(3) && "Algo only for odd n no smaller than 3!");
        T m = Pow(T(2), n) - T(1);
        T s = 4;
        for (T i = 2; i < n; ++i) {
            s = (s * s - T(2)) % m;
        }
        if (s == T(0)) {
            return true;
        }
        return false;
    }
}  // namespace lp