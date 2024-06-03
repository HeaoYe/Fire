#pragma once

#include <Fire/core/macros.hpp>
#include <Fire/spectrum/distributions/spectrum_distribution.hpp>
#include <Fire/spectrum/color/colorspace.hpp>

namespace Fire {
    class RGBSigmoidPolynomialSD : public SpectrumDistribution {
    public:
        FIRE_API static RGBSigmoidPolynomialSD FromRGB(const ColorSpace &colorspace, const RGB &rgb);
    public:
        RGBSigmoidPolynomialSD(Real a, Real b, Real c) : a(a), b(b), c(c) {}
        FIRE_API Real sample(Real nm) const override;
    private:
        Real a {}, b {}, c {};
    };
}
