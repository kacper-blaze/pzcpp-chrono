// Tests for api_key.cpp. Dates are compared as "YYYY-MM-DD" strings so that failures print readably
// on every compiler (older ones cannot print chrono calendar types).
#include "api_key.h"

#include <gtest/gtest.h>

#include <cstdio>
#include <string>

using namespace std::chrono;

namespace {

std::string iso(year_month_day d) {
    char buf[16];
    std::snprintf(buf, sizeof buf, "%04d-%02u-%02u", static_cast<int>(d.year()),
                  static_cast<unsigned>(d.month()), static_cast<unsigned>(d.day()));
    return buf;
}

}  // namespace

TEST(KeyExpiryTest, SameDayInALaterMonth) {
    EXPECT_EQ(iso(key_expiry(2025y / March / 15d, months{1})), "2025-04-15");
    EXPECT_EQ(iso(key_expiry(2025y / March / 15d, months{0})), "2025-03-15");
}

TEST(KeyExpiryTest, CrossesTheEndOfTheYear) {
    EXPECT_EQ(iso(key_expiry(2025y / November / 20d, months{3})), "2026-02-20");
}

TEST(KeyExpiryTest, ShortMonthEndsOnItsLastDay) {
    EXPECT_EQ(iso(key_expiry(2025y / January / 31d, months{1})), "2025-02-28");
    EXPECT_EQ(iso(key_expiry(2024y / January / 31d, months{1})), "2024-02-29") << "2024 is a leap year";
    EXPECT_EQ(iso(key_expiry(2025y / August / 31d, months{1})), "2025-09-30");
    EXPECT_EQ(iso(key_expiry(2025y / December / 31d, months{2})), "2026-02-28");
}

TEST(KeyExpiryTest, LeapDayPlusAYear) {
    EXPECT_EQ(iso(key_expiry(2024y / February / 29d, months{12})), "2025-02-28");
    EXPECT_EQ(iso(key_expiry(2024y / February / 29d, months{48})), "2028-02-29");
}

TEST(DaysLeftTest, CountsAcrossMonthAndYearBoundaries) {
    EXPECT_EQ(days_left(2025y / December / 30d, 2026y / January / 2d), 3);
    EXPECT_EQ(days_left(2024y / February / 28d, 2024y / March / 1d), 2) << "2024 has a 29 February";
    EXPECT_EQ(days_left(2025y / January / 1d, 2026y / January / 1d), 365);
}

TEST(DaysLeftTest, ExpiredKeyHasNoDaysLeft) {
    EXPECT_EQ(days_left(2025y / June / 10d, 2025y / June / 10d), 0);
    EXPECT_EQ(days_left(2025y / June / 11d, 2025y / June / 10d), 0);
}

TEST(LastWorkingDayTest, MonthEndingOnAWeekday) {
    EXPECT_EQ(iso(last_working_day(2025y / June)), "2025-06-30");     // Monday
    EXPECT_EQ(iso(last_working_day(2025y / October)), "2025-10-31");  // Friday
}

TEST(LastWorkingDayTest, MonthEndingOnAWeekend) {
    EXPECT_EQ(iso(last_working_day(2025y / May)), "2025-05-30");      // 31st is a Saturday
    EXPECT_EQ(iso(last_working_day(2025y / August)), "2025-08-29");   // 31st is a Sunday
    EXPECT_EQ(iso(last_working_day(2026y / February)), "2026-02-27"); // 28th is a Saturday
}
