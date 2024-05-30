#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/linear.hpp>
#include <Fire/core/math/traits/metric.hpp>

namespace Fire {
    DEFINE_TRAIT(Norm, REQUIRE_TRAIT(Linear), REQUIRE_TRAIT(Metric))

    TRAIT_API(Norm) Real OneNorm(const T &rhs) {
        return INVOKE_TRAIT_IMPL(Norm, OneNorm, rhs);
    }

    TRAIT_API(Norm) Real TwoNorm(const T &rhs) {
        return INVOKE_TRAIT_IMPL(Norm, TwoNorm, rhs);
    }

    TRAIT_API(Norm) Real Length(const T &rhs) {
        return TwoNorm(rhs);
    }

    TRAIT_API(Norm) T Normalize(const T &rhs) {
        return rhs / TwoNorm(rhs);
    }

    TRAIT_API(Norm) T SafeNormalize(const T &rhs) {
        Real l = TwoNorm(rhs);
        if (l == Real { 0 }) {
            return {};
        }
        return rhs / l;
    }

    TRAIT_API(Norm) void NormalizeSelf(T &rhs) {
        rhs /= TwoNorm(rhs);
    }

    TRAIT_API(Norm) T SafeNormalizeSelf(T &rhs) {
        Real l = TwoNorm(rhs);
        if (l == Real { 0 }) {
            rhs = {};
        }
        return rhs /= l;
    }
}
