# lib
file(GLOB src *.h *.cpp)
add_library(core SHARED ${src})
set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(core PUBLIC /W4 /WX)
else()
    target_compile_options(core PUBLIC -Wall -Wextra -pedantic -Werror)
endif()

# tests
file(GLOB test_src test/*.cpp)
add_executable(core_tests ${test_src})
target_link_libraries(core_tests gtest_main core)
add_test(NAME core_test COMMAND core_tests)

# benchmarks
file(GLOB benchmark_src benchmark/*.cpp)
add_executable(core_benchmarks ${benchmark_src})
target_link_libraries(core_benchmarks benchmark::benchmark core)
