/**
 * Copyright (c) 2021 luambda-dev
 * 
 * @file      bridge.cc
 * @author    Siger Yang (siger.yang@outlook.com)
 * @date      Dec 2, 2021
 * 
 */

#include "bridge.h"
#include "lauxlib.h"
#include "lua.h"
#include <cstdarg>
#include <cstring>
#include <cstdlib>

using luambda::bridge;

bridge::bridge() : L(luaL_newstate()), _callback_n(0)
{
    lua_pushlightuserdata(L, this);
    lua_setglobal(L, "__bridge");
    luaL_openlibs(L);
    luaopen_luambda(L);
    lua_settop(L, 0);
}

bridge::~bridge()
{
    for(auto& callbacks : _hook_map)
    {
        for(auto& callback : callbacks)
        {
            if(callback.type == CALLBACK_NAME)
            {
                free((void *) callback.callback_name);
            }
            else
            {
                luaL_unref(L, LUA_REGISTRYINDEX, callback.closure_ref);
            }
        }
    }
    lua_close(L);
}

void bridge::register_hook_name(hook::hook_type type, const char* name)
{
    _hook_map[type].push_back(
        hook_callback{
            hook_callback_type::CALLBACK_CLOSURE,
            {.callback_name = strdup(name)}
        }
    );
}

void bridge::register_hook_closure(hook::hook_type type, int ref)
{
    fprintf(stderr, "[HOOK] Hook %u with closure %d.\n", type, ref);
    _hook_map[type].push_back(
        hook_callback{
            hook_callback_type::CALLBACK_CLOSURE,
            {.closure_ref = ref}
        }
    );
}

bridge::load_result bridge::load_plugin(const char* filename)
{
    lua_createtable(L, 0, 1);
    lua_createtable(L, 0, 1);
    lua_pushvalue(L, LUA_GLOBALSINDEX);
    lua_setfield(L, -2, "__index");
    lua_setmetatable(L, -2);
    int result = luaL_loadfile(L, filename);
    lua_pushvalue(L, -2);
    lua_setfenv(L, -2);
    switch(result)
    {
        case LUA_OK:
        {
            if(lua_pcall(L, 0, 0, 0) != 0)
            {
                fprintf(stderr, "%s\n", lua_tostring(L, -1));
                return LOAD_RUNTIME_ERROR;
            }
            _plugins.push_back(plugin{strdup(filename), luaL_ref(L, LUA_REGISTRYINDEX)});
            return LOAD_OK;
        }
        case LUA_ERRFILE:
            return LOAD_FILE_ERROR;
        case LUA_ERRSYNTAX:
            return LOAD_SYNTAX_ERROR;
        case LUA_ERRMEM:
        default:
            return LOAD_OTHER_ERROR;
    }
}

bool bridge::has_internal(void* env)
{
    return env == (void*)L;
}

void bridge::_hook_callback(hook::hook_type type)
{
    auto& v = _hook_map[type];
    for(int i = 0; i < v.size(); i++)
    {
        switch(v[i].type)
        {
            case CALLBACK_NAME:
                // lua_rawgeti(L, LUA_REGISTRYINDEX, );
                break;
            case CALLBACK_CLOSURE:
                lua_rawgeti(L, LUA_REGISTRYINDEX, v[i].closure_ref);
                // replicate arguments since lua_pcall will eat them
                for(int i = 1; i <= _callback_n; i++)
                {
                    lua_pushvalue(L, i);
                }
                if(lua_pcall(L, _callback_n, 0, 0) != 0)
                {
                    fprintf(stderr, "%s\n", lua_tostring(L, -1));
                }
                else
                {

                }
                break;
        }
    }
    _callback_n = 0;
}
// void lua_bridge::forward_hook(const char* name, ...)
// {
//     if(strcmp(name, "client_connect") == 0)
//     {

//     }
// }
