#include <mk1/ut.h>

#include <mk1/math/quaternion.h>

#include <mk1/math/float4x4.h>
#include <mk1/math/vector.h>

namespace mk1::math {

quaternion quaternion::from_axis_angle(const float3& axis, const float angle)
{
    const float len = length(axis);
    const float axis_multiplier = std::sin(angle * 0.5f) / len;

    return normalized(
            quaternion(std::cos(angle * 0.5f), axis_multiplier * axis.x,
                       axis_multiplier * axis.y, axis_multiplier * axis.z));
}


quaternion quaternion::from_euler(const float3& angles)
{
    return from_axis_angle(float3(1, 0, 0), angles.x)
           * from_axis_angle(float3(0, 1, 0), angles.y)
           * from_axis_angle(float3(0, 0, 1), angles.z);
}

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4996) // scanf unsafe
#endif

quaternion quaternion::from_string(const string& in)
{
    const char* str = (const char*)in.c_str();
    float r, i, j, k;

    if (4 != sscanf(str, " { %f { %f , %f , %f } } ", &r, &i, &j, &k)) {
        throw std::runtime_error(
                "quaternion::from_string : Ill formed input string.");
    }

    return quaternion(r, i, j, k);
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

float3 quaternion::to_axis_angle(float* out_angle) const
{
    if (!out_angle) {
        throw std::runtime_error(
                "quaternion::to_axis_angle : out_angle == nullptr");
    }

    const quaternion in = normalized(*this);

    *out_angle = 2 * std::acos(in.r);

    const float s = std::sqrt(1 - (in.r * in.r));

    if (math::fequals(s, 0.0f)) {
        return normalized(float3(in.i, in.j, in.k));
    } else {
        return normalized(float3(in.i / s, in.j / s, in.k / s));
    }
}


float length(const quaternion& in) { return std::sqrt(dot(in, in)); }
quaternion normalized(const quaternion& in) { return in / length(in); }
}

namespace mk1 {

string to_string(const quaternion& in)
{
    return fmt::format("{{ {}, {{ {}, {}, {} }}}}", in.r, in.i, in.j, in.k);
}
}
