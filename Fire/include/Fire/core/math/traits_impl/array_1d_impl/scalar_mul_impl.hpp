#pragma once

#include <Fire/core/math/traits/scalar_mul.hpp>

namespace Fire {
    class Array1DScalarMulTraitImpl {
    public:
        ENABLE_IF_IMPL_TRAIT(ScalarMul, T, static) OpScalarMul(const T &lhs, typename T::Scalar rhs) {
            return InternalOpScalarMul(lhs, rhs, T::IndexSequence);
        }

        ENABLE_IF_IMPL_TRAIT(ScalarMul, T, static) OpScalarDiv(const T &lhs, typename T::Scalar rhs) {
            return InternalOpScalarMul(lhs, (typename T::Scalar { 1 }) / rhs, T::IndexSequence);
        }
    private:
        template <class T, size_t ...Indices>
        static T InternalOpScalarMul(const T &lhs, typename T::Scalar rhs, std::index_sequence<Indices...>) {
            return T { (lhs.template get<Indices>() * rhs)... };
        }
    };
}
