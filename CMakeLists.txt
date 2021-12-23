cmake_minimum_required(VERSION 3.19)
project(reciprocal)

set(CMAKE_CXX_STANDARD 20)

# use sanitizers if appropriate
include(cmake/sanitizers.cmake)

# get gtest
include(FetchContent)
FetchContent_Declare(
        gtest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

enable_testing()

add_subdirectory(dagnabbit)
