#pragma once

#include <Fire/core/concepts.hpp>
#include <Fire/core/math/storage/macros.hpp>
#include <Fire/core/math/trait_impl/array_1d_impl/array_1d_impl.hpp>

namespace Fire {
    #define DEFINE_STORAGE_ARRAY_1D(...) \
        DEFINE_STORAGE(Array1DImpl, __VA_ARGS__) \
        using BaseStorage::Dims; \
        using BaseStorage::IndexSequence; \

    template <ConceptArithmetic T, size_t N>
    struct StorageArray1D {
        using Scalar = T;
        constexpr static auto Dims = N;
        constexpr static auto IndexSequence = std::make_index_sequence<N>();

        T data[N] { 0 };

        template <size_t Idx>
        T get() const {
            return data[Idx];
        }

        T get(size_t idx) const {
            return data[idx];
        }

        void set(size_t idx, T value) {
            data[idx] = value;
        }

        template <size_t Idx>
        void set(T value) {
            data[Idx] = value;
        }

        T operator[](size_t idx) const {
            return data[idx];
        }

        T &operator[](size_t idx) {
            return data[idx];
        }
    };
}
