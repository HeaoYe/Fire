#pragma once

#include <Fire/core/math/types/scale.hpp>
#include <Fire/core/math/types/vector.hpp>
#include <Fire/core/math/types/normal.hpp>
#include <Fire/core/math/types/point.hpp>
#include <Fire/core/math/types/matrix.hpp>
#include <Fire/core/math/types/transform.hpp>

#define __DEFINE_BASIC_TYPES_1D(NAME) \
    using NAME##2r = NAME<Real, 2>; \
    using NAME##2i = NAME<Int, 2>; \
    using NAME##3r = NAME<Real, 3>; \
    using NAME##3i = NAME<Int, 3>; \

#define __DEFINE_BASIC_TYPES_2D(NAME) \
    using NAME##2r = NAME<Real, 2, 2>; \
    using NAME##2i = NAME<Int, 2, 2>; \
    using NAME##3r = NAME<Real, 3, 3>; \
    using NAME##3i = NAME<Int, 3, 3>; \

namespace Fire {
    __DEFINE_BASIC_TYPES_1D(Scale)
    __DEFINE_BASIC_TYPES_1D(Vector)
    __DEFINE_BASIC_TYPES_1D(Normal)
    __DEFINE_BASIC_TYPES_1D(Point)
    __DEFINE_BASIC_TYPES_2D(Matrix)
}
