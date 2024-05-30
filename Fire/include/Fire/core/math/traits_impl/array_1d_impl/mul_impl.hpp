#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/mul.hpp>

namespace Fire {
    class Array1DMulTraitImpl {
    public:
        ENABLE_IF_IMPL_TRAIT(Mul, T, static) OpMul(const T &lhs, const T &rhs) {
            return InternalOpScalarMul(lhs, rhs, T::IndexSequence);
        }

        ENABLE_IF_IMPL_TRAIT(Mul, T, static) OpDiv(const T &lhs, const T &rhs) {
            return InternalOpDiv(lhs, rhs, T::IndexSequence);
        }

        ENABLE_IF_IMPL_TRAIT(Mul, T, static) Inverse(const T &rhs) {
            return InternalInverse(rhs, T::IndexSequence);
        }

        ENABLE_IF_IMPL_TRAIT(Mul, void, static) InverseSelf(T &rhs) {
            for (SizeT i = 0; i < T::Dims; i ++) {
                rhs.set(i, (typename T::Scalar { 1 }) / rhs.get(i));
            }
        }
    private:
        template <class T, SizeT ...Indices>
        static T InternalOpMul(const T &lhs, const T &rhs, std::index_sequence<Indices...>) {
            return T { (lhs.template get<Indices>() * rhs.template get<Indices>())... };
        }

        template <class T, SizeT ...Indices>
        static T InternalOpDiv(const T &lhs, const T &rhs, std::index_sequence<Indices...>) {
            return T { (lhs.template get<Indices>() / rhs.template get<Indices>())... };
        }

        template <class T, SizeT ...Indices>
        static T InternalInverse(const T &rhs, std::index_sequence<Indices...>) {
            return T { ((typename T::Scalar { 1 }) / rhs.template get<Indices>())... };
        }
    };
}
