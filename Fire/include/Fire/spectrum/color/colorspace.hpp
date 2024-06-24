#pragma once

#include <Fire/core/math/types/types.hpp>
#include <Fire/spectrum/distributions/densely_sampled_spectrum_distribution.hpp>
#include <Fire/spectrum/color/xyz.hpp>
#include <Fire/spectrum/color/rgb.hpp>
#include <Fire/spectrum/color/rgb_to_spectrum.hpp>

namespace Fire {
    class ColorSpace {
    public:
        FIRE_API static void Initialize();
        FIRE_API static void Destroy();
    public:
        ColorSpace() = default;
        FIRE_API ColorSpace(const xyY &r, const xyY &g, const xyY &b, const SpectrumDistribution &illuminant, const RGBToSpectrumTable<Real> &table);
        const Matrix3r &getXYZFromRGB() const { return xyz_from_rgb; }
        const Matrix3r &getRGBFromXYZ() const { return rgb_from_xyz; }
        const SpectrumDistribution &getIllumiant() const { return *illuminant; }
        const RGBToSpectrumTable<Real> &getRGBToSpectrumTable() const { return *table; }
        xyY getW() const { return w; }
    private:
        xyY r, g, b, w;
        Matrix3r xyz_from_rgb;
        Matrix3r rgb_from_xyz;
        const SpectrumDistribution *illuminant;
        const RGBToSpectrumTable<Real> *table;
    };

    FIRE_API extern ColorSpace g_colorspace_sRGB;
    FIRE_API extern ColorSpace g_colorspace_DCI_P3;
    FIRE_API extern ColorSpace g_colorspace_Rec2020;
    FIRE_API extern ColorSpace g_colorspace_ACES2065_1;
}
