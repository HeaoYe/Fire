#pragma once

#include <Fire/core/concepts.hpp>
#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/storage/macros.hpp>
#include <Fire/core/math/traits_impl/array_2d_impl/array_2d_impl.hpp>

namespace Fire {
    #define DEFINE_STORAGE_ARRAY_2D(NAME, T, ...) \
        DEFINE_STORAGE(Array2DImpl, StorageArray2D<T, __VA_ARGS__>) \
        using BaseStorage::NRow; \
        using BaseStorage::NColumn; \
        using BaseStorage::IndexSequence; \
        template <SizeT NewNRow, SizeT NewNColumn> \
        using ResizeToT = NAME<T, NewNRow, NewNColumn>; \

    DEFINE_UNION_2D(StorageArray2D)
    DEFINE_UNION_2D_IMPL(StorageArray2D, 2, 2, m00, m01, m10, m11)
    DEFINE_UNION_2D_IMPL(StorageArray2D, 3, 3, m00, m01, m02, m10, m11, m12, m20, m21, m22)
    DEFINE_UNION_2D_IMPL(StorageArray2D, 4, 4, m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33)

    template <ConceptArithmetic T, SizeT NRow_, SizeT NColumn_>
    struct StorageArray2D : public UNION_DATA_NAME(StorageArray2D)<T, NRow_, NColumn_> {
        using UNION_DATA_NAME(StorageArray2D)<T, NRow_, NColumn_>::data;
        using Scalar = T;
        constexpr static SizeT NRow = NRow_;
        constexpr static SizeT NColumn = NColumn_;
        constexpr static auto IndexSequence = std::make_index_sequence<NRow_ * NColumn_>();

        template <SizeT Row, SizeT Column>
        T get() const {
            return data[Row * NColumn + Column];
        }

        T get(SizeT row, SizeT column) const {
            return data[row * NColumn + column];
        }

        template <SizeT Row, SizeT Column>
        void set(T value) {
            data[Row * NColumn + Column] = value;
        }

        void set(SizeT row, SizeT column, T value) {
            data[row * NColumn + column] = value;
        }
    };
}
