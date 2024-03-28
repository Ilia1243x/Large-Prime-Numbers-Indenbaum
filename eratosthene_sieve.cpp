#include "eratosthene_sieve.h"

std::vector<bool> lp::details::DoSelection(size_t n) {
    std::vector<bool> v(n + 1);
    for (size_t i = 3; i < v.size(); i += 2) {
        if (v[i]) {
            continue;
        }
        for (size_t j = i * i; j < v.size(); j += i) {
            v[j] = true;
        }
    }
    return v;
}

std::vector<size_t> lp::details::CherryPicking(std::vector<bool> &v, size_t m, size_t n) {
    std::vector<size_t> res;
    if (m <= 2 && n >= 2) {
        res.emplace_back(2);
    }
    size_t first_odd_prime = 3;
    size_t m_odd = (m % 2 == 0) ? (m + 1) : m;
    for (size_t i = std::max(first_odd_prime, m_odd); i < n + 1; i += 2) {
        if (v[i]) {
            continue;
        }
        res.emplace_back(i);
    }
    return res;
}

std::vector<size_t> lp::FindPrimes(size_t m, size_t n) {
    assert(m < n && "End should be bigger than start!");
    std::vector<bool> a = lp::details::DoSelection(n);
    std::vector<size_t> res = lp::details::CherryPicking(a, m, n);
    return res;
}
