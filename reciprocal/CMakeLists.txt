# lib
file(GLOB src *.h *.cpp)
add_library(reciprocal SHARED ${src})

# tests
file(GLOB test_src test/*.cpp)
add_executable(reciprocal_tests ${test_src})
target_link_libraries(reciprocal_tests gtest_main reciprocal)
add_test(NAME reciprocal_test COMMAND reciprocal_tests)
