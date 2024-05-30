#pragma once

#include <Fire/core/math/traits_impl/array_2d_impl/add_impl.hpp>

namespace Fire {
    struct Array2DImpl {
        DEFINE_TRAIT_IMPL(Add, Array2DAddTraitImpl);
    };
}
