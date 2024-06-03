#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/add.hpp>

namespace Fire {
    class Array1DAddTraitImpl {
    public:
        TRAIT_API(Add) static T OpAdd(const T &lhs, const T &rhs) {
            return InternalOpAdd(lhs, rhs, T::IndexSequence);
        }

        TRAIT_API(Add) static T OpSub(const T &lhs, const T &rhs) {
            return InternalOpSub(lhs, rhs, T::IndexSequence);
        }

        TRAIT_API(Add) static T OpOpposite(const T &rhs) {
            return InternalOpOpposite(rhs, T::IndexSequence);
        }
    private:
        template <ConceptAdd T, SizeT ...Indices>
        static T InternalOpAdd(const T &lhs, const T &rhs, std::index_sequence<Indices...>) {
            return T { (lhs.template get<Indices>() + rhs.template get<Indices>())... };
        }

        template <ConceptAdd T, SizeT ...Indices>
        static T InternalOpSub(const T &lhs, const T &rhs, std::index_sequence<Indices...>) {
            return T { (lhs.template get<Indices>() - rhs.template get<Indices>())... };
        }

        template <ConceptAdd T, SizeT ...Indices>
        static T InternalOpOpposite(const T &rhs, std::index_sequence<Indices...>) {
            return T { (-(rhs.template get<Indices>()))... };
        }
    };
}
