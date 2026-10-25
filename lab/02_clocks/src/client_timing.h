#pragma once

#include <chrono>

// Timeouts and retries of the API client. All functions are pure: the current time is a parameter,
// so they can be tested without a real clock. Timeouts must use a steady clock; a system_clock
// time point does not convert to Clock::time_point, so passing one is a compile error.
using Clock = std::chrono::steady_clock;

// The moment a request started at `now` times out.
// A timeout of std::chrono::milliseconds::max() means "wait forever" and gives Clock::time_point::max();
// so does any timeout that would reach past Clock::time_point::max().
Clock::time_point deadline(Clock::time_point now, std::chrono::milliseconds timeout);

// Time left until `deadline`, never negative, rounded UP to whole milliseconds
// (0.3 ms left gives 1 ms, so a caller waiting for "remaining()" never spins on 0 ms).
std::chrono::milliseconds remaining(Clock::time_point now, Clock::time_point deadline);

// When retry number `attempt` (0, 1, 2, ...) should start: first_attempt + base * 2^attempt, but never later
// than first_attempt + cap. Counted from the fixed first_attempt, so the result can go straight into sleep_until.
// Example: base 100 ms, cap 2 s -> delays 100, 200, 400, 800, 1600, 2000, 2000, ... ms.
Clock::time_point retry_at(Clock::time_point first_attempt, int attempt,
                           std::chrono::milliseconds base, std::chrono::milliseconds cap);
