cmake_minimum_required(VERSION 3.27)

if (PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
    message("WARN: PROJECT_BINARY_DIR == PROJECT_SOURCE_DIR")
endif()

set(CMAKE_CXX_EXTENSIONS OFF)
if (NOT CMAKE_BUILD_TYPE)
    message("default set CMAKE_BUILD_TYPE to Release")
    set(CMAKE_BUILD_TYPE Release)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("DEBUG MODE")
    set(FIRE_DEBUG_MODE ON)
endif()

if (WIN32)
    add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
endif()

if (NOT MSVC)
    find_program(CCACHE_PROGRAM ccache)
    if (CCACHE_PROGRAM)
        message("Found CCache: ${CCACHE_PROGRAM}")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
    endif()
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(BuildFire)

add_subdirectory(thirdparty)
add_subdirectory(Fire)
add_subdirectory(FireCmd)
