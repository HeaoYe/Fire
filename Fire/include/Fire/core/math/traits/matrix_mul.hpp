#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/macros.hpp>
#include <Fire/core/math/traits/matrix.hpp>

namespace Fire {
    DEFINE_TRAIT(MatrixMul, REQUIRE_TRAIT(Matrix))

    template <ConceptArithmetic T, SizeT N>
    class Vector;

    TRAIT_API_WITH_CONDITIONS(MatrixMul, T::Dims2 == Y::Dims1, (typename T::template ResizeToT<T::Dims1, Y::Dims2>), , ConceptMatrixMul Y) operator*(const T &lhs, const T &rhs) {
        return INVOKE_TRAIT_IMPL(MatrixMul, OpMul, lhs, rhs);
    }

    TRAIT_API_WITH_CONDITIONS(MatrixMul, T::Dims2 == Y::Dims1, (typename T::template ResizeToT<T::Dims1, Y::Dims2>), , ConceptMatrixMul Y) operator/(const T &lhs, const T &rhs) {
        return INVOKE_TRAIT_IMPL(MatrixMul, OpDiv, lhs, rhs);
    }

    TRAIT_API_WITH_CONDITIONS(MatrixMul, T::Dims1 == T::Dims2, T) Inverse(const T &rhs) {
        return INVOKE_TRAIT_IMPL(MatrixMul, Inverse, rhs);
    }

    TRAIT_API_WITH_CONDITIONS(MatrixMul, T::Dims1 == T::Dims2, void) InverseSelf(T &rhs) {
        INVOKE_TRAIT_IMPL(MatrixMul, InverseSelf, rhs);
    }

    TRAIT_API(MatrixMul) Vector<typename T::Scalar, T::Dims1> operator*(const T &lhs, const Vector<typename T::Scalar, T::Dims2> &rhs) {
        return INVOKE_TRAIT_IMPL(MatrixMul, OpMulVector, lhs, rhs);
    }
}
