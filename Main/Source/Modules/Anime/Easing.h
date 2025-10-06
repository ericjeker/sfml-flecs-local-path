// Copyright (c) Eric Jeker. All Rights Reserved.

#pragma once

#include <cmath>

namespace Anime::Easing
{

/**
 * Power-in easing function
 * @param t Normalized time [0, 1]
 * @param power The power exponent (e.g., 2 for quadratic, 3 for cubic)
 * @return Eased value [0, 1]
 */
inline float powerIn(float t, float power = 2.0f)
{
    return std::pow(t, power);
}

} // namespace Anime::Easing
