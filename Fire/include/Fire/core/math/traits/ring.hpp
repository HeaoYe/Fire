#pragma once

#include <Fire/core/math/traits/add.hpp>
#include <Fire/core/math/traits/mul.hpp>

namespace Fire {
    DEFINE_TRAIT(Ring, REQUIRE_TRAIT(Add), REQUIRE_TRAIT(Mul))
}
