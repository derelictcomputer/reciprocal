# lib
file(GLOB src *.h *.cpp)
add_library(reciprocal SHARED ${src})

# get gtest
include(FetchContent)
FetchContent_Declare(gtest
        QUIET
        URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
        )
# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

#enable testing
include(CTest)

# tests
file(GLOB test_src test/*.cpp)
add_executable(reciprocal_tests ${test_src})
target_link_libraries(reciprocal_tests gtest_main reciprocal)
add_test(NAME reciprocal_test COMMAND reciprocal_tests)

# automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(reciprocal_tests
    PROPERTIES
    LABELS "unit"
    DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240)