#pragma once
#include <iomanip>
#include <iostream>
#include <type_traits>

namespace lp {
template <class T>
constexpr bool CanBeLongLong{std::is_integral<T>::value};

template <class T>
using OverflowType = std::conditional_t<CanBeLongLong<T>, int64_t, T>;

template <class T>
constexpr bool IsLight{sizeof(T) <= 16 || std::is_integral<T>::value};


template <class T>
using OptimalType = std::conditional_t<IsLight<T>, T, const T &>;
}  // namespace lp

