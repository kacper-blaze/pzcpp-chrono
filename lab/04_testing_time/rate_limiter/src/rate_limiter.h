#pragma once

#include <chrono>
#include <stdexcept>

// Client-side rate limiter (token bucket). The bucket holds at most `capacity` tokens and starts full.
// One token is added per `interval`; a request takes one token. Time is read from `Clock`,
// so tests can use FakeClock instead of steady_clock.
template <class Clock = std::chrono::steady_clock>
class RateLimiter {
public:
    RateLimiter(int capacity, typename Clock::duration interval)
        : capacity_(capacity), interval_(interval), tokens_(capacity), last_refill_(Clock::now()) {}

    // Takes a token if one is available (after refilling) and returns true; otherwise returns false.
    bool try_acquire() {
        throw std::logic_error("TODO: implement RateLimiter::try_acquire");
    }

    // How long until a token is available: zero if one is available now (after refilling).
    typename Clock::duration wait_time() {
        throw std::logic_error("TODO: implement RateLimiter::wait_time");
    }

private:
    // Adds one token for every WHOLE interval that has passed, up to capacity_.
    // Time between calls is not lost: a part of an interval that was too short for a token still counts
    // towards the next one. A full bucket does not save up idle time.
    void refill() {
        throw std::logic_error("TODO: implement RateLimiter::refill");
    }

    int capacity_;
    typename Clock::duration interval_;
    int tokens_;
    typename Clock::time_point last_refill_;
};
