#pragma once

#include <Fire/core/math/traits/macros.hpp>

namespace Fire {
    DEFINE_TRAIT(Mul)

    ENABLE_IF_IMPL_TRAIT(Mul, T) operator*(const T &lhs, const T &rhs) {
        return INVOKE_TRAIT_IMPL(Mul, OpMul, lhs, rhs);
    }

    ENABLE_IF_IMPL_TRAIT(Mul, void) operator*=(T &lhs, const T &rhs) {
        lhs = lhs * rhs;
    }


    ENABLE_IF_IMPL_TRAIT(Mul, T) operator/(const T &lhs, const T &rhs) {
        return INVOKE_TRAIT_IMPL(Mul, OpDiv, lhs, rhs);
    }

    ENABLE_IF_IMPL_TRAIT(Mul, void) operator/=(T &lhs, const T &rhs) {
        lhs = lhs / rhs;
    }

    ENABLE_IF_IMPL_TRAIT(Mul, T) Inverse(const T &rhs) {
        return INVOKE_TRAIT_IMPL(Mul, Inverse, rhs);
    }

    ENABLE_IF_IMPL_TRAIT(Mul, void) InverseSelf(T &rhs) {
        INVOKE_TRAIT_IMPL(Mul, InverseSelf, rhs);
    }
}
