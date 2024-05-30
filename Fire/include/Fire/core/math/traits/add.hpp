#pragma once

#include <Fire/core/math/traits/macros.hpp>

namespace Fire {
    DEFINE_TRAIT(Add)

    TRAIT_API(Add) T operator+(const T &lhs, const T &rhs) {
        return INVOKE_TRAIT_IMPL(Add, OpAdd, lhs, rhs);
    }

    TRAIT_API(Add) void operator+=(T &lhs, const T &rhs) {
        lhs = lhs + rhs;
    }

    TRAIT_API(Add) T operator-(const T &lhs, const T &rhs) {
        return INVOKE_TRAIT_IMPL(Add, OpSub, lhs, rhs);
    }

    TRAIT_API(Add) void operator-=(T &lhs, const T &rhs) {
        lhs = lhs - rhs;
    }

    TRAIT_API(Add) T operator-(const T &rhs) {
        return INVOKE_TRAIT_IMPL(Add, OpOpposite, rhs);
    }
}
