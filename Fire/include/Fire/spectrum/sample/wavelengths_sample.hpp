#pragma once

#include <Fire/core/math/types/scale.hpp>
#include <Fire/spectrum/basics.hpp>

namespace Fire {
    using WavelengthsPDF = Scale<Real, g_spectrum_sample_count>;

    /** 波长样本 */
    class WavelengthsSample {
    public:
        FIRE_API static WavelengthsSample GenerateUniformSample(Real u, Real lambda_min = g_lambda_min, Real lambda_max = g_lambda_max);
    public:
        Int getSampleCount () const { return g_spectrum_sample_count; }

        Real getWavelength(SizeT idx) const { return lambdas[idx]; }

        Real getPDF(SizeT idx) const { return pdf.get(idx); }

        WavelengthsPDF getWavelengthsPDF() const { return pdf; }
    private:
        Real lambdas[g_spectrum_sample_count];
        WavelengthsPDF pdf;
    };
}
