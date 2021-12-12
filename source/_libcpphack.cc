/**
 * Copyright (c) 2021 luambda-dev
 *
 * @file      _libcpphack.cc
 * @author    Siger Yang (siger.yang@outlook.com)
 * @date      Dec 3, 2021
 *
 */

// This is a C++ hack which avoids using newer CXXABI for compatibility.

#include "ymod.h"
#include <cstdlib>

#ifdef YMOD_WINDOWS
#define HACK_CALL __cdecl
#else
#define HACK_CALL
#endif

extern "C" void __cxa_pure_virtual()
{
    abort();
}

void* HACK_CALL operator new(size_t size)
{
    return malloc(size);
}

void* HACK_CALL operator new[](size_t size)
{
    return malloc(size);
}

void HACK_CALL operator delete(void* p) noexcept
{
    free(p);
}

void HACK_CALL operator delete[](void* p) noexcept
{
    free(p);
}

void HACK_CALL operator delete(void* p, size_t)
{
    free(p);
}
