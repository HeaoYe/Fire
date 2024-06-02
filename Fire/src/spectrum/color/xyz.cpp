#include "spectrum/color/xyz.hpp"
#include "spectrum/color/cie_matching_curves.hpp"
#include "spectrum/color/rgb.hpp"
#include "spectrum/color/colorspace.hpp"

namespace Fire {
    static Real SpectrumDistributionInnerProduct(const SpectrumDistribution &lhs, const SpectrumDistribution &rhs) {
        Real result {};
        for (Int i = g_lambda_min; i <= g_lambda_max; i ++) {
            result += lhs.sample(i) * rhs.sample(i);
        }
        return result;
    }

    XYZ XYZ::FromSpectrumDistribution(const SpectrumDistribution &spectrum_distribution) {
        Real x = SpectrumDistributionInnerProduct(g_cie_x_matching_function, spectrum_distribution);
        Real y = SpectrumDistributionInnerProduct(g_cie_y_matching_function, spectrum_distribution);
        Real z = SpectrumDistributionInnerProduct(g_cie_z_matching_function, spectrum_distribution);
        return XYZ { x, y, z } / g_cie_y_integral;
    }

    XYZ XYZ::FromSpectrumSample(const SpectrumSample &sample) {
        auto pdf = sample.wavelengths_sample.getWavelengthsPDF();
        auto cie_x_sample = SpectrumSample::FromSpectrumDistribution(g_cie_x_matching_function, sample.wavelengths_sample);
        auto cie_y_sample = SpectrumSample::FromSpectrumDistribution(g_cie_y_matching_function, sample.wavelengths_sample);
        auto cie_z_sample = SpectrumSample::FromSpectrumDistribution(g_cie_z_matching_function, sample.wavelengths_sample);
        Real x = SafeDiv(cie_x_sample.value * sample.value, pdf).Average();
        Real y = SafeDiv(cie_y_sample.value * sample.value, pdf).Average();
        Real z = SafeDiv(cie_z_sample.value * sample.value, pdf).Average();
        return XYZ { x, y, z } / g_cie_y_integral;
    }

    XYZ XYZ::FromxyY(const xyY &xyy) {
        Real sum = xyy.get(2) / xyy.get(1);
        return XYZ { xyy.get(0) * sum, xyy.get(1), (Real(1) - xyy.get(0) - xyy.get(1)) * sum };
    }

    XYZ XYZ::FromRGB(const ColorSpace &colorspace, const RGB &rgb) {
        return XYZ { colorspace.getXYZFromRGB() * rgb };
    }

    xyY xyY::FromXYZ(const XYZ &xyz) {
        Real sum = xyz.get(0) + xyz.get(1) + xyz.get(2);
        return xyY { xyz.get(0) / sum, xyz.get(1) / sum, xyz.get(1) };
    }
}
