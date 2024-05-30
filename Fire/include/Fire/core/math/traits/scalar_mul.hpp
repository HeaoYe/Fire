#pragma once

#include <Fire/core/math/traits/macros.hpp>

namespace Fire {
    DEFINE_TRAIT(ScalarMul)

    TRAIT_API(ScalarMul) T operator*(const T &lhs, typename T::Scalar rhs) {
        return INVOKE_TRAIT_IMPL(ScalarMul, OpScalarMul, lhs, rhs);
    }

    TRAIT_API(ScalarMul) T operator*(typename T::Scalar lhs, const T &rhs) {
        return INVOKE_TRAIT_IMPL(ScalarMul, OpScalarMul, rhs, lhs);
    }

    TRAIT_API(ScalarMul) void operator*=(T &lhs, typename T::Scalar rhs) {
        lhs = lhs * rhs;
    }

    TRAIT_API(ScalarMul) T operator/(const T &lhs, typename T::Scalar rhs) {
        return INVOKE_TRAIT_IMPL(ScalarMul, OpScalarDiv, lhs, rhs);
    }

    TRAIT_API(ScalarMul) void operator/=(T &lhs, typename T::Scalar rhs) {
        lhs = lhs / rhs;
    }
}
