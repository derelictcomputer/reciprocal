# lib
file(GLOB src *.h *.cpp)
add_library(dagnabbit STATIC ${src})
target_link_libraries(dagnabbit PUBLIC core)

if (MSVC)
    target_compile_options(dagnabbit PUBLIC /W4 /WX)
else()
    target_compile_options(dagnabbit PUBLIC -Wall -Wextra -pedantic -Werror)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(dagnabbit PUBLIC -fconcepts)
endif()

# tests
file(GLOB test_src test/*.cpp)
add_executable(dagnabbit_tests ${test_src})
target_link_libraries(dagnabbit_tests gtest_main dagnabbit)
add_test(NAME dagnabbit_test COMMAND dagnabbit_tests)

# benchmarks
file(GLOB benchmark_src benchmark/*.cpp)
add_executable(dagnabbit_benchmarks ${benchmark_src})
target_link_libraries(dagnabbit_benchmarks benchmark::benchmark_main dagnabbit)
