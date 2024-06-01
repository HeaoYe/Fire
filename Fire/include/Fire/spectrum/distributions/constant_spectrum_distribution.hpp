#pragma once

#include <Fire/spectrum/distributions/spectrum_distribution.hpp>

namespace Fire {
    /** 常亮光谱分布 */
    class ConstantSD : public SpectrumDistribution {
    public:
        ConstantSD(Real c) : c(c) {}
        Real sample(Real nm) const override { return c; }
    private:
        Real c;
    };
}
