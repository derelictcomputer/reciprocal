# lib
file(GLOB src *.h *.cpp)
add_library(dagnabbit SHARED ${src})

enable_testing()

add_subdirectory(test)
