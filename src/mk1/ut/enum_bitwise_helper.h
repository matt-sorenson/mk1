#pragma once

namespace mk1::ut {

// Provide a specialization of this to allow an enum class to have bitwise
// operations
//
// template<>
// struct enable_bitmask_operators<T> {
//     static constexpr const bool value = true;
// };
template <typename T>
struct enable_bitmask_operators {
    static constexpr const bool value = false;
};
}

template <typename T>
inline constexpr std::enable_if_t<mk1::ut::enable_bitmask_operators<T>::value,
                                  T>
operator~(const T l)
{
    return T(~std::underlying_type_t<T>(l));
}


template <typename T>
inline constexpr std::enable_if_t<mk1::ut::enable_bitmask_operators<T>::value,
                                  T>
operator|(const T l, const T r)
{
    return T(std::underlying_type_t<T>(l) | std::underlying_type_t<T>(r));
}


template <typename T>
inline constexpr std::enable_if_t<mk1::ut::enable_bitmask_operators<T>::value,
                                  T>
operator&(const T l, const T r)
{
    return T(std::underlying_type_t<T>(l) & std::underlying_type_t<T>(r));
}


template <typename T>
inline constexpr std::enable_if_t<mk1::ut::enable_bitmask_operators<T>::value,
                                  T>
operator^(const T l, const T r)
{
    return T(std::underlying_type_t<T>(l) ^ std::underlying_type_t<T>(r));
}


template <typename T>
inline std::enable_if_t<mk1::ut::enable_bitmask_operators<T>::value, T>
operator|=(T& l, const T r)
{
    l = l | r;
    return l;
}


template <typename T>
inline std::enable_if_t<mk1::ut::enable_bitmask_operators<T>::value, T>
operator&=(T& l, const T r)
{
    l = l & r;
    return l;
}


template <typename T>
inline std::enable_if_t<mk1::ut::enable_bitmask_operators<T>::value, T>
operator^=(T& l, const T r)
{
    l = l ^ r;
    return l;
}
