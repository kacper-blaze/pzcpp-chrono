# Common settings for every project in the lab.
#
# Usage (in a topic's CMakeLists.txt, right after project()):
#   include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/lab.cmake)
#
# Provides: C++20, warnings, GoogleTest + gMock (targets GTest::gtest_main,
# GTest::gmock_main), enable_testing() and include(GoogleTest).

include_guard(GLOBAL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(MSVC)
  add_compile_options(/W4 /utf-8)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# GoogleTest is downloaded only once (into lab/_deps) and shared by all
# topics; each project still builds its own copy with its own compiler flags.
set(LAB_GTEST_VERSION 1.18.0)
set(LAB_GTEST_SHA256 6e3191c1455468b3fc35a417fb565c1c5071aee1b7e7f85e30cf48a98d37d8b5)
set(LAB_GTEST_URL
    https://github.com/google/googletest/releases/download/v${LAB_GTEST_VERSION}/googletest-${LAB_GTEST_VERSION}.tar.gz)
set(LAB_DEPS_DIR ${CMAKE_CURRENT_LIST_DIR}/../_deps)
set(LAB_GTEST_ARCHIVE ${LAB_DEPS_DIR}/googletest-${LAB_GTEST_VERSION}.tar.gz)

if(NOT EXISTS ${LAB_GTEST_ARCHIVE})
  message(STATUS "Downloading GoogleTest ${LAB_GTEST_VERSION}")
  file(DOWNLOAD ${LAB_GTEST_URL} ${LAB_GTEST_ARCHIVE}.part
       EXPECTED_HASH SHA256=${LAB_GTEST_SHA256}
       STATUS download_status)
  list(GET download_status 0 download_code)
  if(NOT download_code EQUAL 0)
    file(REMOVE ${LAB_GTEST_ARCHIVE}.part)
    message(FATAL_ERROR "GoogleTest download failed: ${download_status}")
  endif()
  file(RENAME ${LAB_GTEST_ARCHIVE}.part ${LAB_GTEST_ARCHIVE})
endif()

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL ${LAB_GTEST_ARCHIVE}
  URL_HASH SHA256=${LAB_GTEST_SHA256}
)
# MSVC: link gtest with the same runtime library as our code.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)
