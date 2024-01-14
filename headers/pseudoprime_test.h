#pragma once
#include "powers.h"

namespace lp {
    template <class T>
    class PseudoPrime {
    public:
        explicit PseudoPrime(T n) : number_(n) {
            assert(n > T(1) && n % T(2) != T(0) && "Only for odd numbers bigger than 1!");
        }

        T GetCounter() {
            return counter_;
        }

        T GetBase() {
            return base_;
        }

        bool MaybePrime() {
            return ProbPrime(number_);
        }

        bool MaybePrimeGcd() {
            return ProbPrimeGcd(number_);
        }

    private:
        bool ProbPrime(T n) {
            assert(base_ < n && "We use base smaller than n!");
            T po = PowMod(base_, n - T(1), n);
            if (po == T(1)) {
                ++base_;
                ++counter_;
                return true;
            } else {
                ++base_;  // чисто для тестирования
                return false;
            }
        }

        bool ProbPrimeGcd(T n) {
            assert(base_ < n && "We use base smaller than n!");
            T gcd = Gcd(base_, n);
            if (gcd != T(1)) {
                ++base_;  // чисто для тестирования
                return false;
            }
            T po = PowMod(base_, n - T(1), n);
            if (po == T(1)) {
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
