#pragma once
#include <random>
#include <vector>
#include "powers.h"
#include "gauss.h"
#include "sqrt.h"
#include "eratosthene_sieve.h"

namespace lp {
namespace details {
constexpr int MaxFuncArg = 100000;
constexpr int FactorBaseBorder = 2000;

template <class T>
std::vector<T> GetFactorBase() {
    return FindPrimes<T>(2, FactorBaseBorder);
}

template <class T>
std::vector<int> TryFactorize(T n) {
    assert(n >= T(0) && "Only for positive numbers!");
    std::vector<T> FactorBase = GetFactorBase<T>();
    std::vector<T> factors(FactorBase.size(), 0);
    for (int i = 0; i < FactorBase.size(); ++i) {
        T k = 0;
        while (n % FactorBase[i] == 0) {
            n = n / FactorBase[i];
            ++k;
        }
        factors[i] = k % 2;
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
    size_t FactorBaseSize = details::GetFactorBase<T>().size();
    size_t k = 0;
    std::vector<std::vector<int>> Matrix;
    std::vector<T> vector_of_r(FactorBaseSize + 1);
    while (k <= FactorBaseSize) {
        T r = T(distribution(eng));
        T g_r = PowMod<T>(r, 2, n);
        if (g_r == 0) {
            return Gcd(r, n);
        }
        std::vector<int> factors = details::TryFactorize(g_r);
        if (factors[0] != -1) {
            vector_of_r[k] = r;
            Matrix.emplace_back(factors);
            ++k;
        }
    }
    std::vector<int> contrib_r = Gaus(Matrix);
    T final_g_r = 1;
    T final_r = 1;
    for (const auto &index_of_r : contrib_r) {
        //std::cout << index_of_r << " ";
        T g_r = PowMod<T>(vector_of_r[index_of_r], 2, n);
        final_g_r = final_g_r * g_r;
        final_r = final_r * Sqrt<T>(vector_of_r[index_of_r]);
    }
    if (final_r - final_g_r > 0) {
        return Gcd(final_r - final_g_r, n);
    }
    return Gcd(final_g_r - final_r, n);
}

}  // namespace details
template <class T>
T FactorizeD(T n) {
    T res = details::TryGetFactor(n);
    while (res == 1 || res == n) {
        res = details::TryGetFactor(n);
    }
    return res;
}
}  // namespace lp
