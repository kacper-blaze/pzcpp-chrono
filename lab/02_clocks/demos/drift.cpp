// A periodic task: 50 ticks of 20 ms each, every tick does 3 ms of "work".
// Ideal total: 50 * 20 ms = 1000 ms.
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono;
using Clock = steady_clock;

constexpr int ticks = 50;
constexpr auto period = 20ms;
constexpr auto work = 3ms;

void do_work() {
    auto end = Clock::now() + work;
    while (Clock::now() < end) {
        // busy "work"
    }
}

milliseconds with_sleep_for() {
    auto start = Clock::now();
    for (int i = 0; i < ticks; ++i) {
        do_work();
        std::this_thread::sleep_for(period);  // "wait 20 ms from now"
    }
    return duration_cast<milliseconds>(Clock::now() - start);
}

milliseconds with_sleep_until() {
    auto start = Clock::now();
    auto next = start;
    for (int i = 0; i < ticks; ++i) {
        do_work();
        next += period;
        std::this_thread::sleep_until(next);  // "wait until tick i+1 of the schedule"
    }
    return duration_cast<milliseconds>(Clock::now() - start);
}

int main() {
    std::cout << "ideal:       " << (ticks * period).count() << " ms\n";
    std::cout << "sleep_for:   " << with_sleep_for().count() << " ms\n";
    std::cout << "sleep_until: " << with_sleep_until().count() << " ms\n";
}
