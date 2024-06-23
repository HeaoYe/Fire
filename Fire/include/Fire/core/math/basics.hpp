#pragma once

#include <Fire/core/concepts.hpp>
#include <cstdint>
#include <cmath>

namespace Fire {
#if defined (FIRE_USE_DOUBLE_AS_REAL)
    using Real = double;
#else
    using Real = float;
#endif
    using Int = int32_t;
    using SizeT = size_t;
    using Angle = Real;
    using Radian = Real;

    template <ConceptArithmetic T>
    T SafeDiv(T lhs, T rhs) {
        if (rhs == 0) {
            return 0;
        }
        return lhs / rhs;
    }

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
    T Lerp(T a, T b, T t) {
        return a * (1 - t) + b * t;
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

    inline Real Sin(Radian theta) { return std::sin(theta); }
    inline Real Cos(Radian theta) { return std::cos(theta); }
    inline Real Tan(Radian theta) { return std::tan(theta); }

    inline Real EvaluatePolynomial(Real t, Real c) { return c; }

    template <class T, ConceptArithmetic... Args>
    Real EvaluatePolynomial(Real t, T c, Args... args) {
        return FMA(t, EvaluatePolynomial(t, Real(args)...), c);
    }

    inline Real Sigmoid(Real rhs) {
        if (std::isinf(rhs)) {
            return rhs > 0 ? 1 : 0;
        }
        return 0.5 + rhs / (2 * Sqrt(1 + rhs * rhs));
    };
}
