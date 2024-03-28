#pragma once
#include "powers.h"
#include "random_gen.h"

namespace lp {
namespace details {
constexpr int MaxCounter = 105;
} // namespace details
template <class T>
class StrongPseudoPrime {
public:
    explicit StrongPseudoPrime(T n) : number_(n), coefficient_(Build(n).coefficient), power_(Build(n).power) {
        assert(n > T(1) && "Only for numbers bigger than 1!");
    }

    T GetCounter() const{
        return counter_;
    }

    void ResetCounter() {
        counter_ = 0; //int
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

    bool ProbabilisticTest() {
        ResetCounter();
        return TestProb();
    }

    bool DeterministicTest() {
        return true; //to do
    }

private:
    bool ProbPrime(T base) {
        assert(base < number_ && "We use base smaller than n!");
        T po = PowMod<T>(base, coefficient_, number_);
        if (po == T(1) || po == number_ - T(1)) {
            ++counter_;
            return true;
        } else {
            for (T i = 1; i < power_; ++i) {
                po = ((po % number_) * (po % number_)) % number_;
                if (po == number_ - T(1)) {
                    ++counter_;
                    return true;
                }
            }
        }
        return false;
    }
    bool TestProb() {
        if (number_ == 2){
            return true;
        }
        if (number_ % T(2) == T(0)){
            return false;
        }
        Random<T> random_number;
        while (counter_ < details::MaxCounter) {
            T cur_base = random_number.Generate(T(2), number_-1);
            if (!ProbPrime(cur_base)) {
                return false;
            }
            ++counter_;
        }
        return true;
    }
    struct Decomposition {
        T coefficient;
        T power;
    };
    Decomposition Build(T n) {
        T coef = n - T(1);
        T pow = 0;
        if (coef != T(0)) {
            while (coef % T(2) == T(0)) {
                coef = coef / 2;
                ++pow;
            }
        }
        return {coef, pow};
    }
    int counter_ = 0;
    T number_;
    T base_ = 2;
    T coefficient_;
    T power_ = 0;
};

}  // namespace lp
