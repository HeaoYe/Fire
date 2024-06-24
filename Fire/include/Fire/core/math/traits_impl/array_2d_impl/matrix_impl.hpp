#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/matrix.hpp>
#include <Fire/core/math/rounds/compensated_float.hpp>

namespace Fire {
    class Array2DMatrixTraitImpl {
    public:
        TRAIT_API(Matrix) static typename T::template ResizeToT<T::NColumn, T::NRow> Transpose(const T &rhs) {
            using ResultT = typename T::template ResizeToT<T::NColumn, T::NRow>;
            ResultT result {};
            for (SizeT i = 0; i < T::NRow; i ++) {
                for (SizeT j = 0; j < T::NColumn; j ++) {
                    result.set(j, i, rhs.get(i, j));
                }
            }
            return result;
        }

        TRAIT_API_WITH_CONDITIONS(Matrix, T::NRow == T::NColumn, typename T::Scalar) static Det(const T &rhs) {
            if constexpr (T::NRow == 2) {
                return InternalDet2(rhs);
            } else if constexpr (T::NRow == 3) {
                return InternalDet3(rhs);
            } else if constexpr (T::NRow == 4) {
                return internalDet4(rhs);
            }
            return {};
        }
    private:
        template <ConceptMatrix T>
        static typename T::Scalar InternalDet2(const T &rhs) {
            return DifferenceOfProducts(rhs.m00, rhs.m11, rhs.m01, rhs.m10);
        }

        template <ConceptMatrix T>
        static typename T::Scalar InternalDet3(const T &rhs) {
            Real minor12 = DifferenceOfProducts(rhs.m11, rhs.m22, rhs.m12, rhs.m21);
            Real minor02 = DifferenceOfProducts(rhs.m10, rhs.m22, rhs.m12, rhs.m20);
            Real minor01 = DifferenceOfProducts(rhs.m10, rhs.m21, rhs.m11, rhs.m20);
            return FMA<Real>(rhs.m02, minor01, DifferenceOfProducts(rhs.m00, minor12, rhs.m01, minor02));
        }

        template <ConceptMatrix T>
        static typename T::Scalar internalDet4(const T &rhs) {
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
        }
    };
}
