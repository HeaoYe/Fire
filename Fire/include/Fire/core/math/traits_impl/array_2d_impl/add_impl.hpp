#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/add.hpp>

namespace Fire {
    class Array2DAddTraitImpl {
    public:
        ENABLE_IF_IMPL_TRAIT(Add, T, static) OpAdd(const T &lhs, const T &rhs) {
            T result {};
            for (SizeT i = 0; i < T::Dims1; i ++) {
                for (SizeT j = 0; j < T::Dims2; j ++) {
                    result.set(i, j, lhs.get(i, j) + rhs.get(i, j));
                }
            }
            return result;
        }

        ENABLE_IF_IMPL_TRAIT(Add, T, static) OpSub(const T &lhs, const T &rhs) {
            T result {};
            for (SizeT i = 0; i < T::Dims1; i ++) {
                for (SizeT j = 0; j < T::Dims2; j ++) {
                    result.set(i, j, lhs.get(i, j) - rhs.get(i, j));
                }
            }
            return result;
        }

        ENABLE_IF_IMPL_TRAIT(Add, T, static) OpOpposite(const T &rhs) {
            T result {};
            for (SizeT i = 0; i < T::Dims1; i ++) {
                for (SizeT j = 0; j < T::Dims2; j ++) {
                    result.set(i, j, -rhs.get(i, j));
                }
            }
            return result;
        }
    };
}
