#pragma once

#include <Fire/core/math/types.hpp>
#include <Fire/core/math/traits/macros.hpp>

namespace Fire {
    DEFINE_TRAIT(EuclideanV)

    ENABLE_IF_IMPL_TRAIT_WITH_CONDITIONS(EuclideanV, T, (EQUAL<SizeT, T::Dims, 3>)) Cross(const T &lhs, const T &rhs) {
        return INVOKE_TRAIT_IMPL(EuclideanV, Cross, lhs, rhs);
    }
}
