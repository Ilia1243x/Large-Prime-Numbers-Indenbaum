#pragma once
#include <random>
#include <vector>
#include "powers.h"
#include "strong_pseudoprime_test.h"

namespace lp {
namespace details {
constexpr int MaxCycles = 1000;
constexpr int ProductSize = 10;
constexpr int RandomRange = 1000;
template <class T>
T ComputeAbsDif(T x1, T x2) {
    if (x1 >= x2) {
        return x1 - x2;
    }
    return x2 - x1;
}
template <class T>
T ComputeFactor(T x1, T c, T number) {
    T x2 = ((x1 % number) * (x1 % number) + (c % number)) % number;
    T range = 1;
    T product = 1;
    int terms = 0;
    while (terms < MaxCycles) {
        for (T i = 1; i <= range; ++i) {
            ++terms;
            x2 = (x2 * x2 + c) % number;
            if (x2 != x1) {
                product = (product * ComputeAbsDif(x1, x2)) % number;
            }
            if (product == T(0)) {
                T g = Gcd(number, ComputeAbsDif(x1, x2));
                if (g > 1) {
                    return g;
                }
            }
            if (terms % ProductSize == 0) {
                T g = Gcd(number, product);
                if (g > 1) {
                    return g;
                }
            }
        }
        product = 1;
        x1 = x2;
        range = range * 2;
        for (T i = 1; i <= range; ++i) {
            x2 = (x2 * x2 + c) % number;
        }
    }
    return T(0);
}

template <class T>
T FindFactorRo(T number) {
    assert(number > T(0) && "Only positive numbers!");
    static std::random_device rd;
    static std::mt19937 eng(rd());
    std::uniform_int_distribution<> distribution(2, details::RandomRange);
    T g = T(0);
    while (g == T(0) || g == number) {
        T x1 = T(distribution(eng));
        T c = T(distribution(eng));
        g = details::ComputeFactor(x1, c, number);
    }
    return g;
}

template <class T>
void DoFactorizeRo(T number, std::vector<T> &factors) {
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
    T factor = FindFactorRo(number);
    DoFactorizeRo(factor, factors);
    DoFactorizeRo(T(number / factor), factors);
}
}  // namespace details
template <class T>
std::vector<T> FactorizeRo(T number) {
    std::vector<T> factors = {T(1)};
    while (number % T(2) == 0) {
        number = number / T(2);
        factors.emplace_back(2);
    }
    details::DoFactorizeRo(number, factors);
    return factors;
}

}  // namespace lp
