#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/linear.hpp>
#include <Fire/core/math/traits/metric.hpp>

namespace Fire {
    DEFINE_TRAIT(Norm, REQUIRE_TRAIT(Linear), REQUIRE_TRAIT(Metric))

    ENABLE_IF_IMPL_TRAIT(Norm, Real) OneNorm(const T &rhs) {
        return INVOKE_TRAIT_IMPL(Norm, OneNorm, rhs);
    }

    ENABLE_IF_IMPL_TRAIT(Norm, Real) TwoNorm(const T &rhs) {
        return INVOKE_TRAIT_IMPL(Norm, TwoNorm, rhs);
    }

    ENABLE_IF_IMPL_TRAIT(Norm, Real) Length(const T &rhs) {
        return TwoNorm(rhs);
    }

    ENABLE_IF_IMPL_TRAIT(Norm, T) Normalize(const T &rhs) {
        return rhs / TwoNorm(rhs);
    }

    ENABLE_IF_IMPL_TRAIT(Norm, T) SafeNormalize(const T &rhs) {
        Real l = TwoNorm(rhs);
        if (l == Real { 0 }) {
            return {};
        }
        return rhs / l;
    }

    ENABLE_IF_IMPL_TRAIT(Norm, void) NormalizeSelf(T &rhs) {
        rhs /= TwoNorm(rhs);
    }

    ENABLE_IF_IMPL_TRAIT(Norm, T) SafeNormalizeSelf(T &rhs) {
        Real l = TwoNorm(rhs);
        if (l == Real { 0 }) {
            rhs = {};
        }
        return rhs /= l;
    }
}
