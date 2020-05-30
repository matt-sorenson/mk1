#include <mk1/ut/Logger.h>

namespace mk1::ut::loggers {

#if defined _WIN32
#include <windows.h>
#else
static constexpr const char* RESET_COLORS = "\033[0m";

static constexpr const char* LEVEL_COLORS[]
        = {RESET_COLORS, "\033[0;39m", "\033[0;39m",
           "\033[0;33m", "\033[0;31m", RESET_COLORS};
#endif

class ConsoleLogWriter : public Logger::Writer {
  public:
#if defined _WIN32
    ConsoleLogWriter()
    {
        if (!AllocConsole()) {
            FreeConsole();
        }

        if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
            AllocConsole();
            MoveWindow(GetConsoleWindow(), 0, -20, 800, 300, true);
        }

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996)
#endif
        freopen("CONOUT$", "w", stdout);
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
    }

    ~ConsoleLogWriter() { FreeConsole(); }
#endif

    virtual void write(const Logger::Data& data) override
    {
#ifndef _WIN32
        puts(fmt::format("{} [{}{}{}] {}\n", data.timestamp,
                    LEVEL_COLORS[size_t(data.level)], data.level_str,
                    RESET_COLORS, data.raw).c_str());
#else
        puts(data.formatted.c_str());
#endif
    }
};
}
