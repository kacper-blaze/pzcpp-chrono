cmake_minimum_required(VERSION 3.22)
project(lab_04_cache LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/lab.cmake)

add_executable(ttl_cache_tests tests/test_ttl_cache.cpp)
target_include_directories(ttl_cache_tests PRIVATE src ../src)
target_link_libraries(ttl_cache_tests PRIVATE GTest::gtest_main)
gtest_discover_tests(ttl_cache_tests)
