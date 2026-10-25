cmake_minimum_required(VERSION 3.22)
project(lab_03_calendar LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/lab.cmake)

add_library(api_key src/api_key.cpp)
target_include_directories(api_key PUBLIC src)

add_executable(api_key_tests tests/test_api_key.cpp)
target_link_libraries(api_key_tests PRIVATE api_key GTest::gtest_main)
gtest_discover_tests(api_key_tests)
