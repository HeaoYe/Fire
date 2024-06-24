#pragma once

#include <Fire/spectrum/color/colorspace.hpp>

namespace Fire {
    class PixelSensor {
    public:
        FIRE_API PixelSensor(const SpectrumDistribution &r_mf, const SpectrumDistribution &g_mf, const SpectrumDistribution &b_mf, const ColorSpace &output_colorspace, const SpectrumDistribution &sensor_illuminant, Real imaging_ratio = 1);
        FIRE_API PixelSensor(const ColorSpace &output_colorspace, const SpectrumDistribution &sensor_illuminant, Real imaging_ratio = 1);
        PixelSensor(const ColorSpace &output_colorspace, Real imaging_ratio = 1) : PixelSensor(output_colorspace, output_colorspace.getIllumiant(), imaging_ratio) {}

        FIRE_API RGB measureRadiance(const SpectrumSample &radiance_sample) const;
        FIRE_API XYZ XYZFromSensorRGB(const RGB &rgb) const { return XYZ { xyz_from_sensor_rgb * rgb }; }
    private:
        DenselySampledSD r_mf, g_mf, b_mf;
        Real imaging_ratio;
        Matrix3r xyz_from_sensor_rgb;
    };
}
