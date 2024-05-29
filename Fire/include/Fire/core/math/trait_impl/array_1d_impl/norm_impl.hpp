#pragma once

#include <Fire/core/math/traits/norm.hpp>

namespace Fire {
    class Array1DNormTraitImpl {
    public:
        ENABLE_IF_IMPL_TRAIT(Norm, Real, static) OneNorm(const T &rhs) {
            Real result { 0 };
            for (std::remove_const_t<decltype(T::Dims)> i { 0 }; i < T::Dims; i ++) {
                result += rhs[i];
            }
            return result;
        }

        ENABLE_IF_IMPL_TRAIT(Norm, Real, static) TwoNorm(const T &rhs) {
            Real result { 0 };
            for (std::remove_const_t<decltype(T::Dims)> i { 0 }; i < T::Dims; i ++) {
                result += rhs[i] * rhs[i];
            }
            return Sqrt(result);
        }
    };
}
