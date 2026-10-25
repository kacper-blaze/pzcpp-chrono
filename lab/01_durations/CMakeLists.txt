cmake_minimum_required(VERSION 3.22)
project(lab_01_durations LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/lab.cmake)

add_library(usage src/usage.cpp)
target_include_directories(usage PUBLIC src)

add_executable(usage_tests tests/test_usage.cpp)
target_link_libraries(usage_tests PRIVATE usage GTest::gtest_main)
gtest_discover_tests(usage_tests)
