#include "client_timing.h"

#include <stdexcept>

Clock::time_point deadline(Clock::time_point now, std::chrono::milliseconds timeout) {
    (void)now;
    (void)timeout;
    throw std::logic_error("TODO: implement deadline");
}

std::chrono::milliseconds remaining(Clock::time_point now, Clock::time_point deadline) {
    (void)now;
    (void)deadline;
    throw std::logic_error("TODO: implement remaining");
}

Clock::time_point retry_at(Clock::time_point first_attempt, int attempt,
                           std::chrono::milliseconds base, std::chrono::milliseconds cap) {
    (void)first_attempt;
    (void)attempt;
    (void)base;
    (void)cap;
    throw std::logic_error("TODO: implement retry_at");
}
