#include "spectrum/distributions/rgb_spectrum_distributions.hpp"

namespace Fire {
    RGBAlbedoSD::RGBAlbedoSD(const ColorSpace &colorspace, const RGB &rgb)
        : rgb_sigmoid_polynomial_spectrum_distribution(RGBSigmoidPolynomialSD::FromRGB(colorspace, rgb)) {}

    Real RGBAlbedoSD::sample(Real nm) const {
        return rgb_sigmoid_polynomial_spectrum_distribution.sample(nm);
    }

    RGBUnboundedSD::RGBUnboundedSD(const ColorSpace &colorspace, const RGB &rgb)
        : RGBAlbedoSD(colorspace, [&]() {
            Real max = std::max<Real>({ rgb.get(0), rgb.get(1), rgb.get(2) });
            scale = 2 * max;
            return scale == 0 ? (RGB {}) : (rgb / scale);
        }()) {}

    Real RGBUnboundedSD::sample(Real nm) const {
        return scale * RGBAlbedoSD::sample(nm);
    }

    RGBIlluminantSD::RGBIlluminantSD(const ColorSpace &colorspace, const RGB &rgb)
        : RGBUnboundedSD(colorspace, rgb), illuminant(colorspace.getIllumiant()) {}

    Real RGBIlluminantSD::sample(Real nm) const {
        return RGBUnboundedSD::sample(nm) * illuminant.sample(nm);
    }
}
