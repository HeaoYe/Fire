#pragma once

#include <Fire/core/thread/task.hpp>
#include <Fire/core/thread/lock_free_queue.hpp>
#include <thread>
#include <atomic>
#include <span>

namespace Fire {
    class ThreadPool {
    private:
        static void WorkerThreadFunc(ThreadPool *master);
    public:
        ThreadPool(uint32_t thread_count = 0);
        ~ThreadPool();
        void addTask(TaskPtr task);
        void addTasks(std::span<TaskPtr> tasks);
        uint32_t getWorkingThreadCount() const { return working_thread_count.load(); }
        uint32_t getThreadCount() const { return threads.size(); }
    private:
        bool is_alive { true }, enqueue_lock { false };
        std::vector<std::thread> threads;
        std::atomic<uint32_t> working_thread_count { 0 };
        LockFreeQueue<TaskPtr> pending_tasks {};
    };
}
