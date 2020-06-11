#include <mk1/ut.h>

#include <mk1/os/sdl/helpers.h>

#include <mk1/os/SystemProc.h>
#include <mk1/os/Window.h>

#include <mk1/input/input-sdl.h>

namespace mk1::os {

using namespace input::SDL;

SystemProc::SystemProc() : core::Process("System", nullptr)
{
    SDL::throw_assert(0 == SDL_Init(SDL_INIT_EVERYTHING),
                      "Failed to initialize SDL");
    mk1::log.info("SDL Initialized");

    SDL::throw_assert(-1 != SDL_GameControllerAddMappingsFromFile(
                                    "gamepads.txt"),
                      "Failed to setup controller mappings");
}

SystemProc::~SystemProc() { SDL_Quit(); }
static void handle_key_event(const SDL_KeyboardEvent& e,
                             std::list<input::KeyboardHandler*>& handlers)
{
    const auto key = SDL_keycode_to_Key(e.keysym.sym);

    input::KeyEvent key_event{key, !!e.repeat};

    if (SDL_KEYDOWN == e.type) {
        for (auto i : handlers) {
            if (i->on_key_down(key_event)) {
                return;
            }
        }
    } else {
        for (auto i : handlers) {
            if (i->on_key_up(key_event)) {
                return;
            }
        }
    }
}


static void handle_mouse_event(const SDL_Event& e,
                               std::list<input::MouseHandler*> handlers)
{
    switch (e.type) {
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP: {
        const int2 pos = {e.button.x, e.button.y};
        const auto button = SDL_mousebutton_to_Button(e.button.button);

        if (SDL_MOUSEBUTTONDOWN == e.type) {
            for (auto i : handlers) {
                if (i->on_button_down(pos, button)) {
                    return;
                }
            }
        } else {
            for (auto i : handlers) {
                if (i->on_button_up(pos, button)) {
                    return;
                }
            }
        }
    } break;
    case SDL_MOUSEMOTION: {
        const int2 pos = {e.motion.x, e.motion.y};
        const int2 delta = {e.motion.xrel, e.motion.yrel};

        for (auto i : handlers) {
            if (i->on_move(pos, delta)) {
                return;
            }
        }
    } break;
    case SDL_MOUSEWHEEL:
        if (e.wheel.y != 0) {
            for (auto i : handlers) {
                if (i->on_wheel(e.wheel.y)) {
                    return;
                }
            }
        }
        break;
    default:
        log.warn(fmt::format("Unknown event passed to handle_mouse_event: {}",
                             e.type));
        break;
    }
}

static void handle_gamepad_event(const SDL_Event& e,
                                 std::list<input::GamepadHandler*> handlers)
{
    switch (e.type) {
    case SDL_CONTROLLERAXISMOTION: {
        const auto axis = SDL_GamepadAxis_to_GamepadAxis(e.caxis.axis);
        for (auto i : handlers) {
            if (i->on_axis_move(axis, e.caxis.value)) {
                return;
            }
        }

    } break;
    case SDL_CONTROLLERBUTTONDOWN: {
        const auto btn = SDL_GamepadButton_to_GamepadButton(e.cbutton.button);
        for (auto i : handlers) {
            if (i->on_button_down(btn)) {
                return;
            }
        }

    } break;
    case SDL_CONTROLLERBUTTONUP: {
        const auto btn = SDL_GamepadButton_to_GamepadButton(e.cbutton.button);
        for (auto i : handlers) {
            if (i->on_button_up(btn)) {
                return;
            }
        }

    } break;
    default:
        break;
    }
}

static void open_gamepad(const int32_t id, std::map<int32_t, void*>& gamepads)
{
    log.info(fmt::format("Gamepad connected", id));

    SDL_GameController* controller = SDL_GameControllerOpen(id);
    if (!controller) {
        log.warn(fmt::format("failed to open Gamepad {}", id));
        return;
    }
    auto joystick = SDL_GameControllerGetJoystick(controller);

    char guid[33] = {};
    SDL_JoystickGetGUIDString(SDL_JoystickGetGUID(joystick), guid,
                                COUNT_OF(guid));

    log.info(fmt::format("Gamepad '{}' - {} opened.",
                            SDL_GameControllerName(controller), guid));

    const int32_t joy_id = SDL_JoystickInstanceID(joystick);
    gamepads[joy_id] = controller;
}

static void close_gamepad(int32_t id, std::map<int32_t, void*>& gamepads)
{
    auto i = gamepads.find(id);
    if (gamepads.end() != i) {
        SDL_GameControllerClose((SDL_GameController*)(i->second));
        log.info(fmt::format("Gamepad {} closed", id));
        gamepads.erase(i);
    }
}

core::Process::State SystemProc::update(ut::Timer::duration MK1_UNUSED(dt))
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_QUIT:
            return core::Process::State::EXIT_APP;

        case SDL_CONTROLLERDEVICEREMOVED: {
            log.info(fmt::format("Gamepad {} disconnected", e.cdevice.which));
            close_gamepad(e.cdevice.which, gamepads);
        } break;
        case SDL_CONTROLLERDEVICEADDED: {
            open_gamepad(e.cdevice.which, gamepads);
        } break;

        case SDL_CONTROLLERAXISMOTION:
        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
            handle_gamepad_event(e, gamepad_handlers);
            break;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
            handle_key_event(e.key, keyboard_handlers);
            break;

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEMOTION:
        case SDL_MOUSEWHEEL:
            handle_mouse_event(e, mouse_handlers);
            break;
        default:
            break;
        }
    }

    return core::Process::State::ALIVE;
}
std::shared_ptr<Window> SystemProc::get_window(const uint32_t id)
{
    auto window = windows.find(id);
    if (window != windows.end()) {
        return window->second.lock();
    }

    return {};
}

std::shared_ptr<Window> SystemProc::create_window(const string& title,
                                                  const int2& resolution,
                                                  const bool fullscreen)
{
    auto out = std::make_shared<Window>(title, resolution, fullscreen);
    windows[out->get_window_id()] = out;

    return out;
}
}
