project(Fire)

option(FILE_BUILD_SHARED OFF)

set(CMAKE_C_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE source CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE headers CONFIGURE_DEPENDS include/*.hpp)

if (FILE_BUILD_SHARED)
    add_library(Fire SHARED ${source} ${headers})
else()
    add_library(Fire STATIC ${source} ${headers})
endif()

target_include_directories(Fire PUBLIC include)
target_include_directories(Fire PRIVATE include/Fire)

target_link_libraries(Fire PUBLIC spdlog)

if (FIRE_DEBUG_MODE)
    target_compile_definitions(Fire PUBLIC FIRE_DEBUG_MODE)
endif()

if (WIN32)
    target_compile_definitions(Fire PUBLIC FIRE_PLATFORM_WINDOWS)
    if (FIRE_BUILD_SHARED)
        target_compile_definitions(Fire PUBLIC FIRE_BUILD_SHARED)
        target_compile_definitions(Fire PRIVATE FIRE_BUILD_SHARED_EXPORT)
    endif()
endif()
