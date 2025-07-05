#include "Timer.h"

// Constructs a Timer and call reset()
Timer::Timer() {
    reset();
}

// Resets the timer to the current time
void Timer::reset() {
    start_time_ = std::chrono::steady_clock::now();
}

// time after reset in seconds
double Timer::elapsed() const {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = now - start_time_;
    return diff.count();
}
