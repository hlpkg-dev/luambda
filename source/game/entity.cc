/**
 * Copyright (c) 2021 luambda-dev
 *
 * @file      entity.cc
 * @author    Siger Yang (siger.yang@outlook.com)
 * @date      Nov 29, 2021
 *
 */

#include "util.h"

#include "entity.h"

using luambda::entity;

// stands for a basic entity in the game
entity::entity() : _ent(nullptr) { }
entity::entity(std::nullptr_t) : _ent(nullptr) { }
entity::entity(edict_t* ent) : _ent(ent) { }
entity::entity(const entvars_t* pev) : _ent(pev->pContainingEntity) { }

entity entity::find_by_index(int index)
{
    return edict_by_index(index);
}

bool entity::is_valid()
{
    // the entity is valid iff "edict" exists and it has not been freed.
    return (_ent != nullptr) && (_ent->free);
}

void entity::set_origin(const vec3_t& origin)
{
    _ent->v.origin = origin;
}

void entity::set_velocity(const vec3_t& velocity)
{
    _ent->v.velocity = velocity;
}
edict_t* entity::raw_entity()
{
    return _ent;
}
edict_t* entity::edict()
{
    return _ent;
}
entvars_t* entity::entvars()
{
    return &_ent->v;
}
entvars_t* entity::pev()
{
    return &_ent->v;
}