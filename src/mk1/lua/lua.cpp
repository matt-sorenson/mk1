#include <mk1/lua/lua.h>

#include <mk1/fs/fs.h>

namespace mk1::lua {

static int print(lua_State* L);
static int error(lua_State* L);

static int load_file(lua_State* L);
static int load_string(lua_State* L);

static int do_file(lua_State* L);
static int do_string(lua_State* L);

static const luaL_Reg mk1_funcs[] = {
    // replace the default print/error functions with ones that use the
    // logging system.
    {"print", safe_function<print>},
    {"error", safe_function<error>},

    {"loadfile", safe_function<load_file>},
    {"loadstring", safe_function<load_string>},

    {"dofile", safe_function<do_file>},
    {"dostring", safe_function<do_string>},
};

static const luaL_Reg lualibs[] = {
    {"", luaopen_base},
    {LUA_TABLIBNAME, luaopen_table},
    {LUA_STRLIBNAME, luaopen_string},
    {LUA_MATHLIBNAME, luaopen_math },
    //{LUA_LOADLIBNAME, luaopen_package },
    //{LUA_IOLIBNAME, luaopen_io },
    //{LUA_OSLIBNAME, luaopen_os },
    //{LUA_DBLIBNAME, luaopen_debug },
    {nullptr, nullptr}
};

lua_State* new_state()
{
    lua_State* L = luaL_newstate();

    for (const luaL_Reg* lib = lualibs; lib->func; lib++) {
        lua_pushcfunction(L, lib->func);
        lua_pushstring(L, lib->name);
        lua_call(L, 1, 0);
    }

    for (auto i : mk1_funcs) {
        lua_pushcfunction(L, i.func);
        lua_setglobal(L, i.name);
    }

    insist_global_table(L, "mk1");

    return L;
}

int sanitize_index(lua_State* L, const int idx)
{
    if ((idx < 0) && (idx > LUA_REGISTRYINDEX)) {
        return lua_gettop(L) + idx + 1;
    }

    return idx;
}

int load_string(lua_State* L, const string& str, const string& name)
{
    return load_string(L, str.data(), str.length(), name.c_str());
}


int load_string(lua_State* L, const char* str, const char* name)
{
    return load_string(L, str, strlen(str), name);
}


int load_string(lua_State* L, const char* str, const size_t len,
                const char* name)
{
    return luaL_loadbuffer(L, str, len, name);
}

int do_string(lua_State* L, const string& str)
{
    return do_string(L, str.data(), str.length());
}


int do_string(lua_State* L, const char* str)
{
    return do_string(L, str, strlen(str));
}


int do_string(lua_State* L, const char* str, const size_t len)
{
    return load_string(L, str, len, nullptr) || lua_pcall(L, 0, LUA_MULTRET, 0);
}

int load_file(lua_State* L, const string& filename)
{
    fs::ReadFile file(filename);

    const size_t len = (size_t)file.size();

    char* buffer = new char[len];
    file.read(buffer, len);

    const int res = load_string(L, buffer, len, filename.c_str());

    return res;
}


int do_file(lua_State* L, const string& filename)
{
    return load_file(L, filename) || lua_pcall(L, 0, LUA_MULTRET, 0);
}

bool insist_table(lua_State* L, int idx, const char* k)
{
    idx = sanitize_index(L, idx);

    assert_throw<std::invalid_argument>(
            !lua_istable(L, idx),
            "Index passed to insist_table does not point to a table");

    lua_getfield(L, idx, k);

    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_setfield(L, idx, k);

        return true;
    }

    assert_throw<std::invalid_argument>(
            !lua_istable(L, -1), "The element '"s + k + "' already exists as a "
                                         + luaL_typename(L, -1));

    return false;
}

bool insist_global_table(lua_State* L, const char* k)
{
    lua_getglobal(L, k);

        if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_setglobal(L, k);

        return true;
    }

    assert_throw<std::invalid_argument>(
            !lua_istable(L, -1), "The element '"s + k + "' already exists as a "
                                         + luaL_typename(L, -1));

    return false;
}


bool insist_mk1_table(lua_State* L, const char* k)
{
    insist_global_table(L, "mk1");
    const bool res = insist_table(L, -1, k);

    // replace the mk1 table with the table the caller is actually asking for
    lua_replace(L, -2);

    return res;
}

int safe_function_wrapper(lua_State* L, lua_CFunction func)
{
    try {
        return func(L);
    } catch (std::invalid_argument e) {
        return luaL_error(L,
                          "Uncaught std::invalid_argument in c++ function call "
                          "from lua:\n%s",
                          e.what());
    } catch (std::bad_alloc e) {
        return luaL_error(
                L, "Uncaught std::bad_alloc in c++ function call from lua:\n%s",
                e.what());
    } catch (std::exception e) {
        return luaL_error(
                L, "Uncaught std::exception in c++ function call from lua:\n%s",
                e.what());
    } catch (...) {
        log.fatal("Unknown exception in c++ function call from lua.");
        throw;
    }
}

// Taken from lbaselib.c from lua and converted to use mk1::ut::Logger
static int log_helper(lua_State* L, const ut::Logger::Level level)
{
    std::stringstream stream;

    int n = lua_gettop(L); /* number of arguments */
    int i;
    lua_getglobal(L, "tostring");
    for (i = 1; i <= n; i++) {
        const char* s;
        lua_pushvalue(L, -1); /* function to be called */
        lua_pushvalue(L, i);  /* value to print */
        lua_call(L, 1, 1);
        s = lua_tostring(L, -1); /* get result */
        if (s == NULL)
            return luaL_error(
                    L, LUA_QL("tostring") " must return a string to " LUA_QL(
                               "print"));
        if (i > 1)
            stream << "\t";
        stream << s;
        lua_pop(L, 1); /* pop result */
    }

    const string msg = stream.str();
    log.write(level, msg);

    if (ut::Logger::Level::FATAL == level) {
        push(L, msg);
        return lua_error(L);
    } 
    return 0;
}


static int print(lua_State* L)
{
    return log_helper(L, ut::Logger::Level::INFO);
}


static int error(lua_State* L)
{
    log_helper(L, ut::Logger::Level::FATAL);
    return lua_error(L);
}

// Returns the compiled chunk as a function, or in case of an error the pair
// [nil, error_message]
static int load_file(lua_State* L)
{
    size_t len;
    const char* filename = lua_tolstring(L, 1, &len);

    if (!load_file(L, string{filename, len})) {
        return 1;
    }

    lua_pushnil(L);
    lua_pushvalue(L, -2);

    return 2;
}

// Returns the compiled chunk as a function, or in case of an error the pair
// [nil, error_message]
static int load_string(lua_State* L)
{
    size_t len;
    const char* str = lua_tolstring(L, 1, &len);
    const char* name = lua_tostring(L, 2);

    if (!load_string(L, str, len, name)) {
        return 1;
    }

    lua_pushnil(L);
    lua_pushvalue(L, -2);

    return 2;
}

static int do_string(lua_State* L)
{
    size_t len;
    const char* str = lua_tolstring(L, 1, &len);

    const int init_top = lua_gettop(L);

    if (!do_string(L, str, len)) {
        return lua_gettop(L) - init_top;
    }

    lua_pushnil(L);
    lua_pushvalue(L, -2);

    return 2;
}

static int do_file(lua_State* L)
{
    size_t len;
    const char* filename = lua_tolstring(L, 1, &len);

    const int init_top = lua_gettop(L);

    if (!do_file(L, string{filename, len})) {
        return lua_gettop(L) - init_top;
    }

    lua_pushnil(L);
    lua_pushvalue(L, -2);

    return 2;
}

} // namespace mk1::lua
