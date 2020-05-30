#pragma once

#include <mk1/math/vector.h>
#include <mk1/ut/containers/containers.h>

namespace mk1::math {

struct quaternion;

struct float4x4 {
  public:
    constexpr float4x4();
    constexpr float4x4(const float a[16]);
    // This is specified in row order so that the constructor call can
    // look like the standard representation of a matrix
    constexpr float4x4(float r00, float r01, float r02, float r03, float r10,
                       float r11, float r12, float r13, float r20, float r21,
                       float r22, float r23, float r30, float r31, float r32,
                       float r33);
    constexpr float4x4(const float4 r0, const float4 r1, const float4 r2,
                       const float4 r3);

    constexpr const float& at(const size_t i) const { return operator[](i); }
    constexpr const float& at(const size_t r, const size_t c) const
    {
        return operator[](r + (c * 4));
    }

    float& at(const size_t i) { return operator[](i); }
    float& at(const size_t r, const size_t c)
    {
        return operator[](r + (c * 4));
    }

    constexpr float4 col(const size_t c) const;
    constexpr float4 row(const size_t r) const;

    MK1_CONTAINERS_CONTIGUOUS(float, &c00, 16)

    constexpr size_t size() const { return 16; }
  private:
    float c00, c01, c02, c03;
    float c10, c11, c12, c13;
    float c20, c21, c22, c23;
    float c30, c31, c32, c33;
};

constexpr float4x4 operator*(const float4x4& l, const float4x4& r);
constexpr float4 operator*(const float4x4& r, const float4& l);

constexpr float determinate(const float4x4& in);
constexpr float4x4 transpose(const float4x4& in);
float4x4 inverse(const float4x4& in);

constexpr float3 transform_point(const float4x4& r, const float3& l);
constexpr float3 transform_vector(const float4x4& r, const float3& l);

constexpr float4x4 scale(const float s);
constexpr float4x4 scale(const float3& s);
constexpr float4x4 translate(const float3& t);
float4x4 transform(const float3& _scale, const quaternion& _rotation,
                   const float3& _translation);

float4x4 look_at(const float3& eye, const float3& at, const float3& up);

float4x4 perspective_fov(const float fov_y, const float aspect,
                         const float z_near, const float z_far);

constexpr float4x4 ortho_center(const float width, const float height,
                                const float z_near, const float z_far);

constexpr float4x4 ortho(const float left, const float top, const float right,
                         const float bottom, const float z_near,
                         const float z_far);

constexpr bool fequals(const float4x4& l, const float4x4& r);
}

namespace mk1 {

using math::float4x4;

string to_string(const float4x4& in);

} // namespace mk1

#include <mk1/math/float4x4.cpp.inl>
