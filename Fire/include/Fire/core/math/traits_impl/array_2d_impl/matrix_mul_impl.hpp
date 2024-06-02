#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/matrix_mul.hpp>

namespace Fire {
    class Array2DMatrixMulTraitImpl {
    public:
        TRAIT_API_WITH_CONDITIONS(MatrixMul, (T::Dims2 == Y::Dims1), (typename T::template ResizeToT<T::Dims1, Y::Dims2>), , ConceptMatrixMul Y) static OpMul(const T &lhs, const Y &rhs) {
            using ResultT = typename T::template ResizeToT<T::Dims1, Y::Dims2>;
            ResultT result {};
            for (SizeT i = 0; i < ResultT::Dims1; i ++) {
                for (SizeT j = 0; j < ResultT::Dims2; j ++) {
                    Real n {};
                    for (SizeT k = 0; k < T::Dims2; k ++) {
                        n += lhs.get(i, k) * rhs.get(k, j);
                    }
                    result.set(i, j, n);
                }
            }
            return result;
        }

        TRAIT_API_WITH_CONDITIONS(MatrixMul, (T::Dims2 == Y::Dims1), (typename T::template ResizeToT<T::Dims1, Y::Dims2>), , ConceptMatrixMul Y) static OpDiv(const T &lhs, const Y &rhs) {
            return OpMul(Inverse(rhs));
        }

        TRAIT_API_WITH_CONDITIONS(MatrixMul, T::Dims1 == T::Dims2, T) static Inverse(const T &rhs) {
            if constexpr (T::Dims1 == 2) {
                return InternalInverse2(rhs);
            } else if constexpr (T::Dims1 == 3) {
                return InternalInverse3(rhs);
            }
            return {};
        }

        TRAIT_API_WITH_CONDITIONS(MatrixMul, T::Dims1 == T::Dims2, void) static InverseSelf(T &rhs) {
            rhs = Inverse(rhs);
        }

        TRAIT_API_WITH_CONDITIONS(MatrixMul, T::Dims2 == Y::Dims, typename Y::template ResizeToT<T::Dims1>, , ConceptMatrixMultiplicable Y) static OpMulMultiplicable(const T &lhs, const Y &rhs) {
            typename Y::template ResizeToT<T::Dims1> result {};
            for (SizeT i = 0; i < T::Dims1; i++) {
                Real n {};
                for (SizeT j = 0; j < T::Dims2; j ++) {
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
                rhs.get(1, 1) * inv, -rhs.get(1, 0) * inv,
                -rhs.get(0, 1) * inv, rhs.get(0, 0) * inv
            };
        }

        template <ConceptMatrixMul T>
        static T InternalInverse3(const T &rhs) {
            T result {};
            auto determinant = Det(rhs);
			Real inv = Real(1) / determinant;

            result.set(0, 0, DifferenceOfProducts(rhs.get(1, 1), rhs.get(2, 2), rhs.get(2, 1), rhs.get(1, 2)) * inv);
            result.set(1, 0, DifferenceOfProducts(rhs.get(2, 0), rhs.get(1, 2), rhs.get(1, 0), rhs.get(2, 2)) * inv);
            result.set(2, 0, DifferenceOfProducts(rhs.get(1, 0), rhs.get(2, 1), rhs.get(2, 0), rhs.get(1, 1)) * inv);
            result.set(0, 1, DifferenceOfProducts(rhs.get(2, 1), rhs.get(0, 2), rhs.get(0, 1), rhs.get(2, 2)) * inv);
            result.set(1, 1, DifferenceOfProducts(rhs.get(0, 0), rhs.get(2, 2), rhs.get(2, 0), rhs.get(0, 2)) * inv);
            result.set(2, 1, DifferenceOfProducts(rhs.get(2, 0), rhs.get(0, 1), rhs.get(0, 0), rhs.get(2, 1)) * inv);
            result.set(0, 2, DifferenceOfProducts(rhs.get(0, 1), rhs.get(1, 2), rhs.get(1, 1), rhs.get(0, 2)) * inv);
            result.set(1, 2, DifferenceOfProducts(rhs.get(1, 0), rhs.get(0, 2), rhs.get(0, 0), rhs.get(1, 2)) * inv);
            result.set(2, 2, DifferenceOfProducts(rhs.get(0, 0), rhs.get(1, 1), rhs.get(1, 0), rhs.get(0, 1)) * inv);

            return result;
        }
    };
}
