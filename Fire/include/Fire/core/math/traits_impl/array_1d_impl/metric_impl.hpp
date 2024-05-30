#pragma once

#include <Fire/core/math/traits/metric.hpp>

namespace Fire {
    class Array1DMetricTraitImpl {
    public:
        TRAIT_API(Metric) static Real DistanceSqua(const T &lhs, const T &rhs) {
            Real result { 0 };
            for (SizeT i = 0; i < T::Dims; i ++) {
                result += Squa(lhs.get(i) - rhs.get(i));
            }
            return result;
        }
    };
}
