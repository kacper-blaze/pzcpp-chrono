// The same loop timed twice: once with its result ignored, once with the result used.
#include <chrono>
#include <cstdint>
#include <iostream>

using Clock = std::chrono::steady_clock;

std::uint64_t sum_up_to(std::uint64_t n) {
    std::uint64_t sum = 0;
    for (std::uint64_t i = 0; i < n; ++i) {
        sum += i * i % 7;
    }
    return sum;
}

int main() {
    constexpr std::uint64_t n = 200'000'000;

    auto t0 = Clock::now();
    sum_up_to(n);  // result ignored: the optimizer may delete the whole call
    auto t1 = Clock::now();

    volatile std::uint64_t sink = sum_up_to(n);  // result used: the loop must run
    auto t2 = Clock::now();
    (void)sink;

    std::chrono::duration<double, std::milli> ignored = t1 - t0;
    std::chrono::duration<double, std::milli> used = t2 - t1;
    std::cout << "result ignored: " << ignored.count() << " ms\n";
    std::cout << "result used:    " << used.count() << " ms\n";
}
