message("<3 Adding Reciprocal Editor")

# configure Dear ImGui
# NB: we're using GLFW and OpenGL 3 for every platform for now, because it's cross-platform.
# But we might need to switch Mac to Metal and Win to Vulkan and so on.
message("<3 Configuring Dear ImGui for GLFW and OpenGL3")
find_package(OpenGL REQUIRED)
if (NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL is required")
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL Linux)
    find_package(X11 REQUIRED)
    if (NOT X11_Xi_FOUND)
        message(FATAL_ERROR "X11 Xi library is required")
    endif ()
endif ()

if (NOT TARGET glad)
    FetchContent_Declare(
            glad
            GIT_REPOSITORY https://github.com/Dav1dde/glad.git
            GIT_TAG master
    )
    FetchContent_MakeAvailable(glad)
endif ()

if (NOT TARGET glfw)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_TAG master
    )
    FetchContent_MakeAvailable(glfw)
endif ()

set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG docking
)
FetchContent_GetProperties(imgui)
if (NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
    set(IMGUI_INCLUDE_DIR ${imgui_SOURCE_DIR}/)
    file(GLOB IMGUI_SOURCES ${imgui_SOURCE_DIR}/*.cpp)
    file(GLOB IMGUI_HEADERS ${imgui_SOURCE_DIR}/*.h)
    list(APPEND IMGUI_SOURCES
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)
    add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS})
    add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
    target_include_directories(imgui PUBLIC
            ${IMGUI_INCLUDE_DIR}
            ${OPENGL_INCLUDE_DIR}
            ${GLFW_INCLUDE_DIR}
            ${GLAD_INCLUDE_DIR})
    target_link_libraries(imgui ${OPENGL_LIBRARIES} glfw glad)
endif()

# Get and configure imnodes
FetchContent_Declare(
        imnodes
        GIT_REPOSITORY https://github.com/Nelarius/imnodes.git
        GIT_TAG master
)
FetchContent_GetProperties(imnodes)
if (NOT imnodes_POPULATED)
    FetchContent_Populate(imnodes)
    add_library(imnodes STATIC
            ${imnodes_SOURCE_DIR}/imnodes.h
            ${imnodes_SOURCE_DIR}/imnodes_internal.h
            ${imnodes_SOURCE_DIR}/imnodes.cpp)
    target_include_directories(imnodes PUBLIC ${imnodes_SOURCE_DIR})
    target_link_libraries(imnodes PUBLIC imgui)
endif()

# editor executable
set(target editor)
file(GLOB src *.h *.cpp)
add_executable(${target} MACOSX_BUNDLE ${src})
set_target_properties(
        ${target} PROPERTIES
        OUTPUT_NAME "Reciprocal Editor"
        BUNDLE True
        MACOSX_BUNDLE_GUI_IDENTIFIER com.derelictcomputer.reciprocaleditor
        MACOSX_BUNDLE_BUNDLE_NAME "Reciprocal Editor"
        MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
)
target_link_libraries(${target} PUBLIC dagnabbit imnodes)

if (MSVC)
    target_compile_options(${target} PUBLIC /W4 /WX)
else()
    target_compile_options(${target} PUBLIC -Wall -Wextra -pedantic -Werror)
endif()
