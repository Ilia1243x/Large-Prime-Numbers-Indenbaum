#pragma once
#include "powers.h"

namespace lp {
    template <class T>
    std::vector<T> FindPrimes(T m, T n) {
        assert(m < n && "End should be bigger than start!");
        std::vector<bool> a(n + 1);
        std::vector<T> res;
        for (T i = 2; i < n + 1; ++i) {
            if (!a[i]) {
                for (T j = i * i; j < n + 1; j += i) {
                    a[j] = true;
                }
            }
        }
        T first_prime = 2;  // or first_prime(2)?
        for (int i = std::max(first_prime, m); i < n + 1; ++i) {
            if (!a[i]) {
                res.emplace_back(i);
            }
        }
        return res;
    }

    template <class T>
    class SegmentedSieve {
    public:
        SegmentedSieve(T base, T limit, unsigned int l1_d_cache_size)
                : base_(std::max(T(2), base)), limit_(limit), l1_d_cache_size_(l1_d_cache_size) {
            assert(limit >= T(2) && "Choose limit no smaller than 2!");
            assert(base < limit && "Limit should be bigger than base!");
        }
        T GetCounter() {
            return count_;
        }
        std::vector<T> FindPrimes() {
            return FindPrimesCPU(base_, limit_, l1_d_cache_size_);
        }

    private:
        std::vector<T> FindPrimesCPU(T base, T limit, T l1_d_cache_size) {
            std::vector<T> res;
            T sqrt = static_cast<T>(std::sqrt(limit));
            T segment_size = std::max(sqrt, l1_d_cache_size);
            T i = 3;
            T n = 3;
            T s = 3;
            std::vector<char> sieve(segment_size);
            std::vector<char> is_prime(sqrt + 1, true);
            std::vector<T> primes;
            std::vector<T> multiples;
            for (T low = 0; low <= limit; low += segment_size) {
                std::fill(sieve.begin(), sieve.end(), true);

                T high = low + segment_size - T(1);
                high = std::min(high, limit);

                for (; i * i <= high; i += T(2)) {
                    if (is_prime[i]) {
                        for (T j = i * i; j <= sqrt; j += i) {
                            is_prime[j] = false;
                        }
                    }
                }

                for (; s * s <= high; s += T(2)) {
                    if (is_prime[s]) {
                        primes.push_back(s);
                        multiples.push_back(s * s - low);
                    }
                }

                for (std::size_t i = 0; i < primes.size(); i++) {
                    T j = multiples[i];
                    for (T k = primes[i] * T(2); j < segment_size; j += k) {
                        sieve[j] = false;
                    }
                    multiples[i] = j - segment_size;
                }

                for (; n <= high; n += T(2)) {
                    if (sieve[n - low] && n >= base)  // n is a prime bigger than base
                    {
                        ++count_;
                        res.emplace_back(n);
                    }
                }
            }
            return res;
        }

        T l1_d_cache_size_;
        T base_;
        T limit_;
        T count_ = 1;
    };
}  // namespace lp