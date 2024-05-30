#pragma once

#include <Fire/core/concepts.hpp>
#include <Fire/core/math/types.hpp>
#include <Fire/core/math/storage/macros.hpp>
#include <Fire/core/math/traits_impl/array_2d_impl/array_2d_impl.hpp>

namespace Fire {
    #define DEFINE_STORAGE_ARRAY_2D(...) \
        DEFINE_STORAGE(Array2DImpl, __VA_ARGS__) \
        using BaseStorage::Dims1; \
        using BaseStorage::Dims2; \
        using BaseStorage::IndexSequence; \

    template <ConceptArithmetic T, SizeT N, SizeT M>
    struct StorageArray2D {
        using Scalar = T;
        constexpr static SizeT Dims1 = N;
        constexpr static SizeT Dims2 = M;
        constexpr static auto IndexSequence = std::make_index_sequence<N * M>();

        T data[N][M] { 0 };

        template <SizeT Idx1, SizeT Idx2>
        T get() const {
            return data[Idx1][Idx2];
        }

        T get(SizeT idx1, SizeT idx2) const {
            return data[idx1][idx2];
        }

        template <SizeT Idx1, SizeT Idx2>
        void set(T value) {
            data[Idx1][Idx2] = value;
        }

        void set(SizeT idx1, SizeT idx2, T value) {
            data[idx1][idx2] = value;
        }
    };
}
