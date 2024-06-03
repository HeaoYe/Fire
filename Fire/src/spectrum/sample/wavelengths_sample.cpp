#include "spectrum/sample/wavelengths_sample.hpp"

namespace Fire {
    WavelengthsSample WavelengthsSample::GenerateUniformSample(Real u, Real lambda_min, Real lambda_max) {
        WavelengthsSample result {};
        Real interval = (lambda_max - lambda_min) / Real(g_spectrum_sample_count);
        Real start = Lerp(lambda_min, lambda_max, u);
        for (Int i = 0; i < g_spectrum_sample_count; i ++) {
            result.lambdas[i] = start;
            result.pdf.set(i, Real(1) / (lambda_max - lambda_min + 1));
            start += interval;
            if (start > lambda_max) {
                start = lambda_min + start - lambda_max;
            }
        }
        return result;
    }
}
