#pragma once

#include <functional>
#include <atomic>

namespace Fire {
    class Task {
        friend class ThreadPool;
    public:
        Task(std::function<void ()> &&lambda) {
            callback = std::move(lambda);
        }

        Task(const std::function<void ()> &lambda) {
            callback = lambda;
        }

        bool isCompleted() const;
        void wait() const;
        void reset();
    private:
        std::function<void ()> callback;
        mutable std::atomic_flag completed_flag {};
    };

    using TaskPtr = Task *;
}
