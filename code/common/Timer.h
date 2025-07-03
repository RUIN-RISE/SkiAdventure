#ifndef __TIMER_H__
#define __TIMER_H__

class Timer {
public:
    // Constructs a Timer and call reset()
    Timer();

    // Resets the timer to the current time
    void reset();

    // time after reset in nanoseconds
    double elapsed() const;

private:
    std::chrono::steady_clock::time_point start_time_;
};

#endif
