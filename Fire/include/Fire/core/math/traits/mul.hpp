#pragma once

#include <Fire/core/math/traits/macros.hpp>

namespace Fire {
    DEFINE_TRAIT(Mul)

    TRAIT_API(Mul) T operator*(const T &lhs, const T &rhs) {
        return INVOKE_TRAIT_IMPL(Mul, OpMul, lhs, rhs);
    }

    TRAIT_API(Mul) void operator*=(T &lhs, const T &rhs) {
        lhs = lhs * rhs;
    }


    TRAIT_API(Mul) T operator/(const T &lhs, const T &rhs) {
        return INVOKE_TRAIT_IMPL(Mul, OpDiv, lhs, rhs);
    }

    TRAIT_API(Mul) void operator/=(T &lhs, const T &rhs) {
        lhs = lhs / rhs;
    }

    TRAIT_API(Mul) T Inverse(const T &rhs) {
        return INVOKE_TRAIT_IMPL(Mul, Inverse, rhs);
    }

    TRAIT_API(Mul) void InverseSelf(T &rhs) {
        INVOKE_TRAIT_IMPL(Mul, InverseSelf, rhs);
    }
}
