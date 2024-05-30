#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/affine.hpp>

namespace Fire {
    class Array1DAffineTraitImpl {
    public:
        TRAIT_API_WITH_CONDITIONS(Affine, Y::Dims == T::Dims, Y, , ConceptEuclideanV Y) static OpSubSame(const T &lhs, const T &rhs) {
            return InternalOpSubSame<T, Y>(lhs, rhs, T::IndexSequence);
        }

        TRAIT_API_WITH_CONDITIONS(Affine, Y::Dims == T::Dims, T, , ConceptEuclideanV Y) static OpAdd(const T &lhs, const Y &rhs) {
            return InternalOpAdd(lhs, rhs, T::IndexSequence);
        }

        TRAIT_API_WITH_CONDITIONS(Affine, Y::Dims == T::Dims, T, , ConceptEuclideanV Y) static OpSub(const T &lhs, const Y &rhs) {
            return InternalOpSub(lhs, rhs, T::IndexSequence);
        }
    private:
        template <class T, ConceptEuclideanV Y, SizeT ...Indices>
        static Y InternalOpSubSame(const T &lhs, const T &rhs, std::index_sequence<Indices...>) {
            return Y { (lhs.template get<Indices>() - rhs.template get<Indices>())... };
        }

        template <class T, ConceptEuclideanV Y, SizeT ...Indices>
        static T InternalOpAdd(const T &lhs, const Y &rhs, std::index_sequence<Indices...>) {
            return T { (lhs.template get<Indices>() + rhs.template get<Indices>())... };
        }

        template <class T, ConceptEuclideanV Y, SizeT ...Indices>
        static T InternalOpSub(const T &lhs, const Y &rhs, std::index_sequence<Indices...>) {
            return T { (lhs.template get<Indices>() - rhs.template get<Indices>())... };
        }
    };
}
