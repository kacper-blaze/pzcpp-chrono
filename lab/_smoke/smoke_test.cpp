// Environment check: if this file builds and its tests pass, your compiler,
// CMake and GoogleTest/gMock are ready for the lab.
#include <compare>
#include <optional>
#include <string_view>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

// C++20 features used in the lab exercises.
struct Version {
    int major;
    int minor;
    auto operator<=>(const Version&) const = default;
};

class Greeter {
public:
    virtual ~Greeter() = default;
    virtual std::optional<std::string_view> greeting() const = 0;
};

class MockGreeter : public Greeter {
public:
    MOCK_METHOD(std::optional<std::string_view>, greeting, (), (const, override));
};

}  // namespace

TEST(SmokeTest, CompilerSupportsCpp20Comparisons) {
    EXPECT_LT((Version{1, 17}), (Version{1, 18}));
    EXPECT_EQ((Version{1, 18}), (Version{1, 18}));
}

TEST(SmokeTest, GMockWorks) {
    MockGreeter greeter;
    EXPECT_CALL(greeter, greeting()).WillOnce(::testing::Return("hello"));
    EXPECT_EQ(greeter.greeting(), "hello");
}
