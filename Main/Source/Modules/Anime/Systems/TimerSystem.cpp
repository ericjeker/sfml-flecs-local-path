// Copyright (c) Eric Jeker. All Rights Reserved.

#include "TimerSystem.h"

#include "Modules/Anime/Components/Timer.h"

namespace Anime
{

void TimerSystem::Register(const flecs::world& world)
{
    world.system<Timer>().each([](const flecs::entity& e, Timer& timer) {
        const float dt = e.world().delta_time();

        timer.elapsed += dt;

        // Update the timer every time the game loop progresses
        if (timer.onUpdate != nullptr)
        {
            timer.onUpdate(e, timer);
        }

        // Check if the timer has expired
        if (timer.elapsed < timer.duration)
        {
            return;
        }

        // Timer has expired, call the onLoop callback if it exists
        if (timer.onLoop != nullptr)
        {
            timer.onLoop(e, timer);
        }

        // If the timer is not set to loop, call the onDestroy callback if it exists
        if (!timer.loop)
        {
            if (timer.onDestroy != nullptr)
            {
                timer.onDestroy(e, timer);
            }

            return;
        }

        // Loop the timer
        timer.elapsed -= timer.duration;

        if (timer.alternate)
        {
            timer.reverse = !timer.reverse;
        }
    });
}

} // namespace Anime
