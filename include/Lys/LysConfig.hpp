#ifndef _LYS_CONFIG_HPP
#define _LYS_CONFIG_HPP 1

#define LYS_PLATFORM_WINDOWS 1
#define LYS_PLATFORM_LINUX 2

#if defined(_WIN32)
#define LYS_PLATFORM LYS_PLATFORM_WINDOWS
#elif defined(__unix__)
#if defined(__linux__)
#define LYS_PLATFORM LYS_PLATFORM_LINUX
#else
#error "Unix platform undefined"
#endif  // defined
#else
#error "Platform undefined"
#endif  // defined

#ifdef LYS_BUILD_DLL
#if (LYS_PLATFORM == LYS_PLATFORM_WINDOWS)
#define LYS_API __declspec(dllexport)
#elif (LYS_PLATFORM == LYS_PLATFORM_LINUX)
#define LYS_API
#endif
#else
#if (LYS_PLATFORM == LYS_PLATFORM_WINDOWS)
#define LYS_API __declspec(dllimport)
#elif (LYS_PLATFORM == LYS_PLATFORM_LINUX)
#define LYS_API __attribute__((__visibility__("default")))
#endif
#endif  // LYS_BUILD_DLL

#endif  // _LYS_CONFIG_HPP
