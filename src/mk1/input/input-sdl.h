#pragma once

#include <SDL.h>

#include <mk1/input/gamepad.h>
#include <mk1/input/keyboard.h>
#include <mk1/input/mouse.h>

namespace mk1::input::SDL {

GamepadAxis SDL_GamepadAxis_to_GamepadAxis(uint8_t axis);
GamepadButton SDL_GamepadButton_to_GamepadButton(uint8_t button);
Key SDL_keycode_to_Key(const SDL_Keycode keycode);
KeyModifier SDL_Keymod_to_KeyModifier(const uint16_t mod);
MouseButton SDL_mousebutton_to_Button(const uint8_t button);
}
