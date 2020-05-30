#include <mk1/input/input-sdl.h>

namespace mk1::input::SDL {

GamepadButton SDL_GamepadButton_to_GamepadButton(uint8_t button)
{
    switch (button) {
    case SDL_CONTROLLER_BUTTON_A:
        return GamepadButton::A;
    case SDL_CONTROLLER_BUTTON_B:
        return GamepadButton::B;
    case SDL_CONTROLLER_BUTTON_X:
        return GamepadButton::X;
    case SDL_CONTROLLER_BUTTON_Y:
        return GamepadButton::Y;
    case SDL_CONTROLLER_BUTTON_BACK:
        return GamepadButton::BACK;
    case SDL_CONTROLLER_BUTTON_GUIDE:
        return GamepadButton::GUIDE;
    case SDL_CONTROLLER_BUTTON_START:
        return GamepadButton::START;
    case SDL_CONTROLLER_BUTTON_LEFTSTICK:
        return GamepadButton::LEFT_STICK;
    case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
        return GamepadButton::RIGHT_STICK;
    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
        return GamepadButton::LEFT_SHOULDER;
    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
        return GamepadButton::RIGHT_SHOULDER;
    case SDL_CONTROLLER_BUTTON_DPAD_UP:
        return GamepadButton::DPAD_UP;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
        return GamepadButton::DPAD_DOWN;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
        return GamepadButton::DPAD_LEFT;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
        return GamepadButton::DPAD_RIGHT;

    default:
        throw std::runtime_error("Unknown controller button: "
                                 + to_string(button));
    }
}

GamepadAxis SDL_GamepadAxis_to_GamepadAxis(uint8_t axis)
{
    switch (axis) {
    case SDL_CONTROLLER_AXIS_LEFTX:
        return GamepadAxis::LEFT_X;
    case SDL_CONTROLLER_AXIS_LEFTY:
        return GamepadAxis::LEFT_Y;
    case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
        return GamepadAxis::LEFT_TRIGGER;
    case SDL_CONTROLLER_AXIS_RIGHTX:
        return GamepadAxis::RIGHT_X;
    case SDL_CONTROLLER_AXIS_RIGHTY:
        return GamepadAxis::RIGHT_Y;
    case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
        return GamepadAxis::RIGHT_TRIGGER;

    default:
        throw std::invalid_argument(fmt::format("Unknown axis: {}", axis));
    }
}

static bool SDL_Keycode_range_to_Key(Key* out, const SDL_Keycode keycode,
                                     const int32_t begin_input,
                                     const int32_t end_input,
                                     const Key begin_out)
{
    if ((begin_input <= keycode) && (end_input >= keycode)) {
        *out = Key(int(begin_out) + (keycode - begin_input));
        return true;
    }

    return false;
}

Key SDL_keycode_to_Key(const SDL_Keycode keycode)
{
    Key out;
    if (SDL_Keycode_range_to_Key(&out, keycode, 'a', 'z', Key::A)) {
        return out;
    } else if (SDL_Keycode_range_to_Key(&out, keycode, '0', '9', Key::NUM_0)) {
        return out;
    } else if (SDL_Keycode_range_to_Key(&out, keycode, SDLK_KP_1, SDLK_KP_9,
                                        Key::KEYPAD_1)) {
        return out;
    } else if (SDL_Keycode_range_to_Key(&out, keycode, SDLK_F1, SDLK_F12,
                                        Key::F1)) {
        return out;
    } else if (SDL_Keycode_range_to_Key(&out, keycode, SDLK_F13, SDLK_F24,
                                        Key::F13)) {
        return out;
    }

    switch (keycode) {
    case SDLK_KP_0:
        return Key::KEYPAD_0;
    case SDLK_KP_MULTIPLY:
        return Key::KEYPAD_MULTIPLY;
    case SDLK_KP_PLUS:
        return Key::KEYPAD_ADD;
    case SDLK_KP_MINUS:
        return Key::KEYPAD_SUBTRACT;
    case SDLK_KP_PERIOD:
        return Key::KEYPAD_DECIMAL;
    case SDLK_KP_DIVIDE:
        return Key::KEYPAD_DIVIDE;
    case SDLK_KP_ENTER:
        return Key::KEYPAD_ENTER;
    case SDLK_CAPSLOCK:
        return Key::CAPS_LOCK;
    case SDLK_NUMLOCKCLEAR:
        return Key::NUM_LOCK;
    case SDLK_SCROLLLOCK:
        return Key::SCROLL_LOCK;
    case SDLK_BACKSPACE:
    case SDLK_KP_BACKSPACE:
        return Key::BACKSPACE;
    case SDLK_TAB:
        return Key::TAB;
    case SDLK_RETURN:
        return Key::RETURN;
    case SDLK_ESCAPE:
        return Key::ESCAPE;
    case SDLK_SPACE:
        return Key::SPACE;
    case SDLK_PAUSE:
        return Key::PAUSE;
    case SDLK_PAGEUP:
        return Key::PAGE_UP;
    case SDLK_PAGEDOWN:
        return Key::PAGE_DOWN;
    case SDLK_HOME:
        return Key::HOME;
    case SDLK_END:
        return Key::END;
    case SDLK_PRINTSCREEN:
        return Key::PRINT_SCREEN;
    case SDLK_INSERT:
        return Key::INSERT;
    case SDLK_DELETE:
        return Key::DELETE;
    case SDLK_LEFT:
        return Key::LEFT;
    case SDLK_UP:
        return Key::UP;
    case SDLK_RIGHT:
        return Key::RIGHT;
    case SDLK_DOWN:
        return Key::DOWN;
    case SDLK_LSHIFT:
        return Key::LSHIFT;
    case SDLK_RSHIFT:
        return Key::RSHIFT;
    case SDLK_LCTRL:
        return Key::LCONTROL;
    case SDLK_RCTRL:
        return Key::RCONTROL;
    case SDLK_LALT:
        return Key::LALT;
    case SDLK_RALT:
        return Key::RALT;
    case SDLK_BACKQUOTE:
        return Key::TILDE;
    case SDLK_SEMICOLON:
        return Key::SEMICOLON;
    case SDLK_EQUALS:
        return Key::EQUAL;
    case SDLK_COMMA:
        return Key::COMMA;
    case SDLK_MINUS:
        return Key::MINUS;
    case SDLK_PERIOD:
        return Key::PERIOD;
    case SDLK_QUOTE:
        return Key::QUOTE;
    case SDLK_SLASH:
        return Key::SLASH;
    case SDLK_BACKSLASH:
        return Key::BACKSLASH;
    case SDLK_LEFTBRACKET:
        return Key::LBRACKET;
    case SDLK_RIGHTBRACKET:
        return Key::RBRACKET;

    default:
        return Key::UNKNOWN;
    }
}

KeyModifier SDL_Keymod_to_KeyModifier(const uint16_t mod)
{
    KeyModifier out = KeyModifier::NONE;

    if (KMOD_LALT | mod) {
        out |= KeyModifier::LALT;
    }
    if (KMOD_RALT | mod) {
        out |= KeyModifier::RALT;
    }

    if (KMOD_LCTRL | mod) {
        out |= KeyModifier::LCTRL;
    }
    if (KMOD_RCTRL | mod) {
        out |= KeyModifier::RCTRL;
    }

    if (KMOD_LSHIFT | mod) {
        out |= KeyModifier::LSHIFT;
    }
    if (KMOD_RSHIFT | mod) {
        out |= KeyModifier::RSHIFT;
    }

    if (KMOD_LGUI | mod) {
        out |= KeyModifier::LMETA;
    }
    if (KMOD_RGUI | mod) {
        out |= KeyModifier::RMETA;
    }

    return out;
}

MouseButton SDL_mousebutton_to_Button(const uint8_t button)
{
    switch (button) {
    case SDL_BUTTON_LEFT:
        return MouseButton::LEFT;
    case SDL_BUTTON_MIDDLE:
        return MouseButton::MIDDLE;
    case SDL_BUTTON_RIGHT:
        return MouseButton::RIGHT;
    case SDL_BUTTON_X1:
        return MouseButton::X1;
    case SDL_BUTTON_X2:
        return MouseButton::X2;

    default:
        throw std::invalid_argument(fmt::format("Unknown button: {}", button));
    }
}
}
