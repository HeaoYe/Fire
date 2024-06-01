#include <Fire/spectrum/sample/spectrum_sample.hpp>

namespace Fire {
    SpectrumSample SampleSpectrumDistribution(const SpectrumDistribution &spectrum_distribution, const WavelengthsSample &wavelengths_sample) {
        SpectrumSample result {};
        for (Int i = 0; i < g_spectrum_sample_count; i ++) {
            result.set(i, spectrum_distribution.sample(wavelengths_sample.getWavelength(i)));
        }
        return result;
    }
}
