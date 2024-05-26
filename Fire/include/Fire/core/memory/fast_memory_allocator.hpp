#pragma once

#include <Fire/core/memory/memory_allocator.hpp>

namespace Fire {
    // TODO: 用分块内存池管理内存
    class FastMemoryAllocator final : public MemoryAllocator {
    public:
        void *allocate(size_t size, size_t alignment, bool is_array) override;
        void deallocate(void *ptr, size_t alignment, bool is_array) override;
        ~FastMemoryAllocator() override;
    };
}
