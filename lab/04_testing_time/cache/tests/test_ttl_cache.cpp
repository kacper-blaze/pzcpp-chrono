// Tests for TtlCache. FakeClock lets every test move time exactly, without sleeping.
#include "fake_clock.h"
#include "ttl_cache.h"

#include <gtest/gtest.h>

#include <string>

using namespace std::chrono_literals;

class TtlCacheTest : public ::testing::Test {
protected:
    void SetUp() override { FakeClock::reset(); }

    TtlCache<std::string, std::string, FakeClock> cache{30s};
};

TEST_F(TtlCacheTest, ReturnsAFreshValue) {
    cache.put("/users/1", "Ala");
    ASSERT_TRUE(cache.get("/users/1").has_value());
    EXPECT_EQ(*cache.get("/users/1"), "Ala");
}

TEST_F(TtlCacheTest, MissingKeyGivesNothing) {
    EXPECT_FALSE(cache.get("/users/404").has_value());
}

TEST_F(TtlCacheTest, StillValidJustBeforeTheTtl) {
    cache.put("/users/1", "Ala");
    FakeClock::advance(29s);
    EXPECT_TRUE(cache.get("/users/1").has_value());
    FakeClock::advance(1s - 1ns);
    EXPECT_TRUE(cache.get("/users/1").has_value()) << "one nanosecond before the TTL the value is still fresh";
}

TEST_F(TtlCacheTest, ExpiresExactlyAtTheTtl) {
    cache.put("/users/1", "Ala");
    FakeClock::advance(30s);
    EXPECT_FALSE(cache.get("/users/1").has_value()) << "at exactly 30 s the value is no longer fresh";
}

TEST_F(TtlCacheTest, OverwriteReplacesTheValueAndRestartsTheTtl) {
    cache.put("/users/1", "Ala");
    FakeClock::advance(20s);
    cache.put("/users/1", "Ola");
    FakeClock::advance(20s);  // 40 s after the first put, 20 s after the second
    ASSERT_TRUE(cache.get("/users/1").has_value());
    EXPECT_EQ(*cache.get("/users/1"), "Ola");
    FakeClock::advance(10s);  // 30 s after the second put
    EXPECT_FALSE(cache.get("/users/1").has_value());
}

TEST_F(TtlCacheTest, GetRemovesAnExpiredEntry) {
    cache.put("/users/1", "Ala");
    FakeClock::advance(31s);
    EXPECT_EQ(cache.size(), 1u);
    EXPECT_FALSE(cache.get("/users/1").has_value());
    EXPECT_EQ(cache.size(), 0u);
}

TEST_F(TtlCacheTest, PurgeRemovesOnlyExpiredEntries) {
    cache.put("/old", "1");
    FakeClock::advance(20s);
    cache.put("/new", "2");
    FakeClock::advance(15s);  // "/old" is 35 s old, "/new" is 15 s old
    EXPECT_EQ(cache.purge_expired(), 1u);
    EXPECT_EQ(cache.size(), 1u);
    EXPECT_TRUE(cache.get("/new").has_value());
}

TEST_F(TtlCacheTest, PurgeOfAFreshCacheRemovesNothing) {
    cache.put("/a", "1");
    cache.put("/b", "2");
    EXPECT_EQ(cache.purge_expired(), 0u);
    EXPECT_EQ(cache.size(), 2u);
}

TEST_F(TtlCacheTest, PurgeRemovesAnEntryExactlyAtTheTtl) {
    cache.put("/users/1", "Ala");
    FakeClock::advance(30s);
    EXPECT_EQ(cache.purge_expired(), 1u) << "at exactly 30 s the entry has expired";
}
