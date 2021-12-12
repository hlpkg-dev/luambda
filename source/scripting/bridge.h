/**
 * Copyright (c) 2021 luambda-dev
 *
 * @file      bridge.h
 * @author    Siger Yang (siger.yang@outlook.com)
 * @date      Dec 2, 2021
 *
 */

#pragma once

#include "game/entity.h"
#include "game/player.h"
#include "hook.h"

#include <lua.hpp>
#include <vector>

// library entry generated by SWIG
extern "C" int luaopen_luambda(lua_State* L);

extern void lua_push_object(lua_State* L, const luambda::entity& entity);
extern void lua_push_object(lua_State* L, const luambda::player& player);
extern void lua_push_object(lua_State* L, int value);
extern void lua_push_object(lua_State* L, const char* cstr);

namespace luambda
{
    struct plugin
    {
        // plugin name
        const char* name;
        // reference id by luaL_ref
        int fake_env_id;
    };
    class bridge final
    {
        // there are 2 types of hook callbacks
        // CALLBACK_NAME stands for a string of global function name
        // CALLBACK_CLOSURE stands for a immediate closure / any other closures
        enum hook_callback_type
        {
            CALLBACK_NAME,
            CALLBACK_CLOSURE
        };
        enum load_result
        {
            LOAD_OK,
            LOAD_RUNTIME_ERROR,
            LOAD_FILE_ERROR,
            LOAD_SYNTAX_ERROR,
            LOAD_OTHER_ERROR
        };
        struct hook_callback
        {
            hook_callback_type type;
            union
            {
                // this pointer is managed by us
                const char* callback_name;
                // this ref is managed by lua
                int closure_ref;
            };
        };
 
    protected:
        lua_State* L;
        std::vector<hook_callback> _hook_map[hook::hook_type::HOOK_COUNT];
        std::vector<plugin> _plugins;

        size_t _callback_n;
        template<typename T> void _prepare_argument(T& arg)
        {
            lua_push_object(L, arg);
            _callback_n++;
        }
        void _hook_callback(hook::hook_type type);

    public:
        bridge();
        ~bridge();
        load_result load_plugin(const char* filename);
        void register_hook_name(hook::hook_type type, const char *name);
        void register_hook_closure(hook::hook_type type, int ref);
        bool has_internal(void* env);
        template<typename T, typename... V>
        inline void forward_hook(hook::hook_type type, const T& arg, const V&... args)
        {
            // lua_pushinteger(L, arg);
            _prepare_argument(arg);
            forward_hook(type, args...);
        }
        inline void forward_hook(hook::hook_type type)
        {
            _hook_callback(type);
        }
    };
};