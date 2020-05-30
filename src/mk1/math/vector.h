#pragma once

#include <mk1/math/math.h>

#include <mk1/ut/containers/containers.h>

namespace mk1::math {

template <size_t DIM, typename T>
struct vector {
};


template <typename T>
struct vector<2, T> {
    constexpr vector();
    constexpr vector(const T r[2]);
    constexpr vector(const vector<2, T>& r);
    constexpr vector(const T _x, const T _y);

    template <typename Y>
    constexpr explicit vector(const vector<2, Y>& r);

    constexpr const vector& operator+() const { return *this; }
    constexpr vector operator-() const { return {-x, -y}; }
    MK1_CONTAINERS_CONTIGUOUS(T, &x, 2);

    constexpr size_t size() const { return 2; }
    static vector from_string(const string& r);

    T x, y;
};


template <typename T>
struct vector<3, T> {
    constexpr vector();
    constexpr vector(const T r[3]);
    constexpr vector(const vector<2, T>& xy, const T z);
    constexpr vector(const vector<3, T>& r);
    constexpr vector(const T x, const T y, const T z);

    template <typename Y>
    constexpr explicit vector(const vector<3, Y>& r);

    constexpr const vector& operator+() const { return *this; }
    constexpr vector operator-() const { return {-x, -y, -z}; }
    MK1_CONTAINERS_CONTIGUOUS(T, &x, 3);

    constexpr size_t size() const { return 3; }
    static vector from_string(const string& r);

    T x, y, z;
};


template <typename T>
struct vector<4, T> {
    constexpr vector();
    constexpr vector(const T r[4]);
    constexpr vector(const vector<3, T>& xyz, const T w);
    constexpr vector(const vector<4, T>& r);
    constexpr vector(const T x, const T y, const T z, const T w);

    template <typename Y>
    constexpr explicit vector(const vector<4, Y>& r);

    constexpr const vector& operator+() const { return *this; }
    constexpr vector operator-() const { return {-x, -y, -z, -w}; }
    MK1_CONTAINERS_CONTIGUOUS(T, &x, 4);

    constexpr size_t size() const { return 4; }
    static vector from_string(const string& r);

    T x, y, z, w;
};


template <size_t DIM, typename T>
constexpr bool operator==(const vector<DIM, T>& l, const vector<DIM, T>& r);

template <size_t DIM, typename T>
constexpr bool operator!=(const vector<DIM, T>& l, const vector<DIM, T>& r);

template <size_t DIM, typename T>
constexpr vector<DIM, T> operator*(const vector<DIM, T>& l, const T r);

template <size_t DIM, typename T>
constexpr vector<DIM, T> operator*(const T l, const vector<DIM, T>& r);

template <size_t DIM, typename T>
constexpr vector<DIM, T> operator/(const vector<DIM, T>& l, const T r);

template <size_t DIM, typename T>
constexpr vector<DIM, T> operator+(const vector<DIM, T>& l,
                                   const vector<DIM, T>& r);

template <size_t DIM, typename T>
constexpr vector<DIM, T> operator-(const vector<DIM, T>& l,
                                   const vector<DIM, T>& r);

template <size_t DIM, typename T>
constexpr vector<DIM, T> operator*(const vector<DIM, T>& l,
                                   const vector<DIM, T>& r);

template <size_t DIM, typename T>
constexpr vector<DIM, T> operator/(const vector<DIM, T>& l,
                                   const vector<DIM, T>& r);

template <size_t DIM, typename T>
vector<DIM, T> operator*=(vector<DIM, T>& l, const T r);

template <size_t DIM, typename T>
vector<DIM, T>& operator/=(vector<DIM, T>& l, const T r);

template <size_t DIM, typename T>
vector<DIM, T> operator+=(vector<DIM, T>& l, const vector<DIM, T>& r);

template <size_t DIM, typename T>
vector<DIM, T> operator-=(vector<DIM, T>& l, const vector<DIM, T>& r);

template <size_t DIM, typename T>
vector<DIM, T> operator*=(vector<DIM, T>& l, const vector<DIM, T>& r);

template <size_t DIM, typename T>
vector<DIM, T> operator/=(vector<DIM, T>& l, const vector<DIM, T>& r);

template <typename T>
constexpr vector<3, T> cross(const vector<3, T>& l, const vector<3, T>& r);

template <size_t DIM, typename T>
constexpr T dot(const vector<DIM, T>& l, const vector<DIM, T>& r);

template <size_t DIM, typename T>
constexpr bool fequals(const vector<DIM, T>& l, const vector<DIM, T>& r);

template <size_t DIM, typename T>
vector<DIM, T> normalized(const vector<DIM, T> in);

template <size_t DIM, typename T>
T length(const vector<DIM, T> in);
template <size_t DIM, typename T>
constexpr T length_sq(const vector<DIM, T> in);
template <size_t DIM, typename T>
T distance(const vector<DIM, T>& l, const vector<DIM, T>& r);

template <size_t DIM, typename T>
constexpr vector<DIM, T> abs(const vector<DIM, T>& in);
template <size_t DIM, typename T>
constexpr vector<DIM, T> deg_to_rad(const vector<DIM, T>& in);
template <size_t DIM, typename T>
constexpr vector<DIM, T> rad_to_deg(const vector<DIM, T>& in);

template <size_t DIM, typename T>
std::ostream& operator<<(std::ostream& os, const math::vector<DIM, T> in);
}

namespace mk1 {
template <size_t DIM, typename T>
string to_string(const math::vector<DIM, T>& in);

typedef math::vector<2, bool> bool2;
typedef math::vector<3, bool> bool3;
typedef math::vector<4, bool> bool4;

typedef math::vector<2, uint8_t> byte2;
typedef math::vector<3, uint8_t> byte3;
typedef math::vector<4, uint8_t> byte4;

typedef math::vector<2, int> int2;
typedef math::vector<3, int> int3;
typedef math::vector<4, int> int4;

typedef math::vector<2, float> float2;
typedef math::vector<3, float> float3;
typedef math::vector<4, float> float4;
}

#include <mk1/math/vector.cpp.inl>
