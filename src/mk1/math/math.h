#pragma once

namespace mk1::math {

static constexpr const float EPSILON = 0.00001f;
static constexpr const float PI = 3.14159265358979323846264338327950288419f;
static constexpr const float TWO_PI = 2.0f * PI;
static constexpr const float HALF_PI = 0.5f * PI;

template <typename T>
constexpr T abs(const T val)
{
    return (val < T(0)) ? -val : val;
}

template <typename T>
constexpr bool fequals(const T a, const T b)
{
    typedef std::enable_if_t<std::is_floating_point<T>::value, T> type;

    return abs(a - b) < static_cast<type>(EPSILON);
}

template <typename T>
constexpr T deg_to_rad(const T degrees)
{
    typedef std::enable_if_t<std::is_floating_point<T>::value, T> type;

    return degrees * (static_cast<type>(PI) / static_cast<type>(180));
}

template <typename T>
constexpr T rad_to_deg(const T radians)
{
    typedef std::enable_if_t<std::is_floating_point<T>::value, T> type;

    return radians * (static_cast<type>(180) / static_cast<type>(PI));
}

template <typename T>
constexpr T sign(const T num)
{
    return (num < static_cast<T>(0)) ? static_cast<T>(-1) : static_cast<T>(1);
}

template <typename T>
constexpr const T& max(const T& val_1, const T& val_2)
{
    return (val_1 > val_2) ? val_1 : val_2;
}

template <typename T>
constexpr const T& min(const T& val_1, const T& val_2)
{
    return (val_1 < val_2) ? val_1 : val_2;
}

template <typename T>
constexpr const T& clamp(const T& num, const T& min_val, const T& max_val)
{
    return max(min_val, min(max_val, num));
}
}

#include <mk1/math/float4x4.h>
#include <mk1/math/quaternion.h>
#include <mk1/math/vector.h>
