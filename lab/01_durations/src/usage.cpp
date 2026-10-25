#include "usage.h"

#include <stdexcept>

std::chrono::seconds billable_seconds(std::chrono::milliseconds call_time) {
    (void)call_time;
    throw std::logic_error("TODO: implement billable_seconds");
}

std::chrono::minutes minute_bucket(std::chrono::milliseconds offset) {
    (void)offset;
    throw std::logic_error("TODO: implement minute_bucket");
}

std::chrono::duration<double, std::milli> average_latency(const std::vector<std::chrono::milliseconds>& latencies) {
    (void)latencies;
    throw std::logic_error("TODO: implement average_latency");
}
