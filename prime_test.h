#pragma once
#include "gcd.h"
#include <vector>
#include <cmath>

namespace lp {
    template <class T>
    bool IsPrime(T n) {
        assert(n > T(0) && "We check only positive numbers!");
        if (n == T(1)) {
            return false;
        }
        for (T i = 2; i * i <= n; ++i) {
            if (n % i == T(0)) {
                return false;
            }
        }
        return true;
    }
}  // namespace lp
