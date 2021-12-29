# lib
file(GLOB src *.h *.cpp)
add_library(dagnabbit SHARED ${src})
set_target_properties(dagnabbit PROPERTIES LINKER_LANGUAGE CXX)

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
