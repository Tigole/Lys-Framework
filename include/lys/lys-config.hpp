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

#ifdef LYS_BUILD_STATIC
#define LYS_API
#else
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
#endif  // LYS_BUILD_STATIC

#define LYS_CLASS_NO_COPY(class_type)                  \
private:                                               \
    class_type& operator=(const class_type&) = delete; \
    class_type(const class_type&)            = delete;

#define LYS_DECL_IMPL_PART_SINGLETON(class_type)     \
LYS_CLASS_NO_COPY(class_type) private: class_type(); \
                                                     \
public:                                              \
    static class_type& smt_Get()                     \
    {                                                \
        static class_type ls_Singleton;              \
        return ls_Singleton;                         \
    }

#include <cassert>
#define LYS_ASSERT(expr) assert((expr))

#endif  // _LYS_CONFIG_HPP
