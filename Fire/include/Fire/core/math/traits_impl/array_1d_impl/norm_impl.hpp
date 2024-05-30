#pragma once

#include <Fire/core/math/traits/norm.hpp>

namespace Fire {
    class Array1DNormTraitImpl {
    public:
        TRAIT_API(Norm) static Real OneNorm(const T &rhs) {
            Real result { 0 };
            for (SizeT i = 0; i < T::Dims; i ++) {
                result += rhs.get(i);
            }
            return result;
        }

        TRAIT_API(Norm) static Real TwoNorm(const T &rhs) {
            Real result { 0 };
            for (SizeT i = 0; i < T::Dims; i ++) {
                result += rhs.get(i) * rhs.get(i);
            }
            return Sqrt(result);
        }
    };
}
