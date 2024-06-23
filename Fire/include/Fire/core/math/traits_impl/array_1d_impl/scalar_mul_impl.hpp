#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/scalar_mul.hpp>

namespace Fire {
    class Array1DScalarMulTraitImpl {
    public:
        TRAIT_API(ScalarMul, , ConceptArithmetic Y) static T OpScalarMul(const T &lhs, Y rhs) {
            return InternalOpScalarMul(lhs, rhs, T::IndexSequence);
        }

        TRAIT_API(ScalarMul, , ConceptArithmetic Y) static T OpScalarDiv(const T &lhs, Y rhs) {
            return InternalOpScalarMul(lhs, Real(1) / Real(rhs), T::IndexSequence);
        }

        TRAIT_API(ScalarMul, , ConceptArithmetic Y) static T SafeDiv(const T &lhs, Y rhs) {
            return InternalSafeDiv(lhs, rhs, T::IndexSequence);
        }
    private:
        template <ConceptScalarMul T, ConceptArithmetic Y, SizeT ...Indices>
        static T InternalOpScalarMul(const T &lhs, Y rhs, std::index_sequence<Indices...>) {
            return T { static_cast<typename T::Scalar>(lhs.template get<Indices>() * rhs)... };
        }

        template <ConceptScalarMul T, ConceptArithmetic Y, SizeT ...Indices>
        static T InternalSafeDiv(const T &lhs, Y rhs, std::index_sequence<Indices...>) {
            return T { static_cast<typename T::Scalar>(SafeDiv<Real>(lhs.template get<Indices>(), rhs))... };
        }
    };
}
