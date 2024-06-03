#include "spectrum/color/xyz.hpp"
#include "spectrum/color/rgb.hpp"
#include "spectrum/color/colorspace.hpp"

namespace Fire {
    RGB RGB::FromXYZ(const ColorSpace &colorspace, const XYZ &xyz) {
        return RGB { colorspace.getRGBFromXYZ() * xyz };
    }

    RGB RGB::FromRGB(const ColorSpace &dst_colorspace, const ColorSpace &src_colorspace, const RGB &rgb) {
        return RGB { dst_colorspace.getRGBFromXYZ() * XYZ::FromRGB(src_colorspace, rgb) };
    }

    RGB RGB::FromSpectrumSample(const class ColorSpace &colorspace, const class SpectrumSample &sample) {
        return RGB { colorspace.getRGBFromXYZ() * XYZ::FromSpectrumSample(sample) };
    }
}
