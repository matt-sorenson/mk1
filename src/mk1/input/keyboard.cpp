#include <mk1/ut.h>

#include <mk1/input/keyboard.h>

namespace mk1 {

static const string Key_strings[] = {
#define X_MACRO(x) #x,
#include <mk1/input/keyboard_key.x.inl.h>
#undef X_MACRO
};

const string& to_string(const input::Key key)
{
    return Key_strings[size_t(key)];
}


string to_string(const input::KeyModifier mod)
{
#define X_MACRO(k, v)                                                          \
    if ((input::KeyModifier::k | mod) != input::KeyModifier::NONE) {           \
        return #k;                                                        \
    }
#include <mk1/input/keyboard_keymodifier.x.inl.h>
#undef X_MACRO
    throw std::invalid_argument(
            fmt::format("Uknown key modifier: {}", int(mod)));
}
}
