#include <mk1/ut.h>

#include <mk1/math/interpolation.h>

#include <mk1/math/quaternion.h>

namespace mk1::math {

quaternion slerp(const quaternion& v1, const quaternion& v2, const float time)
{
    const float cos_theta = dot(v1, v2);

    if (EPSILON > (1 - cos_theta)) {
        return lerp(v1, v2, time);
    }

    const float theta = std::acos(std::abs(cos_theta));
    const float inv_sin_theta = 1.0f / std::sin(theta);
    const float flip_factor = (cos_theta < 0.0f) ? -1.0f : 1.0f;

    const float alpha = std::sin(((1.0f - time) * theta) * inv_sin_theta);
    const float beta = std::sin((time * theta) * inv_sin_theta);

    return normalized((alpha * v1) + (beta * flip_factor * v2));
}
}
