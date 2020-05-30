#include <mk1/ut.h>

#include <mk1/os/Window.h>

#include <mk1/os/sdl/helpers.h>

namespace mk1::os {
Window::Window(const string& title, const int2& resolution,
               const bool fullscreen)
{
    window = SDL_CreateWindow(
            (const char*)title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            resolution.x, resolution.y, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
                                                | SDL_WINDOW_ALLOW_HIGHDPI);

    SDL::throw_assert(window, "Failed to create window");

    set_fullscreen(fullscreen);
}

Window::~Window() { SDL_DestroyWindow((SDL_Window*)window); }
string Window::get_title() const
{
    return (const char*)SDL_GetWindowTitle((SDL_Window*)window);
}

int2 Window::get_location() const
{
    int2 out;
    SDL_GetWindowPosition((SDL_Window*)window, &out.x, &out.y);

    return out;
}

int2 Window::get_resolution() const
{
    int2 out;
    SDL_GetWindowSize((SDL_Window*)window, &out.x, &out.y);

    return out;
}

Window* Window::set_title(const string& title)
{
    SDL_SetWindowTitle((SDL_Window*)window, title.c_str());

    return this;
}

Window* Window::set_fullscreen(const bool _fullscreen)
{
    SDL_SetWindowFullscreen((SDL_Window*)window, _fullscreen);
    fullscreen = _fullscreen;

    return this;
}

Window* Window::set_location(const int2& top_left)
{
    SDL_SetWindowPosition((SDL_Window*)window, top_left.x, top_left.y);

    return this;
}

Window* Window::set_resolution(const int2& resolution)
{
    SDL_SetWindowSize((SDL_Window*)window, resolution.x, resolution.y);

    return this;
}

uint32_t Window::get_window_id() const
{
    return SDL_GetWindowID((SDL_Window*)window);
}
}
