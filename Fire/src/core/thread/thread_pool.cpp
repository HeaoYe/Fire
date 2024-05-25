#include "core/thread/thread_pool.hpp"

namespace Fire {
    void ThreadPool::WorkerThreadFunc(ThreadPool *master) {
        while (master->is_alive) {
            TaskPtr task = master->pending_tasks.dequeue();
            if (task) {
                master->working_thread_count.fetch_add(1);
                task->callback();
                master->working_thread_count.fetch_sub(1);
                task->completed_flag.test_and_set();
                task->completed_flag.notify_all();
            }
        }
    }

    ThreadPool::ThreadPool(uint32_t thread_count) {
        if (thread_count == 0) {
            thread_count = std::thread::hardware_concurrency() - 1;
        }
        for (uint32_t i = 0; i < thread_count; i ++) {
            threads.push_back(std::thread(WorkerThreadFunc, this));
        }
    }

    ThreadPool::~ThreadPool() {
        enqueue_lock = true;
        while (pending_tasks.size()) {}
        is_alive = false;
        for (int i = 0; i < threads.size(); i++) {
            pending_tasks.enqueue(nullptr);
        }
        for (auto &thread : threads) {
            thread.join();
        }
    }

    void ThreadPool::addTask(TaskPtr task) {
        if (enqueue_lock) {
            return;
        }
        pending_tasks.enqueue(task);
    }

    void ThreadPool::addTasks(std::span<TaskPtr> tasks) {
        if (enqueue_lock) {
            return;
        }
        pending_tasks.enqueue(tasks);
    }
}
