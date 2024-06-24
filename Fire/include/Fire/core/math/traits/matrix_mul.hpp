#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/macros.hpp>
#include <Fire/core/math/traits/matrix.hpp>
#include <Fire/core/math/traits/matrix_multiplicable.hpp>

namespace Fire {
    DEFINE_TRAIT(MatrixMul, REQUIRE_TRAIT(Matrix))

    TRAIT_API_WITH_CONDITIONS(MatrixMul, T::NColumn == Y::NRow, (typename T::template ResizeToT<T::NRow, Y::NColumn>), , ConceptMatrixMul Y) operator*(const T &lhs, const Y &rhs) {
        return INVOKE_TRAIT_IMPL(MatrixMul, OpMul, lhs, rhs);
    }

    TRAIT_API_WITH_CONDITIONS(MatrixMul, T::NColumn == Y::NRow, (typename T::template ResizeToT<T::NRow, Y::NColumn>), , ConceptMatrixMul Y) operator/(const T &lhs, const Y &rhs) {
        return INVOKE_TRAIT_IMPL(MatrixMul, OpDiv, lhs, rhs);
    }

    TRAIT_API_WITH_CONDITIONS(MatrixMul, T::NColumn == Y::NRow, (typename T::template ResizeToT<T::NRow, Y::NColumn>), , ConceptMatrixMul Y) SafeDiv(const T &lhs, const Y &rhs) {
        static_assert(false, "矩阵不支持SafeDiv");
    }

    TRAIT_API_WITH_CONDITIONS(MatrixMul, T::NRow == T::NColumn, T) Inverse(const T &rhs) {
        return INVOKE_TRAIT_IMPL(MatrixMul, Inverse, rhs);
    }

    TRAIT_API_WITH_CONDITIONS(MatrixMul, T::NRow == T::NColumn, void) InverseSelf(T &rhs) {
        INVOKE_TRAIT_IMPL(MatrixMul, InverseSelf, rhs);
    }

    TRAIT_API_WITH_CONDITIONS(MatrixMul, T::NColumn == Y::Dims, typename Y::template ResizeToT<T::NRow>, , ConceptMatrixMultiplicable Y) operator*(const T &lhs, const Y &rhs) {
        return INVOKE_TRAIT_IMPL(MatrixMul, OpMulMultiplicable, lhs, rhs);
    }
}
