#pragma once

#include <chrono>
#include <vector>

// Usage accounting for calls to an external API.

// The API bills every started second: 1000 ms costs 1 s, 1001 ms costs 2 s, 0 ms costs nothing.
std::chrono::seconds billable_seconds(std::chrono::milliseconds call_time);

// Statistics are grouped into one-minute slots counted from the start of a session.
// Slot 0 covers [0 ms, 60 000 ms), slot 1 covers [60 000 ms, 120 000 ms), and so on.
// Events logged slightly before the start (clock skew, negative offset) belong to slot -1, -2, ...
std::chrono::minutes minute_bucket(std::chrono::milliseconds offset);

// Mean latency without losing fractions of a millisecond: {1 ms, 2 ms} -> 1.5 ms.
// Throws std::invalid_argument for an empty list.
std::chrono::duration<double, std::milli> average_latency(const std::vector<std::chrono::milliseconds>& latencies);
