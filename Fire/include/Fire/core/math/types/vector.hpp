#pragma once

#include <Fire/core/math/storage/storage_array_1d.hpp>

namespace Fire {
    template <ConceptArithmetic T, size_t N>
    struct Vector : public StorageArray1D<T, N> {
        DEFINE_STORAGE_ARRAY_1D(StorageArray1D<T, N>)
    };

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(Add, Vector<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(ScalarMul, Vector<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(Linear, Vector<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(Metric, Vector<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(Norm, Vector<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(InnerProduct, Vector<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(EuclideanV, Vector<T, N>)
}
