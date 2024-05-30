#pragma once

#include <Fire/core/math/types/scale.hpp>
#include <Fire/core/math/types/vector.hpp>
#include <Fire/core/math/types/normal.hpp>
#include <Fire/core/math/types/point.hpp>

#define __DEFINE_BASIC_TYPES(NAME) \
    using NAME##3r = NAME<Real, 3>; \
    using NAME##3i = NAME<Int, 3>; \
    using NAME##3 = NAME##3r; \

namespace Fire {
    __DEFINE_BASIC_TYPES(Scale)
    __DEFINE_BASIC_TYPES(Vector)
    __DEFINE_BASIC_TYPES(Normal)
    __DEFINE_BASIC_TYPES(Point)
}
