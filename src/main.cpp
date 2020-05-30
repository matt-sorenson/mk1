#include <mk1/ut.h>

#include <mk1/math/Color.h>
#include <mk1/math/quaternion.h>

#include <mk1/input/gamepad.h>
#include <mk1/input/input-sdl.h>
#include <mk1/input/keyboard.h>

#include <mk1/lua/lua.h>

#include <mk1/os/SystemProc.h>

#include <SDL.h>

#include <mk1/ut/loggers/ConsoleLogWriter.h>
#include <mk1/ut/loggers/OutputDebugStringLogWriter.h>

static void sdl_assert(const bool condition, const char* message)
{
    if (true != condition) {
        const auto output = fmt::format("{}: {}", message, SDL_GetError());
        mk1::log.info((const char*)output.c_str());
        throw std::runtime_error(output);
    }
}

SDL_GameController* open_controller()
{
    SDL_GameController* controller = SDL_GameControllerOpen(0);

    if (controller) {
        mk1::log.info(fmt::format("Controller loaded: {}",
                                  SDL_GameControllerName(controller)));

        SDL_Joystick* joystick = SDL_GameControllerGetJoystick(controller);
        char buffer[60] = {};
        SDL_JoystickGetGUIDString(SDL_JoystickGetGUID(joystick), buffer,
                                  COUNT_OF(buffer));

        mk1::log.info(fmt::format("GUID: {}", buffer));
    }

    return controller;
}

int main(int MK1_UNUSED(argc), char** MK1_UNUSED(argv))
{
    mk1::ut::loggers::ConsoleLogWriter console_log_writer;

#if defined(_MSC_VER)
    mk1::ut::loggers::OutputDebugStringLogWriter output_debug_string_log_writer;
#endif

    mk1::os::SystemProc system_proc;
    auto window = system_proc.create_window("Test", mk1::int2(800, 600), false);

    SDL_Surface* image = SDL_LoadBMP("hello_world.bmp");
    sdl_assert(image, "Could not load image");
    mk1::log.info("Image loaded");

    bool running = true;
    uint8_t red = 0;
    while (running) {
        mk1::ut::Timer timer;
        running = mk1::core::Process::State::ALIVE
                  == system_proc.update(timer.get_duration());

        auto surface = SDL_GetWindowSurface(window->get_handle<SDL_Window>());
        const auto color = SDL_MapRGB(surface->format, red++, 0, 0);

        SDL_Rect dst_rect;

        const auto window_res = window->get_resolution();
        dst_rect.x = (window_res.x - image->w) / 2;
        dst_rect.y = (window_res.y - image->h) / 2;

        SDL_FillRect(surface, nullptr, color);
        SDL_BlitSurface(image, nullptr, surface, &dst_rect);
        SDL_UpdateWindowSurface(window->get_handle<SDL_Window>());
    }

    SDL_FreeSurface(image);

    mk1::log.info("Exiting");

    return EXIT_SUCCESS;
}
