#pragma once

#include <Fire/core/macros.hpp>
#include <Fire/spectrum/distributions/spectrum_distribution.hpp>
#include <vector>
#include <span>

namespace Fire {
    class PiecewiseLinearSD : public SpectrumDistribution {
    public:
        FIRE_API PiecewiseLinearSD(std::span<const Real> values, std::span<const Real> lambdas);

        FIRE_API Real sample(Real lambda) const override;
    private:
        std::vector<Real> values;
        std::vector<Real> lambdas;
    };
}
