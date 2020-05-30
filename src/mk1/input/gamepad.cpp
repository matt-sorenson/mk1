#include <mk1/ut.h>

#include <mk1/input/gamepad.h>

namespace mk1::input {


static const string gamepad_buttons_str[]{
#define X_MACRO(x) #x
#include "mk1/input/gamepad_buttons.x.inl.h"
#undef X_MACRO
};

const string& GamepadButton_to_string(const GamepadButton button)
{
    return gamepad_buttons_str[size_t(button)];
}

GamepadButton string_to_GamepadButton(const string& str)
{
    for (size_t i = 0; i <= size_t(GamepadButton::COUNT); ++i) {
        if (gamepad_buttons_str[i] == str) {
            return GamepadButton(i);
        }
    }

    throw std::invalid_argument("Unknown gamepad button: "s + (const char*)str.c_str());
}
}
