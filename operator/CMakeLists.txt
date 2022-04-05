set(target operator)

# lib
file(GLOB src *.h *.cpp)
add_library(${target} STATIC ${src})
target_link_libraries(${target} PUBLIC core)

if (MSVC)
    target_compile_options(${target} PUBLIC /W4 /WX)
else()
    target_compile_options(${target} PUBLIC -Wall -Wextra -pedantic -Werror)
endif()

target_include_directories(${target} PUBLIC ${CMAKE_SOURCE_DIR})

# tests
file(GLOB test_src test/*.cpp)
add_executable(${target}_tests ${test_src})
target_link_libraries(${target}_tests gtest_main dagnabbit)
add_test(NAME ${target}_test COMMAND dagnabbit_tests)

# benchmarks
file(GLOB benchmark_src benchmark/*.cpp)
add_executable(${target}_benchmarks ${benchmark_src})
target_link_libraries(${target}_benchmarks benchmark::benchmark_main ${target})
