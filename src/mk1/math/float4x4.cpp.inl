#pragma once

namespace mk1::math {

constexpr float4x4::float4x4()
    : c00(1.0f), c01(0.0f), c02(0.0f), c03(0.0f), c10(0.0f), c11(1.0f),
      c12(0.0f), c13(0.0f), c20(0.0f), c21(0.0f), c22(1.0f), c23(0.0f),
      c30(0.0f), c31(0.0f), c32(0.0f), c33(1.0f)
{
}


constexpr float4x4::float4x4(const float a[16])
    : c00(a[0]), c01(a[1]), c02(a[2]), c03(a[3]), c10(a[4]), c11(a[5]),
      c12(a[6]), c13(a[7]), c20(a[8]), c21(a[9]), c22(a[10]), c23(a[11]),
      c30(a[12]), c31(a[13]), c32(a[14]), c33(a[15])
{
}


constexpr float4x4::float4x4(float r00, float r01, float r02, float r03,
                             float r10, float r11, float r12, float r13,
                             float r20, float r21, float r22, float r23,
                             float r30, float r31, float r32, float r33)
    : c00(r00), c01(r10), c02(r20), c03(r30), c10(r01), c11(r11), c12(r21),
      c13(r31), c20(r02), c21(r12), c22(r22), c23(r32), c30(r03), c31(r13),
      c32(r23), c33(r33)
{
}


constexpr float4x4::float4x4(const float4 r0, const float4 r1, const float4 r2,
                             const float4 r3)
    : c00(r0.x), c01(r1.x), c02(r2.x), c03(r3.x), c10(r0.y), c11(r1.y),
      c12(r2.y), c13(r3.y), c20(r0.z), c21(r1.z), c22(r2.z), c23(r3.z),
      c30(r0.w), c31(r1.w), c32(r2.w), c33(r3.w)
{
}

constexpr float4 float4x4::col(const size_t c) const
{
    return {at(0, c), at(1, c), at(2, c), at(3, c)};
}


constexpr float4 float4x4::row(const size_t r) const
{
    return {at(r, 0), at(r, 1), at(r, 2), at(r, 3)};
}


constexpr float4x4 operator*(const float4x4& l, const float4x4& r)
{
    const float4 l_row[] = {l.row(0), l.row(1), l.row(2), l.row(3)};
    const float4 r_col[] = {r.col(0), r.col(1), r.col(2), r.col(3)};

    return {dot(l_row[0], r_col[0]), dot(l_row[0], r_col[1]),
            dot(l_row[0], r_col[2]), dot(l_row[0], r_col[3]),
            dot(l_row[1], r_col[0]), dot(l_row[1], r_col[1]),
            dot(l_row[1], r_col[2]), dot(l_row[1], r_col[3]),
            dot(l_row[2], r_col[0]), dot(l_row[2], r_col[1]),
            dot(l_row[2], r_col[2]), dot(l_row[2], r_col[3]),
            dot(l_row[3], r_col[0]), dot(l_row[3], r_col[1]),
            dot(l_row[3], r_col[2]), dot(l_row[3], r_col[3])};
}


constexpr float4 operator*(const float4x4& r, const float4& l)
{
    return {dot(r.row(0), l), dot(r.row(1), l), dot(r.row(2), l),
            dot(r.row(3), l)};
}


constexpr float determinate(const float4x4& in)
{
    return ((in.at(0) * in.at(5) - in.at(1) * in.at(4))
            * (in.at(10) * in.at(15) - in.at(11) * in.at(14)))
           - ((in.at(0) * in.at(6) - in.at(2) * in.at(4))
              * (in.at(9) * in.at(15) - in.at(11) * in.at(13)))
           + ((in.at(0) * in.at(7) - in.at(3) * in.at(4))
              * (in.at(9) * in.at(14) - in.at(10) * in.at(13)))
           + ((in.at(1) * in.at(6) - in.at(2) * in.at(5))
              * (in.at(8) * in.at(15) - in.at(11) * in.at(12)))
           - ((in.at(1) * in.at(7) - in.at(3) * in.at(5))
              * (in.at(8) * in.at(14) - in.at(10) * in.at(12)))
           + ((in.at(2) * in.at(7) - in.at(3) * in.at(6))
              * (in.at(8) * in.at(13) - in.at(9) * in.at(12)));
}


constexpr float4x4 transpose(const float4x4& in)
{
    return {in.at(0, 0), in.at(1, 0), in.at(2, 0), in.at(3, 0),
            in.at(0, 1), in.at(1, 1), in.at(2, 1), in.at(3, 1),
            in.at(0, 2), in.at(1, 2), in.at(2, 2), in.at(3, 2),
            in.at(0, 3), in.at(1, 3), in.at(2, 3), in.at(3, 3)};
}


constexpr float3 transform_point(const float4x4& r, const float3& l)
{
    const float4 result = r * float4{l, 1.0f};
    return {result.x / result.w, result.y / result.w, result.z / result.w};
}


constexpr float3 transform_vector(const float4x4& r, const float3& l)
{
    const float4 result = r * float4{l, 0.0f};
    return {result.x, result.y, result.z};
}


constexpr float4x4 scale(const float s)
{
    return {s, 0, 0, 0, 0, s, 0, 0, 0, 0, s, 0, 0, 0, 0, 1};
}


constexpr float4x4 scale(const float3& s)
{
    return {s.x, 0, 0, 0, 0, s.y, 0, 0, 0, 0, s.z, 0, 0, 0, 0, 1};
}


constexpr float4x4 translate(const float3& t)
{
    return {1, 0, 0, t.x, 0, 1, 0, t.y, 0, 0, 1, t.z, 0, 0, 0, 1};
}


constexpr float4x4 ortho_center(const float width, const float height,
                                const float z_near, const float z_far)
{
    return ortho(-width / 2.0f, height / 2.0f, width / 2.0f, -height / 2.0f,
                 z_near, z_far);
}


constexpr float4x4 ortho(const float l, const float t, const float r,
                         const float b, const float zn, const float zf)
{
    const float sx = 2.0f / (r - l);
    const float sy = 2.0f / (t - b);
    const float sz = -2.0f / (zf - zn);
    const float tx = -(r + l) / (r - l);
    const float ty = -(t + b) / (t - b);
    const float tz = -(zf + zn) / (zf - zn);

    return {sx,   0.0f, 0.0f, tx, 0.0f, sy,   0.0f, ty,
            0.0f, 0.0f, sz,   tz, 0.0f, 0.0f, 0.0f, 1.0f};
}


constexpr bool fequals(const float4x4& l, const float4x4& r)
{
    return fequals(l[0], r[0]) && fequals(l[1], r[1]) && fequals(l[2], r[2])
           && fequals(l[3], r[3]) && fequals(l[4], r[4]) && fequals(l[5], r[5])
           && fequals(l[6], r[6]) && fequals(l[7], r[7]) && fequals(l[8], r[8])
           && fequals(l[9], r[9]) && fequals(l[10], r[10])
           && fequals(l[11], r[11]) && fequals(l[12], r[12])
           && fequals(l[13], r[13]) && fequals(l[14], r[14])
           && fequals(l[15], r[15]);
}
}
