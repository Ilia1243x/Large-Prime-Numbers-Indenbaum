#pragma once
#include <iostream>
#include <random>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include "cassert"

template <typename T>
class Random;

template<>
class Random<int64_t>{
public:
    int64_t Generate(int64_t left, int64_t right) {
        assert(left <= right && "First write a left point!");
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int64_t> distrib(left, right);
        return distrib(gen);
    }
};

template<>
class Random<int>{
public:
    int Generate(int left, int right) {
        assert(left <= right && "First write a left point!");
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distrib(left, right);
        return distrib(gen);
    }
};


template <>
class Random<boost::multiprecision::cpp_int> {
public:
    boost::multiprecision::cpp_int Generate(boost::multiprecision::cpp_int left, boost::multiprecision::cpp_int right) {
        assert(left <= right && "First write a left point!");
        std::random_device rd;
        std::mt19937 gen(rd());
        boost::random::uniform_int_distribution<boost::multiprecision::cpp_int> distrib(left, right);
        return distrib(gen);
    }
};
