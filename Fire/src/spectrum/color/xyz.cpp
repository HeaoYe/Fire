#include "spectrum/color/xyz.hpp"
#include "spectrum/color/cie_matching_curves.hpp"
#include "spectrum/color/rgb.hpp"
#include "spectrum/color/colorspace.hpp"

namespace Fire {
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
        Real x = SafeDiv(cie_x_sample.value * sample.value, pdf).average();
        Real y = SafeDiv(cie_y_sample.value * sample.value, pdf).average();
        Real z = SafeDiv(cie_z_sample.value * sample.value, pdf).average();
        return XYZ { x, y, z } / g_cie_y_integral;
    }

    XYZ XYZ::FromxyY(const xyY &xyy) {
        Real sum = xyy.Y / xyy.y;
        return XYZ { xyy.x * sum, xyy.Y, (Real(1) - xyy.x - xyy.y) * sum };
    }

    XYZ XYZ::FromRGB(const ColorSpace &colorspace, const RGB &rgb) {
        return XYZ { colorspace.getXYZFromRGB() * rgb };
    }

    xyY xyY::FromXYZ(const XYZ &xyz) {
        Real sum = xyz.x + xyz.y + xyz.z;
        return xyY { xyz.x / sum, xyz.y / sum, xyz.y };
    }
}
