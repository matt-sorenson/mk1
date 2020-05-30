#pragma once

#include <mk1/ut.h>

#include <SDL.h>

namespace mk1::os::SDL {
void throw_assert(const bool condition, const char* message)
{
    if (true != condition) {
        const auto output = fmt::format("{}: {}", (const char*)message, SDL_GetError());
        mk1::log.info((const char*)output.c_str());
        throw std::runtime_error(output);
    }
}
}
