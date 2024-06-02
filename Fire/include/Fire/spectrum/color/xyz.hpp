#pragma once

#include <Fire/core/math/storage/storage_array_1d.hpp>
#include <Fire/spectrum/sample/spectrum_sample.hpp>

namespace Fire {
    class xyY;

    class XYZ : public StorageArray1D<Real, 3> {
        DEFINE_STORAGE_ARRAY_1D_FIXED_SIZE(XYZ, Real, 3);
    public:
        FIRE_API static XYZ FromSpectrumDistribution(const SpectrumDistribution &spectrum_distribution);
        FIRE_API static XYZ FromSpectrumSample(const SpectrumSample &sample);
        FIRE_API static XYZ FromxyY(const xyY &xyy);
        FIRE_API static XYZ FromRGB(const class ColorSpace &colorspace, const class RGB &rgb);
    };

    template <>
    IMPL_TRAIT(Add, XYZ);

    template <>
    IMPL_TRAIT(ScalarMul, XYZ);

    template <>
    IMPL_TRAIT(Linear, XYZ);

    template <>
    IMPL_TRAIT(MatrixMultiplicable, XYZ);

    class xyY : public StorageArray1D<Real, 3> {
        DEFINE_STORAGE_ARRAY_1D_FIXED_SIZE(xyY, Real, 3);
    public:
        FIRE_API static xyY FromXYZ(const XYZ &xyz);
    };
}
