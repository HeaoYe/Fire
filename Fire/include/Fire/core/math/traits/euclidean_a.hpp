#pragma once

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/traits/macros.hpp>
#include <Fire/core/math/traits/metric.hpp>
#include <Fire/core/math/traits/affine.hpp>

namespace Fire {
    DEFINE_TRAIT(EuclideanA, REQUIRE_TRAIT(Metric), REQUIRE_TRAIT(Affine))
}
