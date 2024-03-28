#include "iostream"

#include "Timer.h"

Timer::Timer() {
    start_ = std::chrono::steady_clock::now();
}
Timer::~Timer() {
    std::cout << "Seconds" << std::chrono::duration<double>(std::chrono::steady_clock::now()- start_).count() << '\n';
}