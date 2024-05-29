#pragma once

#include <Fire/core/math/traits/inner_product.hpp>

namespace Fire {
    class Array1DInnerProductTraitImpl {
    public:
        ENABLE_IF_IMPL_TRAIT(InnerProduct, Real, static) Dot(const T &lhs, const T &rhs) {
            Real result { 0 };
            for (std::remove_const_t<decltype(T::Dims)> i { 0 }; i < T::Dims; i ++) {
                result += lhs[i] * rhs[i];
            }
            return result;
        }
    };
}
