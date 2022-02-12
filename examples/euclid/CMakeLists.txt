# lib
set(target euclid)
file(GLOB src *.h *.cpp)
add_library(${target} INTERFACE ${src})
target_link_libraries(${target} INTERFACE dagnabbit)

if (MSVC)
    target_compile_options(${target} INTERFACE /W4 /WX)
else()
    target_compile_options(${target} INTERFACE -Wall -Wextra -pedantic -Werror)
endif()

# tests
file(GLOB test_src test/*.cpp)
add_executable(${target}_tests ${test_src})
target_link_libraries(${target}_tests gtest_main ${target})
add_test(NAME ${target}_test COMMAND ${target}_tests)
