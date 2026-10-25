// Tests for client_timing.cpp. Time points are compared as counts of milliseconds since the clock's epoch,
// so that failures print readable numbers on every compiler.
#include "client_timing.h"

#include <gtest/gtest.h>

using namespace std::chrono_literals;
using std::chrono::milliseconds;

namespace {

// A fixed "now" far from the epoch: tests never read the real clock.
const Clock::time_point t0{std::chrono::hours{1000}};

long long ms_since(Clock::time_point origin, Clock::time_point tp) {
    return std::chrono::duration_cast<milliseconds>(tp - origin).count();
}

bool is_forever(Clock::time_point tp) {
    return tp == Clock::time_point::max();
}

}  // namespace

TEST(DeadlineTest, OrdinaryTimeoutIsAddedToNow) {
    EXPECT_EQ(ms_since(t0, deadline(t0, 5s)), 5000);
    EXPECT_EQ(ms_since(t0, deadline(t0, 250ms)), 250);
}

TEST(DeadlineTest, ZeroTimeoutMeansNow) {
    EXPECT_EQ(ms_since(t0, deadline(t0, 0ms)), 0);
}

TEST(DeadlineTest, MaxTimeoutMeansForever) {
    EXPECT_TRUE(is_forever(deadline(t0, milliseconds::max())))
        << "milliseconds::max() must give Clock::time_point::max(), not an overflowed time point";
}

TEST(DeadlineTest, TimeoutPastTheEndOfTheClockMeansForever) {
    // About 342 years: fits in milliseconds, but not in steady_clock's nanoseconds.
    EXPECT_TRUE(is_forever(deadline(t0, std::chrono::hours{3'000'000})));
    // Close to the end of the clock even a short timeout reaches past it.
    const Clock::time_point near_end = Clock::time_point::max() - 10s;
    EXPECT_TRUE(is_forever(deadline(near_end, 20s)));
}

TEST(RemainingTest, TimeLeftBeforeTheDeadline) {
    EXPECT_EQ(remaining(t0, t0 + 5s).count(), 5000);
}

TEST(RemainingTest, PassedDeadlineLeavesNothing) {
    EXPECT_EQ(remaining(t0 + 1s, t0).count(), 0);
    EXPECT_EQ(remaining(t0, t0).count(), 0);
}

TEST(RemainingTest, FractionsOfAMillisecondRoundUp) {
    EXPECT_EQ(remaining(t0, t0 + 300us).count(), 1) << "0.3 ms left must not be reported as 0 ms";
    EXPECT_EQ(remaining(t0, t0 + 1ms + 1ns).count(), 2);
}

TEST(RetryAtTest, DelayDoublesUpToTheCap) {
    const long long expected[] = {100, 200, 400, 800, 1600, 2000, 2000, 2000};
    for (int attempt = 0; attempt < 8; ++attempt) {
        EXPECT_EQ(ms_since(t0, retry_at(t0, attempt, 100ms, 2s)), expected[attempt]) << "attempt " << attempt;
    }
}

TEST(RetryAtTest, CountsFromTheFirstAttempt) {
    const Clock::time_point later = t0 + 1h;
    EXPECT_EQ(ms_since(later, retry_at(later, 3, 50ms, 10s)), 400);
}

TEST(RetryAtTest, CapSmallerThanBase) {
    EXPECT_EQ(ms_since(t0, retry_at(t0, 0, 500ms, 300ms)), 300);
}
