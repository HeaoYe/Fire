#pragma once

#include <Fire/core/concepts.hpp>
#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/storage/macros.hpp>
#include <Fire/core/math/traits_impl/array_1d_impl/array_1d_impl.hpp>

namespace Fire {
    #define DEFINE_STORAGE_ARRAY_1D(NAME, T, ...) \
        public: \
            DEFINE_STORAGE(Array1DImpl, ::Fire::StorageArray1D<T, __VA_ARGS__>) \
            using BaseStorage::Dims; \
            using BaseStorage::IndexSequence; \
            template <SizeT NewDims> \
            using ResizeToT = NAME<T, NewDims>; \
            DEFINE_CONSTRUCTORS(NAME) \

    #define DEFINE_STORAGE_ARRAY_1D_FIXED_SIZE(NAME, T, ...) \
        public: \
            DEFINE_STORAGE(Array1DImpl, ::Fire::StorageArray1D<T, __VA_ARGS__>) \
            using BaseStorage::Dims; \
            using BaseStorage::IndexSequence; \
            template <SizeT NewDims> \
            using ResizeToT = NAME; \
            DEFINE_CONSTRUCTORS(NAME) \

    DEFINE_UNION_1D(StorageArray1D)
    DEFINE_UNION_1D_IMPL(StorageArray1D, 1, (x), (r))
    DEFINE_UNION_1D_IMPL(StorageArray1D, 2, (x, y), (r, g))
    DEFINE_UNION_1D_IMPL(StorageArray1D, 3, (x, y, z), (r, g, b))
    DEFINE_UNION_1D_IMPL(StorageArray1D, 4, (x, y, z, w), (r, g, b, a))

    template <ConceptArithmetic T, SizeT N>
    struct StorageArray1D : public UNION_DATA_NAME(StorageArray1D)<T, N> {
        using UNION_DATA_NAME(StorageArray1D)<T, N>::data;
        using Scalar = T;
        constexpr static SizeT Dims = N;
        constexpr static auto IndexSequence = std::make_index_sequence<N>();

        void fill(T value) {
            for (SizeT i = 0; i < N; i ++) {
                data[i] = value;
            }
        }

        template <SizeT Idx>
        T get() const {
            return data[Idx];
        }

        T get(SizeT idx) const {
            return data[idx];
        }

        template <SizeT Idx>
        void set(T value) {
            data[Idx] = value;
        }

        void set(SizeT idx, T value) {
            data[idx] = value;
        }
    };
}
