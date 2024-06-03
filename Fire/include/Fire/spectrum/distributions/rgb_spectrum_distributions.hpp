#pragma once

#include<Fire/spectrum/distributions/rgb_sigmoid_polynomial_spectrum_distribution.hpp>

namespace Fire {
    class RGBAlbedoSD : public SpectrumDistribution {
    public:
        FIRE_API RGBAlbedoSD(const ColorSpace &colorspace, const RGB &rgb);
        FIRE_API Real sample(Real nm) const override;
    private:
        RGBSigmoidPolynomialSD rgb_sigmoid_polynomial_spectrum_distribution;
    };

    class RGBUnboundedSD : public RGBAlbedoSD {
    public:
        FIRE_API RGBUnboundedSD(const ColorSpace &colorspace, const RGB &rgb);
        FIRE_API Real sample(Real nm) const override;
    private:
        Real scale;
    };

    class RGBIlluminantSD : public RGBUnboundedSD {
    public:
        FIRE_API RGBIlluminantSD(const ColorSpace &colorspace, const RGB &rgb);
        FIRE_API Real sample(Real nm) const override;
    private:
        const SpectrumDistribution &illuminant;
    };
}
