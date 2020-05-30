#include <mk1/ut.h>

#include <mk1/ut/Logger.h>

namespace mk1::ut {

static constexpr const char* LEVEL_STRINGS[]
        = {"all", "debug", "info", "warn", "fatal", "none"};

Logger::Writer::Writer() { log.add_writer(this); }
Logger::Writer::~Writer() { log.remove_writer(this); }
void Logger::add_writer(Writer* writer) { _writers.push_front(writer); }
void Logger::remove_writer(Writer* writer) { _writers.erase(writer); }
#ifdef _MSC_VER
#define localtime_r(time_p, result) localtime_s(result, time_p)
#endif

void Logger::write(const Level level, const string& message)
{
    if (int(level) < int(_min_level)) {
        return;
    }

    time_t current_time_epoch = ::time(nullptr);
    tm current_time;
    ::localtime_r(&current_time_epoch, &current_time);

    Data data;
    data.timestamp = fmt::format(
            "{:04d}-{:02d}-{:02d} {:02d}:{:02d}:{:02d}", current_time.tm_year + 1900,
            current_time.tm_mon + 1, current_time.tm_mday, current_time.tm_hour,
            current_time.tm_min, current_time.tm_sec);

    data.raw = message;
    data.level = level;
    data.level_str = LEVEL_STRINGS[size_t(level)];
    data.formatted = fmt::format("{} [{}]: {}", data.timestamp, data.level_str,
                                  message);

    for (Writer* curr = _writers.front(); curr; curr = curr->get_next()) {
        curr->write(data);
    }
}
}

namespace mk1 {

ut::Logger log;
}
