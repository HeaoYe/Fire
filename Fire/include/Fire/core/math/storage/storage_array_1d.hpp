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

    #define DEFINE_STORAGE_ARRAY_1D_FIXED_SIZE(NAME, T, ...) \
        public: \
            DEFINE_STORAGE(Array1DImpl, ::Fire::StorageArray1D<T, __VA_ARGS__>) \
            using BaseStorage::Dims; \
            using BaseStorage::IndexSequence; \
            template <SizeT NewDims> \
            using ResizeToT = NAME; \

    template <ConceptArithmetic T, SizeT N>
    struct StorageArray1D {
        using Scalar = T;
        constexpr static SizeT Dims = N;
        constexpr static auto IndexSequence = std::make_index_sequence<N>();

        T data[N] { 0 };

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
