#include "testGcd.h"
namespace {
    constexpr int Aboba = 2;
}
void TestGcd(){
    assert(1 == lp::Gcd(1, 150));
    assert(2ll == lp::Gcd<long long>(14, 12));
    boost::multiprecision::cpp_int v = 1000000;
    v *= 1000000;
    boost::multiprecision::cpp_int z = v + 1;
    assert(1 == lp::Gcd(z,v));
    std::cout << "OK";
}