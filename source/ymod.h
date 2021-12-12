#pragma once

#if defined(__linux__)
#define YMOD_LINUX
#elif defined(__APPLE__)
#define YMOD_OSX
#elif defined(_WIN32)
#define YMOD_WINDOWS
#endif

typedef void *YMOD_SHARED_LIB_HANDLE;

#ifdef YMOD_WINDOWS
#include <windows.h>
#define YMOD_SHARED_LIB_OPEN(path) (YMOD_SHARED_LIB_HANDLE) LoadLibrary(path)
#define YMOD_SHARED_LIB_CLOSE(lib) FreeLibrary(lib)
#define YMOD_SHARED_LIB_FUNC(lib, func) GetProcAddress(lib, func)
#else
#include <dlfcn.h>
#define YMOD_SHARED_LIB_OPEN(path) (YMOD_SHARED_LIB_HANDLE) dlopen(path, RTLD_NOW)
#define YMOD_SHARED_LIB_CLOSE(lib) dlclose(lib)
#define YMOD_SHARED_LIB_FUNC(lib, func) dlsym(lib, func)
#endif

#ifdef YMOD_WINDOWS
#define YMOD_DLLEXPORT __declspec(dllexport)
#else
#define YMOD_DLLEXPORT __attribute__((visibility("default")))
#endif
#ifdef __cplusplus
#define YMOD_EXPORT extern "C" YMOD_DLLEXPORT
#else
#define YMOD_EXPORT YMOD_DLLEXPORT
#endif