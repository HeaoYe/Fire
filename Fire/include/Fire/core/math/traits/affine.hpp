#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/macros.hpp>
#include <Fire/core/math/traits/euclidean_v.hpp>

namespace Fire {
    DEFINE_TRAIT(Affine)

    template <ConceptArithmetic T, SizeT N>
    class Vector;

    TRAIT_API_WITH_CONDITIONS(Affine, Y::Dims == T::Dims, Y, , ConceptEuclideanV Y = Vector<typename T::Scalar, T::Dims>) operator-(const T &lhs, const T &rhs) {
        return INVOKE_TRAIT_IMPL(Affine, (template OpSubSame<T, Y>), lhs, rhs);
    }

    TRAIT_API_WITH_CONDITIONS(Affine, Y::Dims == T::Dims, T, , ConceptEuclideanV Y) operator+(const T &lhs, const Y &rhs) {
        return INVOKE_TRAIT_IMPL(Affine, OpAdd, lhs, rhs);
    }

    TRAIT_API_WITH_CONDITIONS(Affine, Y::Dims == T::Dims, void, , ConceptEuclideanV Y) operator+=(T &lhs, const T &rhs) {
        lhs = lhs + rhs;
    }

    TRAIT_API_WITH_CONDITIONS(Affine, Y::Dims == T::Dims, T, , ConceptEuclideanV Y) operator-(const T &lhs, const Y &rhs) {
        return INVOKE_TRAIT_IMPL(Affine, OpSub, lhs, rhs);
    }

    TRAIT_API_WITH_CONDITIONS(Affine, Y::Dims == T::Dims, void, , ConceptEuclideanV Y) operator-=(T &lhs, const Y &rhs) {
        lhs = lhs - rhs;
    }
}
