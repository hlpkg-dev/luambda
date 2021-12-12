/**
 * Copyright (c) 2021 luambda-dev
 * 
 * @file      wrapper.h
 * @author    Siger Yang (sigeryeung@gmail.com)
 * @date      Nov 23, 2021
 * 
 */

#pragma once

#include <extdll.h>
#include <dllapi.h>
#include <h_export.h>
#include <meta_api.h> 
#include <sdk_util.h>
#include "ymod.h"

extern meta_globals_t *gpMetaGlobals;
extern gamedll_funcs_t *gpGamedllFuncs;

extern globalvars_t *gpGlobals;
extern globalvars_t *globals;

extern mutil_funcs_t *gpMetaUtilFuncs;
extern enginefuncs_t meta_engfuncs;
extern enginefuncs_t g_engfuncs;

YMOD_EXPORT int GetEngineFunctions(enginefuncs_t *pengfuncsFromEngine,
                                   int *interfaceVersion);
YMOD_EXPORT int GetEntityAPI2(DLL_FUNCTIONS *table, int *interfaceVersion);

YMOD_EXPORT int Meta_Query(char *interfaceVersion,
                          plugin_info_t **pPlugInfo, mutil_funcs_t *pMetaUtilFuncs);
YMOD_EXPORT int Meta_Attach(PLUG_LOADTIME now,
                            META_FUNCTIONS *pFunctionTable,
                            meta_globals_t *pMGlobals,
                            gamedll_funcs_t *pGamedllFuncs);
YMOD_EXPORT int Meta_Detach(PLUG_LOADTIME now,
                            PL_UNLOAD_REASON reason);

// TO-DO: some feature flags about the game engine

// enum wrapper_flags
// {
//     METAMOD = 1 << 0,
//     REHLDS = 1 << 1
// };

// class wrapper
// {
// public:
//     wrapper_flags flags;
// };