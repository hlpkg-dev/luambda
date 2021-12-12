%module luambda

%include "game.swig"

%{

#include "scripting/hook.h"

// used to push object
void lua_push_object(lua_State* L, const luambda::entity& entity)
{
    SWIG_NewPointerObj(L, &entity, SWIGTYPE_p_luambda__entity, 0);
} 

void lua_push_object(lua_State* L, const luambda::player& player)
{
    SWIG_NewPointerObj(L, &player, SWIGTYPE_p_luambda__player, 0);
}

void lua_push_object(lua_State* L, int value)
{
    lua_pushinteger(L, value);
}

void lua_push_object(lua_State* L, const char* cstr)
{
    lua_pushstring(L, cstr);
}

%}

%native(register_hook) int register_hook(lua_State* L);
%wrapper {

int register_hook(lua_State* L)
{
    lua_getglobal(L, "__bridge");
    luambda::bridge* bridge = (luambda::bridge*) lua_touserdata(L, -1);
    lua_pop(L, 1);

    const char* name = lua_tostring(L, 1);
    printf("REGISTERING HOOK %s.\n", name);
    auto type = luambda::hook::type_from_name(name);

    if(type == luambda::hook::hook_type::UNKNOWN_HOOK)
    {
        return luaL_error(L, "Invalid hook.");
    }
    else if(lua_isfunction(L, 2) || lua_isstring(L, 2))
    {
        if(lua_isfunction(L, 2))
        {
            // a closure
            bridge->register_hook_closure(type, luaL_ref(L, LUA_REGISTRYINDEX));
        }
        else
        {
            // a callback name
            const char* name = lua_tostring(L, 2);
        }
    }
    else
    {
        return luaL_error(L, "Expect a function callback or a function name.");
    }
    return 0;
}

}