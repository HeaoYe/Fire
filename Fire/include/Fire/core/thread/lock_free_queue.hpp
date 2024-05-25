#pragma once

#include <Fire/core/concepts.hpp>
#include <list>
#include <span>
#include <atomic>

namespace Fire {
    template <class T>
    class LockFreeQueue {
    public:
        template <class ...Args>
        LockFreeQueue(Args &&...args) : datas(std::forward<Args>(args)...) {
            queue_flag.clear();
        }

        void enqueue(T element) requires ConceptPointer<T> {
            lock();
            datas.emplace_back(element);
            unlock();
        }

        void enqueue(std::span<T> elements) requires ConceptPointer<T> {
            lock();
            for (T element : elements) {
                datas.emplace_back(element);
            }
            unlock();
        }

        void enqueue(const T &element) requires ConceptNotPointer<T> {
            lock();
            datas.emplace_back(element);
            unlock();
        }

        void enqueue(T &&element) requires ConceptNotPointer<T> {
            lock();
            datas.emplace_back(std::move(element));
            unlock();
        }

        T dequeue() requires ConceptPointer<T> {
            dequeueLock();
            lock();
            if (datas.empty()) {
                unlock();
                while (size() == 0) {}
                lock();
            }
            T element = datas.front();
            datas.pop_front();
            unlock();
            dequeueUnlock();
            return element;
        }

        T &&dequeue() requires ConceptNotPointer<T> {
            dequeueLock();
            lock();
            if (datas.empty()) {
                unlock();
                while (size() == 0) {}
                lock();
            }
            T &&element = std::move(datas.front());
            datas.pop_front();
            unlock();
            dequeueUnlock();
            return std::move(element);
        }

        size_t size() const {
            lock();
            auto size = datas.size();
            unlock();
            return size;
        }
    private:
        void lock() const { while(queue_flag.test_and_set(std::memory_order::acquire)) {} }
        void unlock() const { queue_flag.clear(std::memory_order::release); }
        void dequeueLock() const { while(dequeue_flag.test_and_set(std::memory_order::acquire)) {} }
        void dequeueUnlock() const { dequeue_flag.clear(std::memory_order::release); }
    private:
        std::list<T> datas;
        mutable std::atomic_flag queue_flag {}, dequeue_flag {};
    };
}
