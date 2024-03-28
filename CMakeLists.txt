cmake_minimum_required(VERSION 3.27)
project(Large-Prime-Numbers-Indenbaum)

set(CMAKE_CXX_STANDARD 17)

add_executable(Large-Prime-Numbers-Indenbaum main.cpp
        testGcd.cpp
        Timer.cpp
        gauss.cpp
        eratosthene_sieve.cpp
)
