#pragma once

namespace mk1::math {

struct quaternion;

template <typename T>
constexpr T lerp(const T& v1, const T& v2, const float t)
{
    return ((1.0f - t) * v1) + (t * v2);
}


quaternion slerp(const quaternion& v1, const quaternion& v2, const float time);
}
