#pragma once
#include "powers.h"

namespace lp {
    template <class T>
    class StrongPseudoPrime {
    public:
        explicit StrongPseudoPrime(T n) : number_(n), t_(n - T(1)) {
            assert(n > T(1) && n % T(2) != T(0) && "Only for odd numbers bigger than 1!");
            if (t_ != T(0)) {
                while (t_ % T(2) == T(0)) {
                    t_ = t_ / 2;
                    ++a_;
                }
            }
        }

        T GetCounter() {
            return counter_;
        }

        T GetBase() {
            return base_;
        }

        bool MaybePrime() {
            return ProbPrime();
        }
        bool MaybePrimeGcd() {
            return ProbPrimeGcd();
        }

    private:
        bool ProbPrime() {
            assert(base_ < number_ && "We use base smaller than n!");
            T po = PowMod(base_, t_, number_);
            if (po == T(1) || po == number_ - T(1)) {
                ++base_;
                ++counter_;
                return true;
            } else {
                for (T i = 1; i < a_; ++i) {
                    po = ((po % number_) * (po % number_)) % number_;
                    if (po == number_ - T(1)) {
                        ++base_;
                        ++counter_;
                        return true;
                    }
                }
            }
            ++base_;  // для тестирования
            return false;
        }
        bool ProbPrimeGcd() {
            assert(base_ < number_ && "We use base smaller than n!");
            T gcd = Gcd(base_, number_);
            if (gcd != T(1)) {
                ++base_;  // для тестирования
                return false;
            }
            T po = PowMod(base_, t_, number_);
            if (po == T(1) || po == number_ - T(1)) {
                ++base_;
                ++counter_;
                return true;
            } else {
                for (T i = 1; i < a_; ++i) {
                    po = ((po % number_) * (po % number_)) % number_;
                    if (po == number_ - T(1)) {
                        ++base_;
                        ++counter_;
                        return true;
                    }
                }
            }
            ++base_;  // для тестирования
            return false;
        }
        T counter_ = 0;
        T number_;
        T base_ = 2;
        T t_;
        T a_ = 0;
    };

}  // namespace lp