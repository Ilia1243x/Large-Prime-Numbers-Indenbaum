#pragma once
#include "gcd.h"
#include "sqrt.h"
#include <vector>
#include <cmath>

namespace lp {
template <class T>
std::vector<T> PrimitiveFactorization(T n) {
    assert(n > T(0) && "Only for positive numbers!");
    if (n == T(1)) {
        return {T(1)};
    }
    T n1 = n;
    T sqrt_of_n = Sqrt<T>(n);
    std::vector<T> ans;
    for (T i = 2; i <= sqrt_of_n; ++i) {
        if (n1 < i) {
            break;
        }
        while (n1 % i == T(0) && n1 >= i) {
            ans.emplace_back(i);
            n1 /= i;
        }
    }
    if (n1 != T(1)) {
        ans.emplace_back(n1);
    }
    return ans;
}

namespace details {
template <class T>
void Factorize(T x, std::vector<T> &factors) {
    while (x % T(2) == T(0)) {
        factors.emplace_back(T(2));
        x = x / T(2);
    }
    T sqrt_of_x = Sqrt<T>(x);
    T u = 2 * sqrt_of_x + T(1);
    T v = 1;
    T r = sqrt_of_x * sqrt_of_x - x;
    while (r != T(0)) {
        if (r > T(0)) {
            while (r > T(0)) {
                r -= v;
                v += T(2);
            }

        } else {
            r += u;
            u += T(2);
        }
    }
    T a = u + v - T(2);
    a = a / T(2);
    T b = u - v;
    b = b / T(2);
    if (a == x) {
        if (a != T(1)) {
            factors.emplace_back(a);
        }
        if (b != T(1)) {
            factors.emplace_back(b);
        }
    } else {
        Factorize(a, factors);
        Factorize(b, factors);
    }
}
}  // namespace details

template <class T>
std::vector<T> FermatFactorization(T x) {
    assert(x > T(0) && "Only for positive numbers!");
    if (x == T(1)) {
        return {T(1)};
    }
    std::vector<T> res;
    details::Factorize<T>(x, res);
    return res;
}
}  // namespace lp
