#include "spectrum/distributions/rgb_sigmoid_polynomial_spectrum_distribution.hpp"

namespace Fire {
    RGBSigmoidPolynomialSD RGBSigmoidPolynomialSD::FromRGB(const ColorSpace &colorspace, const RGB &rgb) {
        auto cofficients = colorspace.getRGBToSpectrumTable().SampleRGBCofficients(rgb);
        return RGBSigmoidPolynomialSD { cofficients.get(0), cofficients.get(1), cofficients.get(2) };
    }

    Real RGBSigmoidPolynomialSD::sample(Real nm) const {
        return Sigmoid(EvaluatePolynomial(nm, c, b, a));
    }
}
