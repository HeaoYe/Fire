#pragma once

#include <Fire/core/math/basics.hpp>

namespace Fire {
    class CompensatedFloat {
    public:
        CompensatedFloat(Real value, Real error = 0) : value(value), error(error) {}
        explicit operator float() const { return static_cast<float>(value + error); }
        explicit operator double() const { return static_cast<double>(value) + static_cast<double>(error); }
    public:
        Real value, error;
    public:
        static CompensatedFloat TwoProd(Real a, Real b) {
            Real ab = a * b;
            return CompensatedFloat { ab, FMA(a, b, -ab) };
        }

        static CompensatedFloat TwoSum(Real a, Real b) {
            Real s = a + b;
            Real delta = a - b;
            return CompensatedFloat { s, (a - (s - delta)) + (b - delta) };
        }

        template <ConceptArithmetic T, ConceptArithmetic ...Ts>
        static CompensatedFloat InnerProduct(T a, T b, Ts ...args) {
            if constexpr (sizeof...(args) == 0) {
                return TwoProd(a, b);
            } else {
                auto ab = TwoProd(a, b);
                auto other = InnerProduct(args...);
                auto result = TwoSum(ab.value, other.value);
                return CompensatedFloat { result.value, ab.error + (other.error + result.error) };
            }
        }
    };
}
