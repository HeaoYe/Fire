#pragma once

#include <Fire/core/math/types.hpp>
#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/macros.hpp>

namespace Fire {
    DEFINE_TRAIT(Metric)

    ENABLE_IF_IMPL_TRAIT(Metric, Real) DistanceSqua(const T &lhs, const T &rhs) {
        INVOKE_TRAIT_IMPL(Metric, DistanceSqua, lhs, rhs);
    }

    ENABLE_IF_IMPL_TRAIT(Metric, Real) Distance(const T &lhs, const T &rhs) {
        return Sqrt(DistanceSqua(lhs, rhs));
    }
}
