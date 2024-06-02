#pragma once

#include <Fire/core/math/storage/storage_array_1d.hpp>
#include <Fire/core/math/traits/euclidean_a.hpp>

namespace Fire {
    template <ConceptArithmetic T, size_t N>
    struct Point : public StorageArray1D<T, N> {
        DEFINE_STORAGE_ARRAY_1D(Point, T, N)
    };

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(ScalarMul, Point<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(Metric, Point<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(Affine, Point<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(EuclideanA, Point<T, N>)
}
