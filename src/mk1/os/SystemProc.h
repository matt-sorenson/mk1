#pragma once

#include <mk1/ut.h>

#include <mk1/Core/Process.h>

#include <mk1/os/Window.h>

#include <mk1/input/gamepad.h>
#include <mk1/input/keyboard.h>
#include <mk1/input/mouse.h>

namespace mk1::os {
class SystemProc final : public core::Process {
  public:
    SystemProc();
    virtual ~SystemProc();

    SystemProc(const SystemProc&) = delete;
    SystemProc(const SystemProc&&) = delete;
    void operator=(const SystemProc&) = delete;

    core::Process::State update(ut::Timer::duration dt) final;

    std::shared_ptr<Window> get_window(const uint32_t id);

    std::shared_ptr<Window> create_window(const string& title,
                                          const int2& resolution,
                                          const bool fullscreen);

    void add_gamepad_handler(input::GamepadHandler* handler);
    void add_keyboard_handler(input::KeyboardHandler* handler);
    void add_mouse_handler(input::MouseHandler* handler);

    void remove_gamepad_handlers(input::GamepadHandler* handlers);
    void remove_keyboard_handlers(input::KeyboardHandler* handlers);
    void remove_mouse_handlers(input::MouseHandler* handlers);

  private:
    std::map<uint32_t, std::weak_ptr<Window>> windows;

    std::list<input::GamepadHandler*> gamepad_handlers;
    std::list<input::KeyboardHandler*> keyboard_handlers;
    std::list<input::MouseHandler*> mouse_handlers;

    std::map<int32_t, void*> gamepads;
};
}
