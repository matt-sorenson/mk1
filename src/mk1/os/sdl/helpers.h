#pragma once

#include <mk1/ut.h>

#include <SDL.h>

namespace mk1::os::SDL {
void throw_assert(const bool condition, const char* message);
}
