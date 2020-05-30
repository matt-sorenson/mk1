#include <mk1/input/mouse.h>

namespace mk1 {
static const string MouseButton_strings[] = {
#define X_MACRO(x) #x,
#include <mk1/input/mouse_buttons.x.inl.h>
#undef X_MACRO
};

const string& to_string(input::MouseButton button)
{
    return MouseButton_strings[size_t(button)];
}
}
