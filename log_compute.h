#pragma once
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "cassert"

template <typename T>
class Logarithm;

template<>
class Logarithm<int64_t>{
public:
    long double Compute(int64_t x) {
        assert(x > 0 && "Should be bigger than 0!");
        return std::log(x);
    }
};

template<>
class Logarithm<int>{
public:
    long double Compute(int x) {
        assert(x > 0 && "Should be bigger than 0!");
        return std::log(x);
    }
};


template <>
class Logarithm<boost::multiprecision::cpp_int> {
public:
    boost::multiprecision::cpp_dec_float_50 Compute(boost::multiprecision::cpp_int x) {
        assert(x > 0 && "Should be bigger than 0!");
        return log(x.convert_to<boost::multiprecision::cpp_dec_float_50>());
    }
};
