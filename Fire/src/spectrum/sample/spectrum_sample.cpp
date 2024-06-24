#include "spectrum/sample/spectrum_sample.hpp"

namespace Fire {
    SpectrumSampleValue SpectrumSampleValue::FromSpectrumDistribution(const SpectrumDistribution &spectrum_distribution, const WavelengthsSample &wavelengths_sample) {
        SpectrumSampleValue result {};
        for (Int i = 0; i < g_spectrum_sample_count; i ++) {
            result.set(i, spectrum_distribution.sample(wavelengths_sample.getWavelength(i)));
        }
        return result;
    }

    Real SpectrumSampleValue::average() const {
        Real result = 0;
        for (Int i = 0; i < g_spectrum_sample_count; i ++) {
            result += get(i);
        }
        return result / Real(g_spectrum_sample_count);
    }

    SpectrumSample SpectrumSample::FromSpectrumDistribution(const SpectrumDistribution &spectrum_distribution, const WavelengthsSample &wavelengths_sample) {
        return SpectrumSample { wavelengths_sample, SpectrumSampleValue::FromSpectrumDistribution(spectrum_distribution, wavelengths_sample) };
    }
}
