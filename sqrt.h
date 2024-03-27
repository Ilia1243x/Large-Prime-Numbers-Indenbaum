#pragma once
#include <cassert>
#include "usings.h"
#include "powers.h"

namespace lp {
namespace details {
static constexpr int64_t HalfOfMaxInt64 = 4294967295;
}  // namespace details

template <class T>
OverflowType<T> Sqrt(OverflowType<T> n) {
    assert(n >= OverflowType<T>(0) && "Sqrt is defined for non-negative numbers!");
    OverflowType<T> l = OverflowType<T>(0);
    OverflowType<T> r;
    if (CanBeLongLong<T>) {
        r = details::HalfOfMaxInt64 < n ? details::HalfOfMaxInt64 : n;
    } else {
        r = n;
    }
    while (true) {
        OverflowType<T> mid = (l + r) / OverflowType<T>(2);
        if (l == r) {
            return mid;
        }
        if (mid * mid < n) {
            l = mid + OverflowType<T>(1);
        } else if (mid * mid > n) {
            r = mid;
        } else {
            return mid;
        }
    }
}
}  // namespace lp
