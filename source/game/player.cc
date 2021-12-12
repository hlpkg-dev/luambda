/**
 * Copyright (c) 2021 luambda-dev
 *
 * @file      player.cc
 * @author    Siger Yang (siger.yang@outlook.com)
 * @date      Dec 2, 2021
 *
 */

#include "util.h"

#include "entity.h"
#include "player.h"

using luambda::player;

player player::find_by_index(int index)
{
    // player index ranges in [1, maxClients]
    if(index > 0 && index <= globals->maxClients)
    {
        auto edict = edict_by_index(index);
    }
    return nullptr;
}

void player::print_console(const char *message)
{
    client_printf(_ent, PRINT_TYPE::print_console, message);
}
