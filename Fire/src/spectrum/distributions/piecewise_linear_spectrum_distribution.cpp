#include <Fire/spectrum/distributions/piecewise_linear_spectrum_distribution.hpp>

namespace Fire {
    PiecewiseLinearSD::PiecewiseLinearSD(std::span<Real> values, std::span<Real> lambdas) : values(values.size()), lambdas(lambdas.size()) {
        DASSERT(lambdas.size() == values.size());
        for (Int i = 0; i < values.size(); i ++) {
            this->values[i] = values[i];
            this->lambdas[i] = lambdas[i];
        }
    }

    Real PiecewiseLinearSD::sample(Real lambda) const {
        if ((lambda < lambdas[0]) || (lambda > lambdas.back())) {
            return 0;
        }
        for (Int i = 0; i < lambdas.size() - 1; i ++) {
            if ((lambdas[i] <= lambda) && (lambda < lambdas[i + 1])) {
                Real t = (lambda - lambdas[i]) / (lambdas[i + 1] - lambdas[i]);
                return Lerp(values[i], values[i + 1], t);
            }
        }
        return values.back();
    }
}
