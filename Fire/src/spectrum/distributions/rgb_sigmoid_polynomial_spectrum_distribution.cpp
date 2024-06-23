#include "spectrum/distributions/rgb_sigmoid_polynomial_spectrum_distribution.hpp"

namespace Fire {
    RGBSigmoidPolynomialSD RGBSigmoidPolynomialSD::FromRGB(const ColorSpace &colorspace, const RGB &rgb) {
        auto cofficients = colorspace.getRGBToSpectrumTable().SampleRGBCofficients(rgb);
        return RGBSigmoidPolynomialSD { cofficients.x, cofficients.y, cofficients.z };
    }

    Real RGBSigmoidPolynomialSD::sample(Real nm) const {
        return Sigmoid(EvaluatePolynomial(nm, c, b, a));
    }
}
