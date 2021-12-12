#include "ymod.h"
#include <cstdio>
#include <cmath>

#include <dlfcn.h>

int main(int argc, const char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s <lib>\n", argv[0]);
        return 1;
    }
    YMOD_SHARED_LIB_HANDLE handle = YMOD_SHARED_LIB_OPEN(argv[1]);
    if(!handle)
    {
        printf("Error: %s\n", dlerror());
    }
    return 0;
}