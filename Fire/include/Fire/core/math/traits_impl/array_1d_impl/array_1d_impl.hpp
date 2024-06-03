#pragma once

#include <Fire/core/math/traits_impl/array_1d_impl/add_impl.hpp>
#include <Fire/core/math/traits_impl/array_1d_impl/mul_impl.hpp>
#include <Fire/core/math/traits_impl/array_1d_impl/scalar_mul_impl.hpp>
#include <Fire/core/math/traits_impl/array_1d_impl/metric_impl.hpp>
#include <Fire/core/math/traits_impl/array_1d_impl/norm_impl.hpp>
#include <Fire/core/math/traits_impl/array_1d_impl/inner_product_impl.hpp>
#include <Fire/core/math/traits_impl/array_1d_impl/euclidean_v_impl.hpp>
#include <Fire/core/math/traits_impl/array_1d_impl/affine_impl.hpp>
#include <Fire/core/math/traits/linear.hpp>  // IWYU pragma: export
#include <Fire/core/math/traits/ring.hpp>  // IWYU pragma: export
#include <Fire/core/math/traits/matrix_multiplicable.hpp>  // IWYU pragma: export

namespace Fire {
    struct Array1DImpl {
        DEFINE_TRAIT_IMPL(Add, Array1DAddTraitImpl);
        DEFINE_TRAIT_IMPL(Mul, Array1DMulTraitImpl);
        DEFINE_TRAIT_IMPL(ScalarMul, Array1DScalarMulTraitImpl);
        DEFINE_TRAIT_IMPL(Metric, Array1DMetricTraitImpl);
        DEFINE_TRAIT_IMPL(Norm, Array1DNormTraitImpl);
        DEFINE_TRAIT_IMPL(InnerProduct, Array1DInnerProductTraitImpl);
        DEFINE_TRAIT_IMPL(EuclideanV, Array1DEuclideanVTraitImpl);
        DEFINE_TRAIT_IMPL(Affine, Array1DAffineTraitImpl);
    };
}
