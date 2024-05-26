#pragma once

#include <Fire/core/memory/memory_allocator.hpp>
#include <algorithm>
#include <atomic>

namespace Fire {
    class DebugMemoryAllocator final : public MemoryAllocator {
    public:
        void *allocate(size_t size, size_t alignment, bool is_array) override;
        void deallocate(void *ptr, size_t alignment, bool is_array) override;
        ~DebugMemoryAllocator() override;
    private:
        static constexpr size_t g_max_tracing_memory_exponent = std::max<size_t>(32, sizeof(size_t) * 4 - 1);
        std::atomic<size_t> allocate_count {};
        std::atomic<size_t> deallocate_count {};
        std::atomic<size_t> allocate_info[g_max_tracing_memory_exponent + 1] {};
    };
}
