#pragma once

#include <mk1/ut.h>

#include <mk1/math/math.h>

namespace mk1::input {

enum class MouseButton {
#define X_MACRO(x) x,
#include <mk1/input/mouse_buttons.x.inl.h>
#undef X_MACRO
};

class MouseHandler {
  public:
    virtual void on_frame_start() {}
    virtual bool on_move(const int2 new_pos, const int2 delta) = 0;
    virtual bool on_button_down(const int2 pos, const MouseButton button) = 0;
    virtual bool on_button_up(const int2 pos, const MouseButton button) = 0;
    virtual bool on_wheel(const int dy) = 0;
};
}

namespace mk1 {
const string& to_string(input::MouseButton button);

namespace input {
    inline std::basic_ostream<char>&
    operator<<(std::basic_ostream<char>& os, const MouseButton btn)
    {
        return os << mk1::to_string(btn);
    }
}
}
