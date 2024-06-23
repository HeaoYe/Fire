#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/rounds/compensated_float.hpp>
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
            } else if constexpr (T::NRow == 4) {
                return InternalInverse4(rhs);
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

        template <ConceptMatrixMul T>
        static T InternalInverse4(const T &rhs) {
            // Via: https://github.com/google/ion/blob/master/ion/math/matrixutils.cc,
            // (c) Google, Apache license.

            // For 4x4 do not compute the adjugate as the transpose of the cofactor
            // matrix, because this results in extra work. Several calculations can be
            // shared across the sub-determinants.
            //
            // This approach is explained in David Eberly's Geometric Tools book,
            // excerpted here:
            //   http://www.geometrictools.com/Documentation/LaplaceExpansionTheorem.pdf
            Real s0 = DifferenceOfProducts(rhs.m00, rhs.m11, rhs.m10, rhs.m01);
            Real s1 = DifferenceOfProducts(rhs.m00, rhs.m12, rhs.m10, rhs.m02);
            Real s2 = DifferenceOfProducts(rhs.m00, rhs.m13, rhs.m10, rhs.m03);

            Real s3 = DifferenceOfProducts(rhs.m01, rhs.m12, rhs.m11, rhs.m02);
            Real s4 = DifferenceOfProducts(rhs.m01, rhs.m13, rhs.m11, rhs.m03);
            Real s5 = DifferenceOfProducts(rhs.m02, rhs.m13, rhs.m12, rhs.m03);

            Real c0 = DifferenceOfProducts(rhs.m20, rhs.m31, rhs.m30, rhs.m21);
            Real c1 = DifferenceOfProducts(rhs.m20, rhs.m32, rhs.m30, rhs.m22);
            Real c2 = DifferenceOfProducts(rhs.m20, rhs.m33, rhs.m30, rhs.m23);

            Real c3 = DifferenceOfProducts(rhs.m21, rhs.m32, rhs.m31, rhs.m22);
            Real c4 = DifferenceOfProducts(rhs.m21, rhs.m33, rhs.m31, rhs.m23);
            Real c5 = DifferenceOfProducts(rhs.m22, rhs.m33, rhs.m32, rhs.m23);

            Real determinant = static_cast<Real>(CompensatedFloat::InnerProduct(s0, c5, -s1, c4, s2, c3, s3, c2, s5, c0, -s4, c1));
            if (determinant == 0)
                return {};
            Real s = 1 / determinant;

            return T {
                s * static_cast<Real>(CompensatedFloat::InnerProduct(rhs.m11, c5, rhs.m13, c3, -rhs.m12, c4)),
                s * static_cast<Real>(CompensatedFloat::InnerProduct(-rhs.m01, c5, rhs.m02, c4, -rhs.m03, c3)),
                s * static_cast<Real>(CompensatedFloat::InnerProduct(rhs.m31, s5, rhs.m33, s3, -rhs.m32, s4)),
                s * static_cast<Real>(CompensatedFloat::InnerProduct(-rhs.m21, s5, rhs.m22, s4, -rhs.m23, s3)),

                s * static_cast<Real>(CompensatedFloat::InnerProduct(-rhs.m10, c5, rhs.m12, c2, -rhs.m13, c1)),
                s * static_cast<Real>(CompensatedFloat::InnerProduct(rhs.m00, c5, rhs.m03, c1, -rhs.m02, c2)),
                s * static_cast<Real>(CompensatedFloat::InnerProduct(-rhs.m30, s5, rhs.m32, s2, -rhs.m33, s1)),
                s * static_cast<Real>(CompensatedFloat::InnerProduct(rhs.m20, s5, rhs.m23, s1, -rhs.m22, s2)),

                s * static_cast<Real>(CompensatedFloat::InnerProduct(rhs.m10, c4, rhs.m13, c0, -rhs.m11, c2)),
                s * static_cast<Real>(CompensatedFloat::InnerProduct(-rhs.m00, c4, rhs.m01, c2, -rhs.m03, c0)),
                s * static_cast<Real>(CompensatedFloat::InnerProduct(rhs.m30, s4, rhs.m33, s0, -rhs.m31, s2)),
                s * static_cast<Real>(CompensatedFloat::InnerProduct(-rhs.m20, s4, rhs.m21, s2, -rhs.m23, s0)),

                s * static_cast<Real>(CompensatedFloat::InnerProduct(-rhs.m10, c3, rhs.m11, c1, -rhs.m12, c0)),
                s * static_cast<Real>(CompensatedFloat::InnerProduct(rhs.m00, c3, rhs.m02, c0, -rhs.m01, c1)),
                s * static_cast<Real>(CompensatedFloat::InnerProduct(-rhs.m30, s3, rhs.m31, s1, -rhs.m32, s0)),
                s * static_cast<Real>(CompensatedFloat::InnerProduct(rhs.m20, s3, rhs.m22, s0, -rhs.m21, s1))
            };
        }
    };
}
