/**
 * Copyright (c) 2021 luambda-dev
 * 
 * @file      wrapper.cc
 * @author    Siger Yang (sigeryeung@gmail.com)
 * @date      Nov 23, 2021
 * 
 */

#include "scripting/bridge.h"
#include "scripting/hook.h"
#include "game/player.h"
#include "wrapper.h"
#include <cstdio>
#include <string>

meta_globals_t* gpMetaGlobals;
gamedll_funcs_t* gpGamedllFuncs;
globalvars_t* gpGlobals;
mutil_funcs_t* gpMetaUtilFuncs = nullptr;
globalvars_t* globals = nullptr;
enginefuncs_t meta_engfuncs = { nullptr };
enginefuncs_t g_engfuncs;

static DLL_FUNCTIONS gFunctionTable = { nullptr };

plugin_info_t Plugin_info = {
    const_cast<char*>(META_INTERFACE_VERSION),
    const_cast<char*>("luambda"),
    const_cast<char*>("0.1"),
    const_cast<char*>("2021"),
    const_cast<char*>("luambda"),
    const_cast<char*>(""),
    const_cast<char*>("LUAHL"),
    PT_ANYTIME,
    PT_ANYPAUSE,
};

luambda::bridge bridge;

YMOD_EXPORT int GetEntityAPI2(DLL_FUNCTIONS* table, int* interfaceVersion)
{
    if(!table)
    {
        return false;
    }
    else if(*interfaceVersion != INTERFACE_VERSION)
    {
        *interfaceVersion = INTERFACE_VERSION;
        return false;
    }
    memset(table, 0, sizeof(DLL_FUNCTIONS));
    table->pfnServerActivate = [](edict_t*, int, int)
    {
        bridge.load_plugin("cstrike/test.lua");
    };
    table->pfnClientConnect = [](edict_t* ent, const char* name, const char* ip, char* reject)
    {
        bridge.forward_hook(luambda::hook::hook_type::CLIENT_CONNECT, luambda::player(ent), name, ip);
        return 0;
    };
    return true;
};

YMOD_EXPORT int GetEngineFunctions(enginefuncs_t* table, int* interfaceVersion)
{
    if(!table)
    {
        return false;
    }
    else if(*interfaceVersion != ENGINE_INTERFACE_VERSION)
    {
        *interfaceVersion = ENGINE_INTERFACE_VERSION;
        return false;
    }
    memset(table, 0, sizeof(enginefuncs_t));
    return true;
}

void GiveFnptrsToDll(enginefuncs_t* pengfuncsFromEngine, globalvars_t* pGlobals)
{
    memcpy(&g_engfuncs, pengfuncsFromEngine, sizeof(enginefuncs_t));
    gpGlobals = globals = pGlobals;
}

// metamod wrapper
YMOD_EXPORT int Meta_Query(char* interfaceVersion, plugin_info_t** pPlugInfo,
    mutil_funcs_t* pMetaUtilFuncs)
{
    *pPlugInfo = &Plugin_info;
    gpMetaUtilFuncs = pMetaUtilFuncs;
    return true;
};

YMOD_EXPORT int Meta_Attach(PLUG_LOADTIME now, META_FUNCTIONS* pFunctionTable,
    meta_globals_t* pMGlobals, gamedll_funcs_t* pGamedllFuncs)
{
    if(!pMGlobals)
    {
        LOG_ERROR(PLID, "Meta_Attach called with null pMGlobals");
        return false;
    }
    gpMetaGlobals = pMGlobals;
    if(!pFunctionTable)
    {
        LOG_ERROR(PLID, "Meta_Attach called with null pFunctionTable");
        return false;
    }

    memset(pFunctionTable, 0, sizeof(META_FUNCTIONS));
    pFunctionTable->pfnGetEntityAPI2 = GetEntityAPI2;
    pFunctionTable->pfnGetEngineFunctions = GetEngineFunctions;
    gpGamedllFuncs = pGamedllFuncs;
    return true;
}

YMOD_EXPORT int Meta_Detach(PLUG_LOADTIME now, PL_UNLOAD_REASON reason)
{
    return true;
}
