#include "core/memory/memory_allocator.hpp"

#if defined (FIRE_DEBUG_MODE)
    #include "core/memory/debug_memory_allocator.hpp"
#else
    #include "core/memory/fast_memory_allocator.hpp"
#endif

namespace Fire {
    MemoryAllocator &GetGlobalMemoryAllocator() {
    #if defined (FIRE_DEBUG_MODE)
        static DebugMemoryAllocator memory_allocator {};
    #else
        static FastMemoryAllocator memory_allocator {};
    #endif
        return memory_allocator;
    }
}

void *operator new(size_t size) {
    return Fire::GetGlobalMemoryAllocator().allocate(size, 0, false);
}

void *operator new[](size_t size) {
    return Fire::GetGlobalMemoryAllocator().allocate(size, 0, true);
}

void operator delete(void *ptr) noexcept {
    return Fire::GetGlobalMemoryAllocator().deallocate(ptr, 0, false);
}

void operator delete[](void *ptr) noexcept {
    return Fire::GetGlobalMemoryAllocator().deallocate(ptr, 0, true);
}
