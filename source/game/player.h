/**
 * Copyright (c) 2021 luambda-dev
 *
 * @file      player.h
 * @author    Siger Yang (siger.yang@outlook.com)
 * @date      Dec 2, 2021
 *
 */

#pragma once

#include "entity.h"

namespace luambda
{
    class player : public entity
    {
    private:
    public:
        // simply re-use entity constructor
        using entity::entity;

        static player find_by_index(int index);
        void print_console(const char* message);
    };
};
