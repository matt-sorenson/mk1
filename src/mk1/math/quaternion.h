#pragma once

#include <mk1/math/float4x4.h>
#include <mk1/math/math.h>
#include <mk1/math/vector.h>
#include <mk1/ut/containers/containers.h>

namespace mk1::math {
struct float4x4;

struct quaternion {
    constexpr quaternion(const quaternion& rhs) = default;
    quaternion& operator=(const quaternion&) = default;

    constexpr quaternion(const float r, const float3& i);
    constexpr quaternion(const float r, const float i, const float j,
                         const float k);

    static quaternion from_axis_angle(const float3& axis, const float angle);
    static quaternion from_euler(const float3& angles);
    static quaternion from_string(const string& in);

    quaternion operator+() const { return *this; }
    quaternion operator-() const { return quaternion{-r, -i, -j, -k}; }
    float at(const size_t idx) const { return operator[](idx); }
    MK1_CONTAINERS_CONTIGUOUS(float, &r, 4)

    size_t size() const { return 4; }
    constexpr float4x4 to_float4x4() const;
    float3 to_axis_angle(float* out_angle) const;

    float r = 1, i = 0, j = 0, k = 0;
};

constexpr quaternion operator*(const float l, const quaternion& r);
constexpr quaternion operator*(const quaternion& l, const float r);
constexpr quaternion operator/(const quaternion& l, const float r);

constexpr quaternion operator+(const quaternion& l, const quaternion& r);
constexpr quaternion operator-(const quaternion& l, const quaternion& r);

constexpr float3 operator*(const float3& l, const quaternion& r);
constexpr quaternion operator*(const quaternion& l, const quaternion& r);

constexpr float dot(const quaternion& l, const quaternion& r);
constexpr float length_sq(const quaternion& in);
float length(const quaternion& in);

quaternion normalized(const quaternion& in);
constexpr quaternion inverse(const quaternion& in);

constexpr bool fequals(const quaternion& l, const quaternion& r);
}

namespace mk1 {

using math::quaternion;

string to_string(const quaternion& in);
}

#include <mk1/math/quaternion.cpp.inl>
