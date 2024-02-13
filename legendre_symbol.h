#pragma once
#include "powers.h"

namespace lp {
template <class T>
class LegendreSymbol {
public:
    LegendreSymbol(T a, T p) : base_(a), prime_(p) {
        assert(p > T(2) && "P is odd prime bigger than 2!");
    }
    T GetSymbol() {
        symbol_ = ComputeSymbol(base_, prime_);
        return symbol_;
    }

private:
    T ComputeSymbol(T a, T p) {
        a = a % p;
        if (a == T(0)) {
            return T(0);
        }
        if (a == T(1)) {
            return T(1);
        }
        if (a % T(2) == T(0)) {
            if (p % T8 == 1 || p % T8 == T8 - 1) {
                return ComputeSymbol(a / T(2), p);
            } else if (p % T8 == T4 - 1 || p % T8 == T4 + 1) {
                return -ComputeSymbol(a / 2, p);
            }
        } else {
            if (p % T4 == T4 - 1 && a % T4 == T4 - 1) {
                return -ComputeSymbol(p, a);
            } else {
                return ComputeSymbol(p, a);
            }
        }
    }

    T base_;
    T prime_;
    T symbol_;
    static constexpr T T8 = 8;
    static constexpr T T4 = 4;
};

}  // namespace lp