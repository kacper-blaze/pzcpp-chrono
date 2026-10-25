#include "api_key.h"

#include <stdexcept>

std::chrono::year_month_day key_expiry(std::chrono::year_month_day issued, std::chrono::months validity) {
    (void)issued;
    (void)validity;
    throw std::logic_error("TODO: implement key_expiry");
}

int days_left(std::chrono::year_month_day today, std::chrono::year_month_day expiry) {
    (void)today;
    (void)expiry;
    throw std::logic_error("TODO: implement days_left");
}

std::chrono::year_month_day last_working_day(std::chrono::year_month ym) {
    (void)ym;
    throw std::logic_error("TODO: implement last_working_day");
}
