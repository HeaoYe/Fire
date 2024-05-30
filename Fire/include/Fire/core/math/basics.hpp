#pragma once

#include <Fire/core/concepts.hpp>
#include <Fire/core/math/types.hpp>
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

    template <ConceptArithmetic T>
    T FMA(T a, T b, T c) {
        return a * b + c;
    }

    template <ConceptIntegral T>
    T  DifferenceOfProducts(T a, T b, T c, T d) {
        return a * b - c * d;
    }

    template <ConceptFloating T>
    T  DifferenceOfProducts(T a, T b, T c, T d) {
        T cd = c * d;
        T result = FMA(a, b, -cd);
        T error = FMA(-c, d, cd);
        return result + error;
    }
}
