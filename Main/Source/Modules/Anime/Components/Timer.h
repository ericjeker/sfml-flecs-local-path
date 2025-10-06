// Copyright (c) Eric Jeker. All Rights Reserved.

#pragma once
#include <functional>

namespace Anime
{

struct Timer
{
    float duration{1.f};
    float elapsed{0.f};

    bool loop{true};
    bool alternate{false};
    bool reverse{false};

    std::function<void(flecs::entity, const Timer&)> onUpdate = nullptr;
    std::function<void(flecs::entity, const Timer&)> onLoop = nullptr;
    std::function<void(flecs::entity, const Timer&)> onDestroy = [](const flecs::entity& e, const Timer&) {
        e.remove<Timer>();
    };
};

} // namespace Anime
