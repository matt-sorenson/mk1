#pragma once

namespace mk1::math {

template <typename T>
constexpr vector<2, T>::vector() : x{T(0)}, y{T(0)}
{
}


template <typename T>
constexpr vector<2, T>::vector(const T r[2]) : x{r[0]}, y{r[1]}
{
}


template <typename T>
constexpr vector<2, T>::vector(const vector<2, T>& r) : x{r.x}, y{r.y}
{
}


template <typename T>
constexpr vector<2, T>::vector(const T _x, const T _y) : x{_x}, y{_y}
{
}


template <typename T>
template <typename Y>
constexpr vector<2, T>::vector(const vector<2, Y>& r)
    : x{static_cast<T>(r.x)}, y{static_cast<T>(r.y)}
{
}


template <typename T>
constexpr vector<3, T>::vector() : x{T(0)}, y{T(0)}, z{T(0)}
{
}


template <typename T>
constexpr vector<3, T>::vector(const T r[3]) : x{r[0]}, y{r[1]}, z{r[2]}
{
}


template <typename T>
constexpr vector<3, T>::vector(const vector<2, T>& _xy, const T _z)
    : x{_xy.x}, y{_xy.y}, z{_z}
{
}


template <typename T>
constexpr vector<3, T>::vector(const vector<3, T>& r) : x{r.x}, y{r.y}, z{r.z}
{
}


template <typename T>
constexpr vector<3, T>::vector(const T _x, const T _y, const T _z)
    : x{_x}, y{_y}, z{_z}
{
}


template <typename T>
template <typename Y>
constexpr vector<3, T>::vector(const vector<3, Y>& r)
    : x{static_cast<T>(r.x)}, y{static_cast<T>(r.y)}, z{static_cast<T>(r.z)}
{
}


template <typename T>
constexpr vector<4, T>::vector() : x{T(0)}, y{T(0)}, z{T(0)}, w{T(0)}
{
}


template <typename T>
constexpr vector<4, T>::vector(const T r[4])
    : x{r[0]}, y{r[1]}, z{r[2]}, w{r[3]}
{
}


template <typename T>
constexpr vector<4, T>::vector(const vector<3, T>& _xyz, const T _w)
    : x{_xyz.x}, y{_xyz.y}, z{_xyz.z}, w{_w}
{
}


template <typename T>
constexpr vector<4, T>::vector(const vector<4, T>& r)
    : x{r.x}, y{r.y}, z{r.z}, w{r.w}
{
}


template <typename T>
constexpr vector<4, T>::vector(const T _x, const T _y, const T _z, const T _w)
    : x{_x}, y{_y}, z{_z}, w{_w}
{
}


template <typename T>
template <typename Y>
constexpr vector<4, T>::vector(const vector<4, Y>& r)
    : x{static_cast<T>(r.x)}, y{static_cast<T>(r.y)}, z{static_cast<T>(r.z)},
      w{static_cast<T>(r.w)}
{
}

#define MK1_VEC_FROM_STR_HELPER(DIM, fmt, ...)                                 \
    if (DIM != sscanf((const char*)r.c_str(), fmt, __VA_ARGS__)) {             \
        throw std::runtime_error{                                              \
                "vector::from_string : Failed to parse vector"};               \
    }


#define MK1_VEC_FROM_STR_2(T, fmt)                                             \
    template <>                                                                \
    inline vector<2, T> vector<2, T>::from_string(const string& r)           \
    {                                                                          \
        vector<2, T> out;                                                      \
        MK1_VEC_FROM_STR_HELPER(2, " { " fmt " , " fmt " } ", &out.x, &out.y); \
        return out;                                                            \
    }


#define MK1_VEC_FROM_STR_3(T, fmt)                                             \
    template <>                                                                \
    inline vector<3, T> vector<3, T>::from_string(const string& r)           \
    {                                                                          \
        vector<3, T> out;                                                      \
        MK1_VEC_FROM_STR_HELPER(3, " { " fmt " , " fmt " , " fmt " } ",        \
                                &out.x, &out.y, &out.z);                       \
        return out;                                                            \
    }


#define MK1_VEC_FROM_STR_4(T, fmt)                                             \
    template <>                                                                \
    inline vector<4, T> vector<4, T>::from_string(const string& r)           \
    {                                                                          \
        vector<4, T> out;                                                      \
        MK1_VEC_FROM_STR_HELPER(4,                                             \
                                " { " fmt " , " fmt " , " fmt " , " fmt " } ", \
                                &out.x, &out.y, &out.z, &out.w);               \
        return out;                                                            \
    }

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4996) // scanf unsafe
#endif

MK1_VEC_FROM_STR_2(int, "%d")
MK1_VEC_FROM_STR_3(int, "%d")
MK1_VEC_FROM_STR_4(int, "%d")

MK1_VEC_FROM_STR_2(float, "%f")
MK1_VEC_FROM_STR_3(float, "%f")
MK1_VEC_FROM_STR_4(float, "%f")

#undef MK1_VEC_FROM_STR_4
#undef MK1_VEC_FROM_STR_3
#undef MK1_VEC_FROM_STR_2
#undef MK1_VEC_FROM_STR_HELPER

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#define MK1_VEC_FROM_TYPE_STR(DIM, T, type)                                    \
    template <>                                                                \
    inline vector<DIM, T> vector<DIM, T>::from_string(const string& r)       \
    {                                                                          \
        return vector<DIM, T>(vector<DIM, type>::from_string(r));              \
    }

MK1_VEC_FROM_TYPE_STR(2, bool, int)
MK1_VEC_FROM_TYPE_STR(3, bool, int)
MK1_VEC_FROM_TYPE_STR(4, bool, int)

MK1_VEC_FROM_TYPE_STR(2, uint8_t, int)
MK1_VEC_FROM_TYPE_STR(3, uint8_t, int)
MK1_VEC_FROM_TYPE_STR(4, uint8_t, int)

#undef MK1_VEC_FROM_TYPE_STR

template <typename T>
constexpr bool operator==(const vector<2, T>& l, const vector<2, T>& r)
{
    return (l.x == r.x) && (l.y == r.y);
}


template <typename T>
constexpr bool operator==(const vector<3, T>& l, const vector<3, T>& r)
{
    return (l.x == r.x) && (l.y == r.y) && (l.z == r.z);
}


template <typename T>
constexpr bool operator==(const vector<4, T>& l, const vector<4, T>& r)
{
    return (l.x == r.x) && (l.y == r.y) && (l.z == r.z) && (l.w == r.w);
}


template <size_t DIM, typename T>
constexpr bool operator!=(const vector<DIM, T>& l, const vector<DIM, T>& r)
{
    return !operator==(l, r);
}


template <typename T>
constexpr vector<2, T> operator*(const vector<2, T>& l, const T r)
{
    return {l.x * r, l.y * r};
}


template <typename T>
constexpr vector<3, T> operator*(const vector<3, T>& l, const T r)
{
    return {l.x * r, l.y * r, l.z * r};
}


template <typename T>
constexpr vector<4, T> operator*(const vector<4, T>& l, const T r)
{
    return {l.x * r, l.y * r, l.z * r, l.w * r};
}


template <size_t DIM, typename T>
constexpr vector<DIM, T> operator*(const T l, const vector<DIM, T>& r)
{
    return operator*(r, l);
}


template <typename T>
constexpr vector<2, T> operator/(const vector<2, T>& l, const T r)
{
    return {l.x / r, l.y / r};
}


template <typename T>
constexpr vector<3, T> operator/(const vector<3, T>& l, const T r)
{
    return {l.x / r, l.y / r, l.z / r};
}


template <typename T>
constexpr vector<4, T> operator/(const vector<4, T>& l, const T r)
{
    return {l.x / r, l.y / r, l.z / r, l.w / r};
}


template <typename T>
constexpr vector<2, T> operator+(const vector<2, T>& l, const vector<2, T>& r)
{
    return {l.x + r.x, l.y + r.y};
}


template <typename T>
constexpr vector<3, T> operator+(const vector<3, T>& l, const vector<3, T>& r)
{
    return {l.x + r.x, l.y + r.y, l.z + r.z};
}


template <typename T>
constexpr vector<4, T> operator+(const vector<4, T>& l, const vector<4, T>& r)
{
    return {l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w};
}


template <size_t DIM, typename T>
constexpr vector<DIM, T> operator-(const vector<DIM, T>& l,
                                   const vector<DIM, T>& r)
{
    return l + (-r);
}


template <typename T>
constexpr vector<2, T> operator*(const vector<2, T>& l, const vector<2, T>& r)
{
    return {l.x * r.x, l.y * r.y};
}


template <typename T>
constexpr vector<3, T> operator*(const vector<3, T>& l, const vector<3, T>& r)
{
    return {l.x * r.x, l.y * r.y, l.z * r.z};
}


template <typename T>
constexpr vector<4, T> operator*(const vector<4, T>& l, const vector<4, T>& r)
{
    return {l.x * r.x, l.y * r.y, l.z * r.z, l.w * r.w};
}


template <typename T>
constexpr vector<2, T> operator/(const vector<2, T>& l, const vector<2, T>& r)
{
    return {l.x / r.x, l.y / r.y};
}


template <typename T>
constexpr vector<3, T> operator/(const vector<3, T>& l, const vector<3, T>& r)
{
    return {l.x / r.x, l.y / r.y, l.z / r.z};
}


template <typename T>
constexpr vector<4, T> operator/(const vector<4, T>& l, const vector<4, T>& r)
{
    return {l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w};
}


template <size_t DIM, typename T>
vector<DIM, T>& operator*=(vector<DIM, T>& l, const T r)
{
    for (T& i : l) {
        i *= r;
    }

    return l;
}


template <size_t DIM, typename T>
vector<DIM, T>& operator/=(vector<DIM, T>& l, const T r)
{
    return operator*=(l, T(1) / r);
}


template <size_t DIM, typename T>
vector<DIM, T>& operator+=(vector<DIM, T>& l, const vector<DIM, T>& r)
{
    for (size_t i = 0; i < DIM; ++i) {
        l[i] += r[i];
    }

    return l;
}


template <size_t DIM, typename T>
vector<DIM, T>& operator-=(vector<DIM, T>& l, const vector<DIM, T>& r)
{
    for (size_t i = 0; i < DIM; ++i) {
        l[i] -= r[i];
    }

    return l;
}


template <size_t DIM, typename T>
vector<DIM, T>& operator*=(vector<DIM, T>& l, const vector<DIM, T>& r)
{
    for (size_t i = 0; i < DIM; ++i) {
        l[i] *= r[i];
    }

    return l;
}


template <size_t DIM, typename T>
vector<DIM, T>& operator/=(vector<DIM, T>& l, const vector<DIM, T>& r)
{
    for (size_t i = 0; i < DIM; ++i) {
        l[i] /= r[i];
    }

    return l;
}


template <typename T>
constexpr vector<3, T> cross(const vector<3, T>& l, const vector<3, T>& r)
{
    return {(l.y * r.z) - (l.z * r.y), (l.z * r.x) - (l.x * r.z),
            (l.x * r.y) - (l.y * r.x)};
}


template <typename T>
constexpr T dot(const vector<2, T>& l, const vector<2, T>& r)
{
    return (l.x * r.x) + (l.y * r.y);
}


template <typename T>
constexpr T dot(const vector<3, T>& l, const vector<3, T>& r)
{
    return (l.x * r.x) + (l.y * r.y) + (l.z * r.z);
}


template <typename T>
constexpr T dot(const vector<4, T>& l, const vector<4, T>& r)
{
    return (l.x * r.x) + (l.y * r.y) + (l.z * r.z) + (l.w * r.w);
}


template <typename T>
constexpr bool fequals(const vector<2, T>& l, const vector<2, T>& r)
{
    return fequals(l.x, r.x) && fequals(l.y, r.y);
}


template <typename T>
constexpr bool fequals(const vector<3, T>& l, const vector<3, T>& r)
{
    return fequals(l.x, r.x) && fequals(l.y, r.y) && fequals(l.z, r.z);
}


template <typename T>
constexpr bool fequals(const vector<4, T>& l, const vector<4, T>& r)
{
    return fequals(l.x, r.x) && fequals(l.y, r.y) && fequals(l.z, r.z)
           && fequals(l.w, r.w);
}


template <size_t DIM, typename T>
vector<DIM, T> normalized(const vector<DIM, T> in)
{
    return in / length(in);
}


template <size_t DIM, typename T>
T length(const vector<DIM, T> in)
{
    return std::sqrt(dot(in, in));
}


template <size_t DIM, typename T>
constexpr T length_sq(const vector<DIM, T> in)
{
    return dot(in, in);
}


template <size_t DIM, typename T>
T distance(const vector<DIM, T>& l, const vector<DIM, T>& r)
{
    return length(l - r);
}


template <typename T>
constexpr vector<2, T> abs(const vector<2, T>& in)
{
    return {math::abs(in.x), math::abs(in.y)};
}


template <typename T>
constexpr vector<3, T> abs(const vector<3, T>& in)
{
    return {math::abs(in.x), math::abs(in.y), math::abs(in.z)};
}


template <typename T>
constexpr vector<4, T> abs(const vector<4, T>& in)
{
    return {math::abs(in.x), math::abs(in.y), math::abs(in.z), math::abs(in.w)};
}


template <typename T>
constexpr vector<2, T> deg_to_rad(const vector<2, T>& in)
{
    return {math::deg_to_rad(in.x), math::deg_to_rad(in.y)};
}


template <typename T>
constexpr vector<3, T> deg_to_rad(const vector<3, T>& in)
{
    return {math::deg_to_rad(in.x), math::deg_to_rad(in.y),
            math::deg_to_rad(in.z)};
}


template <typename T>
constexpr vector<4, T> deg_to_rad(const vector<4, T>& in)
{
    return {math::deg_to_rad(in.x), math::deg_to_rad(in.y),
            math::deg_to_rad(in.z), math::deg_to_rad(in.w)};
}


template <typename T>
constexpr vector<2, T> rad_to_deg(const vector<2, T>& in)
{
    return {math::rad_to_deg(in.x), math::rad_to_deg(in.y)};
}


template <typename T>
constexpr vector<3, T> rad_to_deg(const vector<3, T>& in)
{
    return {math::rad_to_deg(in.x), math::rad_to_deg(in.y),
            math::rad_to_deg(in.z)};
}


template <typename T>
constexpr vector<4, T> rad_to_deg(const vector<4, T>& in)
{
    return {math::rad_to_deg(in.x), math::rad_to_deg(in.y),
            math::rad_to_deg(in.z), math::rad_to_deg(in.w)};
}
} // namespace mk1::math

namespace mk1 {
template <typename T>
string to_string(const math::vector<2, T>& in)
{
    return fmt::format("{{{}, {}}}", in.x, in.y);
}

template <typename T>
string to_string(const math::vector<3, T>& in)
{
    return fmt::format("{{{}, {}, {}}}", in.x, in.y, in.z);
}

template <typename T>
string to_string(const math::vector<4, T>& in)
{
    return fmt::format("{{{}, {}, {}, {}}}", in.x, in.y, in.z, in.w);
}
} // namespace mk1
