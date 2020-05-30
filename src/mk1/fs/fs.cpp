#include <mk1/ut.h>

#include <mk1/fs/fs.h>

#include <SDL.h>

namespace mk1 {
namespace fs {

    File::File(const char* filename, const char* mode)
    {
        _file = SDL_RWFromFile(filename, mode);

        if (nullptr == _file) {
            throw std::runtime_error("Failed to open file '"s + filename
                                     + "' :\n" + SDL_GetError());
        }
    }


    File::~File() { SDL_RWclose((SDL_RWops*)_file); }
    void File::seek(int64_t offset)
    {
        const int64_t out = SDL_RWseek((SDL_RWops*)_file, offset, RW_SEEK_SET);

        if (-1 == out) {
            throw std::runtime_error("Failed to seek:\n"s + SDL_GetError());
        }
    }


    int64_t File::tell() const
    {
        const int64_t out = SDL_RWtell((SDL_RWops*)_file);

        if (-1 == out) {
            throw std::runtime_error("Failed to tell:\n"s + SDL_GetError());
        }

        return out;
    }


    int64_t File::size() const
    {
        const int64_t out = SDL_RWsize((SDL_RWops*)_file);

        if (-1 == out) {
            throw std::runtime_error("Failed to get the file size:\n"s
                                     + SDL_GetError());
        }

        return out;
    }


    WriteFile::WriteFile(const char* filename) : File(filename, "w") {}
    WriteFile::~WriteFile() {}
    void WriteFile::write(const void* buffer, const size_t len)
    {
        const size_t out = SDL_RWwrite(get_handle<SDL_RWops>(), buffer, 1, len);

        if (len > out) {
            throw std::runtime_error("Failed to write to file:\n"s
                                     + SDL_GetError());
        }
    }


    ReadFile::ReadFile(const char* filename) : File(filename, "r") {}
    ReadFile::~ReadFile() {}
    size_t ReadFile::read(void* buffer, const size_t len)
    {
        const size_t out = SDL_RWread(get_handle<SDL_RWops>(), buffer, 1, len);

        if (0 == out) {
            throw std::runtime_error("Failed to read from file:\n"s
                                     + SDL_GetError());
        }

        return out;
    }


    static string home;
    static string base;
    static bool init_fs_called = false;


    void init_fs(const string& org, const string& app)
    {
        assert_throw(!init_fs_called,
                     "You're trying to call fs::init_fs multiple times");

        char* pref_path = SDL_GetPrefPath((const char*)org.c_str(),
                                          (const char*)app.c_str());
        char* base_path = SDL_GetBasePath();

        home = (const char*)pref_path;
        base = (const char*)base_path;

        SDL_free(base_path);
        SDL_free(pref_path);
    }


    const string& get_home()
    {
        assert_throw(
                init_fs_called,
                "Called fs::get_home() without having called fs::init_fs()");

        return home;
    }


    const string& get_base()
    {
        assert_throw(
                init_fs_called,
                "Called fs::get_home() without having called fs::init_fs()");

        return base;
    }


} // fs
} // mk1
