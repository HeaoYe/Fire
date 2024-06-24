#pragma once

#include <Fire/core/math/storage/storage_array_2d.hpp>
#include <span>

namespace Fire {
    template <ConceptArithmetic, SizeT>
    class StorageArray1D;

    template <ConceptArithmetic T, SizeT N, SizeT M>
    struct Matrix : public StorageArray2D<T, N, M> {
        DEFINE_STORAGE_ARRAY_2D(Matrix, T, N, M)
    public:
        static Matrix GenerateIdentity(T value = 1) {
            static_assert(N == M, "");
            Matrix result {};
            for (SizeT i = 0; i < N; i ++) {
                result.set(i, i, value);
            }
            return result;
        }

        static Matrix GenerateDiag(std::span<const T> values) {
            static_assert(N == M, "");
            Matrix result {};
            for (SizeT i = 0; i < N; i ++) {
                result.set(i, i, values[i]);
            }
            return result;
        }

        static Matrix GenerateDiag(const StorageArray1D<T, N> &values) {
            static_assert(N == M, "");
            Matrix result {};
            for (SizeT i = 0; i < N; i ++) {
                result.set(i, i, values.get(i));
            }
            return result;
        }
    };

    template <ConceptArithmetic T, SizeT N, SizeT M>
    IMPL_TRAIT(Matrix, Matrix<T, N, M>)

    template <ConceptArithmetic T, SizeT N, SizeT M>
    IMPL_TRAIT(Add, Matrix<T, N, M>)

    template <ConceptArithmetic T, SizeT N, SizeT M>
    IMPL_TRAIT(ScalarMul, Matrix<T, N, M>)

    template <ConceptArithmetic T, SizeT N, SizeT M>
    IMPL_TRAIT(Linear, Matrix<T, N, M>)

    template <ConceptArithmetic T, SizeT N, SizeT M>
    IMPL_TRAIT(MatrixMul, Matrix<T, N, M>)

    template <ConceptArithmetic T, SizeT N, SizeT M>
    IMPL_TRAIT(Ring, Matrix<T, N, M>)

    TRAIT_API_WITH_CONDITIONS(MatrixMul, ((T::NRow == Y::NRow) && (T::NColumn == Y::NColumn)), (typename T::template ResizeToT<T::NColumn, T::NColumn>), , ConceptMatrixMul Y)
    LinearLeastSquares(const T &x, const Y &y) {
        auto xT = Transpose(x);
        auto xTxI = Inverse(xT * x);
        auto xTy = xT * y;
        return Transpose(xTxI * xTy);
    }
}
