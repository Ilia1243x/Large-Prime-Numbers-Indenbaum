#pragma once
#include <algorithm>
#include <iostream>
#include <cassert>

namespace lp {
    template <class T>
    T Gcd(T a, T b) {
        assert(a > T(0) && b > T(0) && "Only for positive numbers!");
        while (b != T(0)) {
            a = a % b;
            std::swap(a, b);
        }
        return a;
    }

    template <class T>
    std::pair<T, T> ExtendedGcd(T a, T b) {
        assert(a > T(0) && b > T(0) && "Only for positive numbers!");
        T u[4];
        T v[4];
        u[1] = T(1);
        u[2] = T(0);
        u[3] = a;
        v[1] = T(0);
        v[2] = T(1);
        v[3] = b;
        T q;
        while (v[3] != T(0)) {
            q = u[3] / v[3];
            for (int i = 1; i < 4; i++) {
                T t = v[i];
                v[i] = u[i] - q * v[i];
                u[i] = t;
            }
        }
        return std::make_pair(u[1], u[2]);
    }
}  // namespace lp