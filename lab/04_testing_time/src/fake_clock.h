#pragma once

#include <chrono>

// A clock for tests: time stands still until the test moves it with advance().
// It meets the standard Clock requirements, so it can replace std::chrono::steady_clock
// as a template argument. Its state is static (now() must be static): call reset() at the
// start of every test, e.g. in SetUp() of a test fixture.
struct FakeClock {
    using duration = std::chrono::nanoseconds;
    using rep = duration::rep;
    using period = duration::period;
    using time_point = std::chrono::time_point<FakeClock>;
    static constexpr bool is_steady = true;

    static time_point now() { return current; }
    static void advance(duration d) { current += d; }
    static void reset() { current = time_point{}; }

    inline static time_point current{};
};
