#pragma once

#include <Fire/core/macros.hpp>
#include <functional>
#include <atomic>
#include <span>

namespace Fire {
    using TaskPtr = class Task *;

    class Task {
        friend class ThreadPool;
    public:
        template <class CallbackType>
        static TaskPtr CreateTask(CallbackType &&callback) {
            return new Task(std::forward<CallbackType>(callback));
        }

        static void FreeTask(TaskPtr task) {
            task->wait();
            FreeTaskInternal(task);
        }

        static void FreeTasks(std::span<TaskPtr> tasks) {
            for (TaskPtr task : tasks) {
                FreeTask(task);
            }
        }
    private:
        static void FreeTaskInternal(TaskPtr task) {
            for (TaskPtr subtask : task->subtasks) {
                FreeTaskInternal(subtask);
            }
            delete task;
        }
    private:
        Task(std::function<void ()> &&lambda) {
            callback = std::move(lambda);
        }

        Task(const std::function<void ()> &function) {
            callback = function;
        }
    public:
        FIRE_API TaskPtr addSubtask(TaskPtr subtask);
        FIRE_API bool isCompleted() const;
        FIRE_API void wait() const;
        FIRE_API void reset();
    private:
        std::function<void ()> callback;
        mutable std::atomic_flag running_flag {}, completed_flag {};
        std::vector<TaskPtr> subtasks;
    };
}
