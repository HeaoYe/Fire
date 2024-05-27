#pragma once

#include <Fire/core/concepts.hpp>
#include <Fire/math/tuple/tuple_macros.hpp>

namespace Fire {
    template <ConceptArithmetic S>
    class Point2 {
        DEFINE_TUPLE(2, Point2, S, x, y)
    };
    DEFINE_TUPLE_INLINE(2, Point2, x, y)

    template <ConceptArithmetic S>
    class Point3 {
        DEFINE_TUPLE(3, Point3, S, x, y, z)
    };
    DEFINE_TUPLE_INLINE(3, Point3, x, y, z)
}
