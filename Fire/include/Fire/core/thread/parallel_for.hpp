#pragma once

#include <Fire/core/macros.hpp>
#include <Fire/core/concepts.hpp>
#include <Fire/core/thread/task.hpp>
#include <Fire/core/thread/thread_pool.hpp>

namespace Fire {
    template <ConceptIntegral IntType, class CallbackType>
    TaskPtr ParallelFor(ThreadPool &pool, IntType start, IntType end, CallbackType &&callback) {
        TaskPtr main_task = Task::CreateTask([]() {});
        for (IntType i = start; i < end; i ++) {
            TaskPtr task = Task::CreateTask([i, callback_ = std::forward<CallbackType>(callback)]() {
                callback_(i);
            });
            main_task->addSubtask(task);
        }
        pool.addTask(main_task);
        return main_task;
    }

    template <ConceptIntegral IntType, class CallbackType>
    TaskPtr ParallelFor2D(ThreadPool &pool, IntType start_x, IntType end_x, IntType start_y, IntType end_y, CallbackType &&callback) {
        TaskPtr main_task = Task::CreateTask([]() {});
        for (IntType i = start_x; i < end_x; i ++) {
            for (IntType j = start_y; j < end_y; j ++) {
                TaskPtr task = Task::CreateTask([i, j, callback_ = std::forward<CallbackType>(callback)]() {
                    callback_(i, j);
                });
                main_task->addSubtask(task);
            }
        }
        pool.addTask(main_task);
        return main_task;
    }

    template <ConceptIntegral IntType, class CallbackType>
    TaskPtr ParallelFor3D(ThreadPool &pool, IntType start_x, IntType end_x, IntType start_y, IntType end_y, IntType start_z, IntType end_z, CallbackType &&callback) {
        TaskPtr main_task = Task::CreateTask([]() {});
        for (IntType i = start_x; i < end_x; i ++) {
            for (IntType j = start_y; j < end_y; j ++) {
                for (IntType k = start_z; k < end_z; k ++) {
                    TaskPtr task = Task::CreateTask([i, j, k, callback_ = std::forward<CallbackType>(callback)]() {
                        callback_(i, j, k);
                    });
                    main_task->addSubtask(task);
                }
            }
        }
        pool.addTask(main_task);
        return main_task;
    }
}
