#pragma once

namespace mk1::ut {

template <typename std_timer>
class BaseTimer {
  public:
    typedef typename std_timer::duration duration;

    void reset() { _start_time = now(); }
    duration get_duration() { return now() - _start_time; }
    template <typename unit, typename T>
    std::chrono::duration<T, unit> get_duration()
    {
        using namespace std::chrono;
        return duration_cast<std::chrono::duration<T, unit>>(get_duration());
    }

    template <typename unit, typename T>
    T get_time() const
    {
        using namespace std::chrono;
        return get_duration<unit, T>().count();
    }

  private:
    typename std_timer::time_point now() const { return std_timer::now(); }
    typename std_timer::time_point _start_time = now();
};

typedef BaseTimer<std::chrono::high_resolution_clock> Timer;
}
