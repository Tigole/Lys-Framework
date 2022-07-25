#ifndef _LYS_CONFIG_HPP
#define _LYS_CONFIG_HPP 1

#ifdef LYS_BUILD_DLL
#define LYS_API __declspec(dllexport)
#else
#define LYS_API __declspec(dllimport)
#endif // LYS_BUILD_DLL

#endif // _LYS_CONFIG_HPP
