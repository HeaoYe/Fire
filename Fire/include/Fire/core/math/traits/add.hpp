#pragma once

#include <Fire/core/math/traits/macros.hpp>

namespace Fire {
    DEFINE_TRAIT(Add)

    ENABLE_IF_IMPL_TRAIT(Add, T) operator+(const T &lhs, const T &rhs) {
        return INVOKE_TRAIT_IMPL(Add, OpAdd, lhs, rhs);
    }

    ENABLE_IF_IMPL_TRAIT(Add, void) operator+=(T &lhs, const T &rhs) {
        lhs = lhs + rhs;
    }

    ENABLE_IF_IMPL_TRAIT(Add, T) operator-(const T &lhs, const T &rhs) {
        return INVOKE_TRAIT_IMPL(Add, OpSub, lhs, rhs);
    }

    ENABLE_IF_IMPL_TRAIT(Add, void) operator-=(T &lhs, const T &rhs) {
        lhs = lhs - rhs;
    }

    ENABLE_IF_IMPL_TRAIT(Add, T) operator-(const T &rhs) {
        return INVOKE_TRAIT_IMPL(Add, OpOpposite, rhs);
    }
}
