#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/mul.hpp>

namespace Fire {
    class Array1DMulTraitImpl {
    public:
        TRAIT_API(Mul) static T OpMul(const T &lhs, const T &rhs) {
            return InternalOpMul(lhs, rhs, T::IndexSequence);
        }

        TRAIT_API(Mul) static T OpDiv(const T &lhs, const T &rhs) {
            return InternalOpDiv(lhs, rhs, T::IndexSequence);
        }

        TRAIT_API(Mul) static T Inverse(const T &rhs) {
            return InternalInverse(rhs, T::IndexSequence);
        }

        TRAIT_API(Mul) static void InverseSelf(T &rhs) {
            for (SizeT i = 0; i < T::Dims; i ++) {
                rhs.set(i, (typename T::Scalar { 1 }) / rhs.get(i));
            }
        }

        TRAIT_API(Mul) static T SafeDiv(const T&lhs, const T &rhs) {
            return InternalOpSafeDiv(lhs, rhs);
        }
    private:
        template <ConceptMul T, SizeT ...Indices>
        static T InternalOpMul(const T &lhs, const T &rhs, std::index_sequence<Indices...>) {
            return T { (lhs.template get<Indices>() * rhs.template get<Indices>())... };
        }

        template <ConceptMul T, SizeT ...Indices>
        static T InternalOpDiv(const T &lhs, const T &rhs, std::index_sequence<Indices...>) {
            return T { (lhs.template get<Indices>() / rhs.template get<Indices>())... };
        }

        template <ConceptMul T, SizeT ...Indices>
        static T InternalOpSafeDiv(const T &lhs, const T &rhs, std::index_sequence<Indices...>) {
            return T { SafeDiv(lhs.template get<Indices>(), rhs.template get<Indices>())... };
        }

        template <ConceptMul T, SizeT ...Indices>
        static T InternalInverse(const T &rhs, std::index_sequence<Indices...>) {
            return T { ((typename T::Scalar { 1 }) / rhs.template get<Indices>())... };
        }
    };
}
