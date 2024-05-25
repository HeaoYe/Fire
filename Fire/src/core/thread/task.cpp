#include "core/thread/task.hpp"

namespace Fire {
    bool Task::isCompleted() const {
        return completed_flag.test();
    }

    void Task::wait() const {
        completed_flag.wait(false);
    }
}
