# lib
add_library(reciprocal SHARED reciprocal.cpp reciprocal.h)

# tests
add_executable(reciprocal_tests test/test_reciprocal.cpp)
target_link_libraries(reciprocal_tests gtest_main reciprocal)
add_test(NAME reciprocal_test COMMAND reciprocal_tests)
