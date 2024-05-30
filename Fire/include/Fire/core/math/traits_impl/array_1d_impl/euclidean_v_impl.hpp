#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/euclidean_v.hpp>

namespace Fire {
    class Array1DEuclideanVTraitImpl {
    public:
        TRAIT_API_WITH_CONDITIONS(EuclideanV, T::Dims == 3, T) static Cross(const T &lhs, const T &rhs) {
            return T {
                DifferenceOfProducts(lhs.template get<1>(), rhs.template get<2>(), lhs.template get<2>(), rhs.template get<1>()),
                DifferenceOfProducts(lhs.template get<2>(), rhs.template get<0>(), lhs.template get<0>(), rhs.template get<2>()),
                DifferenceOfProducts(lhs.template get<0>(), rhs.template get<1>(), lhs.template get<1>(), rhs.template get<0>())
            };
        }
    };
}
