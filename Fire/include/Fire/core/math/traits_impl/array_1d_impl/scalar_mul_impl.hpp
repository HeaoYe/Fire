#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/scalar_mul.hpp>

namespace Fire {
    class Array1DScalarMulTraitImpl {
    public:
        TRAIT_API(ScalarMul) static T OpScalarMul(const T &lhs, typename T::Scalar rhs) {
            return InternalOpScalarMul(lhs, rhs, T::IndexSequence);
        }

        TRAIT_API(ScalarMul) static T OpScalarDiv(const T &lhs, typename T::Scalar rhs) {
            return InternalOpScalarMul(lhs, (typename T::Scalar { 1 }) / rhs, T::IndexSequence);
        }
    private:
        template <class T, SizeT ...Indices>
        static T InternalOpScalarMul(const T &lhs, typename T::Scalar rhs, std::index_sequence<Indices...>) {
            return T { (lhs.template get<Indices>() * rhs)... };
        }
    };
}
