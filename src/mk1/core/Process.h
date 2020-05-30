#pragma once

#include <mk1/ut.h>

namespace mk1::core {

class ProcessManager;

class Process {
  public:
    struct Init {
        ProcessManager* process_manager;
    };

    enum class State {
        ALIVE,   // Process is still alive and should continue to run
        DONE,    // Process is done and can be cleaned up
        EXIT_APP // The application should close
    };

    Process(const string& name, ProcessManager* proc_man)
        : process_manager{proc_man}, name{name}
    {
    }
    virtual ~Process() {}
    Process(const Process&) = delete;
    void operator=(const Process&) = delete;

    virtual State update(ut::Timer::duration dt) = 0;

    const string& get_name() const { return name; }
    virtual void kill() {}
  protected:
    ProcessManager* const process_manager;

  private:
    const string& name;
};
}
