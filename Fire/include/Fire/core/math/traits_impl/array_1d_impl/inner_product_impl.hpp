#pragma once

#include <Fire/core/math/traits/inner_product.hpp>

namespace Fire {
    class Array1DInnerProductTraitImpl {
    public:
        TRAIT_API(InnerProduct) static Real Dot(const T &lhs, const T &rhs) {
            Real result { 0 };
            for (SizeT i = 0; i < T::Dims; i ++) {
                result += lhs.get(i) * rhs.get(i);
            }
            return result;
        }
    };
}
