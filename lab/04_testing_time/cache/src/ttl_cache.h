#pragma once

#include <chrono>
#include <cstddef>
#include <map>
#include <optional>
#include <stdexcept>
#include <utility>

// Cache of API responses. Every entry expires `ttl` after it was stored:
// with a TTL of 30 s, an entry stored at 0 s is present at 29 s and gone at exactly 30 s.
// The clock is a template parameter, so tests can use FakeClock instead of steady_clock.
template <class Key, class Value, class Clock = std::chrono::steady_clock>
class TtlCache {
public:
    explicit TtlCache(typename Clock::duration ttl) : ttl_(ttl) {}

    // Stores `value` under `key`, valid until now + ttl. Storing an existing key replaces the value
    // and starts its time to live again.
    void put(const Key& key, Value value) {
        (void)key;
        (void)value;
        throw std::logic_error("TODO: implement TtlCache::put");
    }

    // The value stored under `key`, if it has not expired yet (valid while now < expiry time).
    // An expired entry found here is removed from the cache.
    std::optional<Value> get(const Key& key) {
        (void)key;
        throw std::logic_error("TODO: implement TtlCache::get");
    }

    // Removes every expired entry and returns how many were removed.
    std::size_t purge_expired() {
        throw std::logic_error("TODO: implement TtlCache::purge_expired");
    }

    // Number of stored entries, expired or not.
    std::size_t size() const { return entries_.size(); }

private:
    struct Entry {
        Value value;
        typename Clock::time_point expires;
    };

    typename Clock::duration ttl_;
    std::map<Key, Entry> entries_;
};
