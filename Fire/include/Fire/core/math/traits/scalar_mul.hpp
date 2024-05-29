#pragma once

#include <Fire/core/math/traits/macros.hpp>

namespace Fire {
    DEFINE_TRAIT(ScalarMul)

    ENABLE_IF_IMPL_TRAIT(ScalarMul, T) operator*(const T &lhs, typename T::Scalar rhs) {
        return INVOKE_TRAIT_IMPL(ScalarMul, OpScalarMul, lhs, rhs);
    }

    ENABLE_IF_IMPL_TRAIT(ScalarMul, T) operator*(typename T::Scalar lhs, const T &rhs) {
        return INVOKE_TRAIT_IMPL(ScalarMul, OpScalarMul, rhs, lhs);
    }

    ENABLE_IF_IMPL_TRAIT(ScalarMul, void) operator*=(T &lhs, typename T::Scalar rhs) {
        lhs = lhs * rhs;
    }

    ENABLE_IF_IMPL_TRAIT(ScalarMul, T) operator/(const T &lhs, typename T::Scalar rhs) {
        return INVOKE_TRAIT_IMPL(ScalarMul, OpScalarDiv, lhs, rhs);
    }

    ENABLE_IF_IMPL_TRAIT(ScalarMul, void) operator/=(T &lhs, typename T::Scalar rhs) {
        lhs = lhs / rhs;
    }
}
