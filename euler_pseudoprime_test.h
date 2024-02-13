#pragma once
#include "legendre_symbol.h"

namespace lp {
template <class T>
class EulerPrime {
public:
    explicit EulerPrime(T n) : number_(n) {
        assert(n > T(1) && n % T(2) != T(0) && "Only for odd numbers bigger than 1!");
    }

    T GetCounter() {
        return counter_;
    }

    T GetBase() {
        return base_;
    }

    bool MaybePrime() {
        return TestPrime(number_);
    }

private:
    bool TestPrime(T n) {
        assert(base_ < n && "We use base smaller than n!");
        T gcd = Gcd(base_, n);
        if (gcd != T(1)) {
            ++base_;  // чисто для тестирования
            return false;
        }
        T po = PowMod(base_, (n - T(1)) / T(2), n);
        LegendreSymbol<T> legendre(base_, n);
        if (po == legendre.GetSymbol()) {
            ++base_;
            ++counter_;
            return true;
        } else {
            ++base_;  // чисто для тестирования
            return false;
        }
    }

    T counter_ = 0;  // или опять же надо T(0) или блин counter_(0)?
    T number_;
    T base_ = 2;
};
}  // namespace lp
