#pragma once

#include <random>
#include <vector>
#include "powers.h"
#include "gauss.h"
#include "sqrt.h"
#include "eratosthene_sieve.h"
#include "strong_pseudoprime_test.h"
#include "legendre_symbol.h"

namespace lp {
namespace details_qs {
constexpr size_t FactorBaseBorder = 560;
constexpr int Diametr = 300000;
template <class T>

T ComputeResFactor(T final_f_r, T final_r, T n) {
    if (final_r == final_f_r) {
        return T(1);
    }
    T res = final_f_r - final_r;
    if (res > T(0)) {
        return Gcd(res, n);
    }
    res = res * -1;
    return Gcd(res, n);
}

template <class T>
std::vector<int> SureFactorize(T n, const std::vector<size_t> &factor_base) {
    assert(n > T(1) && "Only for positive numbers!");
    std::vector<int> factors(factor_base.size(), 0);
    for (int i = 0; i < factor_base.size(); ++i) {
        T k = 0;
        while (n % factor_base[i] == T(0)) {
            n = n / factor_base[i];
            ++k;
        }
        if (k % 2 == T(1)) {
            factors[i] = 1;
        } else {
            factors[i] = 0;
        }
    }
    return factors;
}

template <class T>
T TryGetFactor(T n) {
    assert(n > T(1) && "Only for positive numbers!");
    std::vector<size_t> pre_factor_base = FindPrimes(3, FactorBaseBorder);
    std::vector<size_t> factor_base = {2};
    for (auto p : pre_factor_base) {
        auto z = LegendreSymbol<T>(n, p);
        if (z.GetSymbol() == 1) {
            factor_base.emplace_back(p);
        }
    }
    std::vector<T> vector_of_r;
    std::vector<T> candidates;
    T r = Sqrt<T>(n);
    for (int i = 0; i <= Diametr; ++i) {
        // T f_r = (r+T(i))*(r+T(i)) - n;
        T f_r = PowMod<T>(r + T(i), 2, n);
        if (f_r == T(0)) {
            continue;
            return Gcd(r + T(i), n);
        }
        vector_of_r.emplace_back(r + T(i));
        candidates.emplace_back(f_r);
    }
    std::vector<std::vector<int>> matrix;
    for (const auto &x : factor_base) {
        for (int i = 0; i < candidates.size(); ++i) {
            while (candidates[i] % x == 0) {
                candidates[i] = candidates[i] / x;
            }
        }
    }
    std::vector<T> contrib_r;
    for (int i = 0; i < candidates.size(); ++i) {
        if (candidates[i] == 1) {
            // T f_r_i = vector_of_r[i]*vector_of_r[i] - n;
            T f_r_i = PowMod<T>(vector_of_r[i], 2, n);
            if (f_r_i == 1) {
                continue;
            }
            std::vector<int> factorization = SureFactorize(f_r_i, factor_base);
            contrib_r.emplace_back(vector_of_r[i]);
            matrix.emplace_back(factorization);
        }
    }
    T res_factor = T(1);
    while (res_factor == T(1) || res_factor == n) {
        std::vector<int> contrib_f_r = Gaus(matrix);
        if (contrib_f_r[0] == -1) {
            return -1;
        }
        /* for (auto x: matrix){
             for (auto y: x){
                 std::cout << y << " ";
             }std::cout << '\n';
         }*/
        T final_f_r = 1;
        T final_r = 1;
        for (const auto &index_of_r : contrib_f_r) {
            T f_r = PowMod<T>(contrib_r[index_of_r], 2, n);
            final_f_r = final_f_r * f_r;
            final_r = final_r * Sqrt<T>(contrib_r[index_of_r]);
        }
        res_factor = ComputeResFactor(final_f_r, final_r, n);
    }
    return res_factor;
}

template <class T>
void FactorizeBS(T n, std::vector<T> &factors) {
    if (n == T(1)) {
        return;
    }
    lp::StrongPseudoPrime<T> test_prime(n);
    bool test_1 = test_prime.ProbabilisticTest();
    bool test_2 = test_prime.ProbabilisticTest();
    if (test_1 && test_2) {
        factors.emplace_back(n);
        return;
    }
    T factor = TryGetFactor(n);
    FactorizeBS(factor, factors);
    FactorizeBS(n / factor, factors);
}

}  // namespace details_qs
template <class T>
std::vector<T> BSFactorization(T n) {
    assert(n > T(1) && "Only for numbers bigger than one!");
    std::vector<T> res = {1};
    details_qs::FactorizeBS(n, res);
    return res;
}

template <class T>
T FacBS(T n) {
    T res = details_qs::TryGetFactor(n);
    return res;
}

}  // namespace lp
