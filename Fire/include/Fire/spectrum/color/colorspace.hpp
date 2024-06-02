#pragma once

#include <Fire/core/math/types/types.hpp>
#include <Fire/spectrum/distributions/densely_sampled_spectrum_distribution.hpp>
#include <Fire/spectrum/color/xyz.hpp>
#include <Fire/spectrum/color/rgb.hpp>

namespace Fire {
    class ColorSpace {
    public:
        FIRE_API ColorSpace(const xyY &r, const xyY &g, const xyY &b, const SpectrumDistribution &illuminant);
        const Matrix3r &getXYZFromRGB() const { return xyz_from_rgb; }
        const Matrix3r &getRGBFromXYZ() const { return rgb_from_xyz; }
    private:
        xyY r, g, b, w;
        DenselySampledSD illuminant;
        Matrix3r xyz_from_rgb;
        Matrix3r rgb_from_xyz;
    };
}
