#pragma once

#include <Fire/core/math/traits/add.hpp>

namespace Fire {
    class Array1DAddTraitImpl {
    public:
        ENABLE_IF_IMPL_TRAIT(Add, T, static) OpAdd(const T &lhs, const T &rhs) {
            return InternalOpAdd(lhs, rhs. T::IndexSequence);
        }

        ENABLE_IF_IMPL_TRAIT(Add, T, static) OpSub(const T &lhs, const T &rhs) {
            return InternalOpSub(lhs, rhs, T::IndexSequence);
        }

        ENABLE_IF_IMPL_TRAIT(Add, T, static) OpOpposite(const T &rhs) {
            return InternalOpOpposite(rhs, T::IndexSequence);
        }
    private:
        template <class T, size_t ...Indices>
        static T InternalOpAdd(const T &lhs, const T &rhs, std::index_sequence<Indices...>) {
            return T { (lhs.template get<Indices>() + rhs.template get<Indices>())... };
        }

        template <class T, size_t ...Indices>
        static T InternalOpSub(const T &lhs, const T &rhs, std::index_sequence<Indices...>) {
            return T { (lhs.template get<Indices>() - rhs.template get<Indices>())... };
        }

        template <class T, size_t ...Indices>
        static T InternalOpOpposite(const T &rhs, std::index_sequence<Indices...>) {
            return T { (-rhs.template get<Indices>())... };
        }
    };
}
