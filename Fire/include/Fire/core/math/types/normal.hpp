#pragma once

#include <Fire/core/math/storage/storage_array_1d.hpp>

namespace Fire {
    template <ConceptArithmetic T, SizeT N>
    struct Normal : public StorageArray1D<T, N> {
        DEFINE_STORAGE_ARRAY_1D(Normal, T, N)
    };

    template <ConceptArithmetic T, SizeT N>
    IMPL_TRAIT(Add, Normal<T, N>)

    template <ConceptArithmetic T, SizeT N>
    IMPL_TRAIT(ScalarMul, Normal<T, N>)

    template <ConceptArithmetic T, SizeT N>
    IMPL_TRAIT(Linear, Normal<T, N>)

    template <ConceptArithmetic T, SizeT N>
    IMPL_TRAIT(Metric, Normal<T, N>)

    template <ConceptArithmetic T, SizeT N>
    IMPL_TRAIT(Norm, Normal<T, N>)

    template <ConceptArithmetic T, SizeT N>
    IMPL_TRAIT(InnerProduct, Normal<T, N>)

    template <ConceptArithmetic T, SizeT N>
    IMPL_TRAIT(EuclideanV, Normal<T, N>)
}
