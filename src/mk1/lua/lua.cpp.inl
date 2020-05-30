#pragma once

#include <mk1/lua/lua.h>

namespace mk1::lua {

template <typename T>
inline void push(lua_State* L, const T& val)
{
    if constexpr (std::is_same<bool, typename std::remove_cv<T>::type>::value) {
        lua_pushboolean(L, val);
    } else if constexpr (std::is_arithmetic<T>::value) {
        lua_pushnumber(L, val);
    } else if constexpr (std::is_same<string, typename std::remove_cv<T>::type>::value) {
        lua_pushlstring(L, val.data(), val.length());
    } else if constexpr (std::is_same<const char*, typename std::remove_cv<T>::type>::value) {
        lua_pushstring(L, val)
    } else if constexpr (std::is_same<char*, typename std::remove_cv<T>::type>::
                                 value) {
        lua_pushstring(L, val)
    }
}

} // namespace mk1::lua
