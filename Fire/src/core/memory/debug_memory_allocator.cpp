#include "core/memory/debug_memory_allocator.hpp"
#include <cstdlib>
#include <string>

namespace Fire {
    void *DebugMemoryAllocator::allocate(size_t size, size_t align, bool is_array) {
        allocate_count.fetch_add(1);
        auto ptr = malloc(size);
        int i = 1;
        while ((size >> i) && (i <= g_max_tracing_memory_exponent)) {
            i ++;
        }
        allocate_info[i - 1].fetch_add(1);
        return ptr;
    }

    void DebugMemoryAllocator::deallocate(void *ptr, size_t align, bool is_array) {
        deallocate_count.fetch_add(1);
        free(ptr);
    }

    static std::string convert_size_t(size_t size) {
        if (size < 1024) {
            return std::to_string(size) + std::string("Byte");
        }
        size /= 1024;
        if (size < 1024) {
            return std::to_string(size) + std::string("KiB");
        }
        size /= 1024;
        if (size < 1024) {
            return std::to_string(size) + std::string("MiB");
        }
        size /= 1024;
        if (size < 1024) {
            return std::to_string(size) + std::string("GiB");
        }
        size /= 1024;
        return std::to_string(size) + std::string("TiB");
    }

    DebugMemoryAllocator::~DebugMemoryAllocator() {
        if (allocate_count.load() > 0) {
            printf("内存分配大小统计:\n");
            for (size_t i = 0; i < g_max_tracing_memory_exponent; i ++) {
                if (allocate_info[i].load() == 0) {
                    continue;
                }
                printf("\t%s <= X < %s: 分配%lld次\n", convert_size_t(1ll << i).c_str(), convert_size_t(2ll << i).c_str(), allocate_info[i].load());
            }
            if (allocate_info[g_max_tracing_memory_exponent].load() > 0) {
                printf("\tX >= %s: 分配%lld次\n", convert_size_t(1ll << g_max_tracing_memory_exponent).c_str(), allocate_info[g_max_tracing_memory_exponent].load());
            }
        }

        printf("内存分配数量统计:\n");
        printf("\t共分配%lld次\n", allocate_count.load());
        printf("\t共释放%lld次\n", deallocate_count.load());
        if (allocate_count.load() > deallocate_count.load()) {
            printf("\t发生内存泄漏!\n");
        } else if (allocate_count.load() < deallocate_count.load()) {
            printf("\t发生内存分配错误!\n");
        } else {
            printf("\t内存分配安全\n");
        }
    }
}
