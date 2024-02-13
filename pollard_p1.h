#pragma once
#include "pollard_ro.h"

namespace lp {

namespace details {
constexpr int MaxPow = 10000;
constexpr int RandomRangeP = 1000;
template <class T>
T ComputeFactorP(T c, T number) {
    T g = Gcd(c, number);
    if (g > 1) {
        return g;
    }
    T cin_pow = c;
    for (int i = 1; i <= MaxPow; ++i) {
        T tmp = PowMod<T>(cin_pow, i, number);
        if (tmp == 0) {
            return Gcd(cin_pow, number);
        }
        cin_pow = tmp;
        if (cin_pow > 1 && i % ProductSize == 0) {
            g = Gcd(cin_pow - T(1), number);
            if (g == number) {
                return T(0);
            }
            if (g > 1) {
                return g;
            }
        }
    }
    return T(0);
}
}  // namespace details
template <class T>
std::vector<T> FactorizeP(T number) {
    assert(number > T(0) && "Only positive numbers!");
    std::vector<T> res;
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distribution(2, details::RandomRangeP);
    T copy = number;
    while (copy != T(1)) {
        T c = T(distribution(eng));
        T g = details::ComputeFactorP(c, number);
        while (g != T(0) && g != number && copy % g == T(0)) {
            // std::cout<<g<<" ";
            copy = copy / g;
            res.emplace_back(g);
        }
    }
    return res;
}
}  // namespace lp