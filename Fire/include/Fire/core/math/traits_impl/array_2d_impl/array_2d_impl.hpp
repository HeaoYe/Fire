#pragma once

#include <Fire/core/math/traits_impl/array_2d_impl/add_impl.hpp>
#include <Fire/core/math/traits_impl/array_2d_impl/scalar_mul_impl.hpp>
#include <Fire/core/math/traits_impl/array_2d_impl/matrix_impl.hpp>
#include <Fire/core/math/traits_impl/array_2d_impl/matrix_mul_impl.hpp>
#include <Fire/core/math/traits/linear.hpp>  // IWYU pragma: export
#include <Fire/core/math/traits/ring.hpp>  // IWYU pragma: export

namespace Fire {
    struct Array2DImpl {
        DEFINE_TRAIT_IMPL(Add, Array2DAddTraitImpl);
        DEFINE_TRAIT_IMPL(ScalarMul, Array2DScalarMulTraitImpl);
        DEFINE_TRAIT_IMPL(Matrix, Array2DMatrixTraitImpl);
        DEFINE_TRAIT_IMPL(MatrixMul, Array2DMatrixMulTraitImpl);
    };
}
