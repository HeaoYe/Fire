#pragma once

#include <Fire/core/math/storage/storage_array_1d.hpp>

namespace Fire {
    class RGB : public StorageArray1D<Real, 3> {
        DEFINE_STORAGE_ARRAY_1D_FIXED_SIZE(RGB, Real, 3);
    public:
        FIRE_API static RGB FromXYZ(const class ColorSpace &colorspace, const class XYZ &xyz);
        FIRE_API static RGB FromRGB(const class ColorSpace &dst_colorspace, const class ColorSpace &src_colorspace, const RGB &rgb);
        FIRE_API static RGB FromSpectrumSample(const class ColorSpace &colorspace, const class SpectrumSample &sample);
    };

    template <>
    IMPL_TRAIT(Add, RGB);

    template <>
    IMPL_TRAIT(ScalarMul, RGB);

    template <>
    IMPL_TRAIT(Linear, RGB);

    template <>
    IMPL_TRAIT(MatrixMultiplicable, RGB);
}
