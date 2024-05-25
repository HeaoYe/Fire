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
