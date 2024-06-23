#pragma once

#include <Fire/core/memory/memory_allocator.hpp>
#include <Fire/core/logger.hpp>
#include <Fire/core/thread/task.hpp>
#include <Fire/core/thread/thread_pool.hpp>
#include <Fire/core/thread/parallel_for.hpp>

#include <Fire/core/math/basics.hpp>
#include <Fire/core/math/types/types.hpp>
#include <Fire/core/math/rounds/compensated_float.hpp>

#include <Fire/spectrum/basics.hpp>
#include <Fire/spectrum/distributions/constant_spectrum_distribution.hpp>
#include <Fire/spectrum/distributions/densely_sampled_spectrum_distribution.hpp>
#include <Fire/spectrum/distributions/piecewise_linear_spectrum_distribution.hpp>
#include <Fire/spectrum/distributions/rgb_sigmoid_polynomial_spectrum_distribution.hpp>
#include <Fire/spectrum/distributions/rgb_spectrum_distributions.hpp>
#include <Fire/spectrum/sample/wavelengths_sample.hpp>
#include <Fire/spectrum/sample/spectrum_sample.hpp>
#include <Fire/spectrum/color/cie_matching_curves.hpp>
#include <Fire/spectrum/color/illuminants.hpp>
#include <Fire/spectrum/color/rgb_to_spectrum.hpp>
#include <Fire/spectrum/color/xyz.hpp>
#include <Fire/spectrum/color/colorspace.hpp>
#include <Fire/spectrum/color/rgb.hpp>

#include <Fire/camera/ray.hpp>
#include <Fire/camera/film.hpp>
#include <Fire/camera/camera.hpp>
#include <Fire/camera/projective_camera.hpp>
#include <Fire/camera/orthographic_camera.hpp>
#include <Fire/camera/perspective_camera.hpp>
