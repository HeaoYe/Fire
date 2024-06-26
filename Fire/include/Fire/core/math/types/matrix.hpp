#pragma once

#include <Fire/core/math/storage/storage_array_2d.hpp>
#include <span>

namespace Fire {
    template <ConceptArithmetic T, size_t N, size_t M>
    struct Matrix : public StorageArray2D<T, N, M> {
        DEFINE_STORAGE_ARRAY_2D(Matrix, T, N, M)
    public:
        static std::enable_if_t<N == M, Matrix> GenerateIdentity(T value = 1) {
            Matrix result {};
            for (SizeT i = 0; i < N; i ++) {
                result.set(i, i, value);
            }
            return result;
        }

        static std::enable_if_t<N == M, Matrix> GenerateDiag(std::span<const T> values) {
            Matrix result {};
            for (SizeT i = 0; i < N; i ++) {
                result.set(i, i, values[i]);
            }
            return result;
        }
    };

    template <ConceptArithmetic T, size_t N, size_t M>
    IMPL_TRAIT(Matrix, Matrix<T, N, M>)

    template <ConceptArithmetic T, size_t N, size_t M>
    IMPL_TRAIT(Add, Matrix<T, N, M>)

    template <ConceptArithmetic T, size_t N, size_t M>
    IMPL_TRAIT(ScalarMul, Matrix<T, N, M>)

    template <ConceptArithmetic T, size_t N, size_t M>
    IMPL_TRAIT(Linear, Matrix<T, N, M>)

    template <ConceptArithmetic T, size_t N, size_t M>
    IMPL_TRAIT(MatrixMul, Matrix<T, N, M>)

    template <ConceptArithmetic T, size_t N, size_t M>
    IMPL_TRAIT(Ring, Matrix<T, N, M>)
}
