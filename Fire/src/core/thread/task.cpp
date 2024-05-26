#include "core/thread/task.hpp"

namespace Fire {
    TaskPtr Task::addSubtask(TaskPtr subtask) {
        if (!running_flag.test()) {
            subtasks.push_back(subtask);
        }
        return subtask;
    }

    bool Task::isCompleted() const {
        bool is_completed = completed_flag.test();
        for (TaskPtr subtask : subtasks) {
            is_completed &= subtask->isCompleted();
            if (!is_completed) {
                return false;
            }
        }
        return is_completed;
    }

    void Task::wait() const {
        completed_flag.wait(false);
        for (TaskPtr subtask : subtasks) {
            subtask->wait();
        }
    }

    void Task::reset() {
        wait();
        for (TaskPtr subtask : subtasks) {
            subtask->wait();
        }
        completed_flag.clear();
        for (TaskPtr subtask : subtasks) {
            subtask->reset();
        }
    }
}
