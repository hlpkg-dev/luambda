/**
 * Copyright (c) 2021 luambda-dev
 *
 * @file      game.h
 * @author    Siger Yang (siger.yang@outlook.com)
 * @date      Dec 7, 2021
 *
 */

#pragma once

#include <vector>

#include "scripting/bridge.h"

namespace luambda
{
    enum game_flags
    {
        GAME_METAMOD = 1,
        GAME_REHLDS = 1 << 1
    };
    class game
    {
    private:
        std::vector<bridge *> _bridges;
        game_flags _flags;
    public:
        game();
        ~game();
        // void set_flags(game_flags flags);
        // void add_flags(game_flags flags);
        // game_flags flags();
    };
    game& current_game();
};
