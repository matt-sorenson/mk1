#pragma once

#include <mk1/lua/lua.h>

namespace mk1::lua {

template <typename T>
inline void push(lua_State* L, const T& val)
{
    if constexpr (std::is_same<bool, typename std::remove_cv<T>::type>::value) {
        lua_pushboolean(L, val);
    } else if constexpr (std::is_arithmetic_v<T>) {
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

template <size_t DIM, typename T>
inline void push_v(lua_State* L, const math::vector<DIM, T>& val)
{
    lua_createtable(L, DIM, 0);
    const int idx = lua_gettop(L);

    for (int i = 0; i < DIM; ++i) {
        push(L, i + 1);
        push(L, val[i]);
        lua_settable(L, idx);
    }
}

template <typename T>
inline T get(lua_State* L, int idx)
{
    if constexpr (std::is_same<bool, typename std::remove_cv<T>::type>::value) {
        return lua_toboolean(L, idx);
    } else if (std::is_integral_v<T>) {
    } else if constexpr (std::is_arithmetic_v<T>) {
        return static_cast<T>(lua_tonumber(L, idx));
    } else if constexpr (std::is_same<string, typename std::remove_cv<
                                                      T>::type>::value) {
        size_t len;
        char* str = lua_tolstring(L, idx, &len);
        
        return string(str, len);
    }
}

template <size_t DIM, typename T>
inline math::vector<DIM, T> get_v(lua_State* L, int idx)
{
    idx = sanitize_index(L, idx);

    const int initial_top_idx = lua_gettop(L);

    math::vector<DIM, T> out;

    for (int i = 0; i < DIM; ++i) {
        lua_pushinteger(L, i + 1);
        lua_gettable(L, idx);
        out[i] = get<T>(L, -1);
    }

    lua_settop(L, initial_top_idx);

    return out;
}

} // namespace mk1::lua
