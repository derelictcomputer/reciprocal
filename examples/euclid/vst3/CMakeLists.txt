message("<3 Including Euclid VST3")

# disable all the VST stuff we don't need
set(SMTG_ADD_VSTGUI OFF CACHE BOOL "" FORCE)
set(SMTG_ADD_VST3_PLUGINS_SAMPLES OFF CACHE BOOL "" FORCE)
set(SMTG_RUN_VST_VALIDATOR OFF CACHE BOOL "" FORCE)

# get the VST SDK
FetchContent_Declare(
        vstsdk
        GIT_REPOSITORY https://github.com/steinbergmedia/vst3sdk.git
        GIT_TAG v3.7.4_build_25
)
FetchContent_MakeAvailable(vstsdk)

# HACK: the VST SDK loses its place when used as a subproject
set(SDK_ROOT ${vstsdk_SOURCE_DIR})
set(public_sdk_SOURCE_DIR ${SDK_ROOT}/public.sdk)

# Plugin config
set(target euclid_vst3)
file(GLOB plug_sources *.h *.cpp)
smtg_add_vst3plugin(${target} SOURCES_LIST ${plug_sources})
target_include_directories(${target} PUBLIC
        ${SDK_ROOT}/public.sdk
        ${SDK_ROOT}/plugininterfaces
        ${SDK_ROOT}/base)
target_link_libraries(${target} PRIVATE sdk euclid)

# turn off running validator after build, because if it fails it deletes the binary,
# and there's no way to debug
add_dependencies(${target} validator)

if(SMTG_MAC)
    smtg_target_set_bundle(${target} INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" PREPROCESS)
elseif(SMTG_WIN)
    target_sources(${target} PRIVATE resource/plug.rc)
endif(SMTG_MAC)
