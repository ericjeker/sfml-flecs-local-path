// Copyright (c) Eric Jeker. All Rights Reserved.

#pragma once

#include "flecs.h"

namespace Anime
{

struct TimerSystem
{
    static void Register(const flecs::world& world);
};

}
