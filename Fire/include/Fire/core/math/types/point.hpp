#pragma once

#include <Fire/core/math/storage/storage_array_1d.hpp>

namespace Fire {
    template <ConceptArithmetic T, size_t N>
    struct Point : public StorageArray1D<T, N> {
        DEFINE_STORAGE_ARRAY_1D(StorageArray1D<T, N>)
    };

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(ScalarMul, Point<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(Metric, Point<T, N>)
}