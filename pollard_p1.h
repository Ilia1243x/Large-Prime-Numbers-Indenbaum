#pragma once

#include "pollard_ro.h"
#include "strong_pseudoprime_test.h"

namespace lp {

namespace details {
constexpr int MaxPow = 10000;
constexpr int RandomRangeP = 10000;

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

template <class T>
T FindFactorP(T number) {
    assert(number > T(0) && "Only positive numbers!");
    static std::random_device rd;
    static std::mt19937 eng(rd());
    std::uniform_int_distribution<> distribution(2, RandomRangeP);
    T g = T(0);
    while (g == T(0) || g == number) {
        T c = T(distribution(eng));
        g = details::ComputeFactorP(c, number);
    }
    return g;
}

template <class T>
void DoFactorizeP(T number, std::vector<T> &factors) {
    assert(number > T(0) && "Only positive numbers!");
    if (number == T(1)) {
        return;
    }
    lp::StrongPseudoPrime<T> test_prime(number);
    bool test_1 = test_prime.ProbabilisticTest();
    bool test_2 = test_prime.ProbabilisticTest();
    if (test_1 && test_2) {
        factors.emplace_back(number);
        return;
    }
    T factor = FindFactorP(number);
    DoFactorizeP(factor, factors);
    DoFactorizeP(T(number / factor), factors);
}
}  // namespace details
template <class T>
std::vector<T> FactorizeP(T number) {
    std::vector<T> factors = {T(1)};
    details::DoFactorizeP(number, factors);
    return factors;
}
}  // namespace lp
