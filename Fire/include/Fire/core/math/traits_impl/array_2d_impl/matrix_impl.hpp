#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/matrix.hpp>

namespace Fire {
    class Array2DMatrixTraitImpl {
    public:
        TRAIT_API(Matrix) static typename T::template ResizeToT<T::Dims2, T::Dims1> Transpose(const T &rhs) {
            using ResultT = typename T::template ResizeToT<T::Dims2, T::Dims1>;
            ResultT result {};
            for (SizeT i = 0; i < T::Dims1; i ++) {
                for (SizeT j = 0; j < T::Dims2; j ++) {
                    result.set(j, i, rhs.get(i, j));
                }
            }
            return result;
        }

        TRAIT_API_WITH_CONDITIONS(Matrix, T::Dims1 == T::Dims2, typename T::Scalar) static Det(const T &rhs) {
            if constexpr (T::Dims1 == 2) {
                return InternalDet2(rhs);
            } else if constexpr (T::Dims1 == 3) {
                return InternalDet3(rhs);
            }
            return {};
        }
    private:
        template <ConceptMatrix T>
        static typename T::Scalar InternalDet2(const T &rhs) {
            return DifferenceOfProducts(rhs.get(0, 0), rhs.get(1, 1), rhs.get(0, 1), rhs.get(1, 0));
        }

        template <ConceptMatrix T>
        static typename T::Scalar InternalDet3(const T &rhs) {
			return rhs.get(0, 0) * DifferenceOfProducts(rhs.get(1, 1), rhs.get(2, 2), rhs.get(2, 1), rhs.get(1, 2)) +
                rhs.get(1, 0) * DifferenceOfProducts(rhs.get(2, 1), rhs.get(0, 2), rhs.get(0, 1), rhs.get(2, 2)) +
                rhs.get(2, 0) * DifferenceOfProducts(rhs.get(0, 1), rhs.get(1, 2), rhs.get(1, 1), rhs.get(0, 2));
        }
    };
}
