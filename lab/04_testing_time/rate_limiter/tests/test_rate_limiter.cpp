// Tests for RateLimiter: a bucket of 3 tokens, one new token per second. FakeClock moves time exactly.
// Durations are compared in milliseconds so that failures print readable numbers on every compiler.
#include "fake_clock.h"
#include "rate_limiter.h"

#include <gtest/gtest.h>

using namespace std::chrono_literals;

class RateLimiterTest : public ::testing::Test {
protected:
    void SetUp() override { FakeClock::reset(); }

    static long long wait_ms(RateLimiter<FakeClock>& limiter) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(limiter.wait_time()).count();
    }

    // Takes tokens until refused; returns how many were granted. Bounded, so a limiter that never
    // refuses makes the test fail instead of hanging.
    static int drain(RateLimiter<FakeClock>& limiter) {
        int granted = 0;
        while (granted < 100 && limiter.try_acquire()) {
            ++granted;
        }
        return granted;
    }
};

TEST_F(RateLimiterTest, StartsFull) {
    RateLimiter<FakeClock> limiter{3, 1s};
    EXPECT_EQ(drain(limiter), 3);
}

TEST_F(RateLimiterTest, AllowsABurstUpToCapacity) {
    RateLimiter<FakeClock> limiter{3, 1s};
    EXPECT_TRUE(limiter.try_acquire());
    EXPECT_TRUE(limiter.try_acquire());
    EXPECT_TRUE(limiter.try_acquire());
    EXPECT_FALSE(limiter.try_acquire()) << "the 4th request in a row must wait";
}

TEST_F(RateLimiterTest, NoWaitWhileTokensAreLeft) {
    RateLimiter<FakeClock> limiter{3, 1s};
    EXPECT_EQ(wait_ms(limiter), 0);
    EXPECT_TRUE(limiter.try_acquire());
    EXPECT_EQ(wait_ms(limiter), 0);
}

TEST_F(RateLimiterTest, WaitTimeCountsDownToTheNextToken) {
    RateLimiter<FakeClock> limiter{3, 1s};
    drain(limiter);
    EXPECT_EQ(wait_ms(limiter), 1000);
    FakeClock::advance(700ms);
    EXPECT_EQ(wait_ms(limiter), 300);
    FakeClock::advance(300ms);
    EXPECT_EQ(wait_ms(limiter), 0);
}

TEST_F(RateLimiterTest, OneTokenPerInterval) {
    RateLimiter<FakeClock> limiter{3, 1s};
    drain(limiter);
    FakeClock::advance(999ms);
    EXPECT_FALSE(limiter.try_acquire());
    FakeClock::advance(1ms);
    EXPECT_TRUE(limiter.try_acquire());
    EXPECT_FALSE(limiter.try_acquire());
}

TEST_F(RateLimiterTest, PartOfAnIntervalIsNotLost) {
    RateLimiter<FakeClock> limiter{3, 1s};
    drain(limiter);
    FakeClock::advance(1500ms);
    EXPECT_TRUE(limiter.try_acquire());
    EXPECT_FALSE(limiter.try_acquire());
    FakeClock::advance(500ms);  // 2 s since the bucket was drained
    EXPECT_TRUE(limiter.try_acquire()) << "the half interval left over at 1.5 s must count towards the next token";
}

TEST_F(RateLimiterTest, LongIdleTimeGivesAtMostCapacity) {
    RateLimiter<FakeClock> limiter{3, 1s};
    drain(limiter);
    FakeClock::advance(1h);
    EXPECT_EQ(drain(limiter), 3);
}

TEST_F(RateLimiterTest, FullBucketDoesNotSaveUpIdleTime) {
    RateLimiter<FakeClock> limiter{3, 1s};
    FakeClock::advance(10500ms);  // idle with a full bucket
    drain(limiter);
    FakeClock::advance(600ms);
    EXPECT_FALSE(limiter.try_acquire()) << "time spent with a full bucket must not count towards the next token";
    FakeClock::advance(400ms);  // 1 s after draining
    EXPECT_TRUE(limiter.try_acquire());
}
