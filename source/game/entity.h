/**
 * Copyright (c) 2021 luambda-dev
 *
 * @file      entity.h
 * @author    Siger Yang (siger.yang@outlook.com)
 * @date      Dec 2, 2021
 *
 */

#pragma once

#include <extdll.h>
#include <cstddef>

namespace luambda
{
    class entity
    {
    protected:
        edict_t* _ent;

    public:
        // these are invalid entities, should be ignored, or created soon.
        entity();
        entity(std::nullptr_t);

        // entity does not have other states, keep the default copy constructor
        entity(const entity&) = default;

        entity(edict_t* ent);
        entity(const entvars_t* pev);
        static entity find_by_index(int index);
        bool is_valid();
        void set_origin(const vec3_t& origin);
        void set_velocity(const vec3_t& velocity);
        edict_t* raw_entity();
        edict_t* edict();
        entvars_t* pev();
        entvars_t* entvars();
    };
};
