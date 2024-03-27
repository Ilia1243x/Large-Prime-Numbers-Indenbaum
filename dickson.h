#pragma once

#include <random>
#include <vector>
#include "powers.h"
#include "gauss.h"
#include "sqrt.h"
#include "eratosthene_sieve.h"
#include "strong_pseudoprime_test.h"

namespace lp {
namespace details {
constexpr size_t MaxFuncArg = 10000;
constexpr size_t FactorBaseBorder = 2000;

template <class T>
std::vector<int> TryFactorize(T n) {
    assert(n >= T(0) && "Only for positive numbers!");
    std::vector<size_t> factor_base = FindPrimes(2, FactorBaseBorder);
    std::vector<int> factors(factor_base.size(), 0);
    for (int i = 0; i < factor_base.size(); ++i) {
        T k = 0;
        while (n % factor_base[i] == T(0)) {
            n = n / factor_base[i];
            ++k;
        }
        if (k % 2 == T(1)){
            factors[i] = 1;
        }
        else{
            factors[i] = 0;
        }
        //factors[i] = k % 2;
    }
    if (n == 1) {
        return factors;
    }
    return {-1};
}

template <class T>
T TryGetFactor(T n) {
    assert(n > T(1) && "Only for positive numbers!");
    static std::random_device rd;
    static std::mt19937 eng(rd());
    std::uniform_int_distribution<> distribution(2, details::MaxFuncArg);
    size_t factor_base_size = FindPrimes(2, FactorBaseBorder).size();
    size_t k = 0;
    std::vector<std::vector<int>> matrix;
    std::vector<T> vector_of_r(factor_base_size + 1);
    while (k <= factor_base_size) {
        T r = T(distribution(eng));
        T g_r = PowMod<T>(r, 2, n);
        if (g_r == T(0)) {
            return Gcd(r, n);
        }
        std::vector<int> factors = details::TryFactorize(g_r);
        if (factors[0] != -1) {
            vector_of_r[k] = r;
            matrix.emplace_back(factors);
            ++k;
        }
    }
    std::vector<int> contrib_r = Gaus(matrix);
    T final_g_r = 1;
    T final_r = 1;
    for (const auto &index_of_r : contrib_r) {
        // std::cout << index_of_r << " ";
        T g_r = PowMod<T>(vector_of_r[index_of_r], 2, n);
        final_g_r = final_g_r * g_r;
        final_r = final_r * Sqrt<T>(vector_of_r[index_of_r]);
    }
    if (final_r == final_g_r) {
        return T(1);
    }
    T res = final_g_r - final_r;
    if (res > T(0)) {
        return Gcd(res, n);
    }
    res = res * -1;
    return Gcd(res, n);
}

template <class T>
void FactorizeD(T n, std::vector<T> &factors) {
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
    T factor = details::TryGetFactor(n);
    while (factor == 1 || factor == n) {
        factor = details::TryGetFactor(n);
    }
    // factors.emplace_back(factor);
    FactorizeD(factor, factors);
    FactorizeD(T(n / factor), factors);
}

}  // namespace details
template <class T>
std::vector<T> DiFactorization(T n) {
    assert(n > T(1) && "Only for numbers bigger than one!");
    std::vector<T> res = {T(1)};
    details::FactorizeD(n, res);
    return res;
}

template <class T>
T FacDickSon(T n) {
    T res = details::TryGetFactor(n);
    while (res == 1 || res == n) {
        res = details::TryGetFactor(n);
    }
    return res;
}
}  // namespace lp
