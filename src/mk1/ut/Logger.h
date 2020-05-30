#pragma once

#include <mk1/ut/containers/containers.h>

namespace mk1::ut {

class Logger final {
  public:
    enum class Level { ALL, DEBUG, INFO, WARN, FATAL, NONE };

    struct Data {
        Level level = Level::ALL;
        string level_str;
        string timestamp;
        string raw;
        string formatted;
    };

    class Writer : public containers::IntrusiveList<Writer>::Node {
      public:
        typedef containers::IntrusiveList<Writer> IntruList;

        Writer();
        virtual ~Writer();

        virtual void write(const Data& data) = 0;
    };

    void set_min_level(const Level min_level) { _min_level = min_level; }
    inline void debug(const string& msg) { write(Level::DEBUG, msg); }
    inline void fatal(const string& msg) { write(Level::FATAL, msg); }
    inline void info(const string& msg) { write(Level::INFO, msg); }
    inline void warn(const string& msg) { write(Level::WARN, msg); }
    void write(const Level level, const string& message);

    void add_writer(Writer* writer);
    void remove_writer(Writer* writer);

   private:

    Level _min_level = Level::ALL;
    Writer::IntruList _writers;
};
}

namespace mk1 {

extern ut::Logger log;

} // namespace mk1
