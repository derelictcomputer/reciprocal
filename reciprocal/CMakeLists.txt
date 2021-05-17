# lib
file(GLOB src *.h *.cpp)
add_library(reciprocal SHARED ${src})

# tests
file(GLOB test_src test/*.cpp)
add_executable(reciprocal_tests ${test_src})
target_link_libraries(reciprocal_tests gtest_main reciprocal)
add_test(NAME reciprocal_test COMMAND reciprocal_tests)

# automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(unit_tests
    PROPERTIES
    LABELS "unit"
    DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240)