cmake_minimum_required(VERSION 3.22)
project(lab_smoke LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/lab.cmake)

add_executable(smoke_tests smoke_test.cpp)
target_link_libraries(smoke_tests PRIVATE GTest::gmock_main)
gtest_discover_tests(smoke_tests)
