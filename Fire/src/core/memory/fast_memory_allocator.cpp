#include "core/memory/fast_memory_allocator.hpp"
#include <cstdlib>

namespace Fire {
    void *FastMemoryAllocator::allocate(size_t size, size_t alignment, bool is_array) {
        return malloc(size);
    }

    void FastMemoryAllocator::deallocate(void *ptr, size_t alignment, bool is_array) {
        free(ptr);
    }

    FastMemoryAllocator::~FastMemoryAllocator() {}
}
