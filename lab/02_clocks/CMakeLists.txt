cmake_minimum_required(VERSION 3.22)
project(lab_02_clocks LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/lab.cmake)

add_library(client_timing src/client_timing.cpp)
target_include_directories(client_timing PUBLIC src)

add_executable(client_timing_tests tests/test_client_timing.cpp)
target_link_libraries(client_timing_tests PRIVATE client_timing GTest::gtest_main)
gtest_discover_tests(client_timing_tests)
