#pragma once

#include <Fire/core/math/storage/storage_array_1d.hpp>

namespace Fire {
    template <ConceptArithmetic T, size_t N>
    struct Normal : public StorageArray1D<T, N> {
        DEFINE_STORAGE_ARRAY_1D(T, N)
    };

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(Add, Normal<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(ScalarMul, Normal<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(Linear, Normal<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(Metric, Normal<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(Norm, Normal<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(InnerProduct, Normal<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(EuclideanV, Normal<T, N>)
}
