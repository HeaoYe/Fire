#pragma once

#include <Fire/core/macros.hpp>
#include <Fire/spectrum/distributions/spectrum_distribution.hpp>
#include <vector>
#include <span>

namespace Fire {
    class DenselySampledSD : public SpectrumDistribution {
    public:
        template <class T>
        DenselySampledSD(T sample_function, Int lambda_min, Int lambda_max) : DenselySampledSD(lambda_min, lambda_max) {
            for (Int i = 0; i < values.size(); i ++) {
                values[i] = sample_function(lambda_min + i);
            }
        }

        FIRE_API DenselySampledSD(std::span<Real> values, Int lambda_min, Int lambda_max);

        FIRE_API DenselySampledSD(const SpectrumDistribution &other, Int lambda_min, Int lambda_max);

        FIRE_API Real sample(Real lambda) const override;
    private:
        DenselySampledSD(Int lambda_min, Int lambda_max) : lambda_min(lambda_min), lambda_max(lambda_max), values(lambda_max - lambda_min + 1) {
            DASSERT(lambda_min <= lambda_max);
        }
    private:
        std::vector<Real> values;
        Int lambda_min { g_lambda_min }, lambda_max { g_lambda_max };
    };
}
