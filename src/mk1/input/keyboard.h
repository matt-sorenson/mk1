#pragma once

namespace mk1::input {

enum class Key {
#define X_MACRO(x) x,
#include <mk1/input/keyboard_key.x.inl.h>
#undef X_MACRO
};


enum class KeyModifier : uint32_t {
#define X_MACRO(k, v) k = v,
#include <mk1/input/keyboard_keymodifier.x.inl.h>
#undef X_MACRO
};

struct KeyEvent {
    Key key;
    bool repeat;
};

class KeyboardHandler {
  public:
    virtual void on_frame_start() {}
    virtual bool on_key_down(const KeyEvent& event) = 0;
    virtual bool on_key_up(const KeyEvent& event) = 0;
};
}

namespace mk1::ut {
template <>
struct enable_bitmask_operators<input::KeyModifier> {
    static constexpr bool value = true;
};
}

namespace mk1 {

const string& to_string(const input::Key key);
string to_string(const input::KeyModifier key);

namespace input {
    inline std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const Key key)
    {
        return os << mk1::to_string(key);
    }

    inline std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const KeyModifier key)
    {
        return os << mk1::to_string(key);
    }
}
}
