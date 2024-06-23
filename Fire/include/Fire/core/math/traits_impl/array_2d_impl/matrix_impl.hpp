#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/matrix.hpp>

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
    };
}
