#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/matrix_mul.hpp>

namespace Fire {
    class Array2DMatrixMulTraitImpl {
    public:
        TRAIT_API_WITH_CONDITIONS(MatrixMul, (T::NColumn == Y::NRow), (typename T::template ResizeToT<T::NRow, Y::NColumn>), , ConceptMatrixMul Y) static OpMul(const T &lhs, const Y &rhs) {
            using ResultT = typename T::template ResizeToT<T::NRow, Y::NColumn>;
            ResultT result {};
            for (SizeT i = 0; i < ResultT::NRow; i ++) {
                for (SizeT j = 0; j < ResultT::NColumn; j ++) {
                    Real n {};
                    for (SizeT k = 0; k < T::NRow; k ++) {
                        n += lhs.get(i, k) * rhs.get(k, j);
                    }
                    result.set(i, j, n);
                }
            }
            return result;
        }

        TRAIT_API_WITH_CONDITIONS(MatrixMul, (T::NColumn == Y::NRow), (typename T::template ResizeToT<T::NRow, Y::NColumn>), , ConceptMatrixMul Y) static OpDiv(const T &lhs, const Y &rhs) {
            return OpMul(Inverse(rhs));
        }

        TRAIT_API_WITH_CONDITIONS(MatrixMul, T::NRow == T::NColumn, T) static Inverse(const T &rhs) {
            if constexpr (T::NRow == 2) {
                return InternalInverse2(rhs);
            } else if constexpr (T::NRow == 3) {
                return InternalInverse3(rhs);
            }
            return {};
        }

        TRAIT_API_WITH_CONDITIONS(MatrixMul, T::NRow == T::NColumn, void) static InverseSelf(T &rhs) {
            rhs = Inverse(rhs);
        }

        TRAIT_API_WITH_CONDITIONS(MatrixMul, T::NColumn == Y::Dims, typename Y::template ResizeToT<T::NRow>, , ConceptMatrixMultiplicable Y) static OpMulMultiplicable(const T &lhs, const Y &rhs) {
            typename Y::template ResizeToT<T::NRow> result {};
            for (SizeT i = 0; i < T::NRow; i++) {
                Real n {};
                for (SizeT j = 0; j < T::NColumn; j ++) {
                    n += lhs.get(i, j) * rhs.get(j);
                }
                result.set(i, n);
            }
            return result;
        }
    private:
        template <ConceptMatrixMul T>
        static T InternalInverse2(const T &rhs) {
            T result {};
            auto determinant = Det(rhs);
			Real inv = Real(1) / determinant;
            return {
                rhs.m11 * inv, -rhs.m10 * inv,
                -rhs.m01 * inv, rhs.m00 * inv
            };
        }

        template <ConceptMatrixMul T>
        static T InternalInverse3(const T &rhs) {
            T result {};
            auto determinant = Det(rhs);
			Real inv = Real(1) / determinant;

            result.m00 = DifferenceOfProducts(rhs.m11, rhs.m22, rhs.m21, rhs.m12) * inv;
            result.m10 = DifferenceOfProducts(rhs.m20, rhs.m12, rhs.m10, rhs.m22) * inv;
            result.m20 = DifferenceOfProducts(rhs.m10, rhs.m21, rhs.m20, rhs.m11) * inv;
            result.m01 = DifferenceOfProducts(rhs.m21, rhs.m02, rhs.m01, rhs.m22) * inv;
            result.m11 = DifferenceOfProducts(rhs.m00, rhs.m22, rhs.m20, rhs.m02) * inv;
            result.m21 = DifferenceOfProducts(rhs.m20, rhs.m01, rhs.m00, rhs.m21) * inv;
            result.m02 = DifferenceOfProducts(rhs.m01, rhs.m12, rhs.m11, rhs.m02) * inv;
            result.m12 = DifferenceOfProducts(rhs.m10, rhs.m02, rhs.m00, rhs.m12) * inv;
            result.m22 = DifferenceOfProducts(rhs.m00, rhs.m11, rhs.m10, rhs.m01) * inv;

            return result;
        }
    };
}
