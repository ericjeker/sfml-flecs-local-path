// Copyright (c) Eric Jeker. All Rights Reserved.

#include "AnimeModule.h"

#include "Components/Timer.h"
#include "Systems/TimerSystem.h"

namespace Modules
{

AnimeModule::AnimeModule(const flecs::world& world)
{
    world.component<Anime::Timer>();

    Anime::TimerSystem::Register(world);
}

} // namespace Modules
