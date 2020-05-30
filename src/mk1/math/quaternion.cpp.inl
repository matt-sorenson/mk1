#pragma once

namespace mk1::math {

constexpr quaternion::quaternion(const float _r, const float3& _i)
    : r{_r}, i{_i.x}, j{_i.y}, k{_i.z}
{
}


constexpr quaternion::quaternion(const float _r, const float _x, const float _y,
                                 const float _k)
    : r{_r}, i{_x}, j{_y}, k{_k}
{
}


constexpr float4x4 quaternion::to_float4x4() const
{
    const float ii = 2 * i * i;
    const float jj = 2 * j * j;
    const float kk = 2 * k * k;

    const float ri = 2 * r * i;
    const float rj = 2 * r * j;
    const float rk = 2 * r * k;

    const float ij = 2 * i * j;
    const float ik = 2 * i * k;

    const float jk = 2 * j * k;

    return {1 - jj - kk, ij - rk, ik + rj, 0.0f,    ij + rk,     1 - ii - kk,
            jk - ri,     0.0f,    ik - rj, jk + ri, 1 - ii - jj, 0.0f,
            0.0f,        0.0f,    0.0f,    1.0f};
}


constexpr quaternion operator*(const float l, const quaternion& r)
{
    return quaternion(r.r * l, r.i * l, r.j * l, r.k * l);
}


constexpr quaternion operator*(const quaternion& l, const float r)
{
    return operator*(r, l);
}


constexpr quaternion operator/(const quaternion& l, const float r)
{
    return operator*(l, 1.0f / r);
}


constexpr quaternion operator+(const quaternion& l, const quaternion& r)
{
    return {l.r + r.r, l.i + r.i, l.j + r.j, l.k + r.k};
}


constexpr quaternion operator-(const quaternion& l, const quaternion& r)
{
    return {l.r - r.r, l.i - r.i, l.j - r.j, l.k - r.k};
}


constexpr float3 operator*(const float3& l, const quaternion& r)
{
    quaternion out = r * quaternion(0, l.x, l.y, l.z) * inverse(r);
    return {out.i, out.j, out.k};
}


constexpr quaternion operator*(const quaternion& l, const quaternion& r)
{
    const float3 lv = {l.i, l.j, l.k};
    const float3 rv = {r.i, r.j, r.k};

    const float tmp_r = (l.r * r.r) - dot(lv, rv);
    const float3 tmp = (l.r * rv) + (r.r * lv) + cross(lv, rv);

    return quaternion(tmp_r, tmp);
}


constexpr float dot(const quaternion& l, const quaternion& r)
{
    return (l.r * r.r) + (l.i * r.i) + (l.j * r.j) + (l.k * r.k);
}


constexpr float length_sq(const quaternion& in) { return dot(in, in); }
constexpr quaternion inverse(const quaternion& in)
{
    return {in.r, -in.i, -in.j, -in.k};
}

constexpr bool fequals(const quaternion& l, const quaternion& r)
{
    return fequals(l.r, r.r) && fequals(l.i, r.i) && fequals(l.j, r.j)
           && fequals(l.k, r.k);
}
}
