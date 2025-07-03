#include "Timer.h"

Timer::Timer() {
    reset();
}
void Timer::reset() {
    start_time_ = std::chrono::steady_clock::now();
}
double Timer::elapsed() const {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = now - start_time_;
    return diff.count();
}
