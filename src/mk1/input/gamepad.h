#pragma once

#include <mk1/ut.h>

namespace mk1::input {

enum class GamepadButton {
#define X_MACRO(x) x,
#include "mk1/input/gamepad_buttons.x.inl.h"
#undef X_MACRO
};

enum class GamepadAxis {
#define X_MACRO(x) x,
#include "mk1/input/gamepad_axis.x.inl.h"
#undef X_MACRO
};

const string& GamepadButton_to_string(const GamepadButton button);
GamepadButton string_to_GamepadButton(const string& str);

struct GamepadState {
    bool button_states[size_t(GamepadButton::COUNT)];
    int2 left_stick;
    int2 right_stick;
    int left_trigger;
    int right_trigger;
};

class GamepadHandler {
  public:
    virtual void on_frame_start() {}
    virtual bool on_button_down(GamepadButton button) = 0;
    virtual bool on_button_up(GamepadButton button) = 0;
    virtual bool on_axis_move(GamepadAxis axis, int16_t value) = 0;
};
}
