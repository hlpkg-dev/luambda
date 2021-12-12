/**
 * Copyright (c) 2021 luambda-dev
 * 
 * @file      hook.h
 * @author    Siger Yang (siger.yang@outlook.com)
 * @date      Dec 9, 2021
 * 
 */

#pragma once

#include <cstring>

namespace luambda
{
    namespace hook
    {
        enum hook_type
        {
            CLIENT_CONNECT,
            // these are not hook types
            HOOK_COUNT,
            UNKNOWN_HOOK = HOOK_COUNT,
        };
        // TO-DO: a hash function for "const char* name" to compare fast
        // int hash(const char* name) { ... }
        inline hook_type type_from_name(const char* name)
        {
            if(name != nullptr)
            {
                if(strcmp(name, "client_connect") == 0)
                {
                    return CLIENT_CONNECT;
                }
            }
            return UNKNOWN_HOOK;
        }
    };
};
