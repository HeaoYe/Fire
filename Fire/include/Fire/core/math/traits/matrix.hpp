#pragma once

#include <Fire/core/math/traits/macros.hpp>

namespace Fire {
    DEFINE_TRAIT(Matrix)

    TRAIT_API(Matrix) typename T::template ResizeToT<T::Dims2, T::Dims1> Transpose(const T &rhs) {
        return INVOKE_TRAIT_IMPL(Matrix, Transpose, rhs);
    }

    TRAIT_API_WITH_CONDITIONS(Matrix, T::Dims1 == T::Dims2, typename T::Scalar) Det(const T &rhs) {
        return INVOKE_TRAIT_IMPL(Matrix, Det, rhs);
    }
}
