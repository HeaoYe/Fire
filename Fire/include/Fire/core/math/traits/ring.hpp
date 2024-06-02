#pragma once

#include <Fire/core/math/traits/add.hpp>
#include <Fire/core/math/traits/mul.hpp>
#include <Fire/core/math/traits/matrix_mul.hpp>

namespace Fire {
    DEFINE_TRAIT(Ring, REQUIRE_TRAIT(Add), REQUIRE_ONE_OF(Mul, MatrixMul))
}
