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

# get google benchmark
FetchContent_Declare(
        gbenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.6.1
)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
FetchContent_MakeAvailable(gbenchmark)

add_subdirectory(core)
add_subdirectory(dagnabbit)
