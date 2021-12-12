/**
 * Copyright (c) 2021 luambda-dev
 *
 * @file      game.cc
 * @author    Siger Yang (siger.yang@outlook.com)
 * @date      Dec 7, 2021
 *
 */

#include "game.h"

using luambda::game;

game::game() { }

game::~game()
{
}

// TO-DO:
// void game::set_flags(game_flags flags) {}
// void game::add_flags(game_flags flags) {}
// game_flags game::flags() {}

game& luambda::current_game()
{
    static game _game;
    return _game;
}