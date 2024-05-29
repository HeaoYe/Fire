#pragma once

#include <Fire/core/concepts.hpp>
#include <cmath>

namespace Fire {
    template <ConceptArithmetic T>
    T Sqrt(T value) {
        return std::sqrt(value);
    }

    template <ConceptArithmetic T>
    T SafeSqrt(T value) {
        return std::sqrt(std::max(value, T { 0 }));
    }

    template <ConceptArithmetic T>
    T Squa(T value) {
        return value * value;
    }
}
