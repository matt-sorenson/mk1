#pragma once

#include <mk1/ut/Logger.h>

#if defined(_MSC_VER)

#include <windows.h>

namespace mk1::ut::loggers {

class OutputDebugStringLogWriter : public Logger::Writer {
  public:
    virtual void write(const Logger::Data& data) override
    {
        OutputDebugStringA(data.formatted.c_str());
        OutputDebugStringA("\n");
    }
};
} // namespace mk1::ut::loggers

#endif