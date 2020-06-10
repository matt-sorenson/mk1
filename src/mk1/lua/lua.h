#pragma once

#include <mk1/ut.h>

extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}

namespace mk1::lua {

lua_State* new_state();

int sanitize_index(lua_State* L, const int idx);

int load_string(lua_State* L, const string& str, const string& name);
int load_string(lua_State* L, const char* str, const char* name);
int load_string(lua_State* L, const char* str, const size_t len,
                const char* name);

int do_string(lua_State* L, const string& str);
int do_string(lua_State* L, const char* str);
int do_string(lua_State* L, const char* str, const size_t len);

int load_file(lua_State* L, const string& filename);
int do_file(lua_State* L, const string& filename);

bool insist_table(lua_State* L, int idx, const char* k);
bool insist_global_table(lua_State* L, const char* k);
bool insist_mk1_table(lua_State* L, const char* k);

int safe_function_wrapper(lua_State* L, lua_CFunction func);

template <lua_CFunction func>
inline int safe_function(lua_State* L)
{
    return safe_function_wrapper(L, func);
}

template <typename T>
inline void push(lua_State* L, const T& val);

template <size_t DIM, typename T>
inline void push_v(lua_State* L, const math::vector<DIM, T>& val);

template <typename T>
inline T get(lua_State* L, int idx);

template <size_t DIM, typename T>
inline math::vector<DIM, T> get_v(lua_State* L, int idx);

}

#include <mk1/lua/lua.cpp.inl>
