#pragma once

#include <Fire/core/concepts.hpp>
#include <Fire/math/tuple/tuple_macros.hpp>

namespace Fire {
    template <ConceptArithmetic S>
    class Vector2 {
        DEFINE_TUPLE(2, Vector2, S, x, y)
    };
    DEFINE_TUPLE_INLINE(2, Vector2, x, y)

    template <ConceptArithmetic S>
    class Vector3 {
        DEFINE_TUPLE(3, Vector3, S, x, y, z)
    };
    DEFINE_TUPLE_INLINE(3, Vector3, x, y, z)
}
