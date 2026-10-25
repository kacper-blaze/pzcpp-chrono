#pragma once

#include <chrono>

// Validity of the API client's key and its billing date.

// The key issued on `issued` is valid for `validity` months. If the resulting month is too short
// for the day (e.g. 31 January + 1 month), the key expires on the LAST day of that month:
// 2025-01-31 + 1 month -> 2025-02-28, 2024-01-31 + 1 month -> 2024-02-29.
std::chrono::year_month_day key_expiry(std::chrono::year_month_day issued, std::chrono::months validity);

// Whole days from `today` until `expiry` (2025-12-30 -> 2026-01-02 is 3). An expired key has 0 days left.
int days_left(std::chrono::year_month_day today, std::chrono::year_month_day expiry);

// Billing happens on the last working day (Monday-Friday) of the month; public holidays are ignored.
// May 2025 ends on a Saturday, so its last working day is 2025-05-30.
std::chrono::year_month_day last_working_day(std::chrono::year_month ym);
