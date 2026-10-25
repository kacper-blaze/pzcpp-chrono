// Tests for usage.cpp. Values are compared with .count() so that failures print readable numbers
// on every compiler (older ones cannot print chrono types).
#include "usage.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <vector>

using namespace std::chrono_literals;

TEST(BillableSecondsTest, EveryStartedSecondIsBilled) {
    EXPECT_EQ(billable_seconds(1000ms).count(), 1);
    EXPECT_EQ(billable_seconds(1001ms).count(), 2);
    EXPECT_EQ(billable_seconds(1ms).count(), 1);
    EXPECT_EQ(billable_seconds(59'999ms).count(), 60);
}

TEST(BillableSecondsTest, NoCallTimeCostsNothing) {
    EXPECT_EQ(billable_seconds(0ms).count(), 0);
}

TEST(MinuteBucketTest, PositiveOffsetsFallIntoTheirMinute) {
    EXPECT_EQ(minute_bucket(0ms).count(), 0);
    EXPECT_EQ(minute_bucket(59'999ms).count(), 0);
    EXPECT_EQ(minute_bucket(60'000ms).count(), 1);
    EXPECT_EQ(minute_bucket(150'000ms).count(), 2);
}

TEST(MinuteBucketTest, EventsBeforeTheStartGoToNegativeSlots) {
    EXPECT_EQ(minute_bucket(-200ms).count(), -1) << "an event 200 ms before the start is in slot -1, not 0";
    EXPECT_EQ(minute_bucket(-60'000ms).count(), -1);
    EXPECT_EQ(minute_bucket(-60'001ms).count(), -2);
}

TEST(AverageLatencyTest, KeepsFractionsOfAMillisecond) {
    EXPECT_DOUBLE_EQ(average_latency({1ms, 2ms}).count(), 1.5);
    EXPECT_DOUBLE_EQ(average_latency({10ms, 20ms, 40ms}).count(), 70.0 / 3);
}

TEST(AverageLatencyTest, SingleValueIsItsOwnAverage) {
    EXPECT_DOUBLE_EQ(average_latency({250ms}).count(), 250.0);
}

TEST(AverageLatencyTest, EmptyListIsAnError) {
    EXPECT_THROW(average_latency({}), std::invalid_argument);
}
