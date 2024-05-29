#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/norm.hpp>

namespace Fire {
    DEFINE_TRAIT(InnerProduct, REQUIRE_TRAIT(Norm))

    ENABLE_IF_IMPL_TRAIT(InnerProduct, Real) Dot(const T &lhs, const T &rhs) {
        return INVOKE_TRAIT_IMPL(InnerProduct, Dot, lhs, rhs);
    }

    ENABLE_IF_IMPL_TRAIT(InnerProduct, Real) CosTheta(const T &lhs, const T &rhs) {
        Real l = Length(lhs) * Length(rhs);
        return Dot(lhs, rhs) / l;
    }

    ENABLE_IF_IMPL_TRAIT(InnerProduct, T) ProjectTo(const T &rhs, const T &normal) {
        auto normalized_normal = Normalize(normal);
        return Dot(rhs, normalized_normal) * normalized_normal;
    }

    ENABLE_IF_IMPL_TRAIT(InnerProduct, T) SafeProjectTo(const T &rhs, const T &normal) {
        auto normalized_normal = SafeNormalize(normal);
        return Dot(rhs, normalized_normal) * normalized_normal;
    }
}
