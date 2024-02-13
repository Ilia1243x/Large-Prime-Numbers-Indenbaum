#pragma once
#include "powers.h"
#include "usings.h"
#include "sqrt.h"

namespace lp {
namespace details {
template <class T>
std::vector<bool> DoSelection(OptimalType<T> n) {
    std::vector<bool> v(n + 1);
    for (T i = 3; i < v.size(); i += 2) {
        if (v[i]) {
            continue;
        }
        for (T j = i * i; j < v.size(); j += i) {
            v[j] = true;
        }
    }
    return v;
}

template <class T>
std::vector<T> CherryPicking(std::vector<bool> &v, OptimalType<T> m, OptimalType<T> n) {
    std::vector<T> res;
    if (m <= T(2) && n >= T(2)) {
        res.emplace_back(T(2));
    }
    T first_odd_prime = T(3);
    T m_odd = (m % 2 == 0) ? (m + 1) : m;
    for (int i = std::max(first_odd_prime, m_odd); i < n + 1; i += 2) {
        if (v[i]) {
            continue;
        }
        res.emplace_back(i);
    }
    return res;
}
}  // namespace details

template <class T>
std::vector<T> FindPrimes(OptimalType<T> m, OptimalType<T> n) {
    assert(m < n && "End should be bigger than start!");
    std::vector<bool> a = details::DoSelection<T>(n);
    std::vector<T> res = details::CherryPicking<T>(a, m, n);
    return res;
}
}  // namespace lp
