#pragma once

#include <cstddef>

namespace Fire {
    class MemoryAllocator {
    public:
        virtual void *allocate(size_t size, size_t alignment, bool is_array) = 0;
        virtual void deallocate(void *ptr, size_t alignment, bool is_array) = 0;
        virtual ~MemoryAllocator() = default;
    };

    MemoryAllocator &GetGlobalMemoryAllocator();
}

void *operator new(size_t size);
void *operator new[](size_t size);
void operator delete(void *ptr) noexcept;
void operator delete[](void *ptr) noexcept;
