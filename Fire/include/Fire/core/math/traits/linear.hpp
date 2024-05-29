#pragma once

#include <Fire/core/math/traits/add.hpp>
#include <Fire/core/math/traits/scalar_mul.hpp>

namespace Fire {
    DEFINE_TRAIT(Linear, REQUIRE_TRAIT(Add), REQUIRE_TRAIT(ScalarMul))
}
