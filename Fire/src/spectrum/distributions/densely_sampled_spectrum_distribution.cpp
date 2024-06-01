#include "spectrum/distributions/densely_sampled_spectrum_distribution.hpp"

namespace Fire {
    DenselySampledSD::DenselySampledSD(std::span<Real> values, Int lambda_min, Int lambda_max) : DenselySampledSD(lambda_min, lambda_max) {
        DASSERT(values.size() == this->values.size());
        for (Int i = 0; i < values.size(); i ++) {
            this->values[i] = values[i];
        }
    }

    DenselySampledSD::DenselySampledSD(const SpectrumDistribution &other, Int lambda_min, Int lambda_max) : DenselySampledSD(lambda_min, lambda_max) {
        for (Int i = 0; i < values.size(); i ++) {
            values[i] = other.sample(lambda_min + i);
        }
    }

    Real DenselySampledSD::sample(Real lambda) const {
        Int offset = std::lround(lambda) - lambda_min;
        if ((offset < 0) || (offset >= values.size())) {
            return 0;
        }
        if (offset == (values.size() - 1)) {
            return values.back();
        }
        Real t = lambda - std::lround(lambda);
        return Lerp(values[offset], values[offset + 1], t);
    }
}
