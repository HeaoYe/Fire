#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/macros.hpp>

namespace Fire {
    DEFINE_TRAIT(EuclideanV)

    TRAIT_API_WITH_CONDITIONS(EuclideanV, T::Dims == 3, T) Cross(const T &lhs, const T &rhs) {
        return INVOKE_TRAIT_IMPL(EuclideanV, Cross, lhs, rhs);
    }
}
