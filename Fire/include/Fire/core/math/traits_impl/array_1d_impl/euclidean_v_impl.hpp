#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/euclidean_v.hpp>

namespace Fire {
    class Array1DEuclideanVTraitImpl {
    public:
        ENABLE_IF_IMPL_TRAIT_WITH_CONDITIONS(EuclideanV, T, (EQUAL<SizeT, T::Dims, 3>), static) Cross(const T &lhs, const T &rhs) {
            return T {
                DifferenceOfProducts(lhs.template get<1>(), rhs.template get<2>(), lhs.template get<2>(), rhs.template get<1>()),
                DifferenceOfProducts(lhs.template get<2>(), rhs.template get<0>(), lhs.template get<0>(), rhs.template get<2>()),
                DifferenceOfProducts(lhs.template get<0>(), rhs.template get<1>(), lhs.template get<1>(), rhs.template get<0>())
            };
        }
    };
}
