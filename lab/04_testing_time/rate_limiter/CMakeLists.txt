cmake_minimum_required(VERSION 3.22)
project(lab_04_rate_limiter LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/lab.cmake)

add_executable(rate_limiter_tests tests/test_rate_limiter.cpp)
target_include_directories(rate_limiter_tests PRIVATE src ../src)
target_link_libraries(rate_limiter_tests PRIVATE GTest::gtest_main)
gtest_discover_tests(rate_limiter_tests)
