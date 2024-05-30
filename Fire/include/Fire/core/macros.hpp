#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#if defined (FIRE_PLATFORM_WINDOWS) && defined (FIRE_BUILD_SHARED)
    #if defined (FIRE_BUILD_SHARED_EXPORT)
        #define FIRE_API __declspec(dllexport)
    #else
        #define FIRE_API __declspec(dllimport)
    #endif
#else
    #define FIRE_API
#endif

#define JOIN(x, ...) __INTERNAL_JOIN(x, __VA_ARGS__)
#define __INTERNAL_JOIN(x, ...) x##__VA_ARGS__

#define REMOVE_OPTIONAL_PARENS(...) JOIN(__INTERNAL_REMOVE_OPTIONAL_PARENS, __INTERNAL_REMOVE_OPTIONAL_PARENS __VA_ARGS__)
#define __INTERNAL_REMOVE_OPTIONAL_PARENS(...) __INTERNAL_REMOVE_OPTIONAL_PARENS __VA_ARGS__
#define __INTERNAL_REMOVE_OPTIONAL_PARENS__INTERNAL_REMOVE_OPTIONAL_PARENS
