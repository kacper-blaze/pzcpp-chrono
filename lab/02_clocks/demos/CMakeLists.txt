cmake_minimum_required(VERSION 3.22)
project(lab_02_clocks_demos LANGUAGES CXX)

# Timing demos only make sense with optimizations on.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(MSVC)
  add_compile_options(/W4 /utf-8)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(Threads REQUIRED)

add_executable(drift drift.cpp)
target_link_libraries(drift PRIVATE Threads::Threads)

add_executable(bench bench.cpp)

# `cmake --build build --target run_demos` builds and runs both demos on any platform.
add_custom_target(run_demos
  COMMAND drift
  COMMAND bench
  DEPENDS drift bench
  USES_TERMINAL)
