#include "spectrum/distributions/piecewise_linear_spectrum_distribution.hpp"
#include "spectrum/color/cie_matching_curves.hpp"

namespace Fire {
    PiecewiseLinearSD PiecewiseLinearSD::FromInterleaved(std::span<const Real> interleaved, bool normalize) {
        DASSERT(interleaved.size() % 2 == 0);
        SizeT size = interleaved.size() / 2;
        std::vector<Real> values(size);
        std::vector<Real> lambdas(size);
        for (SizeT i = 0; i < size; i ++) {
            values[i] = interleaved[2 * i + 1];
            lambdas[i] = interleaved[2 * i + 0];
        }
        PiecewiseLinearSD result { values, lambdas };
        if (normalize) {
            Real scale = g_cie_y_integral / SpectrumDistributionInnerProduct(result, g_cie_y_matching_function);
            for (Real &value : result.values) {
                value *= scale;
            }
        }
        return result;
    }

    PiecewiseLinearSD::PiecewiseLinearSD(std::span<const Real> values, std::span<const Real> lambdas) : values(values.size()), lambdas(lambdas.size()) {
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
