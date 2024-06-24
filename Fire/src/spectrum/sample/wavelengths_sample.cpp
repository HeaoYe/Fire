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

    WavelengthsSample WavelengthsSample::GenerateVisibleSample(Real u) {
        WavelengthsSample result {};
        Real up;
        for (Int i = 0; i < g_spectrum_sample_count; i ++) {
            up = u + Real(i) / Real(g_spectrum_sample_count);
            if (up > 1) {
                up -= 1;
            }
            result.lambdas[i] = 538 - 138.888889 * std::atanh(0.85691062 - 1.82750197 * up);
            if ((result.lambdas[i] < g_lambda_min) || (result.lambdas[i] > g_lambda_max)) {
                result.pdf.set(i, 0);
            } else {
                result.pdf.set(i, 0.0039398042f / Squa(std::cosh(0.0072f * (result.lambdas[i] - 538))));
            }
        }
        return result;
    }
}
