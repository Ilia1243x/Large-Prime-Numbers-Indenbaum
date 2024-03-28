#pragma once
#include <random>
#include "powers.h"

namespace lp {
    namespace details{
        constexpr int MaxCounterF = 120;
    } // namespace details
template <class T>
class PseudoPrime {
public:
    explicit PseudoPrime(T n) : number_(n) {
        assert(n > T(1) && n % T(2) != T(0) && "Only for odd numbers bigger than 1!");
    }

    T GetCounter() {
        return counter_;
    }

    void ResetCounter() {
        counter_ = T(0);
    }

    T GetBase() {
        return base_;
    }

    void ResetBase() {
        base_ = T(2);
    }

    void SetBase(T number) {
        base_ = number;
    }

    bool MaybePrime() {
        return ProbPrime(base_);
    }

    bool MaybePrimeGcd() {
        return ProbPrimeGcd(base_);
    }

    bool ProbabilisticTest() {
        ResetCounter();
        return TestProb();
    }

private:
    bool ProbPrime(T base) {
        assert(base < number_ && "We use base smaller than n!");
        T po = PowMod<T>(base, number_ - T(1), number_);
        if (po == T(1)) {
            ++counter_;
            return true;
        } else {
            return false;
        }
    }

    bool ProbPrimeGcd(T base) {
        assert(base < number_ && "We use base smaller than n!");
        T gcd = Gcd(base, number_);
        if (gcd != T(1)) {
            return false;
        }
        return ProbPrime(base);
    }

    bool TestProb() {
        static std::random_device rd;
        static std::mt19937 eng(rd());
        std::uniform_int_distribution<> distribution(2, number_ - 1);
        while (counter_ < lp::details::MaxCounterF) {
            T cur_base = T(distribution(eng));
            if (Gcd(cur_base, number_) > 1) { continue; }
            if (!ProbPrime(cur_base)) {
                return false;
            }
            ++counter_;
        }
        return true;
    }

    T counter_ = T(0);
    T number_;
    T base_ = T(2);
};
}  // namespace lp
