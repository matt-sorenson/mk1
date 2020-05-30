#include <mk1/ut.h>

#include <mk1/math/float4x4.h>

namespace mk1::math {

float4x4 inverse(const float4x4& in)
{
    float inv[16];

    inv[0] = in[5] * in[10] * in[15] - in[5] * in[11] * in[14]
             - in[9] * in[6] * in[15] + in[9] * in[7] * in[14]
             + in[13] * in[6] * in[11] - in[13] * in[7] * in[10];

    inv[4] = -in[4] * in[10] * in[15] + in[4] * in[11] * in[14]
             + in[8] * in[6] * in[15] - in[8] * in[7] * in[14]
             - in[12] * in[6] * in[11] + in[12] * in[7] * in[10];

    inv[8] = in[4] * in[9] * in[15] - in[4] * in[11] * in[13]
             - in[8] * in[5] * in[15] + in[8] * in[7] * in[13]
             + in[12] * in[5] * in[11] - in[12] * in[7] * in[9];

    inv[12] = -in[4] * in[9] * in[14] + in[4] * in[10] * in[13]
              + in[8] * in[5] * in[14] - in[8] * in[6] * in[13]
              - in[12] * in[5] * in[10] + in[12] * in[6] * in[9];

    inv[1] = -in[1] * in[10] * in[15] + in[1] * in[11] * in[14]
             + in[9] * in[2] * in[15] - in[9] * in[3] * in[14]
             - in[13] * in[2] * in[11] + in[13] * in[3] * in[10];

    inv[5] = in[0] * in[10] * in[15] - in[0] * in[11] * in[14]
             - in[8] * in[2] * in[15] + in[8] * in[3] * in[14]
             + in[12] * in[2] * in[11] - in[12] * in[3] * in[10];

    inv[9] = -in[0] * in[9] * in[15] + in[0] * in[11] * in[13]
             + in[8] * in[1] * in[15] - in[8] * in[3] * in[13]
             - in[12] * in[1] * in[11] + in[12] * in[3] * in[9];

    inv[13] = in[0] * in[9] * in[14] - in[0] * in[10] * in[13]
              - in[8] * in[1] * in[14] + in[8] * in[2] * in[13]
              + in[12] * in[1] * in[10] - in[12] * in[2] * in[9];

    inv[2] = in[1] * in[6] * in[15] - in[1] * in[7] * in[14]
             - in[5] * in[2] * in[15] + in[5] * in[3] * in[14]
             + in[13] * in[2] * in[7] - in[13] * in[3] * in[6];

    inv[6] = -in[0] * in[6] * in[15] + in[0] * in[7] * in[14]
             + in[4] * in[2] * in[15] - in[4] * in[3] * in[14]
             - in[12] * in[2] * in[7] + in[12] * in[3] * in[6];

    inv[10] = in[0] * in[5] * in[15] - in[0] * in[7] * in[13]
              - in[4] * in[1] * in[15] + in[4] * in[3] * in[13]
              + in[12] * in[1] * in[7] - in[12] * in[3] * in[5];

    inv[14] = -in[0] * in[5] * in[14] + in[0] * in[6] * in[13]
              + in[4] * in[1] * in[14] - in[4] * in[2] * in[13]
              - in[12] * in[1] * in[6] + in[12] * in[2] * in[5];

    inv[3] = -in[1] * in[6] * in[11] + in[1] * in[7] * in[10]
             + in[5] * in[2] * in[11] - in[5] * in[3] * in[10]
             - in[9] * in[2] * in[7] + in[9] * in[3] * in[6];

    inv[7] = in[0] * in[6] * in[11] - in[0] * in[7] * in[10]
             - in[4] * in[2] * in[11] + in[4] * in[3] * in[10]
             + in[8] * in[2] * in[7] - in[8] * in[3] * in[6];

    inv[11] = -in[0] * in[5] * in[11] + in[0] * in[7] * in[9]
              + in[4] * in[1] * in[11] - in[4] * in[3] * in[9]
              - in[8] * in[1] * in[7] + in[8] * in[3] * in[5];

    inv[15] = in[0] * in[5] * in[10] - in[0] * in[6] * in[9]
              - in[4] * in[1] * in[10] + in[4] * in[2] * in[9]
              + in[8] * in[1] * in[6] - in[8] * in[2] * in[5];

    const float det = in[0] * inv[0] + in[1] * inv[4] + in[2] * inv[8]
                      + in[3] * inv[12];

    if (math::fequals(det, 0.0f)) {
        throw std::runtime_error{"float4x4::inverse : determinate is zero"};
    }

    const float inv_det = 1.0f / det;
    for (float& val : inv) {
        val *= inv_det;
    }

    return float4x4{inv};
}


float4x4 transform(const float3& _scale, const quaternion& _rotation,
                   const float3& _translation)
{
    return scale(_scale) * _rotation.to_float4x4() * translate(_translation);
}


float4x4 look_at(const float3& eye, const float3& at, const float3& up)
{
    const float3 z_axis = normalized(eye - at);
    const float3 x_axis = normalized(cross(z_axis, up));
    const float3 y_axis = cross(z_axis, x_axis);

    return float4x4{x_axis.x, y_axis.x, z_axis.x, -dot(x_axis, eye),
                    x_axis.y, y_axis.y, z_axis.y, -dot(y_axis, eye),
                    x_axis.z, y_axis.z, z_axis.z, -dot(z_axis, eye),
                    0.0f,     0.0f,     0.0f,     1.0f};
}


float4x4 perspective_fov(const float fov_y, const float aspect, const float zn,
                         const float zf)
{
    const float s = std::sin(fov_y);
    const float f = std::cos(fov_y) / s;

    const float sx = f / aspect;
    const float sz = (zf + zn) / (zn - zf);
    const float tz = (2.0f * zf * zn) / (zn - zf);

    return float4x4{sx,   0.0f, 0.0f, 0.0f, 0.0f, f,    0.0f,  0.0f,
                    0.0f, 0.0f, sz,   tz,   0.0f, 0.0f, -1.0f, 0.0f};
}
}

namespace mk1 {

string to_string(const float4x4& in)
{
    std::stringstream out;

    out << "{" << to_string(in.row(0)) << to_string(in.row(1))
        << to_string(in.row(2)) << to_string(in.row(3)) << "}";

    return out.str();
}
}
