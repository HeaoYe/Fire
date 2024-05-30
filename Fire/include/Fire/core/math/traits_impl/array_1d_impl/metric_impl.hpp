#pragma once

#include <Fire/core/math/traits/metric.hpp>

namespace Fire {
    class Array1DMetricTraitImpl {
    public:
        ENABLE_IF_IMPL_TRAIT(Metric, Real, static) DistanceSqua(const T &lhs, const T &rhs) {
            Real result { 0 };
            for (SizeT i = 0; i < T::Dims; i ++) {
                result += Squa(lhs.get(i) - rhs.get(i));
            }
            return result;
        }
    };
}
