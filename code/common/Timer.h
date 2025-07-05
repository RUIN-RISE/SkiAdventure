#ifndef __TIMER_H__
#define __TIMER_H__

class Timer {
public:
    
    Timer();

    void reset();

    double elapsed() const;

private:
    std::chrono::steady_clock::time_point start_time_;
};

#endif
