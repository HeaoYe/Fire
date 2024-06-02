#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/scalar_mul.hpp>

namespace Fire {
    class Array2DScalarMulTraitImpl {
    public:
        TRAIT_API(ScalarMul) static T OpScalarMul(const T &lhs, typename T::Scalar rhs) {
            T result {};
            for (SizeT i = 0; i < T::Dims1; i ++) {
                for (SizeT j = 0; j < T::Dims2; j ++) {
                    result.set(i, j, lhs.get(i, j) * rhs);
                }
            }
            return result;
        }

        TRAIT_API(ScalarMul) static T OpScalarDiv(const T &lhs, typename T::Scalar rhs) {
            return OpScalarMul(lhs, typename T::Scalar { 1 } / rhs);
        }

        TRAIT_API(ScalarMul) static T SafeDiv(const T &lhs, typename T::Scalar rhs) {
            T result {};
            for (SizeT i = 0; i < T::Dims1; i ++) {
                for (SizeT j = 0; j < T::Dims2; j ++) {
                    result.set(i, j, SafeDiv(lhs.get(i, j), rhs));
                }
            }
            return result;
        }
    };
}
