// Copyright (c) Eric Jeker. All Rights Reserved.

#pragma once

#include <cmath>
#include <numbers>

namespace Anime::Easing
{

/**
 * Power-in easing function
 * @param t Normalized time [0, 1]
 * @param power The power exponent (e.g., 2 for quadratic, 3 for cubic)
 * @return Eased value [0, 1]
 */
inline float powerIn(const float t, const float power = 2.0f)
{
    return std::pow(t, power);
}

/**
 * Elastic-out easing function (spring-like bounce effect)
 * @param t Normalized time [0, 1]
 * @param amplitude Amplitude of the oscillation (default 1.0f)
 * @param period Period of the oscillation (default 0.3f)
 * @return Eased value that overshoots and oscillates before settling
 */
inline float elasticOut(const float t, const float amplitude = 1.0f, const float period = 0.3f)
{
    if (t == 0.0f)
        return 0.0f;
    if (t == 1.0f)
        return 1.0f;

    const float s = period / (2.0f * std::numbers::pi_v<float>) * std::asin(1.0f / amplitude);
    return amplitude * std::pow(2.0f, -10.0f * t) * std::sin((t - s) * (2.0f * std::numbers::pi_v<float>) / period) + 1.0f;
}


} // namespace Anime::Easing
