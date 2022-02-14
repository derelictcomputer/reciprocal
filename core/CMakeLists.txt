# lib
add_library(core INTERFACE)
set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

if (MSVC)
    target_compile_options(core INTERFACE /W4 /WX)
else()
    target_compile_options(core INTERFACE -Wall -Wextra -pedantic -Werror)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(core PUBLIC -fconcepts)
endif()

# tests
file(GLOB test_src test/*.cpp)
add_executable(core_tests ${test_src})
target_link_libraries(core_tests gtest_main core)
add_test(NAME core_test COMMAND core_tests)

# benchmarks
file(GLOB benchmark_src benchmark/*.cpp)
add_executable(core_benchmarks ${benchmark_src})
target_link_libraries(core_benchmarks benchmark::benchmark_main core)
