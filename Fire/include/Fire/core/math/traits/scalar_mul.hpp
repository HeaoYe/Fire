#pragma once

#include <Fire/core/math/traits/macros.hpp>
#include <Fire/core/concepts.hpp>

namespace Fire {
    DEFINE_TRAIT(ScalarMul)

    TRAIT_API(ScalarMul, , ConceptArithmetic Y) T operator*(const T &lhs, Y rhs) {
        return INVOKE_TRAIT_IMPL(ScalarMul, OpScalarMul, lhs, rhs);
    }

    TRAIT_API(ScalarMul, , ConceptArithmetic Y) T operator*(Y lhs, const T &rhs) {
        return INVOKE_TRAIT_IMPL(ScalarMul, OpScalarMul, rhs, lhs);
    }

    TRAIT_API(ScalarMul, , ConceptArithmetic Y) void operator*=(T &lhs, Y rhs) {
        lhs = lhs * rhs;
    }

    TRAIT_API(ScalarMul, , ConceptArithmetic Y) T operator/(const T &lhs, Y rhs) {
        return INVOKE_TRAIT_IMPL(ScalarMul, OpScalarDiv, lhs, rhs);
    }

    TRAIT_API(ScalarMul, , ConceptArithmetic Y) void operator/=(T &lhs, Y rhs) {
        lhs = lhs / rhs;
    }

    TRAIT_API(ScalarMul, , ConceptArithmetic Y) T SafeDiv(const T &lhs, Y rhs) {
        return INVOKE_TRAIT_IMPL(ScalarMul, SafeDiv, lhs, rhs);
    }
}
