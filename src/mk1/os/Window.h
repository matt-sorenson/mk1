#pragma once

#include <mk1/ut.h>

namespace mk1::os {
class Window final {
  public:
    friend class SystemProcess;

    Window(const string& title, const int2& resolution, const bool fullscreen);
    ~Window();

    string get_title() const;
    bool get_fullscreen() const { return fullscreen; }
    int2 get_location() const;
    int2 get_resolution() const;

    Window* set_title(const string& title);
    Window* set_fullscreen(const bool fullscreen);
    Window* set_location(const int2& top_left);
    Window* set_resolution(const int2& resolution);

    uint32_t get_window_id() const;

    template <typename T>
    T* get_handle()
    {
        return static_cast<T*>(window);
    }

  private:
    void* window; // void* so we don't have to pull in all of SDL globally
    bool fullscreen;
};
}
