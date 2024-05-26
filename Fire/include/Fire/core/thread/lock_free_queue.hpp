#pragma once

#include <Fire/core/concepts.hpp>
#include <list>
#include <span>
#include <atomic>

namespace Fire {
    template <class T> requires ConceptPointer<T>
    class LockFreeQueue {
    public:
        template <class ...Args>
        LockFreeQueue(Args &&...args) : datas(std::forward<Args>(args)...) {}

        void enqueue(T element) {
            if (quited_flag.test()) {
                return;
            }
            lock();
            datas.emplace_back(element);
            unlock();
        }

        void enqueue(std::span<T> elements) {
            if (quited_flag.test()) {
                return;
            }
            lock();
            for (T element : elements) {
                datas.emplace_back(element);
            }
            unlock();
        }

        T dequeue() {
            dequeueLock();
            lock();
            if (datas.empty()) {
                unlock();
                while (size() == 0) {
                    if (quited_flag.test()) {
                        dequeueUnlock();
                        return nullptr;
                    }
                }
                lock();
            }
            T element = datas.front();
            datas.pop_front();
            unlock();
            dequeueUnlock();
            return element;
        }

        size_t size() const {
            lock();
            auto size = datas.size();
            unlock();
            return size;
        }

        void quit() { quited_flag.test_and_set(); }

        void wait() { while (size() != 0)  {} }
    private:
        void lock() const { while(queue_flag.test_and_set(std::memory_order::acquire)) {} }
        void unlock() const { queue_flag.clear(std::memory_order::release); }
        void dequeueLock() const { while(dequeue_flag.test_and_set(std::memory_order::acquire)) {} }
        void dequeueUnlock() const { dequeue_flag.clear(std::memory_order::release); }
    private:
        std::list<T> datas;
        mutable std::atomic_flag queue_flag {}, dequeue_flag {};
        std::atomic_flag quited_flag {};
    };
}
