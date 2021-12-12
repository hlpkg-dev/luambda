/**
 * Copyright (c) 2021 luambda-dev
 *
 * @file      util.h
 * @author    Siger Yang (siger.yang@outlook.com)
 * @date      Dec 3, 2021
 *
 */

#pragma once

#include "wrapper.h"

// rewrapping engine functions, gamedll functions etc. in "wrapper.h"

namespace luambda
{
    inline edict_t* edict_by_index(int index)
    {
        return (*g_engfuncs.pfnPEntityOfEntIndex)(index);
    }
    inline int index_of_edict(edict_t* edict)
    {
        return (*g_engfuncs.pfnIndexOfEdict)(edict);
    }
    inline void client_printf(edict_t* edict, PRINT_TYPE type, const char* message)
    {
        return (*g_engfuncs.pfnClientPrintf)(edict, type, message);
    }
    inline int user_id(edict_t* edict)
    {
        return (*g_engfuncs.pfnGetPlayerUserId)(edict);
    }
};
