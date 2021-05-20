# lib
file(GLOB src *.h *.cpp)
add_library(dagnabbit SHARED ${src})

# get gtest
include(FetchContent)
FetchContent_Declare(
    gtest
    URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

# tests
file(GLOB test_src test/*.cpp)
add_executable(dagnabbit_tests ${test_src})
target_link_libraries(dagnabbit_tests gtest_main dagnabbit)
add_test(NAME dagnabbit_test COMMAND dagnabbit_tests)
