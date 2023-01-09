#ifndef _LYS_CONFIG_HPP
#define _LYS_CONFIG_HPP 1

#define PLATFORM_WINDOWS 1
#define PLATFORM_LINUX 2

#if defined(_WIN32)
    #define PLATFORM PLATFORM_WINDOWS
#elif defined(__unix__)
    #if defined(__linux__)
        #define PLATFORM PLATFORM_LINUX
    #else
        #error "Unix platform undefined"
    #endif // defined
#else
    #error "Platform undefined"
#endif // defined


#ifdef LYS_BUILD_DLL
    #if (PLATFORM == PLATFORM_WINDOWS)
        #define LYS_API __declspec(dllexport)
    #elif (PLATFORM == PLATFORM_LINUX)
        #define LYS_API
    #endif
#else
    #if (PLATFORM == PLATFORM_WINDOWS)
        #define LYS_API __declspec(dllimport)
    #elif (PLATFORM == PLATFORM_UNIX)
        #define LYS_API
    #endif
#endif // LYS_BUILD_DLL

#endif // _LYS_CONFIG_HPP
